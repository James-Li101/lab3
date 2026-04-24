#include <stdio.h>

/* *************** strlen ************************
 * strlen:
 *  Counts the number of characters in a string
 *  before the null terminator '\0'.
 *
 * We assume:
 *   str is a valid null-terminated string.
 * We return:
 *   The number of characters (not including '\0').
 */
int strlen(const char* str) {
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
}

/* *************** strcpy ************************
 * strcpy:
 *  Copies the string 'src' into 'dest', including
 *  the null terminator.
 *
 * We assume:
 *   dest is large enough to hold src.
 *   src is a valid null-terminated string.
 * We return:
 *   A pointer to dest.
 */
char* strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';  // null-terminate the destination
    return dest;
}

/* *************** strcat ************************
 * strcat:
 *  Appends the string 'src' onto the end of 'dest',
 *  overwriting dest's null terminator and adding a
 *  new one at the end.
 *
 * We assume:
 *   dest is large enough to hold both strings.
 *   Both dest and src are valid null-terminated strings.
 * We return:
 *   A pointer to dest.
 */
char* strcat(char* dest, const char* src) {
    int i = 0;
    int j = 0;

    // Move i to the end of dest
    while (dest[i] != '\0') {
        i++;
    }

    // Append src onto dest
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }

    dest[i] = '\0';  // null-terminate the result
    return dest;
}

/* *************** main ************************
 * main:
 *  Tests all three string functions.
 */
int main() {
    // Test strlen
    char s[] = "Hello";
    printf("strlen(\"Hello\") = %d\n", strlen(s));  // expected: 5

    // Test strcpy
    char dest[50];
    strcpy(dest, "Hello World");
    printf("strcpy result: %s\n", dest);  // expected: Hello World

    // Test strcat
    char base[50] = "Hello, ";
    strcat(base, "World!");
    printf("strcat result: %s\n", base);  // expected: Hello, World!

    return 0;
}
