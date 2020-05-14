#include <stdio.h>
#include <string.h>
#include <stdio.h>

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
// int intal_compare(char* intal1, char* intal2);
// char* intal_diff(char* intal1, char* intal2);
// char* intal_multiply(char* intal1, char* intal2);
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
    d = (digit*)calloc(1, sizeof(digit));
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

    if (max == 0) {
        char *str1 = (char*)calloc(2, sizeof(char));
        char *str2 = (char*)calloc(2, sizeof(char));
        strcpy (str1, "0");
        strcpy (str2, "0");
        *temp1 = str1;
        *temp2 = str2;
        return;
    } else {

        char *str1 = (char*)calloc(max+2, sizeof(char));
        char *str2 = (char*)calloc(max+2, sizeof(char));


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
        printf ("%c", temp->fdig);
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

char* stripZeroes(char *str)
{
    int nlen = strlen(str)+1;
    int size = nlen+1;
    int ptrFlag = 0;
    char *ptr = str;
    char *str2;

    for (int i=0; i < nlen-1; ++i) {
        if (ptr[0] == '0') {
            ptrFlag = 1;
            ++ptr;
            --size;
        }
    }

    if (ptrFlag == 1) {
        str2 = (char*)calloc(size+1, sizeof(char));
        memcpy (str2, ptr, size);
        free (str);
        return str2;
    } else {
        return str;
    }
}

char* makeString (number *num, char *str)
{
    digit *temp = num->head;
    int nlen = numLen(num);
    int size = nlen+1;
    // char *str = (char*)malloc(sizeof(char)*size);
    for (int i=0; i < nlen; ++i) {
        str[i] = temp->fdig;
        temp = temp->next;
    }
    return str;
    // str[nlen] = '\0';

    // str = stripZeroes(num, str);
}

char* Add(char *intal1, char *intal2, char *str)
{
    char *num1, *num2;
    equalise(intal1, intal2, &num1, &num2);

    if (DEBUG) {
        printf ("add:\n");
        printf ("%s\n", num1);
        printf ("%s\n", num2);
        printf ("end\n");
    }

    int max = greatestLength(num1, num2);

    if (DEBUG) {
        printf ("max : ");
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
    // char *str;//= (char*)malloc(sizeof(char)*(numLen(&num)+1));
    str = makeString(&num, str);
    str = stripZeroes(str);
    freeNum(&num);
    free (num1);
    free (num2);
    return str;
}

char* Diff (char *intal1, char *intal2, char *str)
{
    char *num1, *num2;
    equalise(intal1, intal2, &num1, &num2);

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

    str = makeString(&num, str);
    str = stripZeroes(str);
    freeNum(&num);
    free (num1);
    free (num2);
    return str;
}

int Compare (char *intal1, char *intal2)
{
    char *num1, *num2;
    equalise(intal1, intal2, &num1, &num2);

    int max = greatestLength(num1, num2);

    for (int i=0; i < max; i++) {
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

char* Multiply (char *intal1, char *intal2, char *fnum)
{
    char *num1, *num2;
    equalise(intal1, intal2, &num1, &num2);

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
        for (int j=0; j<i; ++j) {
            digit *temp = createNode('\0', '\0');
            temp->fdig = '0';
            insert(&num[i], temp);
        }
        if (DEBUG) {
            printf ("%d : ", i);
            displayNumber(&num[i]);
        }
    }
    int carryFlag = 0;
    for (int iter=0, i = max-1; iter < leastLen; ++iter, --i) {
        if (carryFlag) {
            digit *temp = createNode('\0', '\0');
            temp->fdig = (char)((carryFlag)+'0');
            insert (&num[iter-1], temp);
            if (DEBUG) {
                printf ("inside if carryflag\n");
                printf ("iter %d : ", iter);
                displayNumber(&num[iter]);
                printf ("iter %d : ", iter-1);
                displayNumber(&num[iter]);
            }
            carryFlag = 0;
        }
        for (int j=max-1; j >= 0; --j) {
            digit *temp = createNode(num1[j], num2[i]);
            int v1 = temp->val1-'0';
            int v2 = temp->val2-'0';
            if (v1 == 0 || v2 == 0) {
                temp->fdig = '0';
                insert(&num[iter], temp);
                if (DEBUG) {
                    printf ("inside v1 or v2 0\n");
                    printf ("iter %d : ", iter);
                    displayNumber(&num[iter]);
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
                displayNumber(&num[iter]);
            }
        }
    }
    if (carryFlag) {
        digit *temp = createNode('\0', '\0');
        temp->fdig = (char)((carryFlag)+'0');
        insert (&num[leastLen-1], temp);
        carryFlag = 0;
    }

    fnum = makeString(&num[0], fnum);

    freeNum(&num[0]);

    for (int i=1; i < leastLen; ++i) {
        char *temp = (char*)calloc(numLen(&num[i])+2, sizeof(char));
        if (DEBUG) {
            printf ("num[%d] : ", i);
            displayNumber(&num[i]);
        }
        temp = makeString(&num[i], temp);
        if (DEBUG) {
            printf ("on i = %d, temp = %s\n", i, temp);
        }
        // char *n1, *n2;
        // equalise (fnum, temp, &n1, &n2);
        fnum = Add(fnum, temp, fnum);
        free (temp);
        freeNum(&num[i]);
    }
    free (num1);
    free (num2);
    fnum = stripZeroes(fnum);
    return fnum;
}
/*
char* Mod (char *num1, char *num2)
{
    char *n1 = num1;
    char *n2 = num2;
    char *tempn1 = (char*)calloc(1, sizeof(char));
    char *tempn2 = (char*)calloc(1, sizeof(char));
    int len2 = strlen(n2);
    char *val; // = (char*)calloc(1, sizeof(char));
    // [1000];

    while (intal_compare(n1, num2) > 0) {
        int len1 = strlen(n1);
        int power = (len1 - len2) - 1;

        if (power < 0) {
            n1 = intal_diff(n1, num2);
            // tempn1 = (char*)realloc(tempn1, strlen(n1));
            // strcpy (tempn1, n1);
            // free (n1);
            // n1 = tempn1;
            continue;
        } else if (power == 0) {
            n2 = num2;
        } else {
            n2 = num2;
            for (int i=0; i < power; ++i) {
                n2 = intal_multiply(n2, "10\0");
                // tempn2 = (char*)realloc(tempn2, strlen(n2));
                // strcpy (tempn2, n2);
                // free (n2);
                // n2 = tempn2;
            }
        }

        // strcpy (val, n2);
        // free (val);
        // val = (char*)malloc(sizeof(char)*strlen(n2));
        val = n2;
        // val = n2;

        while (intal_compare(n1, n2) > 0) {
            n2 = intal_add(n2, val);
            // tempn2 = (char*)realloc(tempn2, strlen(n2));
            // strcpy (tempn2, n2);
            // free (n2);
            // n2 = tempn2;
            if (intal_compare(n1, n2) == 0) {
                char *str = (char*)malloc(sizeof(char)*2);
                str[0] = '0';
                str[1] = '\0';
                return str;
            }
        }
        n2 = intal_diff (n2, val);
        // tempn2 = (char*)realloc(tempn2, strlen(n2));
        // strcpy (tempn2, n2);
        // free (n2);
        // n2 = tempn2;
        n1 = intal_diff (n1, n2);
        // tempn1 = (char*)realloc(tempn1, strlen(n1));
        // strcpy (tempn1, n1);
        // free (n1);
        // n1 = tempn1;
    }

    char *str = (char*)malloc(sizeof(char)*strlen(n1));
    strcpy (str, n1);
    free (tempn1);
    free (tempn2);
    return str;
}
*/
