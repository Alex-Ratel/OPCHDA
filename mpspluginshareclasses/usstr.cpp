#include "usstr.h"
#include "usfunc.h"

//******************** USString implementation *********************

USString::USString(int newLen) {
  setObjectName( "USString");
  buffLen = len = 0;
  buff = alloc(newLen);
  buff[0] = 0;
}

USString::USString(char *s) {
  setObjectName( "USString");
  len = strlen(s);
  buffLen = 0;
  buff = alloc(len);
  strncpy(buff,s,len);
  buff[len] = 0;
}

USString::USString(USString &v) {
  setObjectName( "USString");
  len = strlen(v.getChars());
  buffLen = 0;
  buff = alloc(len);
  strncpy(buff, v.getChars(),len);
  buff[len] = 0;
}

USString::~USString(void) {
  free();
}

char *USString::alloc(int n) {
  char *tmp=NULL;
  len = n;
  n+=5;
  if (buffLen<n || buffLen>=n+MIN_BUFFER_LEN) {
    buffLen = (n / MIN_BUFFER_LEN) * MIN_BUFFER_LEN;
    buffLen += (buffLen >= n) ? 0 : MIN_BUFFER_LEN;
    tmp = (char*) malloc(buffLen);
    tmp[0] = 0;
  };
  return tmp;
}

void USString::free(void) {
  ::free(buff);
  len = buffLen = 0;
  buff = NULL;
}

USString &USString::append(char *s) {
  int oldLen = len;
  char *tmp = alloc(len+strlen(s));
  if (tmp) {
    strcpy(tmp,buff);
    ::free(buff);
    buff = tmp;
  }
  strncat(buff, s, buffLen+oldLen);
  return *this;
}

USString &USString::assign(char *s) {
  char *tmp;
  
  if (s) {
    tmp = alloc(strlen(s));
    if (tmp) {
  
      ::free(buff);
      buff = tmp;
    }
    strncpy(buff, s, buffLen);
  } else buff[0]=0;
  return *this;
}

bool USString::startWith(char *s) {
  int sl=strlen(s);
  if (sl>len) return false;
  return (strncmp(buff,s,sl)) ? false : true;
}

bool USString::endWith(char *s) {
  int sl=strlen(s);
  if (sl>len) return false;
  return (strncmp(buff+len-sl,s,sl)) ? false : true;
}
/*
USString &USString::subString(int p, int n) {
  USString *tmp = new USString(n);
  if (tmp) {
	strncpy(tmp->buff,buff+p,n);
	tmp->buff[n] = 0;
  }
  return *tmp;
}

USString &USString::left(int n) {
  USString *tmp = new USString(n);
  if (tmp) {
	strncpy(tmp->buff,buff,n);
	tmp->buff[n] = 0;
  }
  return *tmp;
}

USString &USString::right(int n) {
  USString *tmp = new USString(n);
  if (tmp) strncpy(tmp->buff,buff+len-n,n);
  return *tmp;
}
*/
USString &USString::trimLeft(void) {
  int i=0;
  while ((i<len)&&(buff[i]==' ' || buff[i]=='\t')) i++;
  if (i) {
    char *tmp = alloc(len - i);
    if (tmp) {
      strncpy(tmp, buff+i, len);
      ::free(buff);
      buff = tmp;
    } else strncpy(buff, buff+i, len);
  }
  return *this;
}

USString &USString::trimRight(void) {
  int i=len-1;
  while ((i>0)&&(buff[i]==' ' || buff[i]=='\t')) i--;
  if (i) {
    char *tmp = alloc(++i);
    if (tmp) {
      strncpy(tmp, buff,len=i);
      ::free(buff);
      buff = tmp;
    } else buff[len=i] = 0;
  }
  return *this;
}

USString &USString::trim(void) {
  int i=0, j=len-1;
  while ((i<len)&&(buff[i]==' ' || buff[i]=='\t')) i++;
  while ((j>0)&&(buff[j]==' ' || buff[j]=='\t')) j--;
  if (i) {
    char *tmp = alloc(j-i+1);
    if (tmp) {
      strncpy(tmp, buff+i, j-i+1);
      ::free(buff);
      buff = tmp;
    } else strncpy(buff, buff+i, j-i+1);
  }
  return *this;
}

int USString::indexOf(char c, int n) {
  for(int i=n; i<len; i++)
    if (buff[i]==c) return i;
  return -1;
}

int USString::lastIndexOf(char c, int n) {
  for(int i=len-1; i>=n; i--)
    if (buff[i]==c) return i;
  return -1;
}

USString &USString::replace(char c1, char c2) {
  for(int i=0; i<len; i++)
    if (buff[i]==c1) buff[i] = c2;
  return *this;
}

int USString::compare(char *s, int n) {
  if (n) return strrncmp(buff, s, n);
  return strrcmp(buff, s);
}

int USString::compareIgnoreCase(char *s, int n) {
  if (n) return strrncasecmp(buff, s, n);
  return strrcasecmp(buff, s);
}

USString &USString::toUpperCase(void) {
  strrupr(buff, buff);
  return *this;
}

USString &USString::toLowerCase(void) {
  strrlwr(buff, buff);
  return *this;
}

