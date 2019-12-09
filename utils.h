#ifndef __UTILS431__
#define __UTILS431__

#define BOLD_BLACK "\e[1;90m"
#define BOLD_WHITE "\e[1;37m"

#define BOLD_RED "\e[1;91m"
#define NORMAL_RED "\e[91m"
#define BOLD_GREEN "\e[1;92m"
#define NORMAL_GREEN "\e[92m"
#define BOLD_YELLOW "\e[1;93m"
#define BOLD_BLUE "\e[1;94m"

#define END "\e[0m"

// converts a decimal number into a binary number
char *decimalToBinary (int , int );

//prints the given decimal value as a binary number
void printDecAsBinary (int , int );

#endif
