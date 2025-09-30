//
// Created by adele on 9/22/2025.
// Instructions to binary
//
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

bool cType(char* string);
char* theGreatComboBreaker(char* line);
char* aInstruction(char* string);
char* destination(char* string);
char* jump(char* string);
char* compA(char* string);
static char* binary15Rep(int number);
static int charToDigit(char);
static int stringToInt(char*);
static char* lineType(char*);
static char* removeExtra(char* string);
static char* removeComments(char* string);
static char* removeEndSpaces(char* string);

const int BINARY_SIZE = 15, INSTRUCTION_SIZE = 17, BUFFER_SIZE = 256;

int main() {
  FILE* inputFile = NULL; // Dropping the null declarations just for you Bowe :)
  FILE* outputFile = NULL;
  char inputFileName[BUFFER_SIZE];


  // printf("Please enter an input filename: ");
  // fgets(inputFileName, BUFFER_SIZE, stdin);
  // inputFileName[strcspn(inputFileName, "\n")] = 0;

  inputFile = fopen("in.txt", "r");
  outputFile = fopen("out.txt", "w");

  if(inputFile == NULL){
    puts("Error opening input file");
  }
  else if(outputFile == NULL){
    puts("Error opening output file");
  }
  else{
    char buffer[BUFFER_SIZE];

    while(fgets(buffer, BUFFER_SIZE, inputFile) != NULL){
      if (buffer[0] != '\n') {
        buffer[strcspn(buffer, "\r\n")] = 0; //remove carriage return, line feed
        char* extraRemoved = removeExtra(buffer);
        char* something = removeComments(extraRemoved);
        char* commentsRemoved = removeEndSpaces(something);
        if (strlen(commentsRemoved) > 0) {
          char* type = lineType(commentsRemoved);
          if (type == "Error") {
            puts("ERROR");
          }
          else {
            char* success = theGreatComboBreaker(commentsRemoved);
            fputs(success, outputFile);
            fputs("\n", outputFile);
            free(success);
            success = NULL;
          }
          free(type);
          type = NULL;
        }
        // Finish them
        free(commentsRemoved);
        commentsRemoved = NULL;
        free(extraRemoved);
        extraRemoved = NULL;
        free(something);
        something = NULL;
      }
    }
    //Close the file
    fclose(inputFile);
    fclose(outputFile);
  }
  return 0;
}

/*
 * Returns if it is a jump (true)
 * or destination type (false)
 */
bool cType(char* string) {
  const char* semiCheck = strchr(string, ';');
  const char* equalCheck = strchr(string, '=');

  if (semiCheck != NULL) {
    return true;
  }
  if (equalCheck != NULL) {
    return false;
  }
  return NULL;
}

char* theGreatComboBreaker(char* line) {
  // A instruction
  char* final = (char*)malloc(sizeof(char)*17);
  for (int i = 0; i < 16; i++) {
    final[i] = '0';
  }
  final[16] = '\0';
  if (line[0] == '@') {
    char* theBinary = aInstruction(line);
    for (size_t i = 0; i < BINARY_SIZE; i++) {
      final[i+1] = theBinary[i];
    }
    free(theBinary);
    theBinary = NULL;
  }
  // C instruction
  else {
    for (int i=0; i<3; i++) {
      final[i] = '1';
    }
    // Get comp
    char* theCompA = compA(line);
    for (int i=0; i< strlen(theCompA); i++) {
      final[i+3] = theCompA[i];
    }
    free(theCompA);
    theCompA = NULL;

    // If semicolon/jump
    if (cType(line)) {
      char* theJumpBinary = jump(line);
      for (int i = 0; i < strlen(theJumpBinary); i++) {
        final[i+13] = theJumpBinary[i];
      }
      free(theJumpBinary);
      theJumpBinary = NULL;
    }
    // If equal/destination
    else if (!cType(line)) {
      char* theDesintationBinary = destination(line);
      for (int i = 0; i < strlen(theDesintationBinary); i++) {
        final[i+10] = theDesintationBinary[i];
      }
      free(theDesintationBinary);
      theDesintationBinary = NULL;
    }
  }
  return final;
}

/*
 * Returns the A instruction binary
 */
