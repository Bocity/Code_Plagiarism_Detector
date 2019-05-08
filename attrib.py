def idf(name):
    s = ""
    with open(name) as f:
        s = f.read()
    
    vec = []

    # 1 len
    # vec.append(len(s))
    
    # 2 count
    count_word = ["while","for","if","scanf","cin","cout","printf","+","-","*","/","%","^","<<",">>","&","|"]
    for i in count_word:
        vec.append(s.count(i))
    
    return vec

import numpy as np
import math
def get(name1, name2):
    a1 = np.array(idf(name1))
    a2 = np.array(idf(name2))
    lee = len(a1)
    c = 0;
    for i in range(lee):
        if (a1[i] == a2[i]):
            c = c + 1
    # print(a1, a2)
    return c / lee

# if __name__ == "__main__":
#     name1, name2 = input().split()
#     print( main(name1, name2) 
