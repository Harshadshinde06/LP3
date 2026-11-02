#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// ============================================================
// MEMOIZATION FUNCTION
// ============================================================

int knapsack(
    int i,
    int capacity,
    vector<int>& weight,
    vector<int>& profit,
    vector<vector<int>>& dp,
    int n
)
{
    // Base case
    if (i == n || capacity == 0)
    {
        return 0;
    }


    // If already calculated
    if (dp[i][capacity] != -1)
    {
        return dp[i][capacity];
    }


    // If current item cannot fit
    if (weight[i] > capacity)
    {
        dp[i][capacity] =
            knapsack(
                i + 1,
                capacity,
                weight,
                profit,
                dp,
                n
            );
    }


    // If current item can fit
    else
    {
        // Include current item
        int take =
            profit[i] +
            knapsack(
                i + 1,
                capacity - weight[i],
                weight,
                profit,
                dp,
                n
            );


        // Exclude current item
        int notTake =
            knapsack(
                i + 1,
                capacity,
                weight,
                profit,
                dp,
                n
            );


        // Store best answer
        dp[i][capacity] =
            max(take, notTake);
    }


    return dp[i][capacity];
}


// ============================================================
// ITERATIVE FUNCTION
// ============================================================

int knapsackIterative(
    int n,
    int capacity,
    vector<int>& weight,
    vector<int>& profit
)
{
    // DP table
    vector<vector<int>> dp(
        n + 1,
        vector<int>(capacity + 1, 0)
    );


    // ========================================================
    // ITERATIVE DP
    // ========================================================

    for (int i = n - 1; i >= 0; i--)
    {
        for (int c = 0; c <= capacity; c++)
        {
            // If current item cannot fit
            if (weight[i] > c)
            {
                dp[i][c] =
                    dp[i + 1][c];
            }


            // If current item can fit
            else
            {
                // Include current item
                int take =
                    profit[i] +
                    dp[i + 1][c - weight[i]];


                // Exclude current item
                int notTake =
                    dp[i + 1][c];


                // Store best answer
                dp[i][c] =
                    max(take, notTake);
            }
        }
    }


    return dp[0][capacity];
}


// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    int n, capacity;

    cout << "=============================================\n";
    cout << "       0/1 KNAPSACK - DP APPROACHES\n";
    cout << "=============================================\n";


    // ========================================================
    // INPUT
    // ========================================================

    cout << "\nEnter number of items: ";
    cin >> n;

    vector<int> weight(n);
    vector<int> profit(n);

    cout << "\nEnter weight and profit of each item:\n";

    for (int i = 0; i < n; i++)
    {
        cout << "\nItem " << i + 1 << ":\n";

        cout << "Weight: ";
        cin >> weight[i];

        cout << "Profit: ";
        cin >> profit[i];
    }


    cout << "\nEnter capacity of knapsack: ";
    cin >> capacity;


    // ========================================================
    // MEMOIZATION TABLE
    // -1 means not calculated yet
    // ========================================================

    vector<vector<int>> dp(
        n,
        vector<int>(capacity + 1, -1)
    );


    // ========================================================
    // MEMOIZATION APPROACH
    // ========================================================

    int memoizationAnswer =
        knapsack(
            0,
            capacity,
            weight,
            profit,
            dp,
            n
        );


    // ========================================================
    // ITERATIVE APPROACH
    // ========================================================

    int iterativeAnswer =
        knapsackIterative(
            n,
            capacity,
            weight,
            profit
        );


    // ========================================================
    // OUTPUT
    // ========================================================

    cout << "\n=============================================\n";
    cout << "              RESULTS\n";
    cout << "=============================================\n";

    cout << "\nMaximum Profit using Memoization = "
         << memoizationAnswer << endl;

    cout << "\nMaximum Profit using Iterative DP = "
         << iterativeAnswer << endl;

    cout << "\n=============================================\n";

    if (memoizationAnswer == iterativeAnswer)
    {
        cout << "Both approaches give the same answer.\n";
    }

    cout << "=============================================\n";

    cout << "\nProgram Completed Successfully!\n";

    return 0;
}