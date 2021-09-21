#ifndef _USFUNC_H
#define _USFUNC_H
#define US_TRUE  1
#define US_FALSE 0
#define US_BOOL  unsigned char
/* may be returned any function in any internal
   error cases */
 void *us_malloc(unsigned int size);
 void *us_realloc(void *ptr, unsigned int size);
 void us_free(void *ptr);

#define  INTERNAL_ERROR   0x7FFFFFFF;

/* english characters diapasone */
#define LATIN_CHARS 'A','z'
/* russian characters diapasone ( KOI8 char set) */
#define KOI8R_CHARS 192,255

#include <ctype.h>
#include "usclasses.h"

/* characters set enum types */
typedef enum{etKoi=0,etDos,etWin,etMac} TEncodingType;

/* token enum type */
typedef enum{ttUnknown=0,ttDelim,ttDigit,ttAlpha,ttString} TTokenType;

extern "C" {
/* checking for matches from reqular expressions */
int isMatch(char const *pattern, char const *text);

/* functions for working with russian encoded strings */
char *strrupr(char *dest, char const *src);
char *strrlwr(char *dest, char const *src);
int  strrcmp(char const *dest, char const *src);
int  strrncmp(char const *dest, char const *src, int n);
int  strrcasecmp(char const *dest, char const *src);
int  strrncasecmp(char const *dest, char const *src, int n);
char *strrconv(char *dest, TEncodingType en1,
               char const *src, TEncodingType en2);
char *strrnconv(char *dest, TEncodingType en1,
                char const *src, TEncodingType en2, int n);

#ifdef WIN32
#define strcasecmp      _stricmp
#endif

// type checking functions
#define isdelim(c) (strchr(" :;,+-<>/*%^=()[]|&~@#$`{}\t\r\n",(c))!=NULL)
#define isquote(c) (c=='\'' || c=='\"')
#define iswhite(c) (c==' ' || c=='\t')
#define iseol(c)   (c=='\r' || c=='\n')

/***** functions that converts strings into any representations ****/
/* -into removable format */
char *strwrap(char *dest, const char *src);
/* -from removable format */
char *strunwrap(char *dest, const char *src);


/******* functions that does tokenizing ***************************/

/* func. extract token from string */
TTokenType extractToken(char *buffer, char *token);
/* func. puts token to string */
void putbackToken(char *buffer,char *token);
/* func. deletes quotes from string */
char *deleteQuotes(char *buffer);

/* functions for work with parameter strings */
char *extractParamByNo(char *buffer, int keyNo);
char *extractParam(char *buffer, char *key);
void splitParams(char *params, USStringList *names, USStringList *values);
void splitPrgParams(int argc, char *argv[], USStringList *names, USStringList *values);

/* english characters diapasone */
#define LATIN_CHARS 'A','z'
/* russian characters diapasone ( KOI8 char set) */
#define KOI8R_CHARS 192,255

/* func. returns a random string
   where buff  - buffer to save the string;
         num   - number characters;
         begin, end - diapasone of characters */
char *randString(char *buff, int num, int begin, int end);
char * _gt_(char *string);
}
#endif
