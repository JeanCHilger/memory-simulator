#include <bits/stdc++.h>
#include "utils.h"

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
    int valid;

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
                int value = rand() % 127;
                this -> insertData(address, value);
            }
        }

        int getData(int address) {
            /*
             * Returns the data located at the given address.
             *
             * Parameters: addres -> int
             * Return    : value -> int
             * */

            int blockNumber = address / this -> BLOCK_SIZE;
            int offset = address % this -> BLOCK_SIZE;

            return this -> memory[blockNumber].values[offset].value;
        }

        void insertData(int address, int value) {
            /*
             * Inserts the given value in the given address.
             *
             * Parameters: addres -> int
             *             value  -> int
             * Return    : none
             * */

            int blockNumber = address / this -> BLOCK_SIZE;
            int offset = address % this -> BLOCK_SIZE;

            this -> memory[blockNumber].values[offset].value = value;
            this -> memory[blockNumber].blockNumber = blockNumber;
            this -> memory[blockNumber].values[offset].offset = offset;
        }

        Block getBlock(int address) {
            /*
             * Returns the block at given address.
             *
             * Parameters: address -> int
             * Return    : Block.
             * */

            int blockNumber = address / this -> BLOCK_SIZE;

            return this -> memory[blockNumber];

        }

        void showMemory() {
            /*
             * Prints the memory, displaying
             * addresses and respective data.
             *
             * Parameters: none
             * Return    : none
             * */

            printf(BOLD_WHITE "\n\t" END);
                printf(BOLD_YELLOW "\t\t        PRIMARY MEMORY" END);
                printf(BOLD_WHITE" \n" END);

            printf(BOLD_WHITE "\t+---------------------------------------------------------------+\n" END);

            printf(BOLD_WHITE "\t|" END);
                   printf(BOLD_WHITE "   Address   " END "|"
                           BOLD_WHITE "   BlockNumber   " END "|"
                           BOLD_WHITE "   Offset   " END "|"
                           BOLD_WHITE "       Value      " END);
                   printf(BOLD_WHITE"|\n" END);

            printf(BOLD_WHITE "\t|" END "---------------------------------------------------------------" BOLD_WHITE "|\n" END);

            for (int block=0; block < this -> BLOCKS; block++) {
                for (int cell=0; cell < this -> BLOCK_SIZE; cell++) {
                    printf(BOLD_WHITE "\t|" END);

                    printf("   ");
                    printDecAsBinary(this -> memory[block].blockNumber, 5);
                    printDecAsBinary(this -> memory[block].values[cell].offset, 2);
                    printf("   |");

                    printf("      ");
                    printDecAsBinary(this -> memory[block].blockNumber, 5);
                    printf("      |");

                    printf("     ");
                    printDecAsBinary(this -> memory[block].values[cell].offset, 2);
                    printf("     |");

                    printf("     ");
                    printDecAsBinary(this -> memory[block].values[cell].value, 8);
                    printf("     ");

                    printf(BOLD_WHITE "|\n" END);

                }

                if (block < this -> BLOCKS - 1) {
                    printf(BOLD_WHITE "\t|" END
                            BOLD_BLACK "---------------------------------------------------------------" END
                            BOLD_WHITE "|\n" END);
                }
            }

            printf(BOLD_WHITE "\t+---------------------------------------------------------------+\n" END);
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
            /*
             * Initializes the cache with zero
             * values and sets all valid flag to false.
             * */

            for (int row=0; row < this -> ROWS; row++) {
                this -> memory[row].rowNumber = row;
                this -> memory[row].valid = 0;
                this -> memory[row].tag = 0;
                for (int cell=0; cell < this -> ROW_SIZE; cell++) {
                    this -> memory[row].values[cell].value = 0;
                    this -> memory[row].values[cell].offset = cell;
                }
            }
        }

        bool isRowValid(int address) {
            /*
             * Returns whether or not the row at given
             * address is a valid row.
             *
             * Parameters: address -> int
             * Return    : bool
             * */

            int blockNumber = address / this -> ROW_SIZE;
            int rowNumber = blockNumber % this -> ROWS;

            return this -> memory[rowNumber].valid;
        }

        bool isDataIn(int address) {
            /*
             * Returns whether the given addres is within
             * cache memory or not.
             * If the row is not valid, returns false.
             *
             * Parameters: address -> int
             * Return    : bool
             * */

            if (this -> isRowValid(address)) {

                int blockNumber = address / this -> ROW_SIZE;
                int rowNumber = blockNumber % this -> ROWS;

                Row row = this -> memory[rowNumber];
                int tag = blockNumber - rowNumber;

                if (row.tag == tag) {
                    return true;
                }
            }

            return false;
        }

        int getData(int address) {
            /*
             * Returns the data located at the given address.
             *
             * Parameters: addres -> int
             * Return    : value -> int
             * */

            int blockNumber = address / this -> ROW_SIZE;
            int rowNumber = blockNumber % this -> ROWS;
            int offset = address % this -> ROW_SIZE;

            return this -> memory[rowNumber].values[offset].value;
        }

        void updateValue(int address, int value) {
            /*
             * Inserts the given value at the given
             * address.
             *
             * Parameters: address -> int
             *             value -> int
             * Return    : none
             * */

            int blockNumber = address / this -> ROW_SIZE;
            int rowNumber = blockNumber % this -> ROWS;
            int offset = address % this -> ROW_SIZE;

            this -> memory[rowNumber].values[offset].value = value;
        }

        void insertBlock(int address, Block block) {
            /*
             * Loads a whole block, and its values,
             * into a cache row.
             *
             * Parameters: addres -> int
             *             value  -> int
             * Return:     none
             * */

            int blockNumber = address / this -> ROW_SIZE;
            int rowNumber = blockNumber % this -> ROWS;

            for(int i=0; i < this -> ROW_SIZE; i++) {
                this -> memory[rowNumber].values[i].value = block.values[i].value;

                this -> memory[rowNumber].values[i].offset = block.values[i].offset;
            }

            this -> memory[rowNumber].rowNumber = rowNumber;
            this -> memory[rowNumber].tag = blockNumber / this -> ROWS;
            this -> memory[rowNumber].valid = 1;
        }

        void showMemory() {
            /*
             * Prints the memory, displaying
             * addresses and respective data.
             *
             * Parameters: none
             * Return    : none
             * */

            printf(BOLD_WHITE "\n\t " END);
                printf(BOLD_YELLOW "\t\t\t      CACHE MEMORY" END);
                printf(BOLD_WHITE" \n" END);

            printf(BOLD_WHITE "\t+----------------------------------------------------------------------+\n" END);

            printf(BOLD_WHITE "\t|" END);
                   printf(BOLD_WHITE "   Valid   " END "|"
                           BOLD_WHITE "   Tag   " END "|"
                           BOLD_WHITE "   RowNumber   " END  "|"
                           BOLD_WHITE "   Offset   " END "|"
                           BOLD_WHITE "       Value       " END);
                   printf(BOLD_WHITE"|\n" END);

            printf(BOLD_WHITE "\t|" END "----------------------------------------------------------------------" BOLD_WHITE "|\n" END);

            for (int row=0; row < this -> ROWS; row++) {
                for (int cell=0; cell < this -> ROW_SIZE; cell++) {
                    printf(BOLD_WHITE "\t|" END);

                    printf("     ");
                    printDecAsBinary(this -> memory[row].valid, 1);
                    printf("     |");

                    printf("   ");
                    printDecAsBinary(this -> memory[row].tag, 2);
                    printf("    |");

                    printf("      ");
                    printDecAsBinary(this -> memory[row].rowNumber, 3);
                    printf("      |");

                    printf("     ");
                    printDecAsBinary(this -> memory[row].values[cell].offset, 2);
                    printf("     |");

                    printf("      ");
                    printDecAsBinary(this -> memory[row].values[cell].value, 8);
                    printf("     ");

                    printf(BOLD_WHITE "|\n" END);

                }

                if (row < this -> ROWS - 1) {
                    printf(BOLD_WHITE "\t|" END
                            BOLD_BLACK "----------------------------------------------------------------------" END
                            BOLD_WHITE "|\n" END);
                }
            }


            printf(BOLD_WHITE "\t+----------------------------------------------------------------------+\n" END);
        }

    private:

        Row memory[8];

        const int ROWS = 8;
        const int ROW_SIZE = 4;
        const int CELLS = 32;
        const int PM_BLOCKS = 32;

};

