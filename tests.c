#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// #include "intal.h"

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
    // d->prev = NULL;
    d->fdig = '\0';
    return d;
}

void equalise (char **num1, char **num2)
{
    int len1 = strlen(*num1);
    int len2 = strlen(*num2);
    if (len1 == len2)
        return;


    int max = greatestLength(*num1, *num2);

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

int leastLength (char *str1, char *str2)
{
    return (strlen(str1) > strlen(str2)) ? strlen(str2) : strlen(str1);
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

char* intal_add (char *intal1, char *intal2)
{
    equalise(&intal1, &intal2);

    if (DEBUG) {
        printf ("%s\n", intal1);
        printf ("%s\n", intal2);
    }

    int max = greatestLength(intal1, intal2);

    if (DEBUG) {
        printf ("%d\n", max);
    }

    number num;
    num.head = NULL;
    int carryFlag = 0;

    for (int i=max-1; i >= 0; --i) {
        digit *temp = createNode(intal1[i], intal2[i]);
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

char* intal_diff (char *intal1, char *intal2)
{
    int isEq = intal_compare(intal1, intal2);
    if (isEq == -1) {
        char *temp = intal1;
        intal1 = intal2;
        intal2 = temp;
    }
    equalise(&intal1, &intal2);

    if (DEBUG) {
        printf ("%s\n", intal1);
        printf ("%s\n", intal2);
    }

    int max = greatestLength(intal1, intal2);

    if (DEBUG) {
        printf ("%d\n", max);
    }

    number num;
    num.head = NULL;
    int carryFlag = 0;

    for (int i=max-1; i >= 0; --i) {
        digit *temp = createNode(intal1[i], intal2[i]);
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

int intal_compare (char *intal1, char *intal2)
{
    equalise (&intal1, &intal2);
    int max = greatestLength(intal1, intal2);

    for (int i=0; i < max; i++) {
        if (intal1[i] < intal2[i]) {
            return -1;
        } else if (intal1[i] > intal2[i]) {
            return 1;
        } else {
            continue;
        }
    }
    return 0;
}

char* intal_multiply (char *intal1, char *intal2)
{
    if (strlen(intal1) < strlen(intal2)) {
        char *temp = intal1;
        intal1 = intal2;
        intal2 = temp;
    }
    int leastLen = strlen(intal2);
    equalise(&intal1, &intal2);
    int max = greatestLength(intal1, intal2);
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
            digit *temp = createNode(intal1[j], intal2[i]);
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

    for (int i=1; i < leastLen; ++i) {
        fnum = intal_add(fnum, makeString(&num[i]));
    }
    return fnum;
}



int main()
{
    char num1[1000]; // = "9983475928347958723948579";
    char num2[1000]; // = "909340980394853459";


    scanf("%s", num1);
    scanf("%s", num2);

    printf ("ADD: %s\n", intal_add(num1, num2));
    printf ("DIFF: %s\n", intal_diff(num1, num2));
    printf ("COMPARE: %d\n", intal_compare(num1, num2));
    printf ("MULTIPLY: %s\n", intal_multiply(num1, num2));
}
