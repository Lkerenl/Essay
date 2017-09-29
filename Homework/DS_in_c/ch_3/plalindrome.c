#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define None NULL
typedef struct node
{
     char chr;
     struct node * last;
     struct node * next;
}Node;
typedef Node * pNode;

typedef struct stack
{
     pNode bp;
     pNode sp;
     int size;
}Stack;
typedef Stack * pStack;

pStack init(void)
{
     pStack newStack = ( pStack) calloc(1, sizeof( Stack));
     if ( newStack == None)
     {
          printf( "init err.");
          exit( 0);
     }
     
     newStack->bp = None;
     newStack->sp = None;
     newStack->size = 0;
     
     return newStack;
}

pNode creatNode(char chr)
{
     pNode newNode = ( pNode) calloc(1, sizeof( Node));
     if ( newNode == None)
     {
          printf( "creat node err.");
          exit( 0);
     }

     newNode->chr = chr;
     newNode->last = None;
     newNode->next = None;
     
     return newNode;
}

void push( pStack tStack, char chr)
{
     pNode newNode = creatNode( chr);
     if ( tStack->size == 0)
     {
          tStack->sp = newNode;
          tStack->bp = newNode;
     }
     else
     {
          newNode->next = tStack->sp;
          tStack->sp->last = newNode;
          tStack->sp = newNode;
     }
     
     tStack->size += 1;
}

char pop( pStack tStack)
{
     char n = 0;
     pNode tmp = tStack->sp;
     if ( tmp != None && tStack->size > 0)
     {
          tStack->sp = tStack->sp->next;
          n = tmp->chr;
          free(tmp);
          tStack->size -= 1;
          
          if ( tStack->size == 0)
          {
               tStack->sp = None;
               tStack->bp = None;
          }
     }
     else
     {
          printf( "pop err/\n");
          exit( 0);
     }
     return n;
}

bool cmpStack( pStack a, pStack b)
{
     if ( a->size == b->size)
     {
          while (a->size!=0 && b->size!=0)
          {
               if ( pop( a) != pop( b))
                    return false;
          }
     }
     else
     {
          pop( a);
          return cmpStack( a,b);
     }
     return true;
}

bool isPlalindrome( char * string)
{
     int i;
     int n =strlen( string);
     int m = n/2;                        //in c 7/2 == 6/2 == 3
     pStack a = init();
     pStack b = init();

     for ( i=0; i<n;i++)                 //push string one by one in a...
     {
          push( a,string[i]);
     }

     for ( i=0; i<m;i++)                 //pop count backwards in a and push in b...
     {
          push( b,pop( a));
     }
     
     
     return cmpStack(a,b);               //Compare the previous m numbers in stack a and b...
}

int main(int argc, char *argv[])
{
     if( argc < 2)
     {
          printf( "no input.\n");
     }
     else
     {
          printf( "%s\n", isPlalindrome(argv[1])?"True":"False");
     }
     
     return 0;
}
