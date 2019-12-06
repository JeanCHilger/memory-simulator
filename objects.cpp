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

    char blockNumber[5];

    Cell values[4];
};

typedef struct block Block;

struct row {
    /*
     * Address = tag + number + values[i].offset.
     * */

    char tag[2];
    char rowNumber[3];

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

        char * getData(int address) {
            /*
             * Returns the data located at the given address.
             *
             * Parameters: addres -> int
             * Return    : value -> char *
             * */

            int blockNumber = address % this -> BLOCKS;
            int offset = address % this -> BLOCK_SIZE;

            //Block block = this -> memory[blockNumber];
            //Cell cell = block.values[offset];

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
            int offset = address % this -> BLOCK_SIZE;

            strncpy(this -> memory[blockNumber].values[offset].value, 
                    "0000000", 
                    sizeof(this -> memory[blockNumber].values[offset].value) - 1);

            this -> memory[blockNumber].values[offset].value[sizeof(this -> memory[blockNumber].values[offset].value) - 1] = 0;
        }

        void printAllData () {
            for (int i=0; i < 128; i++) {
                printf("at %d -> %s\n", i, this -> getData(i));
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
     * */

    public:

        CacheMemory () {

        }

        char * getData(int address) {
            /*
             * Returns the data located at the given address.
             *
             * Parameters: addres -> int
             * Return    : value -> char *
             * */

            int blockNumber = address % this -> PM_BLOCKS;
            int rowNumber = blockNumber % this -> ROWS;
            int offset = address % this -> ROW_SIZE;

            //Block block = this -> memory[blockNumber];
            //Cell cell = block.values[offset];

            Row row = this -> memory[rowNumber];
            int tag = blockNumber - rowNumber;

            // hit
            if (row.tag == "10"/*decimalToBinary(tag)*/) {
                return this -> memory[rowNumber].values[offset];
            // miss
            } else {

            }
            
         }


    private:
        Row memory[8];
        const int ROWS = 8;
        const int ROW_SIZE = 4;
        const int CELLS = 32;
        const int PM_BLOCKS = 32;

};

int main () {
    PrimaryMemory mp;

    mp.printAllData();

    return 0;
}
