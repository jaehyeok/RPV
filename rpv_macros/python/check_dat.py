import sys

a=sys.argv[1] 
b=sys.argv[2]
#a = str(input())
#b = str(input())

name = "%s" %b
filepath = "%s" %a
f = open(filepath, 'r')

count = 0
list1 = []
list_bin = []

while True:
    line = f.readline()
    
    if "------------------------------------" in line:
        count = count + 1
    
    if count >= 3:
        worthy_line = line

        if not ((worthy_line == " ") or ('--' in worthy_line)):
            split = worthy_line.split()
            list1.append(split)

    if not line :
         break



list_bin = list1[0]
list_process = list1[1]


for i in range(4, len(list1)-1, 1):
    del list1[i][1]

for i in range(0, len(list1)-1, 1):
    if name in list1[i]:
        print("")
        print("input : %s\n" %name)
        print("%20s%20s%20s%20s%20s%20s" %("bin_name", "signal_M1900", "qcd", "ttbar", "wjets", "other"))
        
        for j in range(1, len(list1[i]), 1):
            if (j%5 == 1):
                print("%20s" %list_bin[j], end = "")
            if (j%5 == 0):
                print("%20s" %list1[i][j])
            else:
                print("%20s" %list1[i][j], end = "")
                




f.close()
