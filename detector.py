import kgram
import maxweightflow
import attrib
import texts

def graph(file1,file2):
    a = maxweightflow.get(file1,file2)
    return a

def tree(file1,file2):
    # a = execfile("./tree.out {0} {1}".format{file1,file2})
    return 0

def token(file1,file2):
    a = kgram.get(file1,file2)
    return a

def text(file1,file2):
    return texts.get(file1,file2)

def attribute(file1,file2):
    a = attrib.get(file1,file2)
    return a