char* aInstruction(char* string) {
  size_t size = 0;
  for (size_t i = 1; i < strlen(string); i++) {
    if (!isdigit(string[i])) {
      break;
    }
    size++;
  }
  char removedA[size+1];
  for (size_t i = 1; i <= size; i++) {
    removedA[i-1] = string[i];
  }
  removedA[size] = '\0';
  int theInt = stringToInt(removedA);
  char* binaryStuff = binary15Rep(theInt);
  return binaryStuff;
}

/*
 * Takes in the user's input
 * Returns the destination part of the binary
 */
char* destination(char* string) {
  char* EQUAL_POS = strchr(string, '=');
  size_t length = strlen(string) - strlen(EQUAL_POS);

  char* finalDestination = (char*)malloc(sizeof(char) * 4);
  for (int i = 0; i < 3; i++) {
    finalDestination[i] = '0';
  }
  finalDestination[3] = '\0';

  char* instructionDest = (char*)malloc(sizeof(char) * (length + 1));
  strncpy(instructionDest, string, length);
  instructionDest[length] = '\0';

  if (strchr(instructionDest, 'A') != NULL) {
    finalDestination[0] = '1';
  }
  if (strchr(instructionDest, 'D') != NULL) {
    finalDestination[1] = '1';
  }
  if (strchr(instructionDest, 'M') != NULL) {
    finalDestination[2] = '1';
  }
  free(instructionDest);

  return finalDestination;
}

/*
 * Takes in the user's input
 * Returns the jump part of the binary
 */
char* jump(char* string) {
  char* SEMI_POS = strchr(string, ';');
  size_t length = strlen(SEMI_POS);

  char* finalDestination = (char*)malloc(sizeof(char) * 4);
  for (int i = 0; i < 3; i++) {
    finalDestination[i] = '0';
  }
  finalDestination[3] = '\0';

  char* instructionDest = (char*)malloc(sizeof(char) * (length-1));
  // Skipping the J since it's going to be in all of them
  strncpy(instructionDest, SEMI_POS+2, length-2);
  instructionDest[length-2] = '\0';

  if (strcmp(instructionDest, "NE") == 0) {
    finalDestination[0] = '1';
    finalDestination[2] = '1';
  }
  else if (strcmp(instructionDest, "MP") == 0) {
    finalDestination[0] = '1';
    finalDestination[1] = '1';
    finalDestination[2] = '1';
  }
  else {
    if (strchr(instructionDest, 'G') != NULL) {
      finalDestination[2] = '1';
    }
    if (strchr(instructionDest, 'E') != NULL) {
      finalDestination[1] = '1';
    }
    if (strchr(instructionDest, 'L') != NULL) {
      finalDestination[0] = '1';
    }
  }
  free(instructionDest);

  return finalDestination;
}

/*
 * Takes in the user's input
 * Returns the a and comp part
 */
