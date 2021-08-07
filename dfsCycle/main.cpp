/**
 * Write a program to determine the minimum spanning tree
 * of a graph using Kruskal's Algorithm
 * 
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include "stack.hpp"
#include <iostream>
#define MAX_NODES 100
using namespace std;

class Node
{
public:
  int node;
  Node *ptr;
};

class Graph
{
public:
  int V, E;
  int matrix[MAX_NODES][MAX_NODES];

  Graph(int V, int E)
  {
    this->V = V;
    this->E = E;
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++)
        if (i == j)
          matrix[i][i] = 0;
        else
          matrix[i][j] = INT8_MAX;
    this->insert();
  }

  void insert()
  {
    int src, dest, weight;
    for (int i = 0; i < E; i++)
    {
      cout << "\nEdge " << (i + 1)
           << "\n=========" << endl;
      cout << "Enter Source Node: ";
      cin >> src;
      cout << "Enter Destination Node: ";
      cin >> dest;
      matrix[src - 1][dest - 1] = 1;
      matrix[dest - 1][src - 1] = 1;
      cout << endl;
    }
  }

  void print()
  {
    cout << "\nADJACENCY MATRIX"
         << "\n================\n";
    for (int i = 0; i < V; i++)
    {
      for (int j = 0; j < V; j++)
        if (matrix[i][j] == INT8_MAX)
          cout << "∞ ";
        else
          cout << matrix[i][j] << " ";
      cout << endl;
    }
  }

  void findCycle()
  {
    Stack<int> s;

    int start = 1;
    bool explored[MAX_NODES] = {false};
    int parent[MAX_NODES] = {0};

    parent[start] = NULL;
    s.push(start);

    Node *dfsTree[MAX_NODES];
    for (int i = 0; i < V; i++)
    {
      dfsTree[i] = new Node();
      dfsTree[i]->node = i;
      dfsTree[i]->ptr = NULL;
    }

    while (!s.isEmpty())
    {
      int u = s.pop();
      if (!explored[u])
      {
        explored[u] = true;
        if (u != start)
        {
        }
      }
    }
  }
};

int main()
{
  int V, E;

  cout << "Enter Number of Vertices: ";
  cin >> V;
  cout << "Enter Number of Edges: ";
  cin >> E;

  Graph graph(V, E);

  cout << endl;
  graph.print();

  return 0;
}
