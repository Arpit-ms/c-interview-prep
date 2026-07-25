/*
 * 1929. Concatenation of Array                                     [Easy]
 * https://leetcode.com/problems/concatenation-of-array/
 *
 * Approach : allocate 2n ints, then in one pass write nums[i] to both ans[i]
 *            and ans[i + n]. No second loop needed.
 * Time     : O(n)
 * Space    : O(n) for the returned buffer, O(1) auxiliary
 * Contract : buffer is malloc'd; CALLER frees it. *returnSize carries the
 *            length back, because a C function returns only one value - hence
 *            the int* output parameter rather than a plain int.
 */

#include <stdlib.h>

int *getConcatenation(int *nums, int numsSize, int *returnSize)
{
    *returnSize = 2 * numsSize;

    int *ans = malloc(sizeof(*ans) * (*returnSize));
    if (ans == NULL) {          /* malloc can fail; never dereference NULL */
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < numsSize; i++) {
        ans[i]            = nums[i];
        ans[i + numsSize] = nums[i];
    }

    return ans;
}
