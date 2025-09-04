/*
C Exercise 2 Starter
CS 325
Adele Bosma
*/

#include <stdio.h>
#include <stdlib.h> //for malloc
#include <string.h> //for string helpers
#include <math.h> //for pow(x,y) where x is raised to y power

static int charToDigit(char);
static char digitToChar(int);
static int stringToInt(char*);
static char* intToBinary(int);
static char* breakBefore(char[], char);
static char* breakAfter(char[], char);

int main(void){
    char theString[] = "22534\0"; 

    long stringConversion = strtol(theString, NULL, 10);
    int num = (int)stringConversion;
    printf("the number is %d\n", num);
    
    int myNum = stringToInt(theString);
    printf("my function gave %d\n", myNum);

    char* binary = intToBinary(num);
    printf("%s\n", binary);
    free(binary);

    const char ultimateString[] = "According to all known laws of aviation, there is no way a bee should be able to fly. Its wings are too small to get its fat little body off the ground. The bee, of course, flies anyway because bees don't care what humans think is impossible. Yellow, black. Yellow, black. Yellow, black. Yellow, black. Ooh, black and yellow! Let's shake it up a little. Barry! Breakfast is ready!";

    char* toe = breakAfter(ultimateString, '.');
    printf("Print After:%s\n", toe);
    free(toe);
    toe = NULL;

    char* toe2 = breakBefore(ultimateString, '.');
    printf("Print Before: %s", toe2);
    free(toe2);
    toe2 = NULL;

    return 0;
}

//converts a 0-9 character to an integer
static int charToDigit(char digit){
    if(digit < '0' || digit >'9'){
        return -1;
    }
    return digit - '0';
}

//converts a 0-9 digit to a character
static char digitToChar(int num){
    if(num < 0 || num > 9){
        return '\0';
    }
    return (char)num + '0';
}

/*
Converts a string containing digits
to an integer representation
"1234" should become 1234.
*/
static int stringToInt(char* string){
    unsigned int len = strlen(string);
    int sum = 0;
    int power = 0;

    for(int i = len-1; i > -1; i--) {
        sum += charToDigit(string[i]) * floor(pow(10, power++));
    }
    return sum;
}

static char* intToBinary(int num){
    char *result = (char*)malloc(16*sizeof(char));
    //set each element in result to '0'

    for (int i = 0; i < 16; i++) {
        result[i] = '0';
    }

    for (int i = 14; i >= 0; i--) {
        if (num % 2 == 1) {
            result[i] = '1';
        }
        num = floor(num / 2);
    }

    result[15] = '\0';
    return result;
}


static char* breakBefore(char string[], char breakChar){
    size_t breakHere = strcspn(string, &breakChar);
    if (breakHere == strlen(string)) {
        return NULL;
    }

    char* daString  = (char*)malloc((breakHere+1)*sizeof(char));
    if (!daString) {
        free(daString);
        return NULL;
    }

    for (int i = 0; i < breakHere; i++) {
        daString[i] = string[i];
    }
    daString[breakHere] = '\0';
    return daString;
}



static char* breakAfter(char string[], char breakChar){
    size_t breakHere = strcspn(string, &breakChar);
    size_t size = strlen(string);
    if (breakHere == strlen(string)) {
        return NULL;
    }

    char* daString  = (char*)malloc(((size - breakHere)+1)*sizeof(char));
    if (!daString) {
        free(daString);
        return NULL;
    }

    for (int i = breakHere+1; i < size; i++) {
        daString[i-(breakHere+1)] = string[i];
    }
    daString[size-breakHere] = '\0';
    return daString;
}








