#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

typedef struct digit {
    char fdig;
    struct digit *next;
} digit;

typedef struct number {
    digit *head;
} number;

void freeNum (number *num);
void displayNumber (number num);
void freeNum (number *num);
void insert (number *num, digit *dig);
int numLen (number num);
digit* createNode();
char* makeString(number num, char *str);
int greatestLength (const char *str1, const char *str2);
void prependZeroes (char *num1, char *num2);
void stripZeroes (char *str);
char *Add (const char *, const char *);//, char *);
char *Diff (const char *, const char *);//, char *);
int Compare (const char *, const char *);
char *Multiply (const char *, const char *);


void freeNum (number *num)
{
    digit *temp;
    while (num->head) {
        temp = num->head;
        num->head = temp->next;
        free (temp);
    }
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

int numLen (number num)
{
    digit *temp = num.head;
    int count = 0;
    while (temp) {
        ++count;
        temp = temp->next;
    }
    return count;
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

int greatestLength (const char *str1, const char *str2)
{
    int l1 = strlen(str1);
    int l2 = strlen(str2);
    return (l1 > l2)? l1 : l2;
}

void prependZeroes (char *num1, char *num2)
{
    int l1 = strlen(num1);
    int l2 = strlen(num2);

    int l = greatestLength(num1, num2);

    char *z1 = (char*)calloc(l+1, sizeof(char)); // +1 for null char
    char *z2 = (char*)calloc(l+1, sizeof(char));
    z1[l] = z2[l] = '\0';
    memset (z1, '0', l);
    memset (z2, '0', l);

    char *z1_ptr = z1;
    char *z2_ptr = z2;

    if (l1 > l2) {
        for (int i=0; i < l1-l2; ++i) {
            ++z2_ptr;
        }
        strncpy (z2_ptr, num2, l2);
        strncpy (num2, z2, l+1);
        // num2[l] = '\0';
        // num1[l1] = '\0';
    } else if (l1 < l2) {
        for (int i=0; i < l2-l1; ++i) {
            ++z1_ptr;
        }
        strncpy (z1_ptr, num1, l1);
        strncpy (num1, z1, l+1);
        // num1[l] = '\0';
        // num2[l2] = '\0';
    }

    free (z1);
    free (z2);
    return;
}

void stripZeroes(char *str)
{
    int l = strlen(str);

    char *str2 = (char*)calloc(l+1, sizeof(char));
    char *str2_ptr = str2;
    str2[l] = '\0';
    strncpy (str2, str, l);

    while (str2_ptr[0] == '0') {
        ++str2_ptr;
    }
    if (strlen(str2_ptr) == 0) {
        --str2_ptr;
    }
    strncpy (str, str2_ptr, strlen(str2_ptr)+1);

    free (str2);
}

char* Add (const char *intal1, const char *intal2)//, char *str)
{
    int len = greatestLength (intal1, intal2);

    int l1 = strlen(intal1);
    int l2 = strlen(intal2);

    char *num1 = (char*)calloc(len+1, sizeof(char));
    char *num2 = (char*)calloc(len+1, sizeof(char));
    // num1[strlen(intal1)] = num2[strlen(intal2)] = '\0';
    strncpy (num1, intal1, strlen(intal1)+1);
    strncpy (num2, intal2, strlen(intal2)+1);

    stripZeroes(num1);
    stripZeroes(num2);
    prependZeroes(num1, num2);  // at this point all zeroes are stripped and no
    // leading zeroes can possibly be added, hence no stripZeroes call
    // in intal_add

    int l = strlen(num1); // l only since at this point the lengths are equal

    char *n1 = (char*)calloc(l+1+1, sizeof(char)); // +1+1 in case of carry
    char *n2 = (char*)calloc(l+1+1, sizeof(char));
    n1[l+1] = n2[l+1] = '\0';
    strncpy (n1, num1, l+1);
    strncpy (n2, num2, l+1);

    free (num1);    // no use of num1 and num2 now, they're just taking
    free (num2);    // up more space than needed.

    if (DEBUG) {
        printf ("ADD:\n");
        printf ("1 : %s\n", n1);
        printf ("2 : %s\n", n2);
        printf ("END ADD.\n");
    }

    number num;
    num.head = NULL;

    int carryFlag = 0;

    for (int i=l-1; i >= 0; --i) {
        digit *temp = createNode();
        int v1 = n1[i]-'0';
        if (carryFlag)
            v1 += 1;
        int v2 = n2[i]-'0';
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

    // printf ("%d\n", numLen(num));

    char *str = (char*)calloc(numLen(num)+1, sizeof(char));
    str = makeString(num, str);

    freeNum(&num);
    free (n1);
    free (n2);

    return str;
}

char* Diff (const char *intal1, const char *intal2)//, char *str)
{
    int len = greatestLength (intal1, intal2);

    int l1 = strlen(intal1);
    int l2 = strlen(intal2);

    char *num1 = (char*)calloc(len+1, sizeof(char));
    char *num2 = (char*)calloc(len+1, sizeof(char));
    // num1[strlen(intal1)] = num2[strlen(intal2)] = '\0';
    strncpy (num1, intal1, strlen(intal1)+1);
    strncpy (num2, intal2, strlen(intal2)+1);

    stripZeroes(num1);
    stripZeroes(num2);
    prependZeroes(num1, num2);

    int l = strlen(num1); // l only since at this point the lengths are equal

    char *n1 = (char*)calloc(l+1+1, sizeof(char)); // +1+1 in case of carry
    char *n2 = (char*)calloc(l+1+1, sizeof(char));
    n1[l+1] = n2[l+1] = '\0';
    strncpy (n1, num1, l+1);
    strncpy (n2, num2, l+1);

    free (num1);
    free (num2);

    if (Compare(n1, n2) < 0) {
        char *temp = n1;
        n1 = n2;
        n2 = temp;
    }

    if (DEBUG) {
        printf ("DIFF:\n");
        printf ("1 : %s\n", n1);
        printf ("2 : %s\n", n2);
        printf ("END DIFF.\n");
    }

    number num;
    num.head = NULL;
    int carryFlag = 0;

    for (int i=l-1; i >= 0; --i) {
        digit *temp = createNode();
        int v1 = n1[i]-'0';
        if (carryFlag)
            v1 -= 1;
        int v2 = n2[i]-'0';
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

    char *str = (char*)calloc(numLen(num)+1, sizeof(char));
    str = makeString(num, str);

    freeNum(&num);
    free (n1);
    free (n2);

    return str;
}

int Compare (const char *intal1, const char *intal2)
{
    int len = greatestLength (intal1, intal2);

    int l1 = strlen(intal1);
    int l2 = strlen(intal2);

    char *num1 = (char*)calloc(len+1, sizeof(char));
    char *num2 = (char*)calloc(len+1, sizeof(char));

    strncpy (num1, intal1, l1+1);
    strncpy (num2, intal2, l2+1);

    stripZeroes(num1);
    stripZeroes(num2);
    prependZeroes(num1, num2);

    int l = strlen(num1); // l only since at this point the lengths are equal

    char *n1 = (char*)calloc(l+1+1, sizeof(char)); // +1+1 in case of carry
    char *n2 = (char*)calloc(l+1+1, sizeof(char));
    n1[l+1] = n2[l+1] = '\0';
    strncpy (n1, num1, l+1);
    strncpy (n2, num2, l+1);

    free (num1);
    free (num2);

    int retVal = 0;

    for (int i=0; i < l; i++) {
        if (n1[i] < n2[i]) {
            retVal = -1;
            break;
        } else if (n1[i] > n2[i]) {
            retVal = 1;
            break;
        } else {
            continue;
        }
    }

    free (n1);
    free (n2);

    return retVal;
}

char* Multiply (const char *intal1, const char *intal2)//, char *fnum)
{
    int len = greatestLength (intal1, intal2);

    int l1 = strlen(intal1);
    int l2 = strlen(intal2);

    char *num1 = (char*)calloc(len+1, sizeof(char));
    char *num2 = (char*)calloc(len+1, sizeof(char));

    strncpy (num1, intal1, l1+1);
    strncpy (num2, intal2, l2+1);

    stripZeroes(num1);
    stripZeroes(num2);

    if (Compare(num1, num2) < 0) {
        char *temp = num1;
        num1 = num2;
        num2 = temp;
    }

    int leastLen = strlen(num2);

    prependZeroes(num1, num2);

    int l = strlen(num1); // l only since at this point the lengths are equal

    char *n1 = (char*)calloc(l+1+1, sizeof(char)); // +1+1 in case of carry
    char *n2 = (char*)calloc(l+1+1, sizeof(char));
    // n1[l+1] = n2[l+1] = '\0';
    strncpy (n1, num1, l+1);
    strncpy (n2, num2, l+1);

    free (num1);
    free (num2);

    number num[leastLen];

    for (int i=0; i<leastLen; ++i) {

        num[i].head = NULL;

        for (int j=0; j<i; ++j) {               // appending zeroes
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

    for (int iter=0, i = l-1; iter < leastLen; ++iter, --i) {
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
        for (int j=l-1; j >= 0; --j) {
            digit *temp = createNode();
            int v1 = n1[j]-'0';
            int v2 = n2[i]-'0';
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

    free (n1);
    free (n2);

    char *prod = (char*)calloc(numLen(num[0])+1, sizeof(char));
    prod = makeString(num[0], prod);

    freeNum(&num[0]);

    for (int i=1; i < leastLen; ++i) {
        char *fnum;
        char *temp = (char*)calloc(numLen(num[i])+1, sizeof(char));

        if (DEBUG) {
            printf ("num[%d] : ", i);
            displayNumber(num[i]);
        }

        temp = makeString(num[i], temp);

        if (DEBUG) {
            printf ("on i = %d, temp = %s\n", i, temp);
        }

        fnum = Add(prod, temp);//, fnum);
        prod = (char*)realloc(prod, strlen(fnum)+1);
        strncpy(prod, fnum, strlen(fnum)+1);

        free (temp);
        free (fnum);
        freeNum(&num[i]);
    }

    return prod;
}
