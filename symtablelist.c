/*Author: Rain Huang*/
#include "symtable.h"
struct Node {
    const char* pcKey;
    const void* pvValue;
    struct Node* next;
};

struct SymTable {
    size_t length;
    struct Node* firstNode;
};

SymTable_T SymTable_new() {
    SymTable_T newSymTable = malloc(sizeof(struct SymTable));
    if(newSymTable == NULL) {
        return NULL;
    }
    newSymTable->firstNode = NULL;
    newSymTable->length = (size_t)0;
    return newSymTable;
}

void SymTable_free(SymTable_T oSymTable) {
    struct Node *curNode;
    struct Node *nextNode;
    assert(oSymTable != NULL);
    for(curNode = oSymTable->firstNode; curNode != NULL; curNode = nextNode) { 
        nextNode = curNode->next; /*Iteratively free every node*/
        free((char*) curNode->pcKey);
        free(curNode);
    }
    free(oSymTable);
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
    struct Node *toSearch;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    for(toSearch = oSymTable->firstNode; toSearch != NULL; toSearch = toSearch->next) {
        if(!strcmp(toSearch->pcKey, pcKey)) {
            return 1;
        }
    }
    return 0;
}

void* SymTable_get(SymTable_T oSymTable, const char *pcKey) {
    struct Node *toSearch;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    for(toSearch = oSymTable->firstNode; toSearch != NULL; toSearch = toSearch->next) {
        if(!strcmp(toSearch->pcKey, pcKey)) {
            return (void*)toSearch->pvValue;
        }
    }
    return NULL;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
    struct Node *newNode;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    newNode = malloc(sizeof(struct Node));
    if(newNode == NULL) {
        return 0;
    }
    newNode->pcKey = (const char*) malloc(strlen(pcKey) + 1);
    strcpy((char*)newNode->pcKey, pcKey); /*key protection*/
    newNode->pvValue = pvValue;
    if(!SymTable_contains(oSymTable, pcKey)) {
        newNode->next = oSymTable->firstNode; /*Insertion*/
        oSymTable->firstNode = newNode;
        oSymTable->length++;
        return 1; /*success*/
    }
    free((char*)newNode->pcKey);
    free(newNode);
    return 0;
}

size_t SymTable_getLength(SymTable_T oSymTable) {
    assert(oSymTable != NULL);
    return oSymTable->length;
}

void *SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
    struct Node *toSearch;
    struct Node *prev = NULL;
    void *toReturn;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    for(toSearch = oSymTable->firstNode; toSearch != NULL; toSearch = toSearch->next) {
        if(!strcmp(toSearch->pcKey, pcKey)) {
            if(prev == NULL) {
                oSymTable->firstNode = toSearch->next; /*Handles case if the first element is removed*/
            } else {
                prev->next = toSearch->next;
            }
            toReturn = (void*) toSearch->pvValue;
            free((char*) toSearch->pcKey); /*Don't forget to free the key!*/
            free(toSearch);
            oSymTable->length--;
            return(toReturn);
        }
        prev = toSearch;
    }
    return NULL;
}

void *SymTable_replace(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
    struct Node *toSearch;
    void* toReturn;
    assert(oSymTable != NULL);
    assert(pcKey != NULL);
    for(toSearch = oSymTable->firstNode; toSearch != NULL; toSearch = toSearch->next) {
        if(!strcmp(toSearch->pcKey, pcKey)) {
            toReturn = (void*) toSearch->pvValue;
            toSearch->pvValue = pvValue;
            return toReturn;
        }
    }
    return NULL;
}

void SymTable_map(SymTable_T oSymTable,
     void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
     const void *pvExtra) {
        struct Node* cur;
        assert(oSymTable != NULL);
        assert(pfApply != NULL);
        for(cur = oSymTable->firstNode; cur != NULL; cur = cur->next) {
            pfApply(cur->pcKey, (void*)cur->pvValue, (void*)pvExtra);
        }
     }