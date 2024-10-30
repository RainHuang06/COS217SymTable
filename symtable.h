/*Author: Rain Huang*/
#ifndef SYMTABLE 
#define SYMTABLE
  #include <stdio.h>
  #include <stddef.h>
  #include <assert.h>
  #include <string.h>
  #include <stdlib.h>

  /*Defines SymTable_T as a pointer to a struct SymTable.*/
  typedef struct SymTable *SymTable_T;
  
  /*Initializes a new SymTable.*/
  SymTable_T SymTable_new(void);

   /*Frees SymTable pointed to by oSymTable and all of its keys. Values are not freed, as they are managed
   by the client.*/
  void SymTable_free(SymTable_T oSymTable);

   /*Returns the size, or number of elements in oSymTable.*/
  size_t SymTable_getLength(SymTable_T oSymTable);

   /*Puts a new key-value pair into oSymTable with key pcKey and value pvValue. Returns 1
   if the insertion was successful, and 0 if it was not.*/
  int SymTable_put(SymTable_T oSymTable,
     const char *pcKey, const void *pvValue);

   /*Replaces the value of pcKey in SymTable with a value of pvValue, then returns
   the original value that was replaced. Returns NULL if pcKey is not found.*/
  void *SymTable_replace(SymTable_T oSymTable,
     const char *pcKey, const void *pvValue);

   /*Searches for a SymTable listing with key pcKey. If it is found, return 1
   and returns 0 if it is not found.*/
  int SymTable_contains(SymTable_T oSymTable, const char *pcKey);

   /*Gets pvValue of the listing with key pcKey, then returns it. If it
   is not found, returns NULL.*/
  void *SymTable_get(SymTable_T oSymTable, const char *pcKey);

   /*Removes the key-value pair with key pcKey from oSymTable and
   returns its value, if not found returns NULL*/
  void *SymTable_remove(SymTable_T oSymTable, const char *pcKey);

   /*Applies pfApply to each pcKey/pvValue pair in oSymTable with extra parameter
   pvExtra*/
  void SymTable_map(SymTable_T oSymTable,
     void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
     const void *pvExtra);
#endif