
#include <iostream>
using namespace std;

long long fibonacciRecursive(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    return fibonacciRecursive(n - 1) +
           fibonacciRecursive(n - 2);
}

long long fibonacciIterative(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    long long previous = 0;
    long long current = 1;

    for (int i = 2; i <= n; i++)
    {
        long long next = previous + current;
        previous = current;
        current = next;
    }

    return current;
}

int main()
{
    int n;

    cout << "Enter n (0 to 92): ";
    cin >> n;

    if (n < 0 || n > 92)
    {
        cout << "Invalid input. Enter a value from 0 to 92.\n";
        return 0;
    }

    cout << "\nNon-recursive (iterative) result: "
         << fibonacciIterative(n) << '\n';

    if (n <= 35)
    {
        cout << "Recursive result: "
             << fibonacciRecursive(n) << '\n';
    }
    else
    {
        cout << "Recursive result: skipped for n > 35 because naive "
                "recursion takes exponential time.\n";
    }

    cout << "\nComplexity analysis:\n";

    cout << "Naive recursive: Time O(2^n) (more tightly, O(phi^n)); "
            "auxiliary space O(n) due to the call stack.\n";

    cout << "Iterative:       Time O(n); auxiliary space O(1).\n";

    return 0;
}




// Enter n (0 to 92): 10

// Non-recursive (iterative) result: 55
// Recursive result: 55

// Complexity analysis:
// Naive recursive: Time O(2^n) (more tightly, O(phi^n)); auxiliary space O(n) due to the call stack.
// Iterative:       Time O(n); auxiliary space O(1).