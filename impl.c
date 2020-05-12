#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intal.h"

#define DEBUG 0

typedef struct digit {
    char val1;
    char val2;
    char fdig;
    struct digit *next;
} digit;

typedef struct number {
    digit *head;
} number;

char* intal_add(char* intal1, char* intal2);
int intal_compare(char* intal1, char* intal2);
char* intal_diff(char* intal1, char* intal2);
char* intal_multiply(char* intal1, char* intal2);
int greatestLength (char *str1, char *str2);
void equalise (char *num1, char *num2, char **temp1, char **temp2);
void insert (number *num, digit *dig);
void freeNum (number *num);

void freeNum (number *num)
{
    digit *temp;
    while (num->head) {
        temp = num->head;
        num->head = temp->next;
        free (temp);
    }
}

digit* createNode (char val1, char val2)
{
    digit *d;
    d = (digit*)malloc(sizeof(digit));
    d->val1 = val1;
    d->val2 = val2;
    d->next =NULL;
    d->fdig = '\0';
    return d;
}

void equalise (char *num1, char *num2, char **temp1, char **temp2)
{
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    *temp1 = num1;
    *temp2 = num2;

    while (*temp1[0] == '0') {
        ++*temp1;
    }
    while (*temp2[0] == '0') {
        ++*temp2;
    }

    len1 = strlen(*temp1);
    len2 = strlen(*temp2);

    int max = greatestLength(*temp1, *temp2);
    char *str1 = (char*)calloc(max+1, sizeof(char));
    char *str2 = (char*)calloc(max+1, sizeof(char));

    memset (str1, '0', max);
    memset (str2, '0', max);

    if (len1 > len2) {
        strcpy (str2 + (len1-len2), *temp2);
        strcpy (str1, *temp1);
    } else if (len2 > len1) {
        strcpy (str1 + (len2-len1), *temp1);
        strcpy (str2, *temp2);
    } else {
        strcpy (str1, *temp1);
        strcpy (str2, *temp2);
    }

    str1[max] = '\0';
    str2[max] = '\0';

    *temp1 = str1;
    *temp2 = str2;
}

int greatestLength (char *str1, char *str2)
{
    return (strlen(str1) > strlen(str2)) ? strlen(str1) : strlen(str2);
}

void insert (number *num, digit *dig)
{
    if (num->head == NULL) {
        num->head = dig;
        return;
    }
    dig->next = num->head;
    num->head = dig;
}

void displayNumber (number *num)
{
    digit *temp = num->head;
    while (temp) {
        printf ("%c ", temp->fdig);
        temp = temp->next;
    }
    printf ("\n");
}

int numLen (number *num)
{
    int len = 0;
    digit *temp = num->head;
    while (temp) {
        ++len;
        temp = temp->next;
    }
    return len;
}

char* makeString (number *num)
{
    digit *temp = num->head;
    char *str = (char*)malloc(sizeof(char)*numLen(num)+1);
    for (int i=0; i < numLen(num); ++i) {
        str[i] = temp->fdig;
        temp = temp->next;
    }
    str[numLen(num)] = '\0';
    while (str[0] == '0') {
        ++str;
    }
    if (strlen(str) == 0) {
        return "0\0";
    }
    return str;
}

char* Add(char *num1, char *num2)
{
    if (DEBUG) {
        printf ("add:\n");
        printf ("%s\n", num1);
        printf ("%s\n", num2);
    }

    int max = greatestLength(num1, num2);

    if (DEBUG) {
        printf ("%d\n", max);
    }

    number num;
    num.head = NULL;
    int carryFlag = 0;

    for (int i=max-1; i >= 0; --i) {
        digit *temp = createNode(num1[i], num2[i]);
        int v1 = temp->val1-'0';
        if (carryFlag)
            v1 += 1;
        int v2 = temp->val2-'0';
        int sum = v1 + v2;
        temp->fdig = (char)((sum%10)+'0');
        carryFlag = sum/10;
        // temp->leftover = (char)((sum/10)+'0');
        insert(&num, temp);
    }
    if (carryFlag) {
        digit *temp = createNode('\0', '\0');
        temp->fdig = '1';
        insert (&num, temp);
    }
    char *str;
    str = makeString(&num);
    freeNum(&num);
    return str;
}

