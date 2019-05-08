import queue

maxn = 20000 + 50
INF = 1<<29

class E:
    def __init__(self, fr, to, cap, flow):
        self.fr = fr
        self.to = to
        self.cap = cap
        self.flow = flow

n,s,t = 0,0,0        
cnt = 0

e = []
G = [[]]*maxn
cur = []
d = [0]*maxn

def add_arc(fr, to, cap):
    e.append(E(fr,to,cap,0))
    e.append(E(to,fr,0,0))
    global cnt
    cnt = cnt + 2
    G[fr].append(cnt-2)
    G[to].append(cnt-1)

def bfs():
    Q = queue.Queue()
    vis = [False]*maxn
    vis[s] = True
    d[s] = 0
    Q.put(s)
    while not Q.empty():
        x = Q.get()
        for i in G[x]:
            ed = e[i]
            if (not vis[ed.to]) and ed.cap > ed.flow :
                vis[ed.to] = True
                d[ed.to] = d[x] + 1
                Q.put(ed.to)
    return vis[t]

def dfs(x, a):
    if (x == t or a == 0):
        return a
    flow = 0
    for i in G[x]:
        ed = e[i]
        if d[ed.to] == d[x] + 1:
            f = dfs(ed.to, min(a, ed.cap - ed.flow) )
            if f > 0:
                ed.flow = ed.flow + f
                e[i^1].flow = e[i^1].flow - f
                flow = flow + f
                a -= f
                if (a == 0):
                    break
    return flow

def maxflow():
    ans = 0
    while(bfs() == True):
        cur = [0]*n
        ans = ans + dfs(s, INF)
    return ans

if __name__ == "__main__":
    n,s,t = 2,1,2
    add_arc(1,2,10)
    print(maxflow())