char* compA(char* string) {
  bool semiEqual = cType(string);
  size_t size = 0;
  if (semiEqual) {
    char* compA = strchr(string, ';');
    size = strlen(string) - strlen(compA);
  }
  else if (!semiEqual) {
    char* compA = strchr(string, '=');
    for (int i=0; i < strlen(compA); i++) {
      size = strlen(compA);
    }
  } else {
    return NULL;
  }

  char* comp = (char*)malloc(sizeof(char) * (size + 1));
  if (semiEqual) {
    strcpy(comp, string);
  }
  else {
    for (int i = 0; i < size; i++) {
      comp[i] = string[i+strlen(string) - size+1];
    }
  }
  comp[size] = '\0';
  free(compA);

  char* finalAComp = (char*)malloc(sizeof(char) * 8);
  for (int i = 0; i < 7; i++) {
    finalAComp[i] = '0';
  }
  finalAComp[7] = '\0';

  // Set a
  if (strchr(comp, 'M') != NULL) {
    finalAComp[0] = '1';
  }

  // The actual comp stuff
  if (strcmp(comp, "0") == 0) {
    finalAComp[1] = '1';
    finalAComp[3] = '1';
    finalAComp[5] = '1';
  }
  else if (strcmp(comp, "1") == 0) {
    finalAComp[1] = '1';
    finalAComp[2] = '1';
    finalAComp[3] = '1';
    finalAComp[4] = '1';
    finalAComp[5] = '1';
    finalAComp[6] = '1';
  }
  else if (strcmp(comp, "-1") == 0) {
    finalAComp[1] = '1';
    finalAComp[2] = '1';
    finalAComp[3] = '1';
    finalAComp[5] = '1';
  }
  else if (strcmp(comp, "D") == 0) {
    finalAComp[3] = '1';
    finalAComp[4] = '1';
  }
  else if (strcmp(comp, "A") == 0 || strcmp(comp, "M") == 0) {
    finalAComp[1] = '1';
    finalAComp[2] = '1';
  }
  else if (strcmp(comp, "!D") == 0) {
    finalAComp[3] = '1';
    finalAComp[4] = '1';
    finalAComp[6] = '1';
  }
  else if (strcmp(comp, "!A") == 0 || strcmp(comp, "!M") == 0) {
    finalAComp[1] = '1';
    finalAComp[2] = '1';
    finalAComp[6] = '1';
  }
  else if (strcmp(comp, "-D") == 0) {
    finalAComp[3] = '1';
    finalAComp[4] = '1';
    finalAComp[5] = '1';
    finalAComp[6] = '1';
  }
  else if (strcmp(comp, "-A") == 0 || strcmp(comp, "-M") == 0) {
    finalAComp[1] = '1';
    finalAComp[2] = '1';
    finalAComp[5] = '1';
    finalAComp[6] = '1';
  }
  else if (strcmp(comp, "D+1") == 0) {
    finalAComp[2] = '1';
    finalAComp[3] = '1';
    finalAComp[4] = '1';
    finalAComp[5] = '1';
    finalAComp[6] = '1';
  }
  else if (strcmp(comp, "A+1") == 0 || strcmp(comp, "M+1") == 0) {
    finalAComp[1] = '1';
    finalAComp[2] = '1';
    finalAComp[4] = '1';
    finalAComp[5] = '1';
    finalAComp[6] = '1';
  }
  else if (strcmp(comp, "D-1") == 0) {
    finalAComp[3] = '1';
    finalAComp[4] = '1';
    finalAComp[5] = '1';
  }
  else if (strcmp(comp, "A-1") == 0 || strcmp(comp, "M-1") == 0) {
    finalAComp[1] = '1';
    finalAComp[2] = '1';
    finalAComp[5] = '1';
  }
  else if (strcmp(comp, "D+A") == 0 || strcmp(comp, "D+M") == 0) {
    finalAComp[5] = '1';
  }
  else if (strcmp(comp, "D-A") == 0 || strcmp(comp, "D-M") == 0) {
    finalAComp[2] = '1';
    finalAComp[5] = '1';
    finalAComp[6] = '1';
  }
  else if (strcmp(comp, "A-D") == 0 || strcmp(comp, "M-D") == 0) {
    finalAComp[4] = '1';
    finalAComp[5] = '1';
    finalAComp[6] = '1';
  }
  else {
    finalAComp[2] = '1';
    finalAComp[4] = '1';
    finalAComp[6] = '1';
  }
  free(comp);
  comp = NULL;

  return finalAComp;
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
 Converts and integer to a 15 character string
 of its binary in base 2
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
 Used https://stackoverflow.com/questions/17292545/how-to-check-if-the-input-is-a-number-or-not-in-c to find
 the isdigit functions. I figured since I've seen it in other languages, it probably existed in C too.
 Used in line 159.
 */
static char* lineType(char* line) {
    switch (line[0]) {
        case '\n':
            return "Empty";
        case '/':
            if (line[1] == '/') {
                return "Comment";
            }
        // A instruction
        case '@':
            return "not an error";
        // C instructions
        case 'A':
          return "not an error";
        case 'M':
          return "not an error";
        case 'D':
          return "not an error";
        case '0':
          return "not an error";
        case '1':
          return "not an error";
        case '-':
          return "not an error";
        case '!':
          return "not an error";
        default:
            return "Error";
    }
}

/*
 Removes any starting spaces
 and tabs
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

static char* removeEndSpaces(char* string) {
  int destructionCount = 0;
  for (int i = strlen(string) - 1; i >= 0; i--) {
    if (string[i] == ' ') {
      destructionCount++;
    }
    else {
      break;
    }
  }
  if (destructionCount == 0) {
    return string;
  }

  char* omgImSoTired = (char*)malloc(sizeof(char)*(strlen(string) - destructionCount + 1));
  strncpy(omgImSoTired, string, strlen(string) - destructionCount);
  omgImSoTired[strlen(string) - destructionCount] = '\0';
  return omgImSoTired;
}