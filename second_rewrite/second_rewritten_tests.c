#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "myfuncs_second.h"
// #include "operations.h"

#define DEBUG 0


char* intal_add (const char *intal1, const char *intal2)
{
    char *str = Add(intal1, intal2);
    // str =
    // stripZeroes (str);
    return str;
}

char* intal_diff (const char *intal1, const char *intal2)
{
    char *str = Diff(intal1, intal2);//, str);
    // str =
    stripZeroes (str);
    return str;
}

int intal_compare (const char *intal1, const char *intal2)
{
    int cmp = Compare(intal1, intal2);
    return cmp;
}

char* intal_multiply (const char *intal1, const char *intal2)
{
    char *str = Multiply(intal1, intal2);//, str);
    stripZeroes(str);
    return str;
}

// char* intal_mod (const char *intal1, const char *intal2)
// {
//     char *str = (char*)calloc(2000, sizeof(char));
//     str = Mod (intal1, intal2, str);
//     str = stripZeroes(str);
//     return str;
// }
//
// char* intal_pow (const char *intal1, unsigned int n)
// {
//     char *str = (char*)calloc(2000, sizeof(char));
//     str = Pow(intal1, n, str);
//     str = stripZeroes(str);
//     return str;
// }

int main ()
{
    char num1[5000];
    char num2[5000];


    scanf("%s", num1);
    scanf("%s", num2);

    // printf ("%d\n", strlen (num1));
    // strlen (num2);

    char *ans;

    if (DEBUG) {
        printf ("length 1 : %ld\n", strlen(num1));
        printf ("length 2 : %ld\n", strlen(num2));
    }

    ans = intal_add(num1, num2);
    printf ("ADD: %s\n", ans);
    if (DEBUG){
        printf ("main:\n");
        printf("%s\n", num1);
        printf("%s\n", num2);
        printf ("end.\n");
    }
    free (ans);

    ans = intal_diff(num1, num2);
    printf ("DIFF: %s\n", ans);
    if (DEBUG){
        printf ("main:\n");
        printf("%s\n", num1);
        printf("%s\n", num2);
        printf ("end.\n");
    }
    free (ans);

    int answer;
    answer = intal_compare(num1, num2);
    printf ("COMPARE: %d\n", answer);
    if (DEBUG){
        printf ("main:\n");
        printf("%s\n", num1);
        printf("%s\n", num2);
        printf ("end.\n");
    }

    ans = intal_multiply(num1, num2);
    printf ("MULTIPLY: %s\n", ans);
    if (DEBUG){
        printf ("main:\n");
        printf("%s\n", num1);
        printf("%s\n", num2);
        printf ("end.\n");
    }
    free (ans);

    // ans = intal_mod(num1, num2);
    // printf ("MOD: %s\n", ans);
    // if (DEBUG){
    //     printf ("main:\n");
    //     printf("%s\n", num1);
    //     printf("%s\n", num2);
    //     printf ("end.\n");
    // }
    // free (ans);
    //
    // printf ("power : ");
    // int n;
    // scanf ("%d", &n);
    // ans = intal_pow(num1, n);
    // printf ("POW: %s\n", ans);
    // if (DEBUG){
    //     printf ("main:\n");
    //     printf("%s\n", num1);
    //     printf("%s\n", num2);
    //     printf ("end.\n");
    // }
    // free (ans);
}
