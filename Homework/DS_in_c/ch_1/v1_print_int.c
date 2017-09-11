#include <stdio.h>

typedef struct leave{int cf; double number;}le;

le sal(double);
void print_int(int);
void printdigit(int);
void print_number( double,int);
void print_double( double,int);

int main(int argc, char *argv[])
{
     print_number( 0,0);
     print_number( 135,0);
     print_number( -456,0);
     print_number( 123.1546,4);
     print_number( -1236.16423,5);
     return 0;
}

void printdigit(int number)
{
    printf("%d",number);
}

le sal(double decimal)
{
    le a;
    a.cf = (int)(decimal * 10);
    a.number = decimal * 10 - a.cf;
    return a;
}

void print_int( int number)
{
     if ( number>=10)
          print_int( number/10);
     printdigit( number%10);
}

void print_double( double number,int size)
{
     le a;
     int i = 0;
     
     print_int( (int)number);
     putchar( '.');

     a.number = number - (int)number;
     
     for ( ; i<size; i++)
     {
          a = sal( a.number);
          printdigit( a.cf);
     }
}

void print_number( double number,int size)
{
     int i=0;
     double a;
     if ( number<0)
     {
          putchar( '-');
          number = -number;
     }
     
     if ( number == (int) number)
          print_int( (int) number);
     else
     {
          print_double( number,size);
          
     }
     
     putchar( '\n');
}
