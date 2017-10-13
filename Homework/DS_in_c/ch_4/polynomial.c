#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define None NULL
/*
typedef union  
{
	int num;
	pTerm formula;
}Ct;
*/
typedef struct term
{
     //bool flag;
	 //Ct coefficient;
	 double ct;
	 int power;
     struct term * next;
}Term;

typedef Term * pTerm;

typedef struct list
{
	pTerm head;
	pTerm target;
    pTerm tail;
}Polynomial;

typedef Polynomial * pPolynomial;

pPolynomial init()
{
	pPolynomial newPolynomial = (pPolynomial)calloc(1, sizeof(Polynomial));
	if (newPolynomial == None)
	{
		puts("init err");
		exit(0);
	}
	newPolynomial->head = None;
	newPolynomial->target = None;
	return newPolynomial;
}

void insert(pPolynomial tP,pTerm tN)
{
     if ( tP->head == None)
     {
          tP->head = tP->tail = tN;
     }
     else
     {
          tP->target = tP->head;
          if( tN->power < tP->head->power)
          {
               tN->next = tP->head;
               tP->head = tN;
          }else
          {
               while( tP->target->next != None &&
                      tP->target->next->power < tN->power)
                    tP->target = tP->target->next;
               if ( tP->tail = tP->target)
               {
                    tP->tail->next = tN;
                    tP->tail = tN;
               }
               else
               {
                    tN->next = tP->target->next;
                    tP->target->next = tN;
               }
          }
     }
     
     tP->target = None;
}

void delNode(pPolynomial tP)
{
	pTerm tmp = None;
	if (tP->head == tP->target)
	{
		tmp = tP->head;
		tP->head = tP->head->next;
		free(tmp);
	}
	else
	{
		tmp = tP->target->next;
		tP->target->next = tmp->next;
		free(tmp);
	}
}

void clear(pPolynomial tP)
{
	pTerm tmp = tP->head;
	tP->target = tP->head->next;
	while (tmp != None)
	{
		free(tmp);
		tmp = tP->target;
		tP->target = tP->target->next;
	}
	free(tP);
}

void moveZero(pPolynomial tP)
{
	pTerm tmp = None;
	while (tP->head->ct == 0)
	{
		tmp = tP->head;
		tP->head = tP->head->next;
		free(tmp);
	}
}

void add(pPolynomial a,pPolynomial b)
{
	a->target = a->head;
	b->target = b->head;
	while (a->target && b->target)
		switch (cmp(a->target, b->target))
		{
			case  0:
				a->target->ct += b->target->ct;
				a->target = a->target->next;
				b->target = b->target->next;
				break;
			case  1:
				a->target = a->target->next;
				break;
			case -1:
				insert(a,b->target);
				a->target = a->target->next->next;
                b->target = b->target->next;
				break;
		}
	if (b->target)
		{
			a->tail->next = b->target;
			a->tail = b->tail;
		}
	//clear(b);
}

int cmp(pTerm a,pTerm b)
{
	if(a->power == b->power)
		return 0;
	else if (a->power > b->power)
		return 1;
	else
		return -1;
}

pTerm creatTerm()
{
	pTerm newT = (pTerm)calloc(1,sizeof(Term));
	if (newT == None)
	{
		puts("creat err.");
		exit(0);
	}

	newT->ct = 0;
	newT->power = 0;
	newT->next = None;
	}

void input(pPolynomial tP)
{
	pTerm tmp = creatTerm();
	scanf("%lf %d", &tmp->ct, &tmp->power);
	while (tmp->ct || tmp->power)
	{
		insert(tP,tmp);
        tmp = creatTerm( );
		scanf("%lf %d", &tmp->ct, &tmp->power);
	}
}

void traverse (pPolynomial tP, void (*pfun)(pTerm tN))
{
	tP->target = tP->head;
	while(tP->target != None)
	{
		(*pfun) (tP->target);
		tP->target = tP->target->next;
	}
}

void show(pTerm tN)
{
	printf("%+lfx^%d",tN->ct,tN->power);
}
void printP(pPolynomial tP)
{
	traverse(tP,show);
}

void opposite(pTerm tN)
{
	tN->ct = -tN->ct;
}

void sub(pPolynomial a, pPolynomial b)
{
	traverse(b,opposite);
	add(a,b);
}

int main()
{
	pPolynomial a = init();
	pPolynomial b = init();
    puts( "input a:");
	input(a);
    puts( "input b:");
	input(b);
	add(a,b);
    moveZero( a);
    printP( a);
	//sub(a,b);
	//printP(a);
	//clear(a);
	return 0;
}

























