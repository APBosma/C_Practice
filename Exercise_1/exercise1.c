//
// Created by Emilio on 8/20/2025.
//
// Used W3 for all syntax and Sly told me about the strcspn when I  was helping him with his code.
// I just noticed it and asked him about it. Anything from your code directly is labeled as well with a comment,
// but I think it was just a function and clearing the buffer. I got strLng or whatever from Geeks4Geeks when
// my boyfriend pointed out that I was returning the size of the array holding the string,
// not the string itself and I was trying to find a way to solve that problem.
#include <ctype.h>
#include <stdio.h>    // for printf
#include <stdlib.h>   // for rand
#include <string.h>   // for strcspn (strip newline)
#include <stdbool.h>
#include <time.h>     // for time(), seeding rand()

void songs();
void fizzBuzz(int countTo);
void guessingGame();
void arrayOutput(int array[], size_t size);
void arrayFlip(int array[], size_t size);
void printInstruction(char string[], size_t size);
void isItThere(char string[], size_t size);
void breakBefore(char string[], char breakPoint, size_t size);
void breakAfter(char string[], char breakPoint, size_t size);\
void arrayRepeat(int array[], size_t size);
void arrayInputRepeat(int array[], size_t size);
int arraySum(int array[], size_t size);
static int getRandom();
float arrayMean(int array[], size_t size);
bool inArray(int array[], int number, int numDone);

int main() {
    int countTo;
    int ch;
    srand((unsigned)time(NULL));

    printf("Question 1:\n");
    songs();
    printf("\n\n");

    printf("Question 2:\n");
    printf("Please enter a number: ");
    scanf("%d",&countTo);
    fizzBuzz(countTo);
    printf("\n\n");

    // printf("Question 3:\n");
    // guessingGame();
    // printf("\n\n");

    printf("Question 4:\n");
    int fourArray[5] = {1,2,3,4,5};
    arrayOutput(fourArray, strlen(fourArray));
    printf("\n\n");

    printf("Question 5:\n");
    int fiveArray[5] = {1,2,3,4,5};
    printf("%d", arraySum(fiveArray, strlen(fiveArray)));
    printf("\n\n");

    printf("Question 6:\n");
    int sixArray[5] = {3,2,3,4,20};
    printf("%f", arrayMean(sixArray, strlen(sixArray)));
    printf("\n\n");

    printf("Question 7:\n");
    int sevenArray[5] = {1,2,3,4,5};
    arrayFlip(sevenArray, strlen(sevenArray));
    for (int i = 0; i < strlen(sevenArray); i++) {
        printf("%d%c", sevenArray[i], '\n');
    }
    printf("\n\n");

    printf("Question 8:\n");
    char string[50];
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Please enter a string with no spaces: ");
    scanf("%s", &string);
    printInstruction(string, strlen(string));
    printf("\n\n");

    printf("Question 9:\n");
    char stringString[50];
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Please enter a string with no spaces: ");
    scanf("%s", &stringString);
    isItThere(stringString, strlen(stringString));
    printf("\n\n");

    printf("Question 10:\n");
    char stringStringString[50];
    char breakAt;
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Please enter a string with no spaces: ");
    scanf("%s", &stringStringString);
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Please enter what character to split your string at: ");
    scanf("%c", &breakAt);
    breakBefore(stringStringString, breakAt, strlen(stringStringString));
    printf("\n\n");

    printf("Question 11:\n");
    char stringStringStringString[50];
    char breakAt2;
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Please enter a string with no spaces: ");
    scanf("%s", &stringStringStringString);
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Please enter what character to split your string at: ");
    scanf("%c", &breakAt2);
    breakAfter(stringStringStringString, breakAt2, strlen(stringStringStringString));
    printf("\n\n");

    printf("Question 12:\n");
    int intArray[] = {1, 2, 3, 4, 5, 6, 1, 8, 3, 10};
    arrayRepeat(intArray, sizeof(intArray)/sizeof(int));
    printf("\n\n");

    printf("Question 13:\n");
    int intArrayInput[10];
    arrayInputRepeat(intArrayInput, sizeof(intArrayInput)/sizeof(int));
    printf("\n\n");

    return 0;
}

void songs() {
    printf("Digital Silence by Peter McPoland\n");
    printf("Lost Umbrella by Inabakumori\n");
    printf("Young Girl A by Siinamota\n");
}

void fizzBuzz(int countTo) {
    for (int i = 1; i < countTo; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            printf("FizzBuzz\n");
        }
        else if (i % 3 == 0) {
            printf("Fizz\n");
        }
        else if (i % 5 == 0) {
            printf("Buzz\n");
        }
        else {
            printf("%d\n", i);
        }
    }
}

