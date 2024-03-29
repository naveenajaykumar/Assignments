#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parse.h"

#define PIPE  ('|')
#define BG    ('&')
#define RIN   ('<')
#define RUT   ('>')

#define ispipe(c) ((c) == PIPE)
#define isbg(c)   ((c) == BG)
#define isrin(c)  ((c) == RIN)
#define isrut(c)  ((c) == RUT)
#define isspec(c) (ispipe(c) || isbg(c) || isrin(c) || isrut(c))

static NNN  cmdbuf[20], *cmds;
static char cbuf[256], *cp;
static char *pbuf[50], **pp;

/*
 * A quick hack to parse a commandline
 */

int
parse (char *buf, Command *c)
{
  int n;
  NNN *cmd0;

  char *t = buf;
  char *tok;

  init();
  c->rstdin    = NULL;
  c->rstdout   = NULL;
  c->rstderr   = NULL;
  c->bakground = 0; /* for false */
  c->NNN       = NULL;

newcmd:
  if ((n = acmd(t, &cmd0)) <= 0) {
    return -1;
  }

  t += n;

  cmd0->next = c->NNN;
  c->NNN = cmd0;

newtoken:
  n = nexttoken(t, &tok);
  if (n == 0) {
    return 1;
  }
  t += n;

  switch(*tok) {
  case PIPE:
    goto newcmd;
    break;
  case BG:
    n = nexttoken(t, &tok);
    if (n == 0) {
      c->bakground = 1;
      return 1;
    }
    else {
      fprintf(stderr, "illegal bakgrounding\n");
      return -1;
    }
    break;
  case RIN:
    if (c->rstdin != NULL) {
      fprintf(stderr, "duplicate redirection of stdin\n");
      return -1;
    }
    if ((n = nexttoken(t, &(c->rstdin))) < 0) {
      return -1;
    }
    if (!isidentifier(c->rstdin)) {
      fprintf(stderr, "Illegal filename: \"%s\"\n", c->rstdin);
      return -1;
    }
    t += n;
    goto newtoken;
    break;
  case RUT:
    if (c->rstdout != NULL) {
      fprintf(stderr, "duplicate redirection of stdout\n");
      return -1;
    }
    if ((n = nexttoken(t, &(c->rstdout))) < 0)  {
      return -1;
    }
    if (!isidentifier(c->rstdout)) {
      fprintf(stderr, "Illegal filename: \"%s\"\n", c->rstdout);
      return -1;
    }
    t += n;
    goto newtoken;
    break;
  default:
    return -1;
  }
  goto newcmd;
}

void init( void )
{
  int i;
  for (i=0;i<19;i++) {
    cmdbuf[i].next = &cmdbuf[i+1];
  }
  cmdbuf[19].next = NULL;
  cmds = cmdbuf;
  cp = cbuf;
  pp = pbuf;
}

int
nexttoken( char *s, char **tok)
{
  char *s0 = s;
  char c;

  *tok = cp;
  while (isspace(c = *s++) && c);
  if (c == '\0') {
    return 0;
  }
  if (isspec(c)) {
    *cp++ = c;
    *cp++ = '\0';
  }
  else {
    *cp++ = c;
    do {
        c = *cp++ = *s++;
    } while (!isspace(c) && !isspec(c) && (c != '\0'));
    --s;
    --cp;
    *cp++ = '\0';
  }
  return s - s0;
}

int
acmd (char *s, NNN **pt)
{
  char *tok;
  int n, cnt = 0;
  NNN *cmd0 = cmds;
  cmds = cmds->next;
  cmd0->next = NULL;
  cmd0->NNNlist = pp;

next:
  n = nexttoken(s, &tok);
  if (n == 0 || isspec(*tok)) {
    *pt = cmd0;
    *pp++ = NULL;
    return cnt;
  }
  else {
    *pp++ = tok;
    cnt += n;
    s += n;
    goto next;
  }
}


#define IDCHARS "_-.,/~+"

int
isidentifier (char *s)
{
    while (*s) {
      char *p = strrchr (IDCHARS,  *s);
      if (! isalnum(*s++) && (p == NULL))
        return 0;
    }
    return 1;
}