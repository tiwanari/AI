#include "defs.h"
#include <malloc.h>

#define BONUS 10000

move(i,j,st,mode,depth,judge,bags)
struct state *st,*bags;
int i,j,mode,depth,judge;
{
    register int n;
    struct state *p;



/*
    printf("To move mode=%d i=%d j=%d... \n",mode,i,j);
    print(st);
*/

    if (!ok(i,j,st)) return DISABLE;

    st->ban[i][j]=ON;

    if ((judge==1) && check_closed(st,bags)) {
	st->ban[i][j]=EMPTY;
	return DISABLE;
    }
    if (judge==1) {
/*	printf("putting ...\n"); 
	print(st); */
	put_closed(st,bags);
/*	printf(" with bags\n"); 
	if (bags!=NULL)
	    for (p=bags; p!=NULL; p=p->next)
 		print(p);  
	printf(" with end of bags\n"); */
    }
    st->eval = evaluate(st,mode);
/*    if (st->eval ==BONUS) {
	printf("BONUS");
	print(st);
    } */
    return ENABLE;
}

free_bags(closed)
struct state *closed;
{

    if (closed->next != NULL) free_bags(closed->next);
    free(closed);  
}

put_closed(st,closed)
struct state *st,*closed;
{
    struct state *w,*copy();
    
    w=copy(st);

    if (closed==NULL) {
	printf("Error in put_closed NULL\n"); 
    }
    w->next = closed->next;
    closed->next = w;
}


int check_closed(st,closed)
struct state *st,*closed;
{
    struct state *p;

/*
    printf("checking...\n"); 
    print(st);
    printf(" with Q \n"); 
    if (closed!=NULL)
	for (p=closed; p!=NULL; p=p->next)
	    print(p);  
    printf(" with end of Q \n"); 
*/
    for (p=closed; p!=NULL; p=p->next) {
	    if (eq_state(st,p)) {
/*	    printf("---> Euqal states\n");  */
	    return 1;
	}
    }
    return 0;
}

eq_state(s1,s2)
struct state *s1,*s2;
{
    int tmp[NNN][NNN],tmp2[NNN][NNN];

    if (eq_3_3(s1->ban,s2->ban)) return 1;
    rotate90(s1->ban,tmp);
    if (eq_3_3(tmp,s2->ban)) return 1;
    rotate180(s1->ban,tmp);
    if (eq_3_3(tmp,s2->ban)) return 1;
    rotate270(s1->ban,tmp);
    if (eq_3_3(tmp,s2->ban)) return 1;
    rev(s1->ban,tmp2);
    if (eq_3_3(tmp2,s2->ban)) return 1;
    rotate90(tmp2,tmp);
    if (eq_3_3(tmp,s2->ban)) return 1;
    rotate180(tmp2,tmp);
    if (eq_3_3(tmp,s2->ban)) return 1;
    rotate270(tmp2,tmp);
    if (eq_3_3(tmp,s2->ban)) return 1;

    return 0;

}


eq_3_3(ban1,ban2)
int ban1[NNN][NNN],ban2[NNN][NNN];
{
    register int i,j;

    for (i=0; i<NNN; i++) 
	for (j=0; j<NNN; j++)
	    if (ban1[i][j]!=ban2[i][j]) return 0;
    return 1;
}    

rev(ban1,ban2)
int ban1[NNN][NNN],ban2[NNN][NNN];
{
    register int i,j;

    for (i=0; i<NNN; i++) 
	for (j=0; j<NNN; j++)
	    ban2[NNN-1-i][j]=ban1[i][j];
}    


rotate90(ban1,ban2)
int ban1[NNN][NNN],ban2[NNN][NNN];
{
    register int i,j;

    for (i=0; i<NNN; i++) 
	for (j=0; j<NNN; j++)
	    ban2[j][NNN-1-i]=ban1[i][j];
}    

rotate180(ban1,ban2)
int ban1[NNN][NNN],ban2[NNN][NNN];
{
    register int i,j;

    for (i=0; i<NNN; i++) 
	for (j=0; j<NNN; j++)
	    ban2[NNN-1-i][NNN-1-j]=ban1[i][j];
}    

