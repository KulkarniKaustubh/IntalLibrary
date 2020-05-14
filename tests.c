#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "myfuncs.h"

#define DEBUG 0

char* intal_add (char *intal1, char *intal2)
{
    char *str = (char*)calloc(1000, sizeof(char));
    str = Add(intal1, intal2, str);
    // free (num1);
    // free (num2);
    return str;
}

char* intal_diff (char *intal1, char *intal2)
{
    char *str = (char*)calloc(1000, sizeof(char));
    str = Diff(intal1, intal2, str);
    // free (num1);
    // free (num2);
    return str;
}

int intal_compare (char *intal1, char *intal2)
{
    int cmp = Compare(intal1, intal2);

    // free (num1);
    // free (num2);

    return cmp;
}

char* intal_multiply (char *intal1, char *intal2)
{
    char *str = (char*)calloc(1000, sizeof(char));
    str = Multiply(intal1, intal2, str);
    // free (num1);
    // free (num2);
    return str;
}
/*
char* intal_mod (char *intal1, char *intal2)
{
    if (intal_compare(intal1, intal2) == 0 || intal_compare("1", intal2) == 0 || intal_compare("0", intal1) == 0) {
        char *str = (char*)malloc(sizeof(char)*2);
        str[0] = '0';
        str[1] = '\0';
        return str;
    } else if (intal_compare(intal1, intal2) == -1) {
        char *str = (char*)malloc(sizeof(char)*strlen(intal1));
        strcpy (str, intal1);
        return str;
    } else if (intal_compare("0", intal2) == 0) {
        char *str = (char*)malloc(sizeof(char)*strlen("Divided by 0 error"));
        strcpy (str, "Divided by 0 error");
        return str;
    }

    char *str = Mod (intal1, intal2);
    return str;
}

char* intal_pow (char *intal1, char *intal2)
{
    if (intal_compare("0", intal2) == 0) {
        char *str = (char*)malloc(sizeof(char)*2);
        str[0] = '1';
        str[1] = '\0';
        return str;
    } else if (intal_compare("0", intal1) == 0) {
        char *str = (char*)malloc(sizeof(char)*2);
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
}
*/
int main()
{
    char num1[1000]; // = "9983475928347958723948579";
    char num2[1000]; // = "909340980394853459";


    scanf("%s", num1);
    scanf("%s", num2);

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
}
