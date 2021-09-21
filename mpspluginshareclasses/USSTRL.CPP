
#include "usclasses.h"
#include <stdio.h>

//**************** USStringList implementation ***************

void USStringList::add(char *value,size_t tag)
 {
  char *buffer = (char*) malloc(strlen(value)+1);
  strcpy(buffer, value);
  USList::add(buffer,tag);
}

void USStringList::insert(int n, char *value, size_t tag)
 {
  char *buffer = (char*) malloc(strlen(value)+1);
  strcpy(buffer, value);
  USList::insert(n,buffer,tag);
}

void USStringList::destroy(int n)
 {
  if (n<0 || n>=count()) return;
  free(
indexNode(n)->item);
  USList::destroy(n);
}

void USStringList::setItem(int n, char *newValue) {
  if (n<0 || n>=count()) return;
  free(indexNode(n)->item);
  char *buffer = (char*) malloc(strlen(newValue)+1);
  strcpy(buffer, newValue);
  indexNode(n)->item = buffer;
}

void USStringList::clear(void)
 {
  for(int i=0; i<count(); i++)
	free(indexNode(i)->item);
  USList::clear();
}

int USStringList::indexOf(char *value)
 {
  for(int i=0; i<count(); i++)
	if (!strcmp((char*)indexNode(i)->item, value))
	  return i;
  return -1;
}

void USStringList::remove(char *value)
 {
  int n = indexOf(value);
  if (n<0 || n>=count()) return;
  destroy(n);
}

#define MAX_CHARS	1024

void USStringList::loadFromFile(char *fileName)
 {
  char buffer[MAX_CHARS+1];
  int l;
  FILE *fp;

  clear();
  if ((fp=fopen(fileName,"rt"))==NULL) return;
  while(!feof(fp)) {
	fgets(buffer, MAX_CHARS, fp);
	l = strlen(buffer)-1;
	while (buffer[l]=='\n' || buffer[l]=='\r')
	  buffer[l--] = 0;

	add(buffer);
  }
  fclose(fp);
}

void USStringList::saveToFile(char *fileName)
 {
  FILE *fp = fopen(fileName,"wt");
  if (fp==NULL) return;

  for(int i=0; i<count(); i++){
	fputs(items(i), fp);
    fputc('\n',fp);
  }
  fclose(fp);
}

void USStringList::sort(void) {
  int n;
  for (int i=1; i<count(); i++) {
    n = 0;
    while (n<i && strcmp(items(n),items(i))<=0) n++;
    if (n<i) move(i,n);
  }
}

void USStringList::sortDesc(void) {
  int n;
  for (int i=1; i<count(); i++) {
    n = 0;
    while (n<i && strcmp(items(n),items(i))>=0) n++;
    if (n<i) move(i,n);
  }
}
