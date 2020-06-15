
class Graph:
    def __init__(self):
        self.nodes = {}
    
    def __repr__(self):
        return str(self.nodes)
        
    def addEdge(self, src, tgt):
        self.nodes.setdefault(src,[]).append(tgt)
        self.nodes.setdefault(tgt,[]) # add other node but not reverse edge
        
    def bfs(self, root):
        queue = [root]
        visited = [False] * len(self.nodes)
        
        while queue:
            node = queue.pop(0)
            if visited[node] == False:
                visited[node] = True
                print(node, end=" ")
                for child in self.nodes[node]:
                    queue.append(child)
        print("")

g = Graph()

g.addEdge(0,1)
g.addEdge(0,2)
g.addEdge(1,2)
g.addEdge(2,0)
g.addEdge(2,3)
g.addEdge(3,3)
g.addEdge(3,4)

print(g)
g.bfs(2)