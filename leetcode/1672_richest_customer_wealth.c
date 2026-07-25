/*
 * 1672. Richest Customer Wealth                                    [Easy]
 * https://leetcode.com/problems/richest-customer-wealth/
 *
 * Approach : nested scan - sum each row, keep a running maximum.
 * Time     : O(m * n)   every element read exactly once
 * Space    : O(1)       two ints, no allocation
 * Contract : nothing allocated, nothing for the caller to free. The result is
 *            a single scalar, so it fits in the return value - which is why
 *            this problem needs no returnSize output parameter, unlike 1480.
 *
 * Signature: int** is an array of ROW POINTERS, not a contiguous 2D block.
 *            accounts[i][j] is *(*(accounts + i) + j) - two loads, not one
 *            address computation. A pointer carries no dimension information,
 *            hence accountsSize and a PER-ROW accountsColSize array.
 *
 * Caveat   : maxWealth starts at 0, which is safe only because the constraints
 *            guarantee accounts[i][j] >= 1. If negatives were allowed this
 *            would return 0 for an all-negative grid - seed with INT_MIN, or
 *            from accounts[0][0], instead.
 *
 * Overflow : worst case 50 * 50 * 100 = 250,000. Fits an int comfortably.
 */

int maximumWealth(int **accounts, int accountsSize, int *accountsColSize)
{
    int maxWealth = 0;

    for (int i = 0; i < accountsSize; i++) {
        int currentWealth = 0;
        int cols          = accountsColSize[i];   /* per-row length */

        for (int j = 0; j < cols; j++)
            currentWealth += accounts[i][j];

        if (currentWealth > maxWealth)
            maxWealth = currentWealth;
    }

    return maxWealth;
}
