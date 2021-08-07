/**
 * Write a program to determine the minimum spanning tree
 * of a graph using Kruskal's Algorithm
 * 
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <iostream>
using namespace std;

class Edge
{
public:
  int src;
  int dest;
  int weight;
};

class Subset
{
public:
  int p;
  int rank;
};

int compEdges(const void *a, const void *b)
{
  return ((Edge *)(a))->weight > ((Edge *)(b))->weight;
}

class Graph
{
public:
  int V, E;
  Edge *edges;
  Subset *subsets;

  Graph(int V, int E)
  {
    this->V = V;
    this->E = E;
    this->edges = new Edge[E];

    for (int i = 0; i < E; i++)
    {
      int src, dest, weight;
      cout << "Edge " << (i + 1)
           << "\n=============\n";
      cout << "Source Node: ";
      cin >> src;
      cout << "Destination Node: ";
      cin >> dest;
      cout << "Edge Weight: ";
      cin >> weight;
      cout << endl;

      if (src < 1 || src > V || dest < 1 || dest > V)
      {
        cout << "Invalid Node" << endl;
        exit(-1);
      }

      this->edges[i].src = src - 1;
      this->edges[i].dest = dest - 1;
      this->edges[i].weight = weight;
    }
  }

  void makeSet()
  {
    this->subsets = new Subset[(this->V * sizeof(Subset))];

    for (int v = 0; v < this->V; ++v)
    {
      this->subsets[v].p = v;
      this->subsets[v].rank = 0;
    }
  }

  int findSet(int i)
  {
    if (this->subsets[i].p != i)
    {
      this->subsets[i].p = this->findSet(this->subsets[i].p);
    }

    return this->subsets[i].p;
  }

  void link(int x, int y)
  {
    if (this->subsets[x].rank > this->subsets[y].rank)
    {
      this->subsets[y].p = x;
    }
    else
    {
      this->subsets[x].p = y;

      if (this->subsets[x].rank == this->subsets[y].rank)
      {
        this->subsets[y].rank++;
      }
    }
  }

  void Union(int x, int y)
  {
    this->link(this->findSet(x), this->findSet(y));
  }

  void KruskalMST()
  {
    int e = 0, i = 0;
    Edge next, result[this->V];

    qsort(this->edges, this->E, sizeof(Edge), compEdges);

    this->makeSet();

    while (e < this->V - 1 && i < this->E)
    {
      next = this->edges[i++];

      int x = this->findSet(next.src);
      int y = this->findSet(next.dest);

      if (x != y)
      {
        result[e++] = next;
        this->Union(x, y);
      }
    }

    qsort(result, this->V - 1, sizeof(Edge), compEdges);

    cout << "Edges in Minimum Spanning Tree:"
         << "\n===============================\n";

    for (i = 0; i < e; ++i)
    {
      cout << "Edge (" << (result[i].src + 1)
           << ", " << (result[i].dest + 1)
           << ") ==> " << result[i].weight
           << endl;
    }

    return;
  }
};

int main()
{
  int V, E;

  cout << "Enter Number of Vertices: ";
  cin >> V;
  cout << "Enter Number of Edges: ";
  cin >> E;
  cout << endl;

  Graph graph(V, E);

  graph.KruskalMST();

  return 0;
}
