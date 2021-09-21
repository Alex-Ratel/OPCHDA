
#ifndef _USCLASSES_H
#define _USCLASSES_H
#include <stdlib.h>
#include <string.h>

/************************ definition USObject class *********************
  class USObject is abstract super-class for all classes in zeos library 
*************************************************************************/
#pragma pack(push,1)
class USObject{
protected:
// Class name string
  char objectName[20]; 
public:
// Class constructor 
  USObject() { strcpy(objectName,"USObject"); }
// Class destructor 
  virtual ~USObject() {}
// Retrieve a class name string
  char *getObjectName() { return objectName; }
// Set a new class name
  void setObjectName(const char *newObjectName) {
    strncpy(objectName, newObjectName, 20); } 
};

// Definition a 'TNotifyEvent' new type 
typedef void (*TNotifyEvent)(USObject &sender);

// Structure 'USNode' is used in linked lists as a node
struct USNode {
  size_t tag;
  void *item;
};

/************************** definition USList class **********************
*           class USList  is  linked list  of  pointers                  *
*************************************************************************/

class USList: public USObject{
protected:
// Number of items in list
  int listCpc, listCnt;
// Buffer for items pointers
  USNode **list;

// Find a node
  USNode *indexNode(int n) { return list[n]; }
// Alloc memory for node list
  int alloc(USNode **&buffer, int n) {
    int r = ((n>>6)+1)<<6; 
    buffer = (USNode**) calloc(r, sizeof(USNode*));
    return r;
  }
public:
// Class constructor 
	USList() { list = NULL;strcpy(objectName, "USList"); listCpc = alloc(list, listCnt = 0); }
// Class destructor 
	virtual ~USList() { clear(); free(list); list = NULL; }
// Add a new item to list
  void add(void *value,size_t tag=0);
// Insert a new item in list in position N
  void insert(int n, void *value, size_t tag=0);
// Remove an item in position N
  void destroy(int n);
// Retrieve a value of item N
  void *items(int n) { return indexNode(n)->item; }
// Retrieves a value of item N 
  void *getItem(int n) { return items(n); }
// Set a new value of item N 
  void setItem(int n, void *newValue);
// Operator to retrieve a value of item N
  void *operator[](int n) { return items(n); }
// Retrieve a tag of item N
  size_t tags(int n) { return indexNode(n)->tag; }
// Retrieve a tag of item N
  size_t getTag(int n) { return tags(n); }
// Set a new tag value of item N
  void setTag(int n, size_t newTag);
// Retrieve a overall number of items in list  
  int count(void) { return listCnt; }
// Retrieve a maximum capacity of list  
  int capacity(void) { return listCpc; }
// Remove all items from list and makes it empty
  virtual void clear(void);
// Exchange items with indexes N1 and N2 
  void exchange(int n1, int n2);
// Moves an item N1 to position N2
  void move(int n1, int n2);
// Remove a first item with VALUE
  void remove(void *value);
// Retrieve an index of first item in list with VALUE
  int indexOf(void *value);
// Retrieve an index of first item in list with TAG
  int indexOfTag(size_t tag);
};

/********************** definition USStringList class ********************
*     class USStringList is linked list  of  structure 'USNode' nodes     *
*************************************************************************/

class USStringList:public USList{
public:
// Class constructor 
  USStringList(){ strcpy(objectName,"USStringList"); }
// Class destructor 
  virtual ~USStringList(){ clear(); }
// Add a string to list 
  void add(char *value, size_t tag=0);
// Insert a string into position N
  void insert(int n, char *value, size_t tag=0);
// Remove a string in position N
  void destroy(int n);
// Retrieve a string with index N
  char *items(int n) { return (char*) indexNode(n)->item; }
// Retrieve a string with index N
  char *getItem(int n) { return items(n); }
// Set a new string to item N
  void setItem(int n, char *newValue);
// Retrieve a string with index N
  char *operator[](int n) { return items(n); }
// Remove all strings in list and makes it empty
  virtual void clear(void);
// Removes a 'value'-string from list
  void remove(char *value);
// Retrieve an index of first 'value'-string
  int indexOf(char *value);
// Load a strings from specifed file
  void loadFromFile(char *fileName);
// Write a strings from list to specifed file
  void saveToFile(char *fileName);
// Sort string list ascending
  void sort(void);
// Sort string list descending
  void sortDesc(void);
};
#pragma pack(pop)
#endif