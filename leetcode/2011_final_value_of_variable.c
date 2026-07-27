/*
 * 2011. Final Value of Variable After Performing Operations        [Easy]
 * https://leetcode.com/problems/final-value-of-variable-after-performing-operations/
 *
 * Approach : inspect ONE character per operation. The middle character,
 *            index [1], is '+' or '-' for all four forms, so a single
 *            comparison decides the direction.
 * Time     : O(n)        one pass, constant work per element
 * Space    : O(1)        no allocation
 * Contract : nothing allocated, nothing for the caller to free.
 *
 * Why index [1] and not [0]:
 *
 *     op    [0]  [1]  [2]
 *     ++X    +    +    X
 *     X++    X    +    +
 *     --X    -    -    X
 *     X--    X    -    -
 *
 * Index [0] cannot discriminate - X++ and X-- both begin with 'X'. Index [1]
 * is the only position that always carries the sign. Same idea as picking the
 * one bit in a status word that actually distinguishes two states.
 *
 * Note     : the bare 'else' treats anything that is not '+' as a decrement.
 *            Safe here because the constraints guarantee well-formed input.
 *            Parsing a real command stream would need an explicit
 *            else-if plus a rejected/malformed path - unknown opcodes should
 *            be flagged, never silently taken as the default case.
 *
 * Follow-up: branchless variant is x += (op[1] == '+') ? 1 : -1; which may
 *            compile to a conditional move instead of a branch, avoiding a
 *            pipeline flush on a mispredict (the IT block on Cortex-M).
 *            Same semantics, no clearer - keep the if/else.
 */

int finalValueAfterOperations(char **operations, int operationsSize)
{
    int x = 0;

    for (int i = 0; i < operationsSize; i++) {
        if (operations[i][1] == '+')
            x++;
        else
            x--;
    }

    return x;
}
