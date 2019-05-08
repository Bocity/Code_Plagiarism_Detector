import os
import Dinic
import numpy as np

def calc(a,b):
    lena=len(a)
    lenb=len(b)
    dp = np.zeros((lena + 1, lenb + 1), dtype=np.int)
    for i in range(1,lena + 1):
        for j in range(1,lenb + 1):
            if (a[i - 1] == b[j - 1]):
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
    return dp[lena][lenb]

def editDistance(fi,fj):
    ans = 0
    w = int(len(fi) * 3.0 / 2);
    sz = len(fi)
    sz2 = len(fj)
    for i in range(0,sz):
        fjj = fj[i:min(i + w + 1,sz2)]
        ans = max(ans,calc(fi,fjj))
    return ans


def getData(filename,level=0):
    os.system("g++-8 -O0 -c {0}.cpp -o {0}.o".format(filename)) 
    os.system("objdump -t {0}.o > 2.txt".format(filename))
    os.system("objdump --no-show-raw-insn -d {0}.o > 1.txt".format(filename))
    files=open("2.txt")
    fuctionName=[]
    fuctionContent={}
    ans=[]
    for i in files.readlines():
        if "g     F __TEXT,__text" in i:
            # print(i)
            s = i.split()[-1:]
            # print(s[0])
            fuctionName.append(s[0])
            fuctionContent[s[0]]=[]
    files.close()
    files=open("1.txt")
    flag = 0
    fname="hhh"
    for i in files.readlines():
        if flag == 1 and (i.count('\n')==len(i) or "Disassembly of section" in i):
            flag = 0
            continue
        if flag != 1:
            for j in fuctionName:
                if (j in i):
                    flag = 1
                    fname = j
                    break
            if flag == 1:
                continue
        if flag == 1:
            # print(i)
            fuctionContent[fname].append(i)
    x = []
    pos = 0
    for i in fuctionName:
        # print(i)
        ans.append([])
        for j in fuctionContent[i]:
            if i in j:
                x = j.split()[1:-1]
            else:
                x = j.split()[1:]
            s=""
            # print(x)
            for k in x:
                # if(k[-1] == 'q' or (k[-1] == 'l' and len(k)!=3 )):
                    # k = k[:-1]
                s = s + k
                if (level == 0):
                    break
            ans[pos].append(s)
        pos = pos + 1
    return ans


def main():
    a = getData("A")
    print(a)
    b = getData("B")
    print(b)
    

        
if __name__ == '__main__':
    main()
