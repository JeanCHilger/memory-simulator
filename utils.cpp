#include <bits/stdc++.h>
#include "utils.h"

using namespace std;

char *decimalToBinary (int value, int binLength=false) {
    /*
     * */

    char *res = (char *)malloc(9 * sizeof(char));;
    int rem;
    int length;

    if (!binLength) {
        length = value > 1 ? ceil(log2(value)) : 1;

    } else {
        length = binLength;
    }

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

void printDecAsBinary (int value, int length=false) {
    /*
     * */

    char *bin = decimalToBinary(value, length);

    for (int i = 0; i < (int) sizeof(bin); i++) {
        printf(BOLD_WHITE "%c" END, bin[i]);
    }

    //printf("\n");
}

//void printBinary
