#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// #include "intal.h"

#define DEBUG 1

typedef struct digit {
    char val1;
    char val2;
    char fdig;
    char leftover;
    struct digit *next;
    struct digit *prev;
} digit;

typedef struct number {
    digit *head;
} number;

int greatestLength (char *str1, char *str2);
void equalise (char **num1, char **num2);
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
    d->prev = NULL;
    d->fdig = '\0';
    d->leftover = '\0';
    return d;
}

void equalise (char **num1, char **num2)
{
    int len1 = strlen(*num1);
    int len2 = strlen(*num2);
    int max = greatestLength(*num1, *num2);
    if (len1 == len2)
        return;

    char *str = (char*)calloc(max+1, sizeof(char));
    for (int i=0; i<max; ++i) {
        str[i] ='0';
    }
    str[max] = '\0';
    if (len1 > len2) {
        strcpy (str+(len1-len2), *num2);
        *num2 = str;
    } else if (len2 > len1) {
        strcpy (str+(len2-len1), *num1);
        *num1 = str;
    }
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
    // if (dig->next->leftover == '1') {
    //     if (dig->fdig == '9') {
    //         dig->fdig = '0';
    //         dig->leftover = '1';
    //     } else {
    //         dig->fdig ++;
    //     }
    // }
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
    return str;
}

char* intal_add (char *intal_1, char *intal_2)
{
    equalise(&intal_1, &intal_2);

    if (DEBUG) {
        printf ("%s\n", intal_1);
        printf ("%s\n", intal_2);
    }

    int max = greatestLength(intal_1, intal_2);

    if (DEBUG) {
        printf ("%d\n", max);
    }

    number num;
    num.head = NULL;
    int carryFlag = 0;

    for (int i=max-1; i >= 0; --i) {
        digit *temp = createNode(intal_1[i], intal_2[i]);
        int v1 = temp->val1-'0';
        if (carryFlag)
            v1 += 1;
        int v2 = temp->val2-'0';
        int sum = v1 + v2;
        temp->fdig = (char)((sum%10)+'0');
        if (sum >= 10) {
            carryFlag = 1;
        } else {
            carryFlag = 0;
        }
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

#if 0
char* intal_diff (char *inal_1, char *intal_2)
{
    equalise(&intal_1, &intal_2);

    if (DEBUG) {
        printf ("%s\n", intal_1);
        printf ("%s\n", intal_2);
    }

    int max = greatestLength(intal_1, intal_2);

    if (DEBUG) {
        printf ("%d\n", max);
    }

    number num;
    num.head = NULL;
    int carryFlag = 0;
    for (int i=max-1; i >= 0; --i) {
        digit *temp = createNode(intal_1[i], intal_2[i]);
        int v1 = temp->val1-'0';
        int v2 = temp->val2-'0';
        int diff = v1 - v2;
        if (diff<0) {
            carryFlag = 1;
            v1 = v1*10;
            diff = v1 - v2;
        }
        temp->fdig = (char)((diff)+'0');
        insert(&num, temp);
    }
    char *str;
    str = makeString(&num);
    freeNum(&num);
    return str;
}
#endif

int main()
{
    char num1[1000];
    char num2[1000];

    scanf("%s", num1);
    scanf("%s", num2);

    printf ("%s\n", intal_add(num1, num2));
}