char* Diff (char *num1, char *num2)
{
    int isEq = intal_compare(num1, num2);
    if (isEq == -1) {
        char *temp = num1;
        num1 = num2;
        num2 = temp;
    }


    if (DEBUG) {
        printf ("diff:\n");
        printf ("%s\n", num1);
        printf ("%s\n", num2);
    }

    int max = greatestLength(num1, num2);

    if (DEBUG) {
        printf ("%d\n", max);
    }

    number num;
    num.head = NULL;
    int carryFlag = 0;

    for (int i=max-1; i >= 0; --i) {
        digit *temp = createNode(num1[i], num2[i]);
        int v1 = temp->val1-'0';
        if (carryFlag)
            v1 -= 1;
        int v2 = temp->val2-'0';
        int diff = v1 - v2;
        if (diff<0) {
            carryFlag = 1;
            v1 = v1+10;
            diff = v1 - v2;
        } else {
            carryFlag = 0;
        }
        temp->fdig = (char)((diff)+'0');
        insert(&num, temp);
    }
    char *str;
    str = makeString(&num);
    freeNum(&num);
    return str;
}

int Compare (char *num1, char *num2)
{
    int max = greatestLength(num1, num2);

    for (int i=0; i < max; i++) {
        if (num1[i] < num2[i]) {
            return -1;
        } else if (num1[i] > num2[i]) {
            return 1;
        } else {
            continue;
        }
    }
    return 0;
}

char* Multiply (char *num1, char *num2)
{
    int isEq = intal_compare(num1, num2);
    if (isEq == -1) {
        char *temp = num1;
        num1 = num2;
        num2 = temp;
    }
    int leastLen = strlen(num2);
    int max = greatestLength(num1, num2);
    number num[leastLen];
    for (int i=0; i<leastLen; ++i) {
        num[i].head = NULL;
    }
    for (int i=0; i<leastLen; i++) {
        for (int j=0; j<i; j++) {
            digit *temp = createNode('\0', '\0');
            temp->fdig = '0';
            insert(&num[i], temp);
        }
    }
    int carryFlag = 0;
    for (int iter=0, i = max-1; iter < leastLen; ++iter, --i) {
        if (carryFlag) {
            digit *temp = createNode('\0', '\0');
            temp->fdig = (char)((carryFlag)+'0');
            insert (&num[iter-1], temp);
            carryFlag = 0;
        }
        for (int j=max-1; j >= 0; --j) {
            digit *temp = createNode(num1[j], num2[i]);
            int v1 = temp->val1-'0';
            int v2 = temp->val2-'0';
            if (v1 == 0 || v2 == 0) {
                temp->fdig = '0';
                insert(&num[iter], temp);
                continue;
            }
            int prod = v1 * v2;
            if (carryFlag) {
                prod += carryFlag;
            }
            carryFlag = prod/10;
            temp->fdig = (char)((prod%10)+'0');
            insert(&num[iter], temp);
        }
    }
    if (carryFlag) {
        digit *temp = createNode('\0', '\0');
        temp->fdig = (char)((carryFlag)+'0');
        insert (&num[leastLen-1], temp);
        carryFlag = 0;
    }

    char *fnum = makeString(&num[0]);
    freeNum(&num[0]);

    for (int i=1; i < leastLen; ++i) {
        char *temp = makeString(&num[i]);
        char *n1, *n2;
        equalise (fnum, temp, &n1, &n2);
        fnum = Add(n1, n2);
        freeNum(&num[i]);
    }
    return fnum;
}

char* Mod (char *num1, char *num2)
{
    char *n1 = num1;
    char *n2 = num2;
    int len2 = strlen(n2);
    char *val;

    while (intal_compare(n1, num2) > 0) {
        int len1 = strlen(n1);
        int power = (len1 - len2) - 1;

        if (power < 0) {
            n1 = intal_diff(n1, num2);
            break;
        } else if (power == 0) {
            n2 = num2;
        } else {
            n2 = num2;
            for (int i=0; i < power; ++i)
                n2 = intal_multiply(n2, "10\0");
        }

        val = n2;

        while (intal_compare(n1, n2) > 0) {
            n2 = intal_add(n2, val);
            if (intal_compare(n1, n2) == 0)
                return "0\0";
        }
        n2 = intal_diff (n2, val);
        n1 = intal_diff (n1, n2);
    }

    char *str = (char*)malloc(sizeof(char));
    strcpy (str, n1);
    return str;
}

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
