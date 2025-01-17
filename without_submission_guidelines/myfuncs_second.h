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

void reAssign (char **ptr1, char **ptr2)
{
    *ptr1 = (char*)realloc(*ptr1, strlen(*ptr2)+1);
    strncpy (*ptr1, *ptr2, strlen(*ptr2)+1);
    free (*ptr2);
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
                temp->fdig = (char)((carryFlag)+'0');
                carryFlag = 0;
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
        // prod = (char*)realloc(prod, strlen(fnum)+1);
        // strncpy(prod, fnum, strlen(fnum)+1);
        // free (fnum);
        reAssign(&prod, &fnum);

        free (temp);
        freeNum(&num[i]);
    }

    return prod;
}

char* Mod (const char *intal1, const char *intal2)
{
    int len = greatestLength(intal1, intal2);

    int l1 = strlen(intal1);
    int l2 = strlen(intal2);

    char *mod = (char*)calloc(l2+1, sizeof(char));

    if (Compare(intal1, intal2) == 0 || Compare("1", intal2) == 0 || Compare("0", intal1) == 0) {
        strncpy (mod, "0", 2);
    } else if (Compare(intal1, intal2) == -1) {
        strncpy (mod, intal1, strlen(intal1)+1);
    } else if (Compare("0", intal2) == 0) {
        int err_len = strlen("Divided by 0 error");
        mod = (char*)realloc(mod, err_len+1);
        strncpy (mod, "Divided by 0 error", err_len+1);
    }

    if (strlen(mod)) {
        return mod;
    }


    char *num1 = (char*)calloc(len+1, sizeof(char));
    char *num2 = (char*)calloc(len+1, sizeof(char));
    // num1[strlen(intal1)] = num2[strlen(intal2)] = '\0';
    strncpy (num1, intal1, strlen(intal1)+1);
    strncpy (num2, intal2, strlen(intal2)+1);

    stripZeroes(num1);
    stripZeroes(num2);

    if (Compare(num1, num2) < 0) {
        char *temp = num1;
        num1 = num2;
        num2 = temp;
    }

    prependZeroes(num1, num2);

    int len1 = strlen(num1); // l only since at this point the lengths are equal

    char *n1 = (char*)calloc(len1+1+1, sizeof(char)); // +1+1 in case of carry
    char *n2 = (char*)calloc(len1+1+1, sizeof(char));
    n1[len1+1] = n2[len1+1] = '\0';
    strncpy (n1, num1, len1+1);
    strncpy (n2, num2, len1+1);

    free (num1);
    free (num2);

    stripZeroes(n2); // since we are going to be working with no of digits

    // below, it is l2+1 since mod can at max be intal2

    int len2 = strlen(n2);

    num2 = (char*)calloc(len2+1, sizeof(char));
    strncpy (num2, n2, len2+1);

    while (Compare(n1, num2) > 0) {

        char *tempn1;
        char *tempn2;

        len1 = strlen(n1);
        int power = (len1 - len2) - 1;

        if (power < 0) {
            tempn1 = Diff(n1, num2);//, n1);
            // n1 = (char*)realloc(n1, strlen(tempn1)+1);
            // strncpy (n1, tempn1, strlen(tempn1)+1);
            // free (tempn1);
            reAssign(&n1, &tempn1);

            stripZeroes(n1);

            continue;
        } else if (power == 0) {
            strncpy (n2, num2, len2+1);
        } else {
            strncpy (n2, num2, len2+1);
            char *zeroes = (char*)calloc(power+1, sizeof(char));
            for (int i=0; i < power; ++i) {
                strcat(zeroes, "0");
            }
            strcat (n2, zeroes);
            free (zeroes);
            stripZeroes(n2);
        }

        char *val = (char*)calloc(strlen(n2)+1, sizeof(char));
        strncpy (val, n2, strlen(n2)+1);

        while (Compare(n1, n2) > 0) {
            tempn2 = Add(n2, val);//, n2);
            // n2 = (char*)realloc(n2, strlen(tempn2)+1);
            // strncpy (n2, tempn2, strlen(tempn2)+1);
            // free (tempn2);
            reAssign(&n2, &tempn2);

            stripZeroes(n2);

            if (Compare(n1, n2) == 0) {
                strncpy (mod, "0", 2);
                free (val);
                free (n1);
                free (n2);
                free (num2);
                return mod;
            }
        }
        tempn2 = Diff(n2, val);//, n2);
        // n2 = (char*)realloc(n2, strlen(tempn2)+1);
        // strncpy (n2, tempn2, strlen(tempn2)+1);
        // free (tempn2);
        reAssign(&n2, &tempn2);

        stripZeroes(n2);

        free (val);

        tempn1 = Diff(n1, n2);//, n1);
        // n1 = (char*)realloc(n1, strlen(tempn1)+1);
        // strncpy (n1, tempn1, strlen(tempn1)+1);
        // free (tempn1);
        reAssign(&n1, &tempn1);

        stripZeroes(n1);
    }

    strcpy (mod, n1);

    free (n1);
    free (n2);
    free (num2);

    return mod;
}

