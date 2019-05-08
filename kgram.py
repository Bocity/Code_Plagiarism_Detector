import Data

def generateKgram(fileLine,K):
    kgram = [] 
    for i in range(len(fileLine)):
        if (i+K > len(fileLine)):
            break
        shingle = fileLine[i:i+K]
        kgram.append(shingle)
    return kgram

def generateHash(Base,kgram,K):
    HashList=[]
    hash=0
    firstShingle = kgram[0]
    for i in range(K):
        hash += ord(firstShingle[i])*(Base**(K-1-i))
    HashList.append(hash)
    for i in range(1,len(kgram)):
        preshingle = kgram[i-1]
        shingle = kgram[i]
        hash = hash * Base - ord(preshingle[0])*Base**K + ord(shingle[K-1])
        HashList.append(hash)
    return HashList 

def getFingerPrint(ll):
    hashValues = generateHash(233,generateKgram(ll,6),6)
    WINSIZE=24
    minHash=0
    minPos=0
    fingerPrint={}
    for i in range(len(hashValues)):
        if ((i+WINSIZE)>len(hashValues)):
            break
        tmplist = hashValues[i:WINSIZE+i]
        minHash= tmplist[WINSIZE-1]
        minPos =WINSIZE+i-1
        for j in range(WINSIZE):
            if tmplist[j]<minHash:
                minHash = tmplist[j]
                minPos = i+j
        if not minPos in fingerPrint:
            fingerPrint[minPos]=minHash
    # print (fingerPrint)
    return fingerPrint

def getOpCode(a):
    ll = ""
    for i in a:
        for j in i:
            ll = ll + j
    # print(ll)
    return ll
def get(file1,file2):
    a = Data.getData(file1,0)
    b = Data.getData(file2,0)
    # print("第一个程序opcode:")
    # print(a)
    # print("第二个程序opcode:")
    # print(b)
    a = getOpCode(a)
    b = getOpCode(b)
    a = getFingerPrint(a)
    b = getFingerPrint(b)
    # print(a)
    # print(b)
    flag = 0
    for i in a:
        for j in b:
            if (a[i] == b[j]):
                flag = flag + 1
                break
    if (flag != 0):
        ans = flag * 1.0 / min(len(a),len(b))
    else:
        ans = 1
    # ans = ans * 100
    return ans
    # print("两个程序相似特征值个数：{1},相似度为：{0}%".format(ans,flag))