/**
 * Write a program to determine the minimum spanning tree
 * of a graph using Prim's Algorithm
 * 
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <iostream>
using namespace std;

class Heap
{
public:
  int *heap;
  int heapSize;

  Heap(int *&A, int n)
  {
    heap = A;
    heapSize = n;
  }

  int parent(int i)
  {
    return (i - 1) / 2;
  }

  int left(int i)
  {
    return 2 * i + 1;
  }

  int right(int i)
  {
    return 2 * i + 2;
  }

  void minHeapify(int *&A, int n, int i)
  {
    int temp;
    int least;
    int l = left(i);
    int r = right(i);
    if (l < n && A[l] <= A[i])
    {
      least = l;
    }
    else
    {
      least = i;
    }
    if (r < n && A[r] <= A[least])
    {
      least = r;
    }
    if (least != i)
    {
      temp = A[i];
      A[i] = A[least];
      A[least] = temp;
      minHeapify(A, n, least);
    }
  }

  void buildMinHeap()
  {
    for (int i = heapSize / 2; i >= 0; i--)
      minHeapify(heap, heapSize, i);
  }
};

class MinPriorityQueue
{
public:
  Heap *heap;

  MinPriorityQueue(int A[], int n)
  {
    heap = new Heap(A, n);
    heap->buildMinHeap();
  }

  ~MinPriorityQueue()
  {
    delete heap;
  }

  int size()
  {
    return heap->heapSize;
  }

  void display()
  {
    if (heap->heapSize == 0)
    {
      cerr << "ERROR: Heap Empty";
      return;
    }
    for (int i = 0; i < heap->heapSize; i++)
      cout << heap->heap[i] << " ";
  }

  void heapDecreaseKey(int i, int key)
  {
    int temp;
    if (key >= heap->heap[i])
    {
      cerr << "ERROR: New Key is larger than Existing Key";
      return;
    }
    heap->heap[i] = key;
    while (i > 0 && heap->heap[heap->parent(i)] >= heap->heap[i])
    {
      temp = heap->heap[heap->parent(i)];
      heap->heap[heap->parent(i)] = heap->heap[i];
      heap->heap[i] = temp;
      i = heap->parent(i);
    }
  }

  void minHeapInsert(int key)
  {
    heap->heapSize++;
    heap->heap[heap->heapSize - 1] = INT8_MAX;
    heapDecreaseKey(heap->heapSize - 1, key);
  }

  int heapMinimum()
  {
    if (heap->heapSize == 0)
    {
      cerr << "ERROR: Heap Empty";
      return -1;
    }
    return heap->heap[0];
  }

  int heapExtractMin()
  {
    if (heap->heapSize < 0)
    {
      cerr << "ERROR: Heap Underflow";
      return -1;
    }
    else if (heap->heapSize == 0)
    {
      cerr << "ERROR: Heap Empty";
      return -1;
    }
    int min = heap->heap[0];
    heap->heap[0] = heap->heap[heap->heapSize];
    heap->minHeapify(heap->heap, --heap->heapSize, 0);
    return min;
  }
};

class Graph
{
  int V;

  list<pair<int, int>> *adj;

public:
  Graph(int V)
  {
    this->V = V;
    adj = new list<iPair>[V];
  }

  // function to add an edge to graph
  void addEdge(int u, int v, int w);

  // Print MST using Prim's algorithm
  void primMST();
};

// Allocates memory for adjacency list
Graph::Graph(int V)

    void Graph::addEdge(int u, int v, int w)
{
  adj[u].push_back(make_pair(v, w));
  adj[v].push_back(make_pair(u, w));
}

void Graph::primMST()
{
  MinPriorityQueue pq();

  int src = 0; // Taking vertex 0 as source

  // Create a vector for keys and initialize all
  // keys as infinite (INF)
  vector<int> key(V, INF);

  // To store parent array which in turn store MST
  vector<int> parent(V, -1);

  // To keep track of vertices included in MST
  vector<bool> inMST(V, false);

  // Insert source itself in priority queue and initialize
  // its key as 0.
  pq.push(make_pair(0, src));
  key[src] = 0;

  /* Looping till priority queue becomes empty */
  while (!pq.empty())
  {
    // The first vertex in pair is the minimum key
    // vertex, extract it from priority queue.
    // vertex label is stored in second of pair (it
    // has to be done this way to keep the vertices
    // sorted key (key must be first item
    // in pair)
    int u = pq.top().second;
    pq.pop();

    inMST[u] = true; // Include vertex in MST

    // 'i' is used to get all adjacent vertices of a vertex
    list<pair<int, int>>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
      // Get vertex label and weight of current adjacent
      // of u.
      int v = (*i).first;
      int weight = (*i).second;

      //  If v is not in MST and weight of (u,v) is smaller
      // than current key of v
      if (inMST[v] == false && key[v] > weight)
      {
        // Updating key of v
        key[v] = weight;
        pq.push(make_pair(key[v], v));
        parent[v] = u;
      }
    }
  }

  // Print edges of MST using parent array
  for (int i = 1; i < V; ++i)
    printf("%d - %d\n", parent[i], i);
}

int main()
{

  return 0;
}
