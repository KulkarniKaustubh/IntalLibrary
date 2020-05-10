#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "intal.h"

#define DEBUG 0

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

int greatest (char *str1, char *str2);
void equalise (char **num1, char **num2);
void insert (number *num, digit *dig);

digit* createNode (char val1, char val2)
{
    digit *d;
    d = (digit*)malloc(sizeof(digit));
    int v1 = val1-'0';
    int v2 = val2-'0';
    int sum = v1 + v2;
    d->val1 = val1;
    d->val2 = val2;
    d->next =NULL;
    d->prev = NULL;
    d->fdig = (char)((sum%10)+'0');
    d->leftover = (char)((sum/10)+'0');
    return d;
}

void equalise (char **num1, char **num2)
{
    int len1 = strlen(*num1);
    int len2 = strlen(*num2);
    int max = greatest(*num1, *num2);
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

int greatest (char *str1, char *str2)
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
    if (dig->next->leftover == '1') {
        if (dig->fdig == '9') {
            dig->fdig = '0';
            dig->leftover = '1';
        } else {
            dig->fdig ++;
        }
    }
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

int lenList (number *num)
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
    if (num->head->leftover == '1') {
        char *str = (char*)malloc(sizeof(char)*lenList(num)+2);
        str[0] = '1';
        for (int i=1; i <= lenList(num); ++i) {
            if (temp) {
                str[i] = temp->fdig;
                temp = temp->next;
            }
        }
        str[lenList(num)+1] = '\0';
        return str;
    } else {
        char *str = (char*)malloc(sizeof(char)*lenList(num)+1);
        for (int i=0; i < lenList(num); ++i) {
            str[i] = temp->fdig;
            temp = temp->next;
        }
        str[lenList(num)] = '\0';
        return str;
    }
}

char* intal_add (char *intal_1, char *intal_2)
{
    equalise(&intal_1, &intal_2);

    if (DEBUG) {
        printf ("%s\n", intal_1);
        printf ("%s\n", intal_2);
    }

    int max = greatest(intal_1, intal_2);

    if (DEBUG) {
        printf ("%d\n", max);
    }

    number num;
    num.head = NULL;

    for (int i=max-1; i >= 0; --i) {
        digit *temp = createNode(intal_1[i], intal_2[i]);
        insert(&num, temp);
    }
    char *str;
    str = makeString(&num);
    if (str[0] == '0')
        return str+1;
    else
        return str;
}
