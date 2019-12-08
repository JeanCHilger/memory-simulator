#include <bits/stdc++.h>
#include "utils.h"

using namespace std;

char *decimalToBinary (int value) {
    /*
     * */

    char *res = (char *)malloc(9 * sizeof(char));;
    int rem;

    int length = value > 1 ? ceil(log2(value)) : 1;
    res[length] = 0;

    int i = length - 1;
    do {
        rem = value % 2;
        value =  value / 2;
        res[i] = (char) rem + 48;
        i--;

    } while (i >= 0);

    return res;
}

void printBinary (int value) {
    /*
     * */

    char *bin = decimalToBinary(value);

    for (int i = 0; i < (int) sizeof(bin); i++) {
        printf("%c", bin[i]);
    }

    printf("\n");
}
