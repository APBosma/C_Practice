#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

static char* removeExtra(char* string);
static char* removeComments(char* string);
static char* lineType(char* line);
static char* binary15Rep(int number);
static int charToDigit(char);
static int stringToInt(char*);

const int BINARY_SIZE = 15;

int main(void) {
    FILE* inputFile = NULL; // Dropping the null declarations just for you Bowe :)
    FILE* outputFile = NULL;
    const int bufferSize = 256;
    char inputFileName[bufferSize];
    char outputFileName[bufferSize];

    printf("Please enter an input filename: ");
    fgets(inputFileName, bufferSize, stdin);
    inputFileName[strcspn(inputFileName, "\n")] = 0;

    printf("Please enter an output filename: ");
    fgets(outputFileName, bufferSize, stdin);
    outputFileName[strcspn(outputFileName, "\n")] = 0;

    inputFile = fopen(inputFileName, "r");
    outputFile = fopen(outputFileName, "w");

    if(inputFile == NULL){
        puts("Error opening input file");
    }
    else if(outputFile == NULL){
        puts("Error opening output file");
    }
    else{
        char buffer[bufferSize];

        while(fgets(buffer, bufferSize, inputFile) != NULL){
            if (buffer[0] != '\n') {
                buffer[strcspn(buffer, "\r\n")] = 0; //remove carriage return, line feed
                char* extraRemoved = removeExtra(buffer);
                char* commentsRemoved = removeComments(extraRemoved);
                if (strlen(commentsRemoved) > 0) {
                    char* type = lineType(commentsRemoved);
                    if (type == "Error") {
                        puts("ERROR");
                    }
                    else {
                        fprintf(outputFile, "%s\n", type);
                    }
                    free(type);
                    type = NULL;
                }
                // Finish them
                free(commentsRemoved);
                commentsRemoved = NULL;
                free(extraRemoved);
                extraRemoved = NULL;
            }
        }
        //Close the file
        fclose(inputFile);
        fclose(outputFile);
    }
    return 0;
}

/*
 Removes any starting spaces
 and tabs
 Question 1
 */
static char* removeExtra(char* string) {
    size_t position;
    size_t len = strlen(string);
    for (position = 0; position < len; position++) {
        if (string[position] != '\t' && string[position] != ' ') {
            break;
        }
    }
    if (position == len) {
        return NULL;
    }
    char* newString = (char*)malloc(sizeof(char)*(len-position+1));
    if (!newString) {
        return NULL;
    }
    for (size_t j = 0; j < len; j++) {
        newString[j] = string[j+position];
    }
    newString[len] = '\0';
    return newString;
}

/*
 Removes any comments
 Question 2
 */
static char* removeComments(char* string) {
    size_t position;
    size_t len = strlen(string);

    for (position = 0; position < len; position++) {
        if (string[position] == '/' && string[position + 1] == '/') {
            break;
        }
    }
    if (position == len) {
        return string;
    }
    char* newString = (char*)malloc(sizeof(char)*(position+1));
    if (!newString) {
        return NULL;
    }
    for (size_t j = 0; j < position; j++) {
        newString[j] = string[j];
    }
    newString[position] = '\0';
    return newString;
}

/*
Converts a string containing digits
to an integer representation
"1234" should become 1234.
*/
static int stringToInt(char* string){
    int len = strlen(string);
    int sum = 0;
    int power = 0;

    for(int i = len-1; i > -1; i--) {
        sum += charToDigit(string[i]) * floor(pow(10, power++));
    }
    return sum;
}

//converts a 0-9 character to an integer
static int charToDigit(char digit){
    if(digit < '0' || digit >'9'){
        return -1;
    }
    return digit - '0';
}

/*
 Just using this to keep the lineType function relatively clean
 */
static char* binary15Rep(int number) {
    char* result = (char*)malloc(sizeof(char)*(BINARY_SIZE+1));

    for (int i = 0; i < BINARY_SIZE; i++) {
        result[i] = '0';
    }
    result[BINARY_SIZE] = '\0';

    for (int i = BINARY_SIZE-1; i >= 0; i--) {
        if (number % 2 == 1) {
            result[i] = '1';
        }
        number = floor(number / 2);
    }
    return result;
}

/*
 Returns line type
 Question 3
 Used https://stackoverflow.com/questions/17292545/how-to-check-if-the-input-is-a-number-or-not-in-c to find
 the isdigit functions. I figured since I've seen it in other languages, it probably existed in C too.
 Used in line 159.
 */
static char* lineType(char* line) {
    const char colon[2] = ";\0", equals[2] = "=\0";
    size_t semiCheck, equalCheck, size = 0;

    switch (line[0]) {
        case '\n':
            return "Empty";
        case '/':
            if (line[1] == '/') {
                return "Comment";
            }
        case '@':
            for (size_t i = 1; i < strlen(line); i++) {
                if (!isdigit(line[i])) {
                    break;
                }
                size++;
            }
            char* removedA = malloc(sizeof(char) * (size+1));
            for (size_t i = 1; i <= size; i++) {
                removedA[i-1] = line[i];
            }
            removedA[size] = '\0';
            char* answer = binary15Rep(stringToInt(removedA));
            return answer;
        // C instructions
        case 'A':
            semiCheck = strcspn(line, colon);
            equalCheck = strcspn(line, equals);
            if (semiCheck < strlen(line) || equalCheck < strlen(line)) {
                if (semiCheck < equalCheck) {
                    return "Jump";
                }
                return "Destination";
            }
        case 'M':
            semiCheck = strcspn(line, colon);
            equalCheck = strcspn(line, equals);
            if (semiCheck < strlen(line) || equalCheck < strlen(line)) {
                if (semiCheck < equalCheck) {
                    return "Jump";
                }
                return "Destination";
            }
        case 'D':
            semiCheck = strcspn(line, colon);
            equalCheck = strcspn(line, equals);
            if (semiCheck < strlen(line) || equalCheck < strlen(line)) {
                if (semiCheck < equalCheck) {
                    return "Jump";
                }
                return "Destination";
            }
        case '0':
            semiCheck = strcspn(line, colon);
            equalCheck = strcspn(line, equals);
            if (semiCheck < strlen(line) || equalCheck < strlen(line)) {
                if (semiCheck < equalCheck) {
                    return "Jump";
                }
                return "Destination";
            }
        case '1':
            semiCheck = strcspn(line, colon);
            equalCheck = strcspn(line, equals);
            if (semiCheck < strlen(line) || equalCheck < strlen(line)) {
                if (semiCheck < equalCheck) {
                    return "Jump";
                }
                return "Destination";
            }
        case '-':
            semiCheck = strcspn(line, colon);
            equalCheck = strcspn(line, equals);
            if (semiCheck < strlen(line) || equalCheck < strlen(line)) {
                if (semiCheck < equalCheck) {
                    return "Jump";
                }
                return "Destination";
            }
        case '!':
            semiCheck = strcspn(line, colon);
            equalCheck = strcspn(line, equals);
            if (semiCheck < strlen(line) || equalCheck < strlen(line)) {
                if (semiCheck < equalCheck) {
                    return "Jump";
                }
                return "Destination";
            }
        default:
            return "Error";
        return "Error";
    }
}