void guessingGame() {
    char choice;

    do {
        int theNumber = getRandom();
        int userNumber;
        int numGuesses = 1;
        int ch;

        printf("Welcome to the guessing game! Please guess the number!\n");
        printf("Please keep in mind the number is between 0 and 100.\n");
        printf("Please enter a number for guess %d%s", numGuesses, ": ");
        scanf("%d",&userNumber);
        while (theNumber != userNumber) {
            if (userNumber < 0 || userNumber > 100) {
                printf("That number isn't even in the right range!\n");
            }
            else if (userNumber < theNumber) {
                printf("Try a little higher!\n");
            }
            else if (userNumber > theNumber) {
                printf("Try a little lower!\n");
            }
            numGuesses++;
            printf("Please enter a number for guess %d%s", numGuesses, ": ");
            scanf("%d",&userNumber);
        }
        // Line 116 taken from your example per your awesome advise during office hours as things were being left in the buffer
        while ((ch = getchar()) != '\n' && ch != EOF);
        printf("You found the number!\n");
        printf("Would you like to play again? Y/N\n");
        scanf("%c",&choice);
        while (toupper(choice) != 'N' && toupper(choice) != 'Y') {
            printf("Invalid choice. Please try again.\n");
            printf("Would you like to play again? Y/N\n");
            scanf("%c",&choice);
        }
    } while (toupper(choice) != 'N');
    printf("Goodbye!");
}

void arrayOutput(int array[], size_t size) {
    for (int i = 0; i < size; i++) {
        printf("%d\n", array[i]);
    }
}

void arrayFlip(int array[], size_t size) {
    int tempArray[size];

    for (int i = 0; i < size; i++) {
        tempArray[i] = array[size-i-1];
    }
    for (int i = 0; i < size; i++) {
        array[i] = tempArray[i];
    }
}

void printInstruction(char string[], size_t size) {
    char cInstructions[] = "AMDamd01-!";
    if (string[0] == '@') {
        printf("A instruction");
        return;
    }
    else if (strcspn(string, cInstructions) == 0) {
        printf("C instruction");
        return;
    }
    printf("Error");
}

void isItThere(char string[], size_t size) {
    bool isItThere = false;
    const size_t locationOfSemi = strcspn(string, ";");
    const size_t locationOfEqual = strcspn(string, "=");
    if (locationOfSemi != size) {
        printf("Jump\n");
        isItThere = true;
    }
    if (locationOfEqual != size) {
        printf("Dest\n");
        isItThere = true;
    }
    if (!isItThere) {
        printf("Error\n");
    }
}

void breakBefore(char string[],char breakPoint, size_t size) {
    size_t breakHere = strcspn(string, &breakPoint);
    if (breakHere == size) {
        printf("Error\n");
    }
    else {
        for (int i=0; i<breakHere; i++) {
            printf("%c", string[i]);
        }
    }
}

void breakAfter(char string[], char breakPoint, size_t size) {
    size_t breakHere = strcspn(string, &breakPoint);
    if (breakHere == size) {
        printf("Error\n");
    }
    else {
        for (int i=breakHere + 1; i<size; i++) {
            printf("%c", string[i]);
        }
    }
}

void arrayRepeat(int array[], size_t size) {
    int tempArray[size];
    tempArray[0] = array[0];
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (tempArray[j] == array[i]) {
                printf("%d\n", array[i]);
            }
        }
        tempArray[i] = array[i];
    }
}

void arrayInputRepeat(int array[], size_t size) {
    int numDone = 1;
    int tempArray[1];
    printf("Please enter a number: ");
    scanf("%d", &array[0]);

    for (int i = 1; i < size; i++) {
        printf("Please enter a number: ");
        scanf("%d", &tempArray[0]);
        while (inArray(array, tempArray[0], numDone)) {
            printf("Please try again: ");
            scanf("%d", &tempArray[0]);
        }
        array[i] = tempArray[0];
        numDone++;
    }

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

int arraySum(int array[], size_t size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

// Stole most of this from your example and then edited it from there
static int getRandom() {
    const int max = 100, min = 1;

    int range = max - min + 1;
    int limit = RAND_MAX - (RAND_MAX % range);

    int r;
    do {
        r = rand();
    } while (r >= limit);

    return (r % range) + min;
}

float arrayMean(int array[], size_t size) {
    int sum = arraySum(array, size);
    return (float)sum / size;
}

bool inArray(int array[], int number, int numDone) {
    for (int i=0; i<numDone; i++) {
        if (array[i] == number) {
            return true;
        }
    }
    return false;
}