class MemoryManager {

    /*
     * */

    public:

        MemoryManager() {

            this -> loadQuantity = 0;
            this -> storeQuantity = 0;

            this -> loadHits = 0;
            this -> loadMisses = 0;

            this -> storeHits = 0;
            this -> storeMisses = 0;
        }

        int getLoads() {
            /*
             * Returns the quantity of loads so far.
             * */

            return this -> loadQuantity;
        }

        int getStores() {
            /*
             * Returns the quantity of stores so far.
             * */

            return this -> storeQuantity;
        }

        int getTotalAccess() {
            /*
             * Returns the total quantity of
             * accessess so far.
             * */

            return this -> getLoads() + this -> getStores();
        }

        int getLoadHits() {
            /*
             * Returns the quantity of load hits so far.
             * */

            return this -> loadHits;
        }

        int getLoadMisses() {
            /*
             * Returns the quantity of load misses so far.
             * */

            return this -> loadMisses;
        }

        int getStoreHits() {
            /*
             * Returns the quantity of store hits so far.
             * */

            return this -> storeHits;
        }

        int getStoreMisses() {
            /*
             * Returns the quantity of store misses so far.
             * */

            return this -> storeMisses;
        }

        int load(int address) {
            /*
             * */

            this -> loadQuantity += 1;

            if (this -> cacheMemory.isDataIn(address)) {
                this -> loadHits += 1;

                return this -> cacheMemory.getData(address);

            } else {
                this -> loadMisses += 1;

                int value = this -> primaryMemory.getData(address);
                Block block = this -> primaryMemory.getBlock(address);

                this -> cacheMemory.insertBlock(address, block);

                return value;
            }
        }

