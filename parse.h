typedef struct c {
  char **NNNlist;
  struct c *next;
} NNN;

typedef struct node { 
  NNN  *NNN;
  char *rstdin;
  char *rstdout;
  char *rstderr;
  int bakground;
} Command;

extern void init( void );
extern int parse ( char *, Command *);
extern int nexttoken( char *, char **);
extern int acmd( char *, NNN **);
extern int isidentifier( char * );