char* Pow (const char *intal1, unsigned int n)
{
    char *num = (char*)calloc(strlen(intal1)+1, sizeof(char));
    strncpy (num, intal1, strlen(intal1)+1);

    stripZeroes(num);

    char *res = (char*)calloc(1+1, sizeof(char)); // 2 for storing 1\0
    strncpy (res, "1", 2);

    while (n > 0) {
        char *tempres;
        char *tempnum;
        if (n & 1) {
            tempres = Multiply(res, num);//, res);
            reAssign(&res, &tempres);
            stripZeroes(res);
        }

        // num2 = divideByTwo(num2);
        // num2 = stripZeroes(num2);
        n = n/2;
        // n = n >> 1;
        tempnum = Multiply(num, num);//, num1);
        reAssign(&num, &tempnum);

        stripZeroes(num);
    }

    free (num);

    return res;
}

char* GCD (const char *intal1, const char *intal2)
{
    int len = greatestLength(intal1, intal2);

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

    char *res = (char*)calloc(len+1, sizeof(char));

    if (Compare("0", intal1) == 0) {
        strncpy (res, intal2, strlen(intal2)+1);
        free (n1);
        free (n2);
        return res;
    } else if (Compare("0", intal1) == 0 && Compare ("0", intal2) == 0) {
        strncpy (res, "0", 2);
        free (n1);
        free (n2);
        return res;
    } else {
        while (Compare("0", n1) != 0) {
            char *mod;
            mod = Mod(n2, n1);
            n2 = (char*)realloc(n2, strlen(n1)+1);
            strncpy (n2, n1, strlen(n1)+1);
            reAssign(&n1, &mod);
        }
    }

    strncpy (res, n2, strlen(n2));

    free (n1);
    free (n2);

    return res;
}

char* Fibonacci (unsigned int n)
{
    char *res1 = (char*)calloc(2, sizeof(char));
    char *res2 = (char*)calloc(2, sizeof(char));

    strncpy (res1, "0", 2);
    strncpy (res2, "1", 2);

    for (int i=0; i<n; ++i) {
        // char *tempres1;
        char *tempres2;
        tempres2 = Add(res2, res1);
        res1 = (char*)realloc(res1, strlen(res2)+1);
        strncpy (res1, res2, strlen(res2)+1);
        reAssign(&res2, &tempres2);
    }

    free (res2);

    return res1;
}

char* Fact (unsigned int n)
{
    char *res = (char*)calloc(1+1, sizeof(char));
    strncpy (res, "1", 2);

    if (n == 0 || n == 1) {
        return res;
    }

    char *numb = (char*)calloc(n, sizeof(char));

    int num = n;

    number temp;
    temp.head = NULL;

    while (num) {
        digit *dig = createNode();
        int r = num%10;
        dig->fdig = (char)(r+'0');
        num = num/10;
        insert (&temp, dig);
    }
    numb = makeString(temp, numb);
    freeNum(&temp);

    while (Compare("1", numb) != 0) {
        char *tempres;
        char *tempnumb;
        tempres = Multiply (numb, res);
        reAssign(&res, &tempres);
        tempnumb = Diff(numb, "1");
        reAssign(&numb, &tempnumb);
    }

    free (numb);

    return res;
}
/*
char *BinCoeff (unsigned int n, unsigned int k)
{

}
*/

int Max (char **arr, int n)
{
    int index = 0;
    char *max = (char*)calloc(strlen(arr[0])+1, sizeof(char));
    strncpy (max, arr[0], strlen(arr[0])+1);

    for (int i=1; i<n; ++i) {
        if (Compare(max, arr[i]) == -1) {
            max = (char*)realloc(max, strlen(arr[i])+1);
            strncpy (max, arr[i], strlen(arr[i])+1);
            index = i;
        }
    }
    free (max);
    return index;
}

int Min (char **arr, int n)
{
    int index = 0;
    char *min = (char*)calloc(strlen(arr[0])+1, sizeof(char));
    strncpy (min, arr[0], strlen(arr[0])+1);

    for (int i=1; i<n; ++i) {
        if (Compare(min, arr[i]) == 1) {
            min = (char*)realloc(min, strlen(arr[i])+1);
            strncpy (min, arr[i], strlen(arr[i])+1);
            index = i;
        }
    }
    free (min);
    return index;
}

