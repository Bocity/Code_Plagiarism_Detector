import os
def main():
    os.system("g++-7 -O2 -c A.cpp") 
    os.system("objdump -t A.o > 2.txt")
    os.system("objdump --no-show-raw-insn -d A.o > 1.txt")
    files=open("2.txt")
    for i in files.readlines():
        if "g     F __TEXT,__text" in i:
            print(i)
    files.close()
if __name__ == '__main__':
    main()