        void store(int address, int value) {
            /*
             * */

            this -> storeQuantity += 1;

            if (this -> cacheMemory.isDataIn(address)) {
                this -> storeHits += 1;

                this -> cacheMemory.updateValue(address, value);

            } else {
                this -> storeMisses += 1;

                Block block = this -> primaryMemory.getBlock(address);
                this -> cacheMemory.insertBlock(address, block);
            }

            this -> primaryMemory.insertData(address, value);
        }

        void showCacheMemory() {
            /*
             * */

            this -> cacheMemory.showMemory();
        }

        void showPrimaryMemory() {
            /*
             * */

            this -> primaryMemory.showMemory();
        }

        void showStatistics() {
            /*
             * */

            printf(BOLD_WHITE "\t+---------------------------------------+" END);

            printf(BOLD_WHITE "\n\t|" END);
                printf(BOLD_YELLOW "\t\tSTATISTICS" END);
                printf(BOLD_WHITE "\t\t|\n" END);

            printf(BOLD_WHITE "\t|" END);
                printf("\t\t\t  ");
                printf(BOLD_WHITE "\t\t|\n" END);

            printf(BOLD_WHITE "\t| Access quantity " END
                    "..............."
                    BOLD_YELLOW " %*d "
                    BOLD_WHITE "|\n" END, 5, this -> getTotalAccess());

            printf(BOLD_WHITE "\t|"
                    BOLD_BLACK "---------------------------------------"
                    BOLD_WHITE "|\n" END);

            printf(BOLD_WHITE "\t| Load quantity " END
                    "................."
                    BOLD_YELLOW " %*d "
                    BOLD_WHITE "|\n" END, 5, this -> getLoads());

                printf(BOLD_WHITE "\t|" END NORMAL_GREEN "\tLoad hits " END
                        "..............."
                        NORMAL_GREEN " %*d "
                        BOLD_WHITE "|\n" END, 5, this -> getLoadHits());

                printf(BOLD_WHITE "\t|" END NORMAL_RED "\tLoad misses " END
                        "............."
                        NORMAL_RED " %*d "
                        BOLD_WHITE "|\n" END, 5, this -> getLoadMisses());

            printf(BOLD_WHITE "\t|"
                    BOLD_BLACK "---------------------------------------"
                    BOLD_WHITE "|\n" END);

            printf(BOLD_WHITE "\t| Store quantity " END
                    "................"
                    BOLD_YELLOW " %*d "
                    BOLD_WHITE "|\n" END, 5, this -> getStores());

                printf(BOLD_WHITE "\t|" END NORMAL_GREEN "\tStore hits " END
                        ".............."
                        NORMAL_GREEN " %*d "
                        BOLD_WHITE "|\n" END, 5, this -> getStoreHits());

                printf(BOLD_WHITE "\t|" END NORMAL_RED "\tStore misses " END
                        "............"
                        NORMAL_RED " %*d "
                        BOLD_WHITE "|\n" END, 5, this -> getStoreMisses());


            printf(BOLD_WHITE "\t+---------------------------------------+\n" END);
        }

