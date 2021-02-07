/**
 * Write a Program to implement Heap Sort and report
 * the number of comparisons made.
 * 
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

#define MIN_SIZE 30
#define MAX_SIZE 1000

using namespace std;

int comparisons;
int heap[MAX_SIZE];

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

int maxHeapify(int *&A, int n, int i)
{
    int temp;
    int largest;
    int comparisons = 0;

    int l = left(i);
    int r = right(i);

    if (l <= n && A[l] > A[i])
    {
        largest = l;
    }
    else
    {
        largest = i;
    }

    if (r <= n && A[r] > A[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        comparisons++;

        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;

        comparisons += maxHeapify(A, n, largest);
    }

    return comparisons;
}

int buildHeap(int A[], int n)
{
    int comparisons = 0;

    for (int i = n / 2; i >= 0; i--)
        comparisons += maxHeapify(A, n, i);

    return comparisons;
}

int heapSort(int A[], int n)
{
    int comparisons = 0;

    comparisons += buildHeap(A, n);

    for (int i = n - 1; i > 0; i--)
    {
        swap(A[0], A[i]);
        comparisons += maxHeapify(A, i, 0);
    }

    return comparisons;
}

int main()
{
    try
    {
        srand(time(0));

        int array[MAX_SIZE];
        int size, comparisons;

        ofstream fout("./results.csv");

        cout << "+------------------------------------------------+\n";
        cout << "| Input Size | Best Case | Avg Case | Worst Case |\n";
        cout << "+------------------------------------------------+\n";

        fout << "size,best,avg,worst\n";

        for (int i = 0; i < 100; i++)
        {
            // rand() % (upperBound + 1 - lowerBound) + lowerBound
            size = rand() % (MAX_SIZE + 1 - MIN_SIZE) + MIN_SIZE;

            // Input Size
            cout << "| " << setw(10) << size;
            fout << size << ",";

            // Best Case
            for (int i = 0; i < size; i++)
                array[i] = i + 1;
            comparisons = heapSort(array, size);
            cout << " | " << setw(9) << right << comparisons;
            fout << comparisons << ",";

            // Average Case
            try
            {
                ifstream fin("./random.txt");
                for (int i = 0; i < size; i++)
                    fin >> array[i];
                fin.close();
                comparisons = heapSort(array, size);
                cout << " | " << setw(8) << right << comparisons;
                fout << comparisons << ",";
            }
            catch (exception e)
            {
                cerr << e.what();
                return -1;
            }

            // Worst Case
            for (int i = 0; i < size; i++)
                array[i] = size - i;
            comparisons = heapSort(array, size);
            cout << " | " << setw(10) << right << comparisons << " |\n";
            fout << comparisons << "\n";
        }

        cout << "+------------------------------------------------+\n\n";

        fout.close();

        return 0;
    }
    catch (exception e)
    {
        cerr << e.what();
        return -1;
    }
}
