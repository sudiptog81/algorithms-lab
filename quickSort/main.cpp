/**
 * Write a Program to implement Quick Sort and report
 * the number of comparisons made.
 * 
 * Written by Sudipto Ghosh for the University of Delhi
 */

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "avl.hpp"

#define MIN_SIZE 30
#define MAX_SIZE 1000

using namespace std;

int partition(int *&A, int p, int r, int &ctr)
{
    int x = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++)
    {
        ctr++;
        if (A[j] <= x)
            swap(A[++i], A[j]);
    }

    swap(A[i + 1], A[r]);

    return i + 1;
}

int quickSort(int A[], int p, int r)
{
    int comparisons = 0;

    if (p < r)
    {
        int q = partition(A, p, r, comparisons);
        comparisons += quickSort(A, p, q - 1);
        comparisons += quickSort(A, q + 1, r);
    }

    return comparisons;
}

int randomPivotPartition(int A[], int p, int r, int &ctr)
{
    swap(A[r], A[p + rand() % (r - p + 1)]);
    return partition(A, p, r, ctr);
}

int randomizedQuickSort(int A[], int p, int r)
{
    int comparisons = 0;

    if (p < r)
    {
        int q = randomPivotPartition(A, p, r, comparisons);
        comparisons += randomizedQuickSort(A, p, q - 1);
        comparisons += randomizedQuickSort(A, q + 1, r);
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

        cout << "+-------------------------------------------------------------+\n";
        cout << "| Input Size | Best Case | Avg Case | Worst Case | Randomized |\n";
        cout << "+-------------------------------------------------------------+\n";

        fout << "size,best,avg,worst,randomized\n";

        for (int i = 0; i < 100; i++)
        {
            // rand() % (upperBound + 1 - lowerBound) + lowerBound
            size = rand() % (MAX_SIZE + 1 - MIN_SIZE) + MIN_SIZE;

            // Input Size
            cout << "| " << setw(10) << size;
            fout << size << ",";

            // Best Case - Post Order of Balanced Tree
            AVLTree tree;
            for (int i = 0; i < size; i++)
                tree.root = tree.insert(i + 1, tree.root);
            int *postArray = tree.getPostOrderArray(size);
            comparisons = quickSort(postArray, 0, size - 1);
            cout << " | " << setw(9) << right << comparisons;
            fout << comparisons << ",";

            // Average Case
            try
            {
                ifstream fin("./random.txt");
                for (int i = 0; i < size; i++)
                    fin >> array[i];
                fin.close();
                comparisons = quickSort(array, 0, size - 1);
                cout << " | " << setw(9) << right << comparisons;
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
            comparisons = quickSort(array, 0, size - 1);
            cout << " | " << setw(10) << right << comparisons;
            fout << comparisons << ",";

            // Randomized Quick Sort
            for (int i = 0; i < size; i++)
                array[i] = i + 1;
            comparisons = randomizedQuickSort(array, 0, size - 1);
            cout << " | " << setw(9) << right << comparisons << " |\n";
            fout << comparisons << "\n";
        }

        cout << "+-------------------------------------------------------------+\n";

        fout.close();

        return 0;
    }
    catch (exception e)
    {
        cerr << e.what();
        return -1;
    }
}
