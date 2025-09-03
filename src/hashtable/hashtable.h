// Hashtable.h - Contains the data structure for a hashtable
#pragma once

/* DLL export
#ifdef HASHTABLELIBRARY_EXPORTS
#define HASHTABLELIBRARY_API __declspec(dllexport)
#else
#define HASHTABLELIBRARY_API __declspec(dllimport)
#endif
*/

#ifndef HASHTABLELIB_H
#define HASHTABLELIB_H

#include <vector>


typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node** buckets;
    unsigned int size;
} HashTable;


/* DLL export
extern "C" {
    HASHTABLELIBRARY_API HashTable* createHashTable(const std::vector<std::pair<const char*, const char*>>& values);
    HASHTABLELIBRARY_API void insertPair(HashTable* table, const char* key, const char* value);
    HASHTABLELIBRARY_API char* getValue(HashTable* table, const char* key);
}
*/

extern "C" {
    HASHTABLELIB_H HashTable* createHashTable(const std::vector<std::pair<const char*, const char*>>& values);
    HASHTABLELIB_H void insertPair(HashTable* table, const char* key, const char* value);
    HASHTABLELIB_H char* getValue(HashTable* table, const char* key);
}

#endif
