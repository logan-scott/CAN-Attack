#ECE469/569 - Course Project
#Dr. Liu
# script developed for parsing CAN dump log file and located relevant CAN frames

#opening CAN log file and creating new file to write relevant frames to
with open('candump.txt', 'r') as f:
    with open('candumpnew.txt', 'w') as g:
        for line in f:
            #removing first 26 characters of each line to focus on ID (removing timestamps)
            g.write(line[26:])

with open('candumpnew.txt', 'r') as f:
    lines = f.readlines()

#removing duplicates
lines = list(set(lines)) 

#sorting by CAN message ID
lines.sort()

#writing back to new text file

with open('candumpnew.txt', 'w') as f:
    for line in lines:
        f.write(line)
