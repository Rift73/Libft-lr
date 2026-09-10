/* Build: make && cc -Wall -Wextra -Werror -I. tests/test.c libft.a -o test.out && ./test.out */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"

static int cases, failed_cases, failed_checks;

static const char *result(int correct)
{
    if (!correct)
        failed_checks++;
    return correct ? "[PASS]" : "[FAIL]";
}

static void check_number(const char *field, long actual, long expected)
{
    int correct = actual == expected;
    printf("  %s %s", result(correct), field);
    if (correct) printf(": %ld\n", actual);
    else printf("\n    Expected: %ld\n    Got:      %ld\n", expected, actual);
}

static void check_pointer(const char *expected_description, const void *actual, const void *expected)
{
    int correct = actual == expected;
    printf("  %s Return pointer", result(correct));
    if (correct) printf(": %s\n", expected_description);
    else printf("\n    Expected: %s\n    Got:      %s\n", expected_description,
        !actual ? "NULL (no pointer)" : !expected ? "a non-NULL pointer" : "a pointer to the wrong location");
}

static void check_allocation(const void *actual)
{
    if (actual) printf("  %s Memory was allocated successfully.\n", result(1));
    else printf("  %s Allocation failed.\n    Expected: allocated memory\n    Got:      NULL (no memory)\n", result(0));
}

static void check_order(int actual)
{
    if (actual > 0) printf("  %s First value is greater (returned %d).\n", result(1), actual);
    else printf("  %s Comparison\n    Expected: first value is greater (positive result)\n"
        "    Got:      %s (returned %d)\n", result(0), actual < 0 ? "first value is smaller" : "values are equal", actual);
}

static void print_text(const char *text)
{
    if (!text) printf("NULL");
    else if (!*text) printf("\"\" (an empty string)");
    else printf("\"%s\"", text);
}

static void check_text(const char *field, const char *actual, const char *expected)
{
    int correct = actual && expected ? strcmp(actual, expected) == 0 : actual == expected;
    printf("  %s %s", result(correct), field);
    if (correct) { printf(": "); print_text(actual); }
    else { printf("\n    Expected: "); print_text(expected); printf("\n    Got:      "); print_text(actual); }
    putchar('\n');
}

static void print_byte(unsigned char byte)
{
    if (byte == 0) printf("'\\0'");
    else if (byte == '\n') printf("'\\n'");
    else if (byte == '\t') printf("'\\t'");
    else if (byte == '\r') printf("'\\r'");
    else if (byte == ' ') printf("' ' (space)");
    else if (byte == '\'') printf("'\\''");
    else if (byte == '\\') printf("'\\\\'");
    else if (byte >= 33 && byte <= 126) printf("'%c'", byte);
    else printf("byte value %u", (unsigned int)byte);
}

static void print_bytes(const unsigned char *data, size_t size)
{
    if (!data) { printf("NULL (no memory)"); return; }
    size_t same = 1;
    while (same < size && data[same] == data[0]) same++;
    if (size > 1 && same == size)
    {
        if (!data[0]) printf("%zu zero bytes", size);
        else { printf("%zu copies of ", size); print_byte(data[0]); }
        return;
    }
    putchar('[');
    for (size_t i = 0; i < size; i++)
    {
        if (i) printf(", ");
        print_byte(data[i]);
    }
    putchar(']');
}

static void check_bytes(const char *field, const void *actual, const void *expected, size_t size)
{
    int correct = actual && memcmp(actual, expected, size) == 0;
    printf("  %s %s", result(correct), field);
    if (correct) { printf(": "); print_bytes(actual, size); }
    else
    {
        printf("\n    Expected: "); print_bytes(expected, size);
        printf("\n    Got:      "); print_bytes(actual, size);
        if (actual)
            for (size_t i = 0; i < size; i++)
                if (((const unsigned char *)actual)[i] != ((const unsigned char *)expected)[i])
                    printf("\n    Byte %zu is wrong (C index %zu).", i + 1, i);
    }
    putchar('\n');
}

