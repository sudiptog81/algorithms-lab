from collections import deque


class Node:
    def __init__(self, node, parent=None):
        self.node = node
        self.parent = parent


class Edge:
    def __init__(self, src, dest, weight):
        self.src = src
        self.dest = dest
        self.weight = weight

    def __str__(self):
        return f"({self.src + 1}, {self.dest + 1})"


def sortEdges(E):
    for x in range(0, len(E)):
        for y in range(x, len(E) - 1):
            if E[x].weight > E[y].weight:
                E[x], E[y] = \
                    E[y], E[x]
    return E


class Graph:
    def __init__(self, n):
        self.n = n
        self.G = []
        self.E = []
        self.V = range(self.n)

        for i in range(self.n):
            self.G.append([-1] * self.n)
            self.G[i][i] = 0

    def insert(self, src, dest, weight):
        self.G[src - 1][dest - 1] = \
            self.G[dest - 1][src - 1] = weight

        self.E.append(
            Edge(src, dest, weight)
        )
        self.E = sortEdges(self.E)

    def adjacent(self, src):
        A = []
        for i in range(self.n):
            if self.G[src - 1][i] != -1 and \
                    self.G[src - 1][i] != 0:
                A.append(i + 1)
        return A

    def weight(self, src, dest):
        return self.G[src - 1][dest - 1]

    def display(self):
        s = '\nAdjacency Matrix' + \
            '\n================\n'
        for x in range(self.n):
            for y in range(self.n):
                if (self.G[x][y] == -1):
                    s += f'∞  '
                else:
                    s += f'{self.G[x][y]}  '
            s += '\n'
        print(s)


def findCycleDFS(G):
    isCyclic = False

    start = 1

    stack = deque()

    explored = []
    for i in range(G.n + 1):
        explored.append(False)

    parent = []
    for i in range(G.n + 1):
        parent.append(0)

    parent[start] = None
    stack.append(start)

    tree = []
    for i in range(G.n + 1):
        tree.append(Node(i, 0))

    nodes = []

    while len(stack) != 0:
        src = stack.pop()

        if explored[src] == False:
            explored[src] = True

            if src != start:
                nodes.append(
                    Node(src, parent[src])
                )
                tree[src].parent = tree[parent[src]]

            adjacent = G.adjacent(src)

            for vertex in adjacent:
                if explored[vertex] == False:
                    stack.append(vertex)
                    parent[vertex] = src
                    tree[vertex].parent = tree[src]
                elif (vertex != src) and \
                        (vertex != parent[src]):
                    isCyclic = True
                    s = ''
                    p = tree[src]
                    while p != tree[vertex]:
                        s += f'{p.node} => '
                        p = p.parent
                    s += f'{vertex} => {src}'

    if (isCyclic):
        print('Cycle was Detected:', s)
        print('DFS Traversal:', end=' ')
        for x in nodes:
            print(f'({x.node}, {x.parent})', end='; ')
        print()
    else:
        print('No Cycle was Detected')


if __name__ == '__main__':
    V = int(input('Enter number of nodes: '))
    E = int(input('Enter number of edges: '))
    print()

    G = Graph(V)
    for i in range(E):
        print(f'Edge {i + 1}')
        print('============')
        src = int(input('Enter source node: '))
        dest = int(input('Enter dest node: '))
        G.insert(src, dest, 1)
        print()
    G.display()

    findCycleDFS(G)
