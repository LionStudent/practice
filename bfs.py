class Graph:
    def __init__(self):
        self.nodes = {}
    
    def addEdge(self, begin, end):
        self.nodes.setdefault(begin, []).append(end)
    
    def bfs(self, root):
        visited = [False] * len(self.nodes)
        queue = [root]
        
        while queue:
            node = queue.pop(0)
            if (visited[node] == False):
                visited[node] = True
                print(node, end=" ")
                for child in self.nodes[node]:
                    queue.append(child)
        print("")
        
    def __repr__(self):
        return str(self.nodes)

g = Graph()

g.addEdge(0,1)
g.addEdge(0,2)
g.addEdge(1,2)
g.addEdge(2,0)
g.addEdge(2,3)
g.addEdge(3,3)

g.bfs(2)
print(g)