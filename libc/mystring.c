/*
 * mystring.c -- hand-written libc string/memory primitives
 *
 * Fill in the five function bodies. Do NOT look at the real implementations
 * first. Write them, run the tests, then read glibc afterwards to compare.
 *
 * BUILD & RUN
 *   gcc -Wall -Wextra -o mystring mystring.c && ./mystring
 *
 * Every test must print PASS. A crash means you wrote past the end of a buffer.
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

/*============================================================================
 * 1. my_strlen
 *    Count characters up to but NOT including the terminating '\0'.
 *    Return type is size_t -- unsigned, because a length is never negative.
 *==========================================================================*/
size_t my_strlen(const char *s)
{
    /* TODO */
    (void)s;
    return 0;
}

/*============================================================================
 * 2. my_strcpy
 *    Copy src into dst including the '\0'.
 *    Return dst -- the ORIGINAL pointer, so calls can be chained.
 *    Caller guarantees dst is large enough. This is why strcpy is unsafe.
 *==========================================================================*/
char *my_strcpy(char *dst, const char *src)
{
    /* TODO */
    (void)src;
    return dst;
}

/*============================================================================
 * 3. my_strncpy
 *    Copy at most n bytes from src to dst.
 *
 *    TWO behaviours people forget:
 *      a) If strlen(src) < n, the remainder of dst is PADDED with '\0'.
 *      b) If strlen(src) >= n, dst is NOT null-terminated.
 *    Both are required by the C standard. (b) is the classic bug.
 *==========================================================================*/
char *my_strncpy(char *dst, const char *src, size_t n)
{
    /* TODO */
    (void)src; (void)n;
    return dst;
}

/*============================================================================
 * 4. my_memcpy
 *    Copy n bytes. Type-agnostic, hence void *.
 *    Cast to unsigned char * internally -- you cannot dereference void *,
 *    and unsigned char is guaranteed to be exactly one byte.
 *    Behaviour is UNDEFINED if the regions overlap. That is what memmove is for.
 *==========================================================================*/
void *my_memcpy(void *dst, const void *src, size_t n)
{
    /* TODO */
    (void)src; (void)n;
    return dst;
}

/*============================================================================
 * 5. my_memmove
 *    Same as memcpy, but MUST work when the regions overlap.
 *
 *    The trick: choose a copy direction.
 *      dst < src  -> copy forward  (front bytes are consumed before overwritten)
 *      dst > src  -> copy BACKWARD (else you overwrite source bytes you still need)
 *
 *    Draw it on paper before coding. This is the whole question.
 *==========================================================================*/
void *my_memmove(void *dst, const void *src, size_t n)
{
    /* TODO */
    (void)src; (void)n;
    return dst;
}

/*============================================================================
 *                              TEST HARNESS
 *                        (nothing below needs editing)
 *==========================================================================*/

static int fails = 0;

static void check(const char *name, int ok)
{
    printf("%-28s %s\n", name, ok ? "PASS" : "FAIL");
    if (!ok) fails++;
}

int main(void)
{
    char buf[32];
    char ref[32];

    /* ---- my_strlen ---- */
    check("strlen empty",      my_strlen("")            == 0);
    check("strlen hello",      my_strlen("hello")       == 5);
    check("strlen embedded",   my_strlen("a\tb c")      == 5);

    /* ---- my_strcpy ---- */
    memset(buf, 'X', sizeof buf);
    check("strcpy returns dst", my_strcpy(buf, "hello") == buf);
    check("strcpy content",     strcmp(buf, "hello")    == 0);
    check("strcpy terminates",  buf[5]                  == '\0');

    memset(buf, 'X', sizeof buf);
    my_strcpy(buf, "");
    check("strcpy empty src",   buf[0]                  == '\0');

    /* ---- my_strncpy ---- */
    memset(buf, 'X', sizeof buf);
    memset(ref, 'X', sizeof ref);
    my_strncpy(buf, "abc", 8);
    strncpy(ref, "abc", 8);
    check("strncpy pads with NUL", memcmp(buf, ref, 8)  == 0);

    memset(buf, 'X', sizeof buf);
    memset(ref, 'X', sizeof ref);
    my_strncpy(buf, "abcdefgh", 4);
    strncpy(ref, "abcdefgh", 4);
    check("strncpy truncates",     memcmp(buf, ref, 8)  == 0);
    check("strncpy no NUL if full", buf[3]              == 'd');

    /* ---- my_memcpy ---- */
    memset(buf, 0, sizeof buf);
    check("memcpy returns dst", my_memcpy(buf, "12345", 5) == buf);
    check("memcpy content",     memcmp(buf, "12345", 5)    == 0);
    check("memcpy n=0 safe",    my_memcpy(buf, "zzzzz", 0) == buf && buf[0] == '1');

    /* ---- my_memmove: forward overlap (dst < src) ---- */
    strcpy(buf, "0123456789");
    strcpy(ref, "0123456789");
    my_memmove(buf + 0, buf + 2, 8);
    memmove(ref + 0, ref + 2, 8);
    check("memmove dst < src", memcmp(buf, ref, 11) == 0);

    /* ---- my_memmove: backward overlap (dst > src) ---- */
    strcpy(buf, "0123456789");
    strcpy(ref, "0123456789");
    my_memmove(buf + 2, buf + 0, 8);
    memmove(ref + 2, ref + 0, 8);
    check("memmove dst > src", memcmp(buf, ref, 11) == 0);

    /* ---- my_memmove: no overlap ---- */
    char a[16] = "hello", b[16] = "XXXXXXXX";
    my_memmove(b, a, 6);
    check("memmove no overlap", strcmp(b, "hello") == 0);

    printf("\n%s  (%d failure%s)\n",
           fails ? "SOME TESTS FAILED" : "ALL TESTS PASSED",
           fails, fails == 1 ? "" : "s");
    return fails != 0;
}
