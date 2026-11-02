/*
    DAA Assignment A5: Quick Sort Analysis
    Variants:
      1. Deterministic Quick Sort: always chooses the last element as pivot.
      2. Randomized Quick Sort: chooses a uniformly random pivot.

    Both variants use Lomuto partitioning and are run on copies of the same
    input array. The program compares comparisons, swaps, and elapsed time.

    Compile:
        g++ -std=c++17 -O2 A5_Quick_Sort_Deterministic_and_Randomized.cpp -o A5_QuickSort

6
45 12 89 33 7 56
       
*/

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace chrono;

struct Statistics {
    long long comparisons = 0;
    long long swaps = 0;
};

// Lomuto partition: the last element is the pivot.
int partitionLastPivot(vector<int>& a, int low, int high, Statistics& stats) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        stats.comparisons++;

        // Values smaller than or equal to pivot are moved to its left.
        if (a[j] <= pivot) {
            i++;
            if (i != j) {
                swap(a[i], a[j]);
                stats.swaps++;
            }
        }
    }

    // Put pivot in its final sorted position.
    if (i + 1 != high) {
        swap(a[i + 1], a[high]);
        stats.swaps++;
    }

    return i + 1;
}

// Deterministic variant: always uses the last element as pivot.
void quickSortDeterministic(vector<int>& a, int low, int high,
                            Statistics& stats) {
    // Recurse on the smaller side and iterate over the larger side.
    // This tail-recursion optimization keeps stack use O(log n).
    while (low < high) {
        int pivotIndex = partitionLastPivot(a, low, high, stats);

        if (pivotIndex - low < high - pivotIndex) {
            quickSortDeterministic(a, low, pivotIndex - 1, stats);
            low = pivotIndex + 1;
        } else {
            quickSortDeterministic(a, pivotIndex + 1, high, stats);
            high = pivotIndex - 1;
        }
    }
}

// Randomized partition: choose a random pivot, move it to the end,
// then reuse the same Lomuto partition routine.
int randomizedPartition(vector<int>& a, int low, int high,
                        Statistics& stats, mt19937& generator) {
    uniform_int_distribution<int> distribution(low, high);
    int randomIndex = distribution(generator);

    if (randomIndex != high) {
        swap(a[randomIndex], a[high]);
        stats.swaps++;
    }

    return partitionLastPivot(a, low, high, stats);
}

void quickSortRandomized(vector<int>& a, int low, int high,
                         Statistics& stats, mt19937& generator) {
    while (low < high) {
        int pivotIndex =
            randomizedPartition(a, low, high, stats, generator);

        if (pivotIndex - low < high - pivotIndex) {
            quickSortRandomized(a, low, pivotIndex - 1, stats, generator);
            low = pivotIndex + 1;
        } else {
            quickSortRandomized(a, pivotIndex + 1, high, stats, generator);
            high = pivotIndex - 1;
        }
    }
}

void printArray(const vector<int>& a) {
    for (int value : a) cout << value << " ";
    cout << '\n';
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    if (n < 0) {
        cout << "Array size cannot be negative.\n";
        return 0;
    }

    vector<int> original(n);
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++) cin >> original[i];

    vector<int> deterministicArray = original;
    vector<int> randomizedArray = original;

    Statistics deterministicStats, randomizedStats;

    auto start1 = high_resolution_clock::now();
    if (n > 1) {
        quickSortDeterministic(deterministicArray, 0, n - 1,
                               deterministicStats);
    }
    auto end1 = high_resolution_clock::now();

    // Seed the generator from the current clock so pivot choices vary.
    mt19937 generator(
        (unsigned int)steady_clock::now().time_since_epoch().count());

    auto start2 = high_resolution_clock::now();
    if (n > 1) {
        quickSortRandomized(randomizedArray, 0, n - 1,
                            randomizedStats, generator);
    }
    auto end2 = high_resolution_clock::now();

    double deterministicTime =
        duration<double, milli>(end1 - start1).count();
    double randomizedTime =
        duration<double, milli>(end2 - start2).count();

    cout << "\nOriginal array:\n";
    printArray(original);

    cout << "\nDeterministic Quick Sort (last element as pivot):\n";
    printArray(deterministicArray);
    cout << "Comparisons: " << deterministicStats.comparisons << '\n';
    cout << "Swaps: " << deterministicStats.swaps << '\n';
    cout << "Time: " << fixed << setprecision(6)
         << deterministicTime << " ms\n";

    cout << "\nRandomized Quick Sort:\n";
    printArray(randomizedArray);
    cout << "Comparisons: " << randomizedStats.comparisons << '\n';
    cout << "Swaps: " << randomizedStats.swaps << '\n';
    cout << "Time: " << fixed << setprecision(6)
         << randomizedTime << " ms\n";

    cout << "\nThe two sorted arrays are "
         << (deterministicArray == randomizedArray ? "identical." : "different.")
         << '\n';

    cout << "\nComplexity analysis (both variants):\n";
    cout << "Best case:    O(n log n)\n";
    cout << "Average case: O(n log n)\n";
    cout << "Worst case:   O(n^2)\n";
    cout << "This implementation recurses on the smaller partition, "
            "so auxiliary call-stack space is O(log n).\n";
    cout << "Randomization improves expected behaviour against input order, "
            "but does not remove the O(n^2) worst case.\n";

    return 0;
}
