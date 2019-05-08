import Data
import networkx as nx
import math

def calcWeight(a,b,alpha = 2,beta = 0.5):
    ans = 1.0 * max(Data.editDistance(a,b),Data.editDistance(b,a))
    ans = ans / min(len(a),len(b))
    ans = -alpha * ans + beta
    ans = math.exp(ans)
    ans = 1.0 / (ans + 1)
    return ans

def get(file1,file2):
    a = Data.getData(file1,0)
    b = Data.getData(file2,0)
    n = len(a)
    m = len(b)
    an = 0
    # print(n,m)
    G = nx.DiGraph()
    l = []
    for i in range(0,n):
        # print(len(a[i]))
        for j in range(0,m):
            # print(len(b[j]))
            # print(i + 1,j + 1 + n,Data.editDistance(a[i],b[j]),calcWeight(a[i],b[j]))
            l.append((i + 1,j + 1 + n,{'capacity':float(Data.editDistance(a[i],b[j])),'weight':0}))
    for i in range(0,n):
        an = an + len(a[i])
        # print(n + m + 1,i + 1,len(a[i]),0)
        l.append((n + m + 1, i + 1 ,{'capacity':float(len(a[i])),'weight':0.0})) 
    for j in range(0,m):
        # print(j + 1 + n,n+ m + 2,len(b[j]),0)
        l.append((j + 1 + n, n + m + 2 ,{'capacity':float(len(b[j])),'weight':0.0}))
    G.add_edges_from(l)
    # print("???")
    # mincostFlow = nx.max_flow_min_cost(G, n + m + 1, n + m + 2)
    # mincost = nx.cost_of_flow(G, mincostFlow)
    anss = nx.maximum_flow_value(G, n + m + 1, n + m + 2)
    return anss/an
    # print("作弊几率:",anss/an)

# a = Data.getData("A",0)
# b = Data.getData("C",0)
# print("第一个程序opcode:")
# print(a)
# print("第二个程序opcode:")
# print(b)
# n = len(a)
# m = len(b)
# an = 0
# print(n,m)
# G = nx.DiGraph()
# l = []
# for i in range(0,n):
#     for j in range(0,m):
#         print(len(a[i]));
#         print(i + 1,j + 1 + n,Data.editDistance(a[i],b[j]),calcWeight(a[i],b[j]))
#         l.append((i + 1,j + 1 + n,{'capacity':float(Data.editDistance(a[i],b[j])),'weight':int(-calcWeight(a[i],b[j]) * 1000000000000)}))
# for i in range(0,n):
#     an = an + len(a[i])
#     print(n + m + 1,i + 1,len(a[i]),0)
#     l.append((n + m + 1, i + 1 ,{'capacity':float(len(a[i])),'weight':0.0})) 
# for j in range(0,m):
#     print(j + 1 + n,n+ m + 2,len(b[j]),0)
#     l.append((j + 1 + n, n + m + 2 ,{'capacity':float(len(b[j])),'weight':0.0}))
# print(l)
# G.add_edges_from(l)
# mincostFlow = nx.max_flow_min_cost(G, n + m + 1, n + m + 2)
# mincost = nx.cost_of_flow(G, mincostFlow)
# print(mincost/1000000000000)
# # anss = -mincost/1000000000000
# # anpp = nx.maximum_flow(G, n + m + 1, n + m + 2)
# # print(anpp)
# anss = nx.maximum_flow_value(G, n + m + 1, n + m + 2)
# # print(anss)
# # print(an)
# print("作弊几率:",anss/an)