int Search (char **arr, int n, const char *key)
{
    // char *keyDup = (char*)calloc(strlen(key)+1, sizeof(char));
    // strncpy (keyDup, key, strlen(key)+1);

    for (int i=0; i<n; ++i) {
        if (Compare(arr[i], key) == 0) {
            return i;
        }
    }
    return -1;
}

void heapify (char **arr, int n, int i)
{
    int max = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && Compare(arr[left], arr[max]) == 1) {
        max = left;
    }

    if (right < n && Compare(arr[right], arr[max]) == 1) {
        max = right;
    }

    if (max != i) {
        char *temp = (char*)calloc(strlen(arr[i])+1, sizeof(char));
        strcpy (temp, arr[i]);
        strcpy (arr[i], arr[max]);
        strcpy (arr[max], temp);
        free (temp);
        heapify (arr, n, max);
    }
}

void heapSort (char **arr, int n)
{
    for (int i = ((n/2) - 1); i>=0; --i) {
        heapify (arr, n, i);
    }

    for (int i=n-1; i>0; --i) {
        char *temp = (char*)calloc(strlen(arr[0])+1, sizeof(char));
        strcpy (temp, arr[0]);
        strcpy (arr[0], arr[i]);
        strcpy (arr[i], temp);
        free (temp);
        heapify (arr, i, 0);
    }
}

int binarySearch (char **arr, int n, const char *key)
{
    int up = n-1;
    int low = 0;
    // int mid = low + (up-low)/2;

    char *keyDup = (char*)calloc(strlen(key)+1, sizeof(char));
    strncpy (keyDup, key, strlen(key)+1);

    char *currNum =(char*)calloc(strlen(arr[mid])+1, sizeof(char));
    strncpy (currNum, arr[mid], strlen(arr[mid])+1);

    while (low <= up) {
        int mid = low + (up-low)/2;
        currNum = (char*)realloc(currNum, strlen(arr[mid])+1);
        strncpy (currNum, arr[mid], strlen(arr[mid])+1);

        if (Compare (keyDup, currNum) > 0) {
            low = mid+1;

        } else if (Compare (keyDup, currNum) < 0) {
            up = mid-1;

        } else {
            free (currNum);
            free (keyDup);
            return mid;
        }
    }
    free (currNum);
    free (keyDup);
    return -1;
}

char* greaterString (char *str1, char *str2)
{
    if (Compare(str1, str2) > 0) {
        return str1;
    } else
        return str2;
}

char* coinRow (char **arr, int n)
{
    int maxLen = strlen(arr[0]);
    for (int i=1; i<n; ++i) {
        if (strlen(arr[i]) > maxLen) {
            maxLen = strlen(arr[i]);
        }
    }

    char *dp0 = (char*)calloc(maxLen+1, sizeof(char));
    char *dp1 = (char*)calloc(maxLen+1, sizeof(char));
    char *dp2 = (char*)calloc(maxLen+1, sizeof(char));
    strncpy (dp0, "0", 2);
    strncpy (dp1, arr[0], strlen(arr[0])+1);

    for (int i=2; i<n+1; ++i) {
        char *tempadd;
        tempadd = Add (arr[i-1], dp0);
        char *tempmax;
        tempmax = greaterString (tempadd, dp1);
        strcpy (dp2, tempmax);
        free (tempadd);

        strcpy (dp0, dp1);
        strcpy (dp1, dp2);
    }

    char *res = (char*)calloc(strlen(dp2)+1, sizeof(char));
    strncpy (res, dp2, strlen(dp2)+1);

    free (dp0);
    free (dp1);
    free (dp2);

    return res;
}

int minimum (int a, int b)
{
    return a>b? b : a;
}

char* binomialCoefficient (unsigned int n, unsigned int k)
{
    char **C = (char**)calloc(k+1, sizeof(char*));
    for (int i=0; i<k+1; ++i) {
        C[i] = (char*)calloc(2, sizeof(char));
        strncpy (C[i], "0", 2);
    }

    strncpy (C[0], "1", 2);

    for (int i=1; i<=n; ++i) {
        for (int j=minimum(i, k); j>0; --j) {
            char *tempadd;
            tempadd = Add (C[j], C[j-1]);
            reAssign (&C[j], &tempadd);
        }
    }

    char *res = (char*)calloc(strlen(C[k])+1, sizeof(char));
    strncpy (res, C[k], strlen(C[k])+1);

    for (int i=0; i<k+1; ++i) {
		free (C[i]);
	}
	free (C);

    return res;

}
