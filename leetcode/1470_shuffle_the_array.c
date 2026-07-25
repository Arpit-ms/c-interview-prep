/*
 * 1470. Shuffle the Array                                          [Easy]
 * https://leetcode.com/problems/shuffle-the-array/
 *
 * Approach : single pass over the first half; nums[i] lands at arr[2i] and
 *            nums[n+i] at arr[2i+1], so both halves are placed in one loop.
 * Time     : O(n)
 * Space    : O(n) for the returned buffer, O(1) auxiliary
 * Contract : buffer is malloc'd; CALLER frees it. *returnSize is the output
 *            parameter carrying the length back, since C returns one value.
 *
 * Follow-up: O(1) extra space is possible because nums[i] <= 1000 fits in
 *            10 bits - pack the destination value into the upper bits of the
 *            same word, then shift down in a second pass. Same idea as
 *            packing two fields into one hardware register.
 */

#include <stdlib.h>

int *shuffle(int *nums, int numsSize, int n, int *returnSize)
{
    *returnSize = numsSize;

    int *arr = malloc(sizeof(*arr) * numsSize);
    if (arr == NULL) {          /* malloc can fail; never dereference NULL */
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        arr[2 * i]     = nums[i];       /* first half  -> even indices */
        arr[2 * i + 1] = nums[n + i];   /* second half -> odd indices  */
    }

    return arr;
}
