#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "usfunc.h"

extern "C" {

char *tableCollate = "áâ÷çäåöúéêëìíîïğòóôõæèãşûıÿùøüàñÁÂ×ÇÄÅÖÚÉÊËÌÍÎÏĞÒÓÔÕÆÈÃŞÛİßÙØÜÀÑ";
char *tableUpper = "áâ÷çäåöúéêëìíîïğòóôõæèãşûıÿùøüàñ";
char *tableLower = "ÁÂ×ÇÄÅÖÚÉÊËÌÍÎÏĞÒÓÔÕÆÈÃŞÛİßÙØÜÀÑ";

static int charrcoll (unsigned char c) {
  if (c<192) return c;
  for (int i=0; tableCollate[i]; i++)
    if (((unsigned char)tableCollate[i])==c) return i + 192;
  return c;
}

static int charrcasecoll (unsigned char c) {
  if (c>='a' && c<='z') return c - 'a' + 'A';
  if (c<192) return c;
  for (int i=0; tableCollate[i]; i++)
    if (((unsigned char)tableCollate[i])==c) return ((i>=32)?i-32:i) + 192;
  return c;
}

char *strrupr(char *dest, char const *src) {
  int i;
  for (i=0; src[i]; i++) {

    dest[i] = src[i];
    if ((src[i]>='a') && (src[i]<='z')) dest[i] = src[i] - 'a' + 'A';
    if ((src[i]>='À') && (src[i]<='ß'))
      for(int j=0; tableLower[j]; j++)
        if(tableLower[j]==src[i]) dest[i] = tableUpper[j];
  }
  dest[i] = 0;
  return dest;
}

char *strrlwr(char *dest, char const *src) {
  int i;
  for (i=0; src[i]; i++) {
    dest[i] = src[i];
    if ((src[i]>='A') && (src[i]<='Z')) dest[i] = src[i] - 'A' + 'a';
    if (src[i]>='ß')
      for(int j=0; tableUpper[j]; j++)
        if(tableUpper[j]==src[i]) dest[i] = tableLower[j];
  }
  dest[i] = 0;
  return dest;
}

int strrcmp(char const *s1, char const *s2) {
  int i=0;
  while ((s1[i]!=0)&&(s2[i]!=0)) {
    if (s1[i]!=s2[i])
      return charrcoll((unsigned char)s1[i])-charrcoll((unsigned char)s2[i]);
    i++;
  }
  return strlen(s1)-strlen(s2);
}

int strrcasecmp(char const*s1, char const*s2) {
  int i=0, c1, c2;
  while ((s1[i]!=0)&&(s2[i]!=0)) {
    c1 = charrcasecoll((unsigned char)s1[i]);
    c2 = charrcasecoll((unsigned char)s2[i]);
    if (c1!=c2) return c1-c2;
    i++;
  }
  return strlen(s1)-strlen(s2);
}

int strrncmp(char const *s1, char const *s2, int n) {
  int i=0;
  while ((s1[i]!=0)&&(s2[i]!=0)&&(i<n)) {
    if (s1[i]!=s2[i])
      return charrcoll((unsigned char)s1[i])-charrcoll((unsigned char)s2[i]);
    i++;
  }
  return strlen(s1)-strlen(s2);
}

int strrncasecmp(char const*s1, char const*s2, int n) {
  int i=0;
  while ((s1[i]!=0)&&(s2[i]!=0)&&(i<n)) {
    if (s1[i]!=s2[i])
      return charrcasecoll((unsigned char)s1[i])-charrcasecoll((unsigned char)s2[i]);
    i++;
  }
  return strlen(s1)-strlen(s2);
}

/*****************************************************************
  It allows unix grep-like pattern comparisons, for instance:

  ?      Matches any single characer
  *      Matches any contiguous characters
  [abc]  Matches a or b or c at that position
  [^abc] Matches anything but a or b or c at that position
  [!abc] Ditto
  [a-e]  Matches a through e at that position

****************************************************************/

//  match defines
#define MATCH_PATTERN   6
#define MATCH_LITERAL   5
#define MATCH_RANGE     4
#define MATCH_ABORT     3
#define MATCH_END       2
#define MATCH_VALID     1
//  pattern defines
#define PATTERN_VALID   0
#define PATTERN_ESC     -1
#define PATTERN_RANGE   -2
#define PATTERN_CLOSE   -3
#define PATTERN_EMPTY   -4
//  character defines
#define MATCH_CHAR_SINGLE               '?'
#define MATCH_CHAR_KLEENE_CLOSURE       '*'
#define MATCH_CHAR_RANGE_OPEN           '['
#define MATCH_CHAR_RANGE                '-'
#define MATCH_CHAR_RANGE_CLOSE          ']'
#define MATCH_CHAR_CARAT_NEGATE         '^'
#define MATCH_CHAR_EXCLAMATION_NEGATE   '!'

int ismatch(const char *pattern, const char *text);
static int matche(const char *pattern, const char *text);
static int matchAfterStar(const char *pattern, const char *text);

//********************** Functions implementation *********************
#define MAX_PATTERN_SIZE 255
#define MAX_TEXT_SIZE 512

BOOL isMatch(const char *pattern, const char *text) {
  return matche(pattern, text) == 1;
}

static int matche(const char *pattern, const char *text) {
  int rangeStart, rangeEnd, p = 0, t = 0, plen, tlen, result = 0;
  BOOL invert, memberMatch, loop;

  plen = strlen(pattern);
  tlen = strlen(text);
  while ( (result == 0) && (p < plen) ) {
    if (t > tlen) {
      if ((pattern[p] == MATCH_CHAR_KLEENE_CLOSURE) && (p >= plen))
        return MATCH_VALID;
      else
        return MATCH_ABORT;
    } else
      switch (pattern[p]) {
        case MATCH_CHAR_KLEENE_CLOSURE:
          result = matchAfterStar(pattern+p,text+t);
          break;
        case MATCH_CHAR_RANGE_OPEN: {
          p++;
          invert = FALSE;
          if ((pattern[p] == MATCH_CHAR_EXCLAMATION_NEGATE) ||
              (pattern[p] == MATCH_CHAR_CARAT_NEGATE)) {
            invert = TRUE;
            p++;
          }
          if (pattern[p] == MATCH_CHAR_RANGE_CLOSE) return MATCH_PATTERN;
          memberMatch = FALSE;
          loop = TRUE;
          while ((loop) && (pattern[p] != MATCH_CHAR_RANGE_CLOSE)) {
            rangeStart = rangeEnd = p;
            p++;
            if (p >= plen) return MATCH_PATTERN;
            if (pattern[p] == MATCH_CHAR_RANGE) {
              p++;
              rangeEnd = p;
              if ((p >= plen) || (pattern[rangeEnd] == MATCH_CHAR_RANGE_CLOSE))
                return MATCH_PATTERN;
              p++;
            }
            if (p >= plen) return MATCH_PATTERN;
            if (rangeStart < rangeEnd) {
              if ((text[t] >= pattern[rangeStart]) &&
                 (text[t] <= pattern[rangeEnd])) {
                memberMatch = TRUE;
                loop = FALSE;
              };
            } else {
              if ((text[t] >= pattern[rangeEnd]) &&
                (text[t] <= pattern[rangeStart])) {
                memberMatch = TRUE;
                loop = FALSE;
              }
            } // if (range_start < range_end)
         } // while (loop)
         if ((invert && memberMatch) || (!(invert || memberMatch))) return MATCH_RANGE;
         if (memberMatch)
           while ((p < plen) && (pattern[p] != MATCH_CHAR_RANGE_CLOSE)) p++;
         if (p >= plen) return MATCH_PATTERN;
         break;
        }  // MATCH_CHAR_RANGE_OPEN:
        default:
          if (pattern[p] != MATCH_CHAR_SINGLE)
            if (pattern[p] != text[t]) result = MATCH_LITERAL;
      } // Case pbuffer[p]
    p++;
    t++;
  } // While ( (Result = 0) and (p < plen) )
  if (result == 0) {
    if (t < tlen) return MATCH_END;
    else return MATCH_VALID;
  } else return result;
}

static int matchAfterStar(const char *pattern,const char *text) {
  int p = 0, t = 0, plen, tlen, result = 0;

  if (matche(pattern+1,text)==MATCH_VALID) return MATCH_VALID;

  plen = strlen(pattern);
  tlen = strlen(text);
  while ((( t < tlen ) && (p < plen)) &&
         (pattern[p] == MATCH_CHAR_SINGLE) || (pattern[p] == MATCH_CHAR_KLEENE_CLOSURE)) {
    if (pattern[p] == MATCH_CHAR_SINGLE) t++;
    p++;
  };
  if (t >= tlen) return MATCH_ABORT;
  if (p >= plen) return MATCH_VALID;
  do {
    if ((pattern[p] == text[t]) || (pattern[p] == MATCH_CHAR_RANGE_OPEN)) {
      pattern += p;
      text += t;
      plen = strlen(pattern);
      tlen = strlen(text);
      p = t = 0;
      result = matche( pattern , text );
    }
    if (t >= tlen) return MATCH_ABORT;
    t++;
  } while( result == 0 );
  return (result)? result : MATCH_ABORT;
}

char *randString(char *buff, int num, int begin, int end) {
  int i;
  for( i = 0; i < num;) buff[i++] = begin + rand() % (end - begin - 1);
  buff[i] = 0;
  return buff;
}
char * _gt_(char *string)
{
	return string;
};

} // end of extern "C"
