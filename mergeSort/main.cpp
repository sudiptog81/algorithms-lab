/**
 * Write a Program to implement Merge Sort and report
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

int mergeSort(int *, int, int);
int merge(int *, int, int, int);

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
            comparisons = mergeSort(array, 0, size - 1);
            cout << " | " << setw(9) << right << comparisons;
            fout << comparisons << ",";

            // Average Case
            try
            {
                ifstream fin("./random.txt");
                for (int i = 0; i < size; i++)
                    fin >> array[i];
                fin.close();
                comparisons = mergeSort(array, 0, size - 1);
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
            comparisons = mergeSort(array, 0, size - 1);
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

int mergeSort(int *array, int beg, int end)
{
    int comparisons = 0;
    if (beg < end)
    {
        int mid = (beg + end) / 2;
        comparisons += mergeSort(array, beg, mid);
        comparisons += mergeSort(array, mid + 1, end);
        comparisons += merge(array, beg, mid, end);
    }
    return comparisons;
}

int merge(int *array, int beg, int mid, int end)
{
    int comparisons = 0;

    int n1 = mid - beg + 1;
    int n2 = end - mid;
    int L[n1 + 1], R[n2 + 1];

    for (int i = 0; i < n1; i++)
        L[i] = array[beg + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[mid + 1 + j];

    L[n1] = R[n2] = INT16_MAX;

    for (int i = 0, j = 0, k = beg; k <= end; k++)
    {
        if (L[i] != INT16_MAX &&
            R[j] != INT16_MAX)
            comparisons++;

        if (L[i] <= R[j])
            array[k] = L[i++];
        else
            array[k] = R[j++];
    }

    return comparisons;
}
