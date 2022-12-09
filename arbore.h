//Preda Ioan Alexandru-313CB
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
typedef struct fisier{
     char *nume;
     struct fisier *st,*dr,*par;

}TNod,*TArb;

TArb InitA();           /* initializare arbore */
TArb ConstrNod(char* x, TArb s, TArb d,TArb p); 
     /* -> adresa nod (cu info x, fiu stanga s, fiu dreapta d)
		   sau NULL daca nu exista spatiu */
TArb ConstrFr(char* x);
void distruge(TArb);
     /* -> adresa frunza cu informatia x, sau NULL daca nu exista spatiu */
void DistrArb(TArb *);    /* distruge arbore */
int NrNoduri(TArb);     /* numar noduri */
int NrNiv(TArb);        /* numar niveluri (0 pentru arbore vid) */
