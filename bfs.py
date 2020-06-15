class Graph:
    nodes = {}
    
    def addEdge(self, a, b):
        self.nodes.setdefault(a, []).append(b)
        self.nodes.setdefault(b, []) # add other node, but no edge in the reverse direction

    def bfs(self, root):
        visited = [False] * len(self.nodes)
        queue = [root]
        
        while len(queue):
            node = queue.pop(0)
            if visited[node] == False:
                visited[node] = True
                print(node, end=" ")
                for adjNode in self.nodes[node]:
                    queue.append(adjNode)
        print("")

test = 2
if test == 1:
    g = Graph()
    g.addEdge(0, 1)
    g.addEdge(0, 2)
    g.addEdge(2, 3)
    
    g.bfs(0)
else: 
    g = Graph()
    g.addEdge(0, 1) 
    g.addEdge(0, 2) 
    g.addEdge(1, 2) 
    g.addEdge(2, 0) 
    g.addEdge(2, 3) 
    g.addEdge(3, 3) 
    
    g.bfs(2)


print(g.nodes)
