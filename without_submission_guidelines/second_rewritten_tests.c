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

char* intal_mod (const char *intal1, const char *intal2)
{
    char *str = Mod (intal1, intal2);
    // str =
    stripZeroes(str);
    return str;
}

char* intal_pow (const char *intal1, unsigned int n)
{
    char *str = Pow(intal1, n);
    // str =
    stripZeroes(str);
    return str;
}

char* intal_gcd (const char *intal1, const char *intal2)
{
    char *str = GCD(intal1, intal2);
    stripZeroes (str);
    return str;
}

char* intal_fibonacci (unsigned int n)
{
    char *str = Fibonacci(n);
    return str;
}

char* intal_factorial (unsigned int n)
{
    char *str = Fact(n);
    return str;
}

int intal_max (char **arr, int n)
{
    int ind = Max(arr, n);
    return ind;
}

int intal_min (char **arr, int n)
{
    int ind = Min(arr, n);
    return ind;
}

int intal_search (char **arr, int n, const char *key)
{
    int ind = Search (arr, n, key);
    return ind;
}

void intal_sort (char **arr, int n)
{
    heapSort (arr, n);
    // return str;
}

int intal_binsearch (char **arr, int n, const char *key)
{
    int ind = binarySearch(arr, n, key);
    return ind;
}

char* coin_row_problem (char **arr, int n)
{
    char *str = coinRow (arr, n);
    return str;
}

char* intal_bincoeff (unsigned int n, unsigned int k)
{
    if (k > n/2) {
        k = n-k;
    }

    char *str = binomialCoefficient (n, k);
    return str;
}


int main ()
{

    char num1[5000];
    // char num2[5000];
    //
    //
    // scanf("%s", num1);
    // scanf("%s", num2);
    //
    // // printf ("%d\n", strlen (num1));
    // // strlen (num2);
    //
    // char *ans;
    //
    // if (DEBUG) {
    //     printf ("length 1 : %ld\n", strlen(num1));
    //     printf ("length 2 : %ld\n", strlen(num2));
    // }
    //
    // ans = intal_add(num1, num2);
    // printf ("ADD: %s\n", ans);
    // if (DEBUG){
    //     printf ("main:\n");
    //     printf("%s\n", num1);
    //     printf("%s\n", num2);
    //     printf ("end.\n");
    // }
    // free (ans);
    //
    // ans = intal_diff(num1, num2);
    // printf ("DIFF: %s\n", ans);
    // if (DEBUG){
    //     printf ("main:\n");
    //     printf("%s\n", num1);
    //     printf("%s\n", num2);
    //     printf ("end.\n");
    // }
    // free (ans);
    //
    // int answer;
    // answer = intal_compare(num1, num2);
    // printf ("COMPARE: %d\n", answer);
    // if (DEBUG){
    //     printf ("main:\n");
    //     printf("%s\n", num1);
    //     printf("%s\n", num2);
    //     printf ("end.\n");
    // }
    //
    // ans = intal_multiply(num1, num2);
    // printf ("MULTIPLY: %s\n", ans);
    // if (DEBUG){
    //     printf ("main:\n");
    //     printf("%s\n", num1);
    //     printf("%s\n", num2);
    //     printf ("end.\n");
    // }
    // free (ans);
    //
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
    //
    // ans = intal_gcd(num1, num2);
    // printf ("GCD: %s\n", ans);
    // if (DEBUG){
    //     printf ("main:\n");
    //     printf("%s\n", num1);
    //     printf("%s\n", num2);
    //     printf ("end.\n");
    // }
    // free (ans);
    //
    //
    // int n;
    // scanf("%d", &n);
    // ans = intal_fibonacci(n);
    // printf ("%s\n", ans);
    // free (ans);
    //
    // // int n;
    // // scanf("%d", &n);
    // // char *ans = intal_factorial(n);
    // // printf ("%s\n", ans);
    // // free (ans);

    scanf ("%s", num1);

    // char arr[3][5000];
    //
    // strcpy (arr[0], "10");
    // strcpy (arr[1], "20");
    // strcpy (arr[2], "30");

    int lim;
    printf ("limit : ");
    scanf ("%d", &lim);

    char **arr_ptr = (char**)calloc(lim, sizeof(char*));

    for (int i=0; i<lim; ++i) {
        char str[5000];
        printf ("string %d : ", i);
        scanf ("%s", str);
        arr_ptr[i] = (char*)calloc(strlen(str)+1, sizeof(char));
        strcpy (arr_ptr[i], str);
    }
    // arr_ptr[0] = (char*)calloc(2, sizeof(char));
    intal_sort(arr_ptr, lim);
    int ind = intal_binsearch(arr_ptr, lim, num1);
    printf ("%d\n", ind);

}
