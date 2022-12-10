with open('candump.txt', 'r') as f:
    with open('candumpnew.txt', 'w') as g:
        for line in f:
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
