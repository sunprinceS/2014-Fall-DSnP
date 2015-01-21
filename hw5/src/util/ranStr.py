#! /usr/bin/env python
from string import ascii_lowercase as chars
import random
import sys

def strGen(strLen,times,outfile="search.in"):
    with open(outfile,"w") as fout:
        fout.write('adta -r '+str(times*5)+'\n')
        fout.write('usage'+'\n')
        #profuce random datas

        for i in range(times):
            ran = ''.join(random.choice(chars) for _ in range(strLen))
            ranStr = 'adtd -s ' + ran
            fout.write(ranStr+"\n")

        fout.write('usage'+'\n')
        fout.write('q -f')

    return 0
def main():
    print ("usage ./ranStr.py <strLen> <# of tests> [outfile]")
    ret = 0
    if len(sys.argv) == 3:
        ret = strGen(int(sys.argv[1]),int(sys.argv[2]))
        print ("search.in is successfully created,which has {} tests".format(sys.argv[2]))
    elif len(sys.argv) == 4:
        ret = strGen(int(sys.argv[1]),int(sys.argv[2]),sys.argv[3])
        print ("{} is successfully created,which has {} tests".format(sys.argv[3],sys.argv[2]))
    else:
        pass
    exit(ret)
if __name__ == "__main__":
    main()