static void check_split(const char *input, char delimiter, const char *expected[])
{
    char **actual = ft_split(input, delimiter);
    size_t i = 0;
    char field[32];

    check_allocation(actual);
    if (!actual)
        return;
    while (expected[i] && actual[i])
    {
        snprintf(field, sizeof(field), "Word %zu", i + 1);
        check_text(field, actual[i], expected[i]);
        i++;
    }
    snprintf(field, sizeof(field), "Word %zu", i + 1);
    if (!expected[i]) snprintf(field, sizeof(field), "End of the word array");
    check_text(field, actual[i], expected[i]);
    for (i = 0; actual[i]; i++)
        free(actual[i]);
    free(actual);
}

/* Each child gets its own memory and a timeout; one broken case cannot stop the rest. */
#define TEST(description, ...) do { \
    printf("\n%02d. %s\n", ++cases, description); fflush(stdout); \
    pid_t child = fork(); \
    int status; \
    if (child == 0) { \
        alarm(2); failed_checks = 0; \
        __VA_ARGS__ \
        fflush(stdout); _exit(failed_checks != 0); \
    } \
    if (child < 0 || waitpid(child, &status, 0) < 0) { perror("test runner"); return 1; } \
    if (WIFSIGNALED(status)) { \
        int signal_number = WTERMSIG(status); \
        printf("  FAIL: %s; no normal result was returned. See expected behavior above.\n", \
            signal_number == SIGALRM ? "timed out after 2 seconds" : strsignal(signal_number)); \
        failed_cases++; \
    } else if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) { failed_cases++; } \
} while (0)

