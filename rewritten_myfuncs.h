#ifndef FUNCS
#define FUNCS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// #include "operations.h"

#define DEBUG 0

typedef struct digit {
    char fdig;
    struct digit *next;
} digit;

typedef struct number {
    digit *head;
} number;

void freeNum (number *num)
{
    digit *temp;
    while (num->head) {
        temp = num->head;
        num->head = temp->next;
        free (temp);
    }
}

void equalise (char *num1, char *num2, int l)
{
    int l1 = strlen(num1);
    int l2 = strlen(num2);

    char *ptr1 = (char*)calloc(1000, sizeof(char));
    char *ptr2 = (char*)calloc(1000, sizeof(char));
    memset (ptr1, '0', l+1);
    memset (ptr2, '0', l+1);

    char *n1 = ptr1;
    char *n2 = ptr2;

    if (l1 == l2) {
        free (n1);
        free (n2);
        return;
    } else if (l1 > l2) {
        for (int i=0; i < l1-l2; ++i) {
            ++ptr2;
        }
        strcpy (ptr2, num2);
        strcpy (num2, n2);
        free (n1);
        free (n2);
        return;
    } else if (l1 < l2) {
        for (int i=0; i < l2-l1; ++i) {
            ++ptr1;
        }
        strcpy (ptr1, num1);
        strcpy (num1, n1);
        free (n1);
        free (n2);
        return;
    }
}

