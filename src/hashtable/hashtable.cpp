// MathLibrary.cpp : Defines the exported functions for the Lib.
#include <limits.h>
#include <utility>
#include "hashtable.h"

#include <stdlib.h>
#include <string.h>


unsigned int __hash(const char* key, unsigned int tableSize) {
    unsigned int hash = 0;
    while (*key) hash = hash * 101  +  *key++;

    return hash % tableSize;
}

HashTable* createHashTable(const std::vector<std::pair<const char*, const char*>>& values) { 
    const unsigned int tableSize = values.size();

    HashTable* table = new HashTable;
    
    table->buckets = static_cast<Node**>(malloc(sizeof(Node*) * tableSize));
    table->size = tableSize;

    memset(table->buckets, 0, sizeof(Node*) * tableSize);

    for (auto& value : values) {
        insertPair(table, value.first, value.second);
    }

    return table;
}

void insertPair(HashTable* table, const char* key, const char* value) {
    unsigned int idx = __hash(key, table->size);

    Node* node = new Node;

    /* TODO: Memory leak / inconsisten allocators
    `node` is allocated with C++ `new`, but `key`/`value` are allocated with `strdup` (which uses `malloc` under the hood). 
    There is no `destroyHashTable` or `freeNode` function anywhere in the file - nothing ever calls `delete` on the nodes/table or `free` 
    on the strdup'd strings. So every hashtable is a guaranteed leak for its whole lifetime, and even if someone added cleanup later, they'd 
    have to remember to `free()` the strings but `delete` the nodes - mixing allocators like this is a common source of real bugs and should be fixed
    */
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = table->buckets[idx];
    table->buckets[idx] = node;
}

char* getValue(HashTable* table, const char* key) {
    unsigned int idx = __hash(key, table->size);
    Node* node = table->buckets[idx];
    
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }

    return NULL;
}
