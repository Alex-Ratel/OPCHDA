
#include "usclasses.h"

//****************** USList implementation ********************

void USList::add(void *value, size_t tag)
 {
  USNode *newNode = (USNode*) malloc(sizeof(USNode));

  newNode->item = value;
  newNode->tag = tag;
  listCnt++;

  if (listCnt>=listCpc) {
	USNode **newList = NULL;
	listCpc = alloc(newList, listCnt);
	#ifdef _WIN64
        memcpy(newList, list, (listCnt - 1) << 3);
   	#else
        memcpy(newList, list, (listCnt - 1) << 2);
    #endif
	free(list);
	list = newList;
  }
  list[listCnt-1] = newNode;
}

void USList::insert(int n, void *value, size_t tag)
 {
  USNode *newNode = (USNode*) malloc(sizeof(USNode));
  USNode **newList = NULL;

  newNode->item = value;
  newNode->tag = tag;
  listCnt++;
  n = (n>=listCnt)?listCnt-1:n;

  listCpc = alloc(newList, listCnt);
  #ifdef _WIN64
    memcpy(newList, list, n << 3);
    memcpy(&newList[n + 1], &list[n], (listCnt - n - 1) << 3);
  #else
    memcpy(newList, list, n << 2);
    memcpy(&newList[n + 1], &list[n], (listCnt - n - 1) << 2);
  #endif
  free(list);
  list = newList;
  list[n] = newNode;
}

void USList::destroy(int n)
 {
  if (n<0 || n>=listCnt) return;
  USNode **newList = NULL;

    free(list[n]);
    listCnt--;
    listCpc = alloc(newList, listCnt);
    #ifdef _WIN64
        memcpy(newList, list, n << 3);
        if (n <= listCnt)
            memcpy(&newList[n], &list[n + 1], (listCnt - n + 1) << 3);
    #else
         memcpy(newList, list, n << 2);
        if (n <= listCnt)
            memcpy(&newList[n], &list[n + 1], (listCnt - n + 1) << 2);
    #endif
  free(list);
  list = newList;
}

void USList::setItem(int n, void *newValue)
 {
  if (n<0 || n>=listCnt) return;
  USNode *node = indexNode(n);
  if (node) node->item = newValue;
}

void USList::setTag(int n, size_t newTag)
 {
  if (n<0 || n>=listCnt) return;
  USNode *node = indexNode(n);
  if (node) node->tag = newTag;
}


void USList::clear(void)
 {
  for(int i=0; i<listCnt; i++)
	free(list[i]);

  if (listCpc>64) {
	free(list);
	listCpc = alloc(list, 0);
  }
  listCnt = 0;
}

void USList::exchange(int n1, int n2)
 {
  USNode *temp;
  if (n1<0 || n1>=listCnt || n2<0 || n2>=listCnt) return;

  temp = list[n1];
  list[n1] = list[n2];
  list[n2] = temp;
}

void USList::move(int n1, int n2)
 {
  if (n1<0 || n1>=listCnt || n2<0 || n2>=listCnt) return;

  void *value = list[n1]->item;
  int tag = list[n1]->tag;

  destroy(n1);
  n2 += (n2>n1)
?-1:0;
  insert(n2,value,tag);
}

void USList::remove(void *value)
 {
  int n=indexOf(value);
  if (n<0 || n>=listCnt) return;
  destroy(n);
}

int USList::indexOf(void *value)
 {
  for (int i=0; i<listCnt; i++)
	if (list[i]->item==value)
	  return i;
  return -1;
}

int USList::indexOfTag(size_t tag)
 {
  for (int i=0; i<listCnt; i++)
	if (list[i]->tag==tag)
	  return i;
  return -1;
}
