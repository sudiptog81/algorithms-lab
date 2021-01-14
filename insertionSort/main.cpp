/**
 * Write a Program to implement Insertion Sort and report
 * the number of comparisons made.
 * 
 * Insertion_Sort (A)
 * ==================
 * i ← 1
 * while i < length(A)
 *   j ← i
 *   while j > 0 and A[j-1] > A[j]
 *     swap A[j] and A[j-1]
 *     j ← j - 1
 *   end while
 *   i ← i + 1
 * end while
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

int insertionSort(int *, int);

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
            comparisons = insertionSort(array, size);
            cout << " | " << setw(9) << right << comparisons;
            fout << comparisons << ",";

            // Average Case
            try
            {
                ifstream fin("./random.txt");
                for (int i = 0; i < size; i++)
                    fin >> array[i];
                fin.close();
                comparisons = insertionSort(array, size);
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
            comparisons = insertionSort(array, size);
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

int insertionSort(int *array, int size)
{
    int i, j, k, key, count = 0;

    for (i = 1; i < size; i++)
    {
        key = array[i];

        for (j = i - 1; j >= 0; j--)
        {
            count++;

            if (array[j] > key)
            {
                array[j + 1] = array[j];
            }
            else
            {
                break;
            }
        }

        array[j + 1] = key;
    }

    return count;
}
