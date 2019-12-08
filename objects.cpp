#include <bits/stdc++.h>

#define BOLD_BLACK "\e[1;90m"
#define BOLD_WHITE "\e[1;37m"

#define BOLD_RED "\e[1;31m"
#define BOLD_GREEN "\e[1;92m"
#define BOLD_YELLOW "\e[1;93m"
#define BOLD_BLUE "\e[1;94m"

#define END "\e[0m"

// printf(COLOR"stuff"END);

struct cell {
    /*
     * Represents a cell memory.
     * */

    int offset;

    int value;
};

typedef struct cell Cell;

struct block {
    /*
     * Address = block + values[i].offset.
     * */

    int blockNumber;

    Cell values[4];
};

typedef struct block Block;

struct row {
    /*
     * Address = tag + number + values[i].offset.
     * */

    int tag;
    int rowNumber;

    Cell values[4];
};

typedef struct row Row;

class PrimaryMemory {

    /*
     * Represents a primary memory.
     * Stores the data.
     * */

    public:

        PrimaryMemory () {
            /*
             * Initializes the memory with
             * random values.
             * */

            for (int address=0; address < this -> CELLS; address++) {
                this -> insertData(address, rand() % 127);
            }

        }

        int getData(int address) {
            /*
             * Returns the data located at the given address.
             *
             * Parameters: addres -> int
             * Return    : value -> int
             * */

            int blockNumber = address % this -> BLOCKS;
            int offset = address / this -> BLOCKS;

            return this -> memory[blockNumber].values[offset].value;
        }

        void insertData(int address, int value) {
            /*
             * Inserts the given value in the given address.
             *
             * Parameters: addres -> int
             *             value  -> int
             * Return:     none
             * */

            int blockNumber = address % this -> BLOCKS;
            int offset = address / this -> BLOCKS;

            this -> memory[blockNumber].values[offset].value = value;
        }

        void printAllData () {
            for (int i=0; i < 128; i++) {
                printf("at %d -> %d\n", i, this -> getData(i));
            }
        }

    private:

        Block memory[32];

        const int BLOCKS = 32;
        const int BLOCK_SIZE = 4;
        const int CELLS = 128;

};

class CacheMemory {

    /*
     * Represents the cache memory.
     * */

    public:

        CacheMemory () {

        }

        bool isDataIn (int address) {
            /*
             * Returns whether the given addres is within
             * cache memory or not.
             *
             * Parameters: address -> int
             * Return    : bool
             * */

            int blockNumber = address % this -> PM_BLOCKS;
            int rowNumber = blockNumber % this -> ROWS;
            int offset = address % this -> ROW_SIZE;

            Row row = this -> memory[rowNumber];
            int tag = blockNumber - rowNumber;

            if (row.tag == tag) {
                return true;

            } else {
                return false;
            }
        }

        int getData(int address) {
            /*
             * Returns the data located at the given address.
             *
             * Parameters: addres -> int
             * Return    : value -> int
             * */

            int blockNumber = address % this -> PM_BLOCKS;
            int rowNumber = blockNumber % this -> ROWS;
            int offset = address % this -> ROW_SIZE;

            return this -> memory[rowNumber].values[offset].value;
        }

        void insertData(int address, int value) {
            /*
             * Inserts the given value in the given address.
             *
             * Parameters: addres -> int
             *             value  -> int
             * Return:     none
             * */

            int blockNumber = address % this -> PM_BLOCKS;
            int rowNumber = blockNumber % this -> ROWS;
            int offset = address % this -> ROW_SIZE;

            this -> memory[rowNumber].values[offset].value = value;
        }

    private:

        Row memory[8];

        const int ROWS = 8;
        const int ROW_SIZE = 4;
        const int CELLS = 32;
        const int PM_BLOCKS = 32;

};
