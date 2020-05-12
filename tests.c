#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "myfuncs.h"

#define DEBUG 0

char* intal_add (char *intal1, char *intal2)
{
    char *num1, *num2;
    equalise(intal1, intal2, &num1, &num2);

    char *str = Add(num1, num2);
    free (num1);
    free (num2);
    return str;
}

char* intal_diff (char *intal1, char *intal2)
{
    char *num1, *num2;
    equalise(intal1, intal2, &num1, &num2);

    char *str = Diff(num1, num2);
    free (num1);
    free (num2);
    return str;
}

int intal_compare (char *intal1, char *intal2)
{
    char *num1, *num2;
    equalise(intal1, intal2, &num1, &num2);

    int cmp = Compare(num1, num2);

    free (num1);
    free (num2);

    return cmp;
}

char* intal_multiply (char *intal1, char *intal2)
{
    char *num1, *num2;
    equalise(intal1, intal2, &num1, &num2);

    char *str = Multiply(num1, num2);
    free (num1);
    free (num2);
    return str;
}

char* intal_mod (char *intal1, char *intal2)
{
    if (intal_compare(intal1, intal2) == 0) {
        return "0\0";
    } else if (intal_compare(intal1, intal2) == -1) {
        return intal1;
    } else if (intal_compare("1", intal2) == 0) {
        return "0\0";
    }

    char *str = Mod (intal1, intal2);
    return str;
}

int main()
{
    char num1[1000]; // = "9983475928347958723948579";
    char num2[1000]; // = "909340980394853459";


    scanf("%s", num1);
    scanf("%s", num2);

    printf ("length 1 : %ld\n", strlen(num1));
    printf ("length 2 : %ld\n", strlen(num2));

    printf ("ADD: %s\n", intal_add(num1, num2));
    if (DEBUG){
        printf ("main:\n");
        printf("%s\n", num1);
        printf("%s\n", num2);
        printf ("end.\n");
    }

    printf ("DIFF: %s\n", intal_diff(num1, num2));
    if (DEBUG){
        printf ("main:\n");
        printf("%s\n", num1);
        printf("%s\n", num2);
        printf ("end.\n");
    }
    printf ("COMPARE: %d\n", intal_compare(num1, num2));
    if (DEBUG){
        printf ("main:\n");
        printf("%s\n", num1);
        printf("%s\n", num2);
        printf ("end.\n");
    }
    printf ("MULTIPLY: %s\n", intal_multiply(num1, num2));
    if (DEBUG){
        printf ("main:\n");
        printf("%s\n", num1);
        printf("%s\n", num2);
        printf ("end.\n");
    }
    printf ("MOD: %s\n", intal_mod(num1, num2));
    if (DEBUG){
        printf ("main:\n");
        printf("%s\n", num1);
        printf("%s\n", num2);
        printf ("end.\n");
    }
}