int main(int argc, char **argv)
{
    char buffer[16];
    char *string;
    void *memory, *returned;
    const char *two_words[] = {"a", "b", NULL};
    const char *no_words[] = {NULL};
    const char *whole_string[] = {"abc", NULL};
    setvbuf(stdout, NULL, _IONBF, 0);
    if (argc == 2 && strcmp(argv[1], "--demo") == 0)
    {
        puts("DEMO ONLY: these made-up results explain PASS and FAIL.");
        puts("They are NOT results from your Libft.\n");
        check_text("Correct copying", "aabcde", "aabcde");
        check_text("Incorrect copying", "abcdef", "aabcde");
        check_number("Incorrect return length", 4, 5);
        check_bytes("Missing string-ending zero byte", "heXX", "he\0X", 4);
        check_pointer("NULL (allocation rejected)", buffer, NULL);
        puts("\nDemo finished. Run ./test.out for your real Libft results.");
        return 0;
    }
    if (argc != 1) { fprintf(stderr, "Usage: %s [--demo]\n", argv[0]); return 2; }
    puts("LIBFT BOUNDARY CHECKS: results from your compiled library.");
    puts("PASS means a match; FAIL means a wrong result, a crash, or a timeout.");
    puts("\\0 means a zero byte; X marks memory that must stay unchanged.");

    TEST("memmove: shifting right must turn \"abcdef\" into \"aabcde\"",
        strcpy(buffer, "abcdef");
        returned = ft_memmove(buffer + 1, buffer, 5);
        check_pointer("the destination pointer (where copying started)", returned, buffer + 1);
        check_text("Text after copying", buffer, "aabcde");
    );
    TEST("memmove: shifting left must turn \"abcdef\" into \"bcdeff\"",
        strcpy(buffer, "abcdef");
        returned = ft_memmove(buffer, buffer + 1, 5);
        check_pointer("the destination pointer (where copying started)", returned, buffer);
        check_text("Text after copying", buffer, "bcdeff");
    );
    TEST("memcpy: copy 'a', a zero byte, and 'b' without stopping at zero",
        memset(buffer, 'X', sizeof(buffer));
        check_pointer("the destination pointer (where copying started)", ft_memcpy(buffer, "a\0b", 3), buffer);
        check_bytes("Copied bytes and the following untouched byte", buffer, "a\0bX", 4);
    );
    TEST("memcmp: byte 255 must compare greater than byte 1",
        check_order(ft_memcmp("\xff", "\1", 1));
    );
    TEST("strncmp: byte 128 must compare greater than byte 127",
        check_order(ft_strncmp("\x80", "\x7f", 1));
    );
    TEST("strlcpy: fit \"hello\" into 3 bytes; store \"he\" plus a zero byte; return 5",
        memset(buffer, 'X', sizeof(buffer));
        check_number("Full length of the source text", ft_strlcpy(buffer, "hello", 3), 5);
        check_bytes("Output and the following untouched byte", buffer, "he\0X", 4);
    );
    TEST("strlcpy: with no room to write, keep \"keep\" unchanged and return 5",
        strcpy(buffer, "keep");
        check_number("Full length of the source text", ft_strlcpy(buffer, "hello", 0), 5);
        check_text("Memory left unchanged", buffer, "keep");
    );
    TEST("strlcat: append \"cde\" to \"ab\" in 5 bytes; store \"abcd\" and return 5",
        memset(buffer, 'X', sizeof(buffer));
        strcpy(buffer, "ab");
        check_number("Length needed before truncation", ft_strlcat(buffer, "cde", 5), 5);
        check_bytes("Output and the following untouched byte", buffer, "abcd\0X", 6);
    );
    TEST("strlcat: no string ending within the first 4 bytes; write nothing and return 7",
        memset(buffer, 'X', sizeof(buffer));
        check_number("Buffer limit plus source length", ft_strlcat(buffer, "abc", 4), 7);
        check_bytes("Memory left unchanged", buffer, "XXXXXXXXXXXXXXXX", 16);
    );
    TEST("strnstr: finding \"cd\" in \"abcde\" requires searching at least 4 characters",
        strcpy(buffer, "abcde");
        check_pointer("NULL (the match does not fit within 3 characters)", ft_strnstr(buffer, "cd", 3), NULL);
        check_pointer("the 'c' at position 3 in the original string", ft_strnstr(buffer, "cd", 4), buffer + 2);
    );
    TEST("calloc(4, 2): allocate 8 bytes and set every byte to zero",
        memory = ft_calloc(4, 2);
        check_allocation(memory);
        if (memory)
            check_bytes("All allocated bytes start at zero", memory, "\0\0\0\0\0\0\0", 8);
        free(memory);
    );
    TEST("calloc: reject a request whose size calculation wraps around; return NULL",
        memory = ft_calloc((size_t)-1 / 2 + 1, 2);
        check_pointer("NULL (the overflowing allocation was rejected)", memory, NULL);
        free(memory);
    );
    TEST("calloc: zero elements must still return memory that free can accept",
        memory = ft_calloc(0, (size_t)-1);
        check_allocation(memory);
        free(memory);
    );
    TEST("calloc: zero bytes per element must still return memory that free can accept",
        memory = ft_calloc((size_t)-1, 0);
        check_allocation(memory);
        free(memory);
    );
    TEST("substr: starting beyond \"abc\" returns an empty string, not NULL",
        string = ft_substr("abc", 99, 8);
        check_text("Returned text", string, "");
        free(string);
    );
    TEST("substr: an oversized length stops at the end of the source; return \"cdef\"",
        string = ft_substr("abcdef", 2, (size_t)-1);
        check_text("Returned text", string, "cdef");
        free(string);
    );
    TEST("split: ignore extra spaces in \"  a  b  \"; return the words \"a\" and \"b\"",
        check_split("  a  b  ", ' ', two_words);
    );
    TEST("split: a string of only spaces gives no words; the array starts with NULL",
        check_split("   ", ' ', no_words);
    );
    TEST("split: using a zero byte as the separator keeps \"abc\" as one word",
        check_split("abc", '\0', whole_string);
    );
    TEST("itoa: turn the smallest int (-2147483648) into text",
        string = ft_itoa(INT_MIN);
        check_text("Number written as text", string, "-2147483648");
        free(string);
    );
    TEST("atoi: skip whitespace, read -2147483648, and stop at \"xyz\"",
        check_number("Number read from the string", ft_atoi(" \t\n-2147483648xyz"), INT_MIN);
    );
    printf("\nSUMMARY: %d/%d cases passed; %d failed.\n", cases - failed_cases, cases, failed_cases);
    if (!failed_cases) puts("No FAIL results: every result in these checks matched its expectation.");
    puts("For failure-message examples, run ./test.out --demo.");
    puts("These focused checks do not cover every Libft requirement.");
    return failed_cases != 0;
}
