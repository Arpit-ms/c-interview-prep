/*
 * 771. Jewels and Stones                                           [Easy]
 * https://leetcode.com/problems/jewels-and-stones/
 *
 * Approach : build a 256-entry lookup table from the jewel characters, then
 *            make one pass over the stones testing membership in O(1).
 * Time     : O(m + n)   one pass over each string
 * Space    : O(1)       fixed 256-int table regardless of input size
 * Contract : nothing allocated, nothing for the caller to free.
 *
 * Why a table and not a hash map: the key space is bounded at 256 (one byte),
 * so a fixed array IS the perfect hash - O(1) lookup, no allocation, no
 * collisions, deterministic timing. The same reasoning used to size a lookup
 * table in firmware, where a bounded input range removes the need for any
 * dynamic structure.
 *
 * The cast matters:
 *   char is SIGNED on x86 and ARM Linux. Any byte >= 128 becomes negative,
 *   so lookup[(int)c] would index BEFORE the array - a buffer underflow.
 *   (unsigned char) maps every byte to 0..255. This is why the standard
 *   specifies isalpha() and friends in terms of unsigned char.
 *   The constraints here are English letters only, so it never fires, but
 *   the habit is what stops it firing somewhere it matters.
 *
 * Naive alternative: nested loops, O(m*n). Fine at these limits, but it does
 * not generalise and the table version is no harder to write.
 *
 * Follow-up: with ASCII letters only there are 52 possibilities, so two
 *            uint64_t bitmasks give O(1) space with no table at all -
 *            mask |= 1ULL << (c - 'A'). Bit manipulation, arriving early.
 */

int numJewelsInStones(char *jewels, char *stones)
{
    int lookup[256] = {0};          /* full byte range, zero-initialised */

    /* mark every character that counts as a jewel */
    while (*jewels) {
        lookup[(unsigned char)*jewels] = 1;
        jewels++;
    }

    /* one pass over the stones, O(1) membership test per character */
    int count = 0;
    while (*stones) {
        if (lookup[(unsigned char)*stones])
            count++;
        stones++;
    }

    return count;
}