rotate270(ban1,ban2)
int ban1[NNN][NNN],ban2[NNN][NNN];
{
    register int i,j;

    for (i=0; i<NNN; i++) 
	for (j=0; j<NNN; j++)
	    ban2[NNN-1-j][i]=ban1[i][j];
}    



ok(i,j,st)
struct state *st;
int i,j;
{
    int k;
    
    for (k=0;k<NNN;k++) {
	if (st->ban[i][k]!=EMPTY) return 0;
	if (st->ban[k][j]!=EMPTY) return 0;
    }
    for (k=1;k<NNN;k++) {
	if ((k+i)>=NNN || (k+j)>=NNN) break;
	if (st->ban[i+k][j+k]!=EMPTY) return 0;
    }
    for (k=1;k<NNN;k++) {
	if ((i-k)<0 || (j-k)<0) break;
	if (st->ban[i-k][j-k]!=EMPTY) return 0;
    }
    for (k=1;k<NNN;k++) {
	if ((k+i)>=NNN || (j-k)<0) break;
	if (st->ban[i+k][j-k]!=EMPTY) return 0;
    }
    for (k=1;k<NNN;k++) {
	if ((i-k)<0 || (k+j)>=NNN) break;
	if (st->ban[i-k][k+j]!=EMPTY) return 0;
    }
    return 1;
}


int safe;

check(st,mode)
struct state *st;
int mode;
{
    register int i,j;

    safe=0;

    for (i=0; i<NNN; i++)
	for (j=0; j<NNN; j++) 
	    if (ok(i,j,st)) safe++;

/*    printf("s/*afe=%d\n",safe);   */

    if (safe==0)
	if (mode==MAXMODE) return MYWIN;
        else return YOUWIN;

    if (full(st)) return DRAWN;
    return CONT;
}


evaluate(st,mode)
struct state *st;
int mode;
{
    switch(check(st,mode)) {
      case MYWIN: 
/*	printf("MYWIN\n"); 
	print(st);   */
	return BONUS;
      case YOUWIN: 
/*	printf("YOUWIN\n");
	print(st);  */
	return -BONUS;
      default: return -safe;
      }
}

int full(st)
struct state *st;
{
    register int i,j;
    
    for (i=0; i<NNN; i++)
        	for (j=0; j<NNN; j++) 
	               if (st->ban[i][j] == EMPTY) return 0;
	   return 1;
}

print(st)
struct state *st;
{
    register int i,j,k;

    for (i=0; i<2*NNN+1; i++) printf("-");    
    putchar('\n');
    for (i=0; i<NNN; i++) {
	printf("|");
	for (j=0; j<NNN; j++) {
	    if (st->ban[i][j] == ON) printf("o|");
	    else  printf(" |");
	}
	putchar('\n');
	for (k=0; k<2*NNN+1; k++) printf("-");    
	putchar('\n');
    }
    
    printf(" value(%d)\n",st->eval);
    putchar('\n');

}


stfree(st)
struct state *st;
{
    if (st==NULL) return;
    stfree(st->sist);
    stfree(st->daut);
    free(st);
}

#define CELLSIZE sizeof(struct state)

struct state *copy(st)
struct state *st;
{
    register int i,j;
    struct state *new;
    
    if ((new = (struct state *) malloc(CELLSIZE)) == NULL) {
	perror(" No more memory !!");
    }

    new->daut = new->sist = NULL;
    new->moth = st;
    
    for (i=0; i<NNN; i++)
	for (j=0; j<NNN; j++) 
	    new->ban[i][j]=st->ban[i][j];

    new->eval = 0;
    new->next = NULL;
    return new;
}

struct state *init()
{
    int i,j;
    struct state *st;
    
    if ((st = (struct state *) malloc(CELLSIZE)) == NULL) {
	perror(" No more memory !!");
    }

    for (i=0; i<NNN; i++)
	for (j=0; j<NNN; j++) 
	    st->ban[i][j]=EMPTY;

    st->eval =  0;
    st->moth = st-> sist = st->daut = NULL;
    st->next = NULL;
    return st;
}


