#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* key;
    int value; 
} Symbol;


typedef struct {
    Symbol* data;
    size_t size;
    size_t capacity;
} SymbolTable;

static void sTableInit(SymbolTable* table);
static void sTableFree(SymbolTable* table);
static void sTablePrint(const SymbolTable* table);
static void sTableGrow(SymbolTable* table); //double the array
static int sTablePut(SymbolTable* table, char* key, int value); //insert at end
static int sTableGet(const SymbolTable* table, const char* key); //return value, -1 if not exist


int main(){
    SymbolTable* theTable;

    sTableInit(theTable);
    sTablePut(theTable, "hello", 5);
    sTablePut(theTable, "world", 6);
    sTablePrint(theTable);

    int value = sTableGet(theTable, "hello");
    printf("%d\n", value);

    sTableFree(theTable);
    puts("the end");
}

static void sTableInit(SymbolTable* table){
    table->data = NULL;
    table->size = 0;
    table->capacity = 0;
}

static void sTableFree(SymbolTable* table){
    if (table->data != NULL) {
        for (int i = 0; i < table->size; i++) {
            free(table->data[i].key);
        }
        free(table->data);
        table->data = NULL;
    }
    table->size = 0;
    table->capacity = 0;
}

static void sTablePrint(const SymbolTable* table){
    printf("Size: %d  Max: %d\n", table->size, table->capacity);
    for(int i = 0; i < table->size; i++){
        printf("Key: %s Value: %d\n", table->data[i].key, table->data[i].value);
    }
}

/*
Should double the size of the data attribute
*/
static void sTableGrow(SymbolTable* table) {
    // Get current size of the table
    // malloc a new Symbol* that's 2* the current size
    // Copy over all the old stuff in the table (table->data[i])
    // Free table->data
    // data = temp so it points at temp
    // Update the capacity

    Symbol* tempTable = malloc(sizeof(Symbol)*(table->capacity*2));
    for(int i = 0; i < table->size; i++) {
        tempTable[i] = table->data[i];
    }
    free(table->data);
    table->data = tempTable;
    table->capacity *= 2;
}

/*
Appends the new value to the end of the data array
Needs to check if data is null and create new array if so
Needs to check if size == capacity and grow if so
*/
static int sTablePut(SymbolTable* table, char* key, int value){
    // If table ->data is null
        // malloc space of size 1
        // update capacity
        // update size
    // If table->data != Null
        // Check to see if there is room
        // if size == capacity
            // call sTableGrow
        // put a new Symbol at table->data[size]
            //create a new symbol (Malloc)
                // Set new symbol's value to value
                // Malloc space for the key and then copy the text into that space
        // Add 1 to size
        // return 1 for success
    if (table->data == NULL) {
        Symbol* tempTable = malloc(sizeof(Symbol)*1);
        table ->data = tempTable;
        table ->capacity += 1;
        free(tempTable);
    }
    if (table->size == table->capacity) {
        sTableGrow(table);
    }
    Symbol* temp = malloc(sizeof(Symbol));
    temp->value = value;
    temp->key = key;
    table->data[table->size] = *temp;
    table->size++;
    return 1;
}

/*
Looks through the table for a key
Returns the key's value if found, -1 if not
Hint: strcmp is your friend
*/
static int sTableGet(const SymbolTable* table, const char* key){
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->data[i].key, key) == 0) {
            return table->data[i].value;
        }
    }
    return -1;
}