    private:

        CacheMemory cacheMemory;
        PrimaryMemory primaryMemory;

        int loadQuantity;
        int storeQuantity;

        int loadMisses;
        int loadHits;
        int storeMisses;
        int storeHits;

};

void printMenu() {
    /*
     * Utility function to print the menu.
     * */


    #define MENU_TITLE_COLOR BOLD_BLUE
    #define NUMBER_COLOR MENU_TITLE_COLOR
    #define USER_SELECT_COLOR NUMBER_COLOR

    printf(BOLD_WHITE "\n\t+-----------------------------------+\n" END);

    printf(BOLD_WHITE "\t|" END);
        printf(MENU_TITLE_COLOR "\t\tMENU\t\t    " END);
        printf(BOLD_WHITE"|\n" END);

    printf(BOLD_WHITE "\t|\t\t\t    \t    |\n" END);

    printf(BOLD_WHITE "\t|" END);
        printf(NUMBER_COLOR " 1)" END " Read from memory ");
        printf(BOLD_WHITE"\t\t    |\n" END);

    printf(BOLD_WHITE "\t|" END);
        printf(NUMBER_COLOR " 2)" END " Write to memory ");
        printf(BOLD_WHITE"\t\t    |\n" END);

    printf(BOLD_WHITE "\t|" END);
        printf(NUMBER_COLOR " 3)" END " Show statistics ");
        printf(BOLD_WHITE"\t\t    |\n" END);

    printf(BOLD_WHITE "\t|" END);
        printf(NUMBER_COLOR " 4)" END " Show cache memory ");
        printf(BOLD_WHITE"\t\t    |\n" END);

    printf(BOLD_WHITE "\t|" END);
        printf(NUMBER_COLOR " 5)" END " Show primary memory ");
        printf(BOLD_WHITE"\t    |\n" END);

    printf(BOLD_WHITE "\t|" END);
        printf(NUMBER_COLOR " 0)" END " Exit            ");
        printf(BOLD_WHITE"\t\t    |\n" END);

    printf(BOLD_WHITE "\t+-----------------------------------+\n" END);

    printf("\n");

    printf(USER_SELECT_COLOR ">>> " END);

}

int main() {
    /*
     * Display and manages the menu.
     * */

    int opt;
    int address;
    int value;

    MemoryManager mm;

    mm.showCacheMemory();
    mm.showPrimaryMemory();
    printf("\n");

    while (true) {
        printMenu();
        scanf(" %d", &opt);

        switch (opt) {

            // Load from memory
            case 1:
                /*
                 * Show data at given address;
                 * Show block and row numbers;
                 * Whether hit or miss.
                 * */

                printf(BOLD_WHITE "Enter address: " END);
                scanf(" %d", &address);

                while (address > 127 || address < 0) {
                    printf(BOLD_RED "[ERROR]" END " Invalid address, choose in the range [0, 127].\n");
                    printf(BOLD_WHITE "Enter address: " END);
                    scanf(" %d", &address);
                }

                value = mm.load(address);
                printf("Read value: ");
                printDecAsBinary(value, 8);
                printf("\n");

                break;

            // Store in memory
            case 2:
                /*
                 * Informs if there was a hit or a miss
                 * for the cache access;
                 * Show block and row numbers;
                 * */

                printf(BOLD_WHITE "Enter address: " END);
                scanf(" %d", &address);

                while (address > 127 || address < 0) {
                    printf(BOLD_RED "[ERROR]" END " Invalid address, choose in the range [0, 127].\n");
                    printf(BOLD_WHITE "Enter address: " END);
                    scanf(" %d", &address);
                }

                printf(BOLD_WHITE "Enter value: " END);
                scanf(" %d", &value);

                mm.store(address, value);

                break;

            // Output statistics
            case 3:
                /*
                 * Present access quantity;
                 * How many loads;
                 *    Hits and misses on loads;
                 * How many stores;
                 *    Hits and misses on stores;
                 * */

                mm.showStatistics();

                break;

            // Show cache memory
            case 4:

                mm.showCacheMemory();

                break;

            // Show primary memory
            case 5:

                mm.showPrimaryMemory();

                break;

            // Exit
            case 0:
                printf(BOLD_BLUE "Goodbye!!\n" END);
                return 0;

                break;

            default:

                printf(BOLD_RED "[ERROR]" END " unknown option '%d'. Choose a valid one please:", opt);

                break;
        }

    }

    return 0;
}
