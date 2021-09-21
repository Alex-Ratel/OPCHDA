
#ifndef _USSTR_H
#define _USSTR_H

#include "usfunc.h"
#include <stdio.h>

#define MIN_BUFFER_LEN 5
#pragma pack(push,8)
class USString: public USObject {
protected:
  char *buff;
  int buffLen, len;

  char *alloc(int n);
public:
/* constructor #1 */
  USString(int newLen=MIN_BUFFER_LEN);
/* constructor #2 */  
  USString(char *s);
/* constructor #3 */  
  USString(USString &v);
/* destructor */  
  ~USString(void);
/* releases memory allocated for string */  
  void free(void);
/* retrieves a string */  
  char *getChars(void) { buff[len]=0; return buff; }
/* retrieves a string length */
  int length(void) { return len;}
/* retrieves a buffer length */  
  int bufferLength(void) { return buffLen; }
/* retrieves a one character of string with 'n' index */
  char charAt(int n) { return buff[n]; }

/* assigns a string to USString object */  
  USString &assign(char *s);
/* assings a one USString object to another */
  USString &assign(USString &v) { return assign(v.getChars()); }
/* operator assigns a string to USString object */
  USString &operator =(char *s) { return assign(s); }
/* operator assings a one USString object to another */  
  USString &operator =(USString &v) { return assign(v); }
  
/* appends a string 's' to USString object string */   
  virtual USString &append(char *s);
/* operator '+' appends a string 's' to USString object string */   
  USString &operator +(char *s) { return append(s); }
/* appends a one USString object to another */  
  USString &append(USString &v) { return append(v.getChars()); }
/* operator '+' appends a one USString object to another */   
  USString &operator +(USString &v) { return append(v); }
  
/* equal operators */   
  bool equals(char *s) { return (strcmp(buff, s))?false:true; }
  bool operator ==(char *s) { return equals(s); }
  bool operator !=(char *s) { return !equals(s); }
  bool equals(USString &v) { return equals(v.getChars()); }
  bool operator ==(USString &v) { return equals(v); }
  bool operator !=(USString &v) { return !equals(v); }
  
/* sets all chars of string to 'c' */  
  USString &fillChar(char c=0) { memset(buff, c, len); return *this; }
  
/* duplicates a USString object and return pointer to this */
  USString &dupe(void) { return *(new USString(buff)); }
/* comparing operations */  
  int compare(char *s, int n=0);
  int compare(USString &v, int n=0) { return compare(v.getChars()); }
  int compareIgnoreCase(char *s, int n=0);
  int compareIgnoreCase(USString &v, int n=0) { return compareIgnoreCase(v.getChars()); }
  
/* compares first part of USString string with 's' ( strlen(s) <= len ) */
  bool startWith(char *s);
/* does the same as previous but uses USString object instead */
  bool startWith(USString &v) { return startWith(v.getChars()); }
/* compares last part of USString string with 's' ( strlen(s) <= len ) */  
  bool endWith(char *s);
/* does the same as previous but uses USString object instead */  
  bool endWith(USString &v) {return endWith(v.getChars()); }

/* case translating methods */
  USString &toUpperCase(void);
  USString &toLowerCase(void);

/* retrieves a index of first occurence of 'c' char (opt. 'n'- limit) */  
  int indexOf(char c, int n=0);
/* retrieves a index of first occurence of 's' string */    
  int indexOf(char *s, int n=0) { 
      char* pstring = strstr(buff, s);
      if (pstring == NULL)
          return -1;
      return pstring - buff;
  }
/* does the same as previous but uses USString object instead */  
  int indexOf(USString &v, int n=0) { return indexOf(v.getChars(),n); }
/* retrieves a index of last occurence of 'c' char (opt. 'n'- limit) */    
  int lastIndexOf(char c, int n=0);
  
/*
  int lastIndexOf(char *s, int n=0);
  int lastIndexOf(USString &v, int n=0) { return lastIndexOf(v.getChars(),n); }
*/
/* replaces the character 'c1' to 'c2' in USString object */
  virtual USString &replace(char c1, char c2);
/*
  virtual USString &replace(char *s1, char *s2);
  virtual USString &replace(USString &v1, USString &v2) { replace(v1.getChars(), v2.getChars()); }
*/

/* creates a new USString object and allocates in it 'n' characters from 'p' pos */
  //virtual USString &subString(int p, int n);
/* creates a new USString object and allocates in it first 'n' characters */
  //virtual USString &left(int n);
/* creates a new USString object and allocates in it last 'n' characters */
  //virtual USString &right(int n);
/* deletes spaces and tabs in USString object from begin (left) */
  virtual USString &trimLeft(void);
/* deletes spaces and tabs in USString object from end (right) */  
  virtual USString &trimRight(void);
/* deletes spaces and tabs in USString object from end and begin */    
  virtual USString &trim(void);
  
/* methods translates the numbers to string view */
  USString &valueOf(double d) { sprintf(buff,"%f",d); return *this; }
  USString &valueOf(long l) { sprintf(buff,"%ld",l); return *this; }
  USString &valueOf(char *s) { assign(s); return *this; }
  USString &valueOf(bool b) { assign((b)?(char *)"true":(char *)"false"); return *this; }
  
/* checks the USString object for substring with 'p' template */    
  bool isMatch(char *p) { return ::isMatch(p, buff) != 0; }
  //bool isMatch(char *p) { return ::isMatch(p, buff); }
/* does the same as previous but uses USString object instead */  
  bool isMatch(USString &v) { return isMatch(v.getChars()); }
/*
  bool like(char *s);
  bool like(USString &v) { return like(v.getChars()); }
*/
};
/*
class USStringBuffer : public USString {
public:
  void setCharAt(int i, char c) { buff[i] = c; }
  USString &setLength(int n);
  USString &setCapacity(int n);
  USString &insert(int p, const char *buffer);
  USString &insert(int p, const char *buffer, int b, int n);
  USString &insert(int p, USString &s);
  USString &insert(int p, USString &s, int b, int n);
  USString &delete(int p, int n);
}
*/
#pragma pack(pop)
#endif
