#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}

// Added by Ansh Prakash
void itoa(int n,char* buf) {
    // char* ret = NULL;
    int numChars = 0;
    // Determine if integer is negative
    int isNegative = 0;
    if (n < 0) {
        n = -n;
        isNegative =1;
        numChars++;
    }
    // Count how much space we will need for the string
    int temp = n;
    do {
        numChars++;
        temp /= 10;
    } while ( temp );
    //Allocate space for the string (1 for negative sign, 1 for each digit, and 1 for null terminator)
    // char buf[numChars + 1];
    // ret = new char[ numChars + 1 ];
    buf[numChars] = 0;
    //Add the negative sign if needed
    if (isNegative) buf[0] = '-';
    // Copy digits to string in reverse order
    int i = numChars - 1;
    do {
        buf[i--] = n%10 + '0';
        n /= 10;
    } while (n);
}