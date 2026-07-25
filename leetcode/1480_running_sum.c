/*
 * 1480. Running Sum of 1d Array                                    [Easy]
 * https://leetcode.com/problems/running-sum-of-1d-array/
 *
 * Approach : prefix sum. Carry a running total across one pass and write it
 *            at each index. Keeping the accumulator in a local avoids
 *            re-reading arr[i-1] from memory each iteration.
 * Time     : O(n)
 * Space    : O(n) for the returned buffer, O(1) auxiliary
 * Contract : buffer is malloc'd; CALLER frees it. *returnSize is set before
 *            any early return, so the caller never reads an uninitialised
 *            length.
 *
 * Firmware : this is ADC sample accumulation - energy monitoring, battery
 *            charge estimation, moving-average filters, event counters.
 *
 * Note     : *returnSize is deliberately zeroed on failure. Returning NULL
 *            while leaving the size set is a classic caller-side crash.
 */

#include <stdlib.h>

int *runningSum(int *nums, int numsSize, int *returnSize)
{
    *returnSize = numsSize;

    if (numsSize == 0)
        return NULL;

    int *arr = malloc(sizeof(*arr) * numsSize);
    if (arr == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        arr[i] = sum;
    }

    return arr;
}
