/**
 * Write a Program to implement Merge Sort and report
 * the number of comparisons made.
 * 
 * Merge_Sort (A)
 * ==============
 * if length(A) ≤ 1 then
 *   return A
 * left := empty list
 * right := empty list
 * for each x with index i in A do
 *   if i < length(A) / 2 then
 *     append x to left
 *   else
 *     append x to right
 * left := Merge_Sort(left)
 * right := Merge_Sort(right)
 * return Merge(left, right)
 * 
 * Merge (left, right)
 * ===================
 * result := empty list
 * while left is not empty and right is not empty do
 *   if first(left) ≤ first(right) then
 *     append first(left) to result
 *     left := rest(left)
 *   else
 *     append first(right) to result
 *     right := rest(right)
 * while left is not empty do
 *   append first(left) to result
 *   left := rest(left)
 * while right is not empty do
 *   append first(right) to result
 *   right := rest(right)
 * return result
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

int comparisons = 0;

int mergeSort(int *, int, int);
int merge(int *, int, int, int);

int main()
{
    try
    {
        srand(time(0));

        int size;
        int array[MAX_SIZE];

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

int mergeSort(int *array, int left, int right)
{
    if (left >= right)
        return 0;
    int comparisons = 0;
    int mid = (left + right) / 2;
    comparisons += mergeSort(array, left, mid);
    comparisons += mergeSort(array, mid + 1, right);
    comparisons += merge(array, left, mid, right);
    return comparisons;
}

int merge(int *array, int left, int mid, int right)
{
    int comparisons = 0;
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int leftArr[leftSize], rightArr[rightSize];

    for (int i = 0; i < leftSize; i++)
        leftArr[i] = array[left + i];
    for (int j = 0; j < rightSize; j++)
        rightArr[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize)
    {
        if (leftArr[i] <= rightArr[j])
            array[k] = leftArr[i++];
        else
            array[k] = rightArr[j++];
        k++;
        comparisons++;
    }

    while (i < leftSize)
        array[k++] = leftArr[i++];

    while (j < rightSize)
        array[k++] = rightArr[j++];

    return comparisons;
}
