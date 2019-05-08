import Data

def getText(file1):
    files=open(file1)
    s = ""
    for i in files.readlines():
        s = s + i
    return s

def get(file1,file2):
    a = getText(file1)
    b = getText(file2)
    return Data.calc(a,b)/min(len(a),len(b))
    
