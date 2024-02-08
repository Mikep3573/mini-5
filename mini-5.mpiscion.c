/**
 * This file is the .c file for Mini-Programming Assignment #5
 * This was written by Michael Piscione
*/

#include "mini-5.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * createRecords takes an array of 'ids', an array of 'names', 
 * a pass-by-reference parameter to store an array of Records, and a value representing the number of elements in these arrays. 
 * It first checks if ids, names, or records is NULL (the arrays from earlier). If any are, it returns -1. If the number of elements is zero,
 * it returns zero. If none of these are true, it then allocates a new array of records and stores created Records in this new array 
 * (using corresponding ids and names). It returns the number of records in this new array. 
 * Furthermore, it passes this new array of records back through the pass-by-reference array.
 * If any id > 0 or length of name is out of bounds (= 0 or > max characters), the corresponding record is not added to the new array.
 * Parameters: unsigned int numRecords (number of elements in the arrays), int *ids (pointer to an array of ids), char **names (pointer to an array of names),
 * and Record **records (pointer to a pointer to a space in memory for an array of records).
 * Return: -1 if any pointer is NULL, 0 if no records to allocate, or number of records in the final array (newRecords).
*/
int createRecords(unsigned int numRecords, int *ids, char **names, Record **records) {
    // If ids, names, or records is NULL
    if (ids == NULL || names == NULL || records == NULL) {
        return -1;  // Return -1
    }

    // If numRecords is zero
    if (numRecords == 0) {
        return 0;  // Return 0
    }

    // Setup a counter variable for number of valid Records
    int recordsCount = 0;

    // Find the valid ids and names
    for (int i = 0; i < numRecords; i++) {
        // Grab the corresponding id and name
        int id = ids[i];
        char *name = names[i];

        // If id <= 0 or length of name (== 0 or > MAXNAMELEN), not a valid Record
        if (id > 0 && strlen(name) > 0 && strlen(name) <= MAXNAMELEN) {
            // Incremement count, only when a valid Record is found
            recordsCount += 1;
        }

        // Set corresponding position in ids and names to be recognizably bad if not a valid Record
        else {
            ids[i] = 0;
            names[i] = "";
        }
    }

    // Allocate memory for new array using recordsCount
    Record *newRecords = malloc(recordsCount * sizeof(Record));

    // Reset recordsCount to be used as index in newRecords
    recordsCount = 0;

    // Fill in each entry with a Record with the corresponding id & name from arrays
    for (int i = 0; i < numRecords; i++) {
        // Grab the corresponding id and name
        int id = ids[i];
        char *name = names[i];

        // If id and name are not 0 and "" respectively, we can add a new Record
        if (id != 0 && name != "") {
            // Add the id and name to the Record at that index
            newRecords[recordsCount].id = id;
            strcpy(newRecords[recordsCount].name, name);

            // Increment recordsCount
            recordsCount++;
        }
    }

    // Pass-by-reference newRecords through records
    *records = newRecords;

    // Return the length of records at the end
    return recordsCount;
}

int main() {
    unsigned int numRecords = 5;
    int *ids = malloc(numRecords * sizeof(int));
    char **names = malloc(numRecords * (sizeof(char) * 10));
    for (int i = 0; i < numRecords; i++) {
        names[i] = "name";
        ids[i] = i + 1;
    }
    Record *records = malloc(numRecords * sizeof(Record));
    int recordsCount = createRecords(numRecords, NULL, names, &records);
    printf("Return val = %d\n", recordsCount);
    for (int i = 0; i < 20; i++) {
        printf("id = %d, name = %s\n", records[i].id, records[i].name);
    }
    return 0;
}

