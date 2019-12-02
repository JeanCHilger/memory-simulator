#include <bits/stdc++.h>

struct cell {
    /*
     * Represents a cell memory.
     * */

    char offset[2];

    char value[8];
};

typedef struct cell Cell;

struct block {
    /*
     * Address = block + values[i].offset.
     * */

    char number[5];

    Cell values[4];
};

typedef struct block Block;

struct row {
    char number[3];

    Cell values[4];
};

typedef struct row Row;


class PrimaryMemory {
    
}

class CacheMemory {

}
