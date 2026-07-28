/*
 * 1108. Defanging an IP Address                                    [Easy]
 * https://leetcode.com/problems/defanging-an-ip-address/
 *
 * Approach : count dots, allocate the exact grown size, then walk the input
 *            with two indices - one reading, one writing - since '.' expands
 *            to three characters and they advance at different rates.
 * Time     : O(n)   two passes
 * Space    : O(n)   new buffer; CALLER frees it
 *
 * Key point: a string cannot be grown in place. "1.1.1.1" is 8 bytes with the
 *            terminator; "1[.]1[.]1[.]1" needs 14. Writing the answer back
 *            into the input buffer is a heap overflow. That is why the
 *            signature returns char* - it hands back a new allocation.
 *
 * Sizing   : len + 2*dots + 1. Each '.' (1 char) becomes "[.]" (3 chars),
 *            so +2 per dot, plus 1 for the terminator.
 *
 * Note     : malloc does not zero memory (calloc does), so the explicit
 *            out[j] = '\0' is mandatory, not optional.
 */

char *defangIPaddr(char *address)
{
    int len  = strlen(address);
    int dots = 0;

    for (int i = 0; i < len; i++)
        if (address[i] == '.')
            dots++;

    char *out = malloc(len + 2 * dots + 1);
    if (out == NULL)
        return NULL;

    int j = 0;
    for (int i = 0; i < len; i++) {
        if (address[i] == '.') {
            out[j++] = '[';
            out[j++] = '.';
            out[j++] = ']';
        } else {
            out[j++] = address[i];
        }
    }

    out[j] = '\0';
    return out;
}