int greatestLength (const char *intal1, const char *intal2)
{
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    return l1>l2? l1 : l2;
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

digit* createNode()
{
    digit *d = (digit*)calloc(1, sizeof(digit));
    d->fdig = '\0';
    d->next = NULL;
    return d;
}

char* makeString(number num, char *str)
{
    digit *temp = num.head;
    int i = 0;
    while (temp) {
        str[i] = temp->fdig;
        temp = temp->next;
        ++i;
    }
    str[i] = '\0';
    return str;
}

void displayNumber (number num)
{
    digit *temp = num.head;
    while (temp) {
        printf ("%c", temp->fdig);
        temp = temp->next;
    }
    printf ("\n");
}

char* stripZeroes (char *str)
{
    if (str == NULL) {
        return NULL;
    }
    int len = strlen(str);
    char *str2 = (char*)calloc(1000, sizeof(char));
    char *ptr = str;
    while (ptr[0] == '0') {
        ++ptr;
    }
    if (strlen(ptr) == 0) {
        --ptr;
    }

    strcpy (str2, ptr);
    strcpy (str, str2);

    free (str2);

    return str;
}

char* Add (const char *intal1, const char *intal2, char *str)
{
    int len = greatestLength (intal1, intal2);

    char *num1 = (char*)calloc(1000, sizeof(char));
    char *num2 = (char*)calloc(1000, sizeof(char));

    strcpy (num1, intal1);
    strcpy (num2, intal2);
    equalise (num1, num2, len);

    if (DEBUG) {
        printf ("ADD:\n");
        printf ("1 : %s\n", num1);
        printf ("2 : %s\n", num2);
        printf ("END ADD.\n");
    }

    number num;
    num.head = NULL;

    int carryFlag = 0;

    for (int i=len-1; i >= 0; --i) {
        digit *temp = createNode();
        int v1 = num1[i]-'0';
        if (carryFlag)
            v1 += 1;
        int v2 = num2[i]-'0';
        int sum = v1 + v2;
        temp->fdig = (char)((sum%10)+'0');
        carryFlag = sum/10;
        insert(&num, temp);
    }
    if (carryFlag) {
        digit *temp = createNode('\0', '\0');
        temp->fdig = '1';
        insert (&num, temp);
    }

    str = makeString(num, str);

    freeNum(&num);
    free (num1);
    free (num2);

    return str;
}

char* Diff (const char *intal1, const char *intal2, char *str)
{
    int len = greatestLength (intal1, intal2);

    char *num1 = (char*)calloc(1000, sizeof(char));
    char *num2 = (char*)calloc(1000, sizeof(char));

    strcpy (num1, intal1);
    strcpy (num2, intal2);
    equalise (num1, num2, len);
    if (Compare(num1, num2) < 0) {
        char *temp = num1;
        num1 = num2;
        num2 = temp;
    }

    if (DEBUG) {
        printf ("DIFF:\n");
        printf ("1 : %s\n", num1);
        printf ("2 : %s\n", num2);
        printf ("END DIFF.\n");
    }

    number num;
    num.head = NULL;
    int carryFlag = 0;

    for (int i=len-1; i >= 0; --i) {
        digit *temp = createNode();
        int v1 = num1[i]-'0';
        if (carryFlag)
            v1 -= 1;
        int v2 = num2[i]-'0';
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

    str = makeString(num, str);

    freeNum(&num);
    free (num1);
    free (num2);

    return str;
}

int Compare (const char *intal1, const char *intal2)
{
    int len = greatestLength (intal1, intal2);

    char *num1 = (char*)calloc(1000, sizeof(char));
    char *num2 = (char*)calloc(1000, sizeof(char));

    strcpy (num1, intal1);
    strcpy (num2, intal2);
    equalise (num1, num2, len);

    for (int i=0; i < len; i++) {
        if (num1[i] < num2[i]) {
            free (num1);
            free (num2);
            return -1;
        } else if (num1[i] > num2[i]) {
            free (num1);
            free (num2);
            return 1;
        } else {
            continue;
        }
    }

    free (num1);
    free (num2);

    return 0;
}

char* Multiply (const char *intal1, const char *intal2, char *fnum)
{
    int len = greatestLength (intal1, intal2);

    char *num1 = (char*)calloc(1000, sizeof(char));
    char *num2 = (char*)calloc(1000, sizeof(char));

    strcpy (num1, intal1);
    strcpy (num2, intal2);
    equalise (num1, num2, len);

    if (Compare(num1, num2) < 0) {
        char *temp = num1;
        num1 = num2;
        num2 = temp;
    }

    int leastLen = strlen(num2);

    number num[leastLen];

    for (int i=0; i<leastLen; ++i) {
        num[i].head = NULL;
    }

    for (int i=0; i<leastLen; i++) {
        for (int j=0; j<i; ++j) {
            digit *temp = createNode();
            temp->fdig = '0';
            insert(&num[i], temp);
        }
        if (DEBUG) {
            printf ("%d : ", i);
            displayNumber(num[i]);
        }
    }

    int carryFlag = 0;

    for (int iter=0, i = len-1; iter < leastLen; ++iter, --i) {
        if (carryFlag) {
            digit *temp = createNode();
            temp->fdig = (char)((carryFlag)+'0');
            insert (&num[iter-1], temp);
            if (DEBUG) {
                printf ("inside if carryflag\n");
                printf ("iter %d : ", iter);
                displayNumber(num[iter]);
                printf ("iter %d : ", iter-1);
                displayNumber(num[iter]);
            }
            carryFlag = 0;
        }
        for (int j=len-1; j >= 0; --j) {
            digit *temp = createNode();
            int v1 = num1[j]-'0';
            int v2 = num2[i]-'0';
            if (v1 == 0 || v2 == 0) {
                temp->fdig = '0';
                insert(&num[iter], temp);
                if (DEBUG) {
                    printf ("inside v1 or v2 0\n");
                    printf ("iter %d : ", iter);
                    displayNumber(num[iter]);
                }
                continue;
            }

            int prod = v1 * v2;

            if (carryFlag) {
                prod += carryFlag;
            }

            carryFlag = prod/10;
            temp->fdig = (char)((prod%10)+'0');

            insert(&num[iter], temp);

            if (DEBUG) {
                printf ("iter %d : ", iter);
                displayNumber(num[iter]);
            }
        }
    }

    if (carryFlag) {
        digit *temp = createNode();
        temp->fdig = (char)((carryFlag)+'0');
        insert (&num[leastLen-1], temp);
        carryFlag = 0;
    }

    fnum = makeString(num[0], fnum);

    freeNum(&num[0]);

    for (int i=1; i < leastLen; ++i) {
        char *temp = (char*)calloc(1000, sizeof(char));

        if (DEBUG) {
            printf ("num[%d] : ", i);
            displayNumber(num[i]);
        }

        temp = makeString(num[i], temp);

        if (DEBUG) {
            printf ("on i = %d, temp = %s\n", i, temp);
        }

        fnum = Add(fnum, temp, fnum);
        free (temp);
        freeNum(&num[i]);
    }

    free (num1);
    free (num2);

    return fnum;
}

char* Mod (const char *intal1, const char *intal2, char *str)
{
    int len = greatestLength (intal1, intal2);

    char *num1 = (char*)calloc(1000, sizeof(char));
    char *num2 = (char*)calloc(1000, sizeof(char));

    strcpy (num1, intal1);
    strcpy (num2, intal2);

    equalise (num1, num2, len);

    num1 = stripZeroes(num1);
    num2 = stripZeroes(num2);

    if (Compare(intal1, intal2) == 0 || Compare("1", intal2) == 0 || Compare("0", intal1) == 0) {
        strcpy (str, "0");
        free (num1);
        free (num2);
        return str;
    } else if (Compare(intal1, intal2) == -1) {
        strcpy (str, num1);
        free (num1);
        free (num2);
        return str;
    } else if (Compare("0", intal2) == 0) {
        strcpy (str, "Divided by 0 error");
        free (num1);
        free (num2);
        return str;
    }

    if (Compare(num1, num2) < 0) {
        char *temp = num1;
        num1 = num2;
        num2 = temp;
    }

    char *n1 = (char*)calloc(1000, sizeof(char));
    char *n2 = (char*)calloc(1000, sizeof(char));
    strcpy (n1, num1);
    strcpy (n2, num2);

    int len2 = strlen(n2);

    while (Compare(n1, num2) > 0) {
        int len1 = strlen(n1);
        int power = (len1 - len2) - 1;

        if (power < 0) {
            n1 = Diff(n1, num2, n1);
            n1 = stripZeroes(n1);
            continue;
        } else if (power == 0) {
            strcpy (n2, num2);
        } else {
            strcpy (n2, num2);
            for (int i=0; i < power; ++i) {
                n2 = Multiply(n2, "10\0", n2);
                n2 = stripZeroes(n2);
            }
        }

        char *val = (char*)calloc(1000, sizeof(char));
        strcpy (val, n2);

        while (Compare(n1, n2) > 0) {
            n2 = Add(n2, val, n2);
            n2 = stripZeroes(n2);
            if (Compare(n1, n2) == 0) {
                strcpy (str, "0");
                free (val);
                free (n1);
                free (n2);
                free (num1);
                free (num2);
                return str;
            }
        }
        n2 = Diff(n2, val, n2);
        n2 = stripZeroes(n2);
        free (val);
        n1 = Diff(n1, n2, n1);
        n1 = stripZeroes(n1);
    }

    strcpy (str, n1);

    free (n1);
    free (n2);
    free (num1);
    free (num2);

    return str;
}

char* divideByTwo (char *str)
{
    int len = strlen(str);
    char *res = (char*)calloc(1000, sizeof(char));

    int carryFlag = 0;

    for (int i=0; i<len; ++i) {
        int val = (10*carryFlag) + (str[i]-'0');
        int fval;
        if (val >= 2) {
            fval = val/2;
            carryFlag = val%2;
        } else {
            fval = 0;
            carryFlag = val;
        }
        res[i] = (char)((fval)+'0');
    }

    strcpy (str, res);

    free (res);

    return str;
}

char* Pow (const char *intal1, unsigned int n, char *str)
{
    char *num1 = (char*)calloc(1000, sizeof(char));

    strcpy (num1, intal1);

    num1 = stripZeroes(num1);

    char *res = (char*)calloc(1000, sizeof(char));
    strcpy (res, "1");

    while (n > 0) {
        if (n & 1) {
            res = Multiply(res, num1, res);
            res = stripZeroes(res);
        }

        // num2 = divideByTwo(num2);
        // num2 = stripZeroes(num2);
        // n = n/2;
        n = n >> 1;
        num1 = Multiply(num1, num1, num1);
        num1 = stripZeroes(num1);
    }

    strcpy(str, res);

    free (res);
    free (num1);
    // free (num2);

    return str;
}

#endif
