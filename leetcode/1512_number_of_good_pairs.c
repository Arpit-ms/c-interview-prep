/*
 * 1512. Number of Good Pairs                                       [Easy]
 * https://leetcode.com/problems/number-of-good-pairs/
 *
 * Approach : single pass with a frequency table. When a value is met for the
 *            (k+1)th time it forms k new pairs with the earlier occurrences,
 *            so add the current count, then increment it.
 * Time     : O(n)        one pass
 * Space    : O(1)        fixed 101-int table, no allocation
 * Contract : nothing allocated, nothing for the caller to free.
 *
 * Why a plain array and not a hash map: the constraints bound the values at
 * 1 <= nums[i] <= 100, so a fixed table covers the whole range. Bounded input
 * range -> static table -> no heap, deterministic timing. Same reasoning used
 * to size a lookup table in embedded code.
 *
 * Note     : count += seen[nums[i]]++ is POST-increment - the old value is
 *            added first, then the counter goes up. Pre- vs post-increment is
 *            a standard C interview question.
 *
 * Brute force (first attempt, also accepted): nested loops, O(n^2). Fine at
 * n <= 100 but it does not generalise. Kept below for reference.
 */

int numIdenticalPairs(int *nums, int numsSize)
{
    int seen[101] = {0};        /* index = value, cell = times seen so far */
    int count = 0;

    for (int i = 0; i < numsSize; i++)
        count += seen[nums[i]]++;

    return count;
}

#if 0
/* O(n^2) brute force - every pair compared once.
 * The (i < j) guard some people add is dead code: j starts at i+1.
 */
int numIdenticalPairs_bruteforce(int *nums, int numsSize)
{
    int count = 0;

    for (int i = 0; i < numsSize; i++)
        for (int j = i + 1; j < numsSize; j++)
            if (nums[i] == nums[j])
                count++;

    return count;
}
#endif
