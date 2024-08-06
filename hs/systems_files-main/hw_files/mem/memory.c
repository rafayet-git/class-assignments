#include <stdio.h>

int main()
{
  char ch = 5;
  int num = 1005;
  long lo = 4324234;

  printf("char: %p %u \n",&ch, &ch);
  printf("int: %p %u \n",&num, &num);
  printf("long: %p %u \n\n",&lo, &lo);

  char* chp = &ch;
  int* nup = &num;
  long* lop = &lo;

  printf("char pointer: %p %p\n",chp, &chp);
  printf("int pointer: %p %p \n",nup, &nup);
  printf("long pointer: %p %p\n\n",lop, &lop);

  printf("pointers after adding +1 \n");
  
  *chp++;
  *nup++;
  *lop++;
  
  printf("char: %d %p \n",*chp, chp);
  printf("int: %d %p \n",*nup, nup);
  printf("long: %ld %p \n\n",*lop, lop);
  
  unsigned int more = 1+2+4+256+512+1024;
  int* point1 = &more;
  char* point2 = &more;
  printf("int pointer: %p points to: %d \n", point1, *point1);
  printf("char pointer: %p points to: %d \n", point2, *point2);
  printf("unsigned int decimal: %x hex: %u %d  \n\n", &more, &more, more);
  
  char* intpointer1 = point2;
  char* intpointer2 = point2+1;
  char* intpointer3 = point2+2;
  char* intpointer4 = point2+3;

  printf("byte 1: %x %u %d\n", intpointer1, intpointer1, *intpointer1);
  printf("byte 2: %x %u %d\n", intpointer2, intpointer2, *intpointer2 );
  printf("byte 3: %x %u %d\n", intpointer3, intpointer3, *intpointer3 );
  printf("byte 4: %x %u %d\n\n", intpointer4, intpointer4, *intpointer4 );
  
  (*intpointer1)++;
  printf("1st byte increment, unsigned int decimal: %x hex: %u %d  \n", &more, &more, more);
  (*intpointer2)++;
  printf("2nd byte increment, unsigned int decimal: %x hex: %u %d  \n", &more, &more, more);
  (*intpointer3)++;
  printf("3rd byte increment, unsigned int decimal: %x hex: %u %d  \n", &more, &more, more);
  (*intpointer4)++;
  printf("4th byte increment, unsigned int decimal: %x hex: %u %d  \n\n", &more, &more, more);

  printf("byte 1: %x %u %d\n", intpointer1, intpointer1, *intpointer1);
  printf("byte 2: %x %u %d\n", intpointer2, intpointer2, *intpointer2 );
  printf("byte 3: %x %u %d\n", intpointer3, intpointer3, *intpointer3 );
  printf("byte 4: %x %u %d\n\n", intpointer4, intpointer4, *intpointer4 );
  
  more = 1+2+4+256+512+1024;
  printf("adding 16 to each byte\n");
  (*intpointer1) += 16;
  printf("1st byte increment, unsigned int decimal: %x hex: %u %d  \n", &more, &more, more);
  (*intpointer2) += 16;
  printf("2nd byte increment, unsigned int decimal: %x hex: %u %d  \n", &more, &more, more);
  (*intpointer3) += 16;
  printf("3rd byte increment, unsigned int decimal: %x hex: %u %d  \n", &more, &more, more);
  (*intpointer4) += 16;
  printf("4th byte increment, unsigned int decimal: %x hex: %u %d  \n", &more, &more, more);
  printf("byte 1: %x %u %d\n", intpointer1, intpointer1, *intpointer1);
  printf("byte 2: %x %u %d\n", intpointer2, intpointer2, *intpointer2 );
  printf("byte 3: %x %u %d\n", intpointer3, intpointer3, *intpointer3 );
  printf("byte 4: %x %u %d\n\n", intpointer4, intpointer4, *intpointer4 );
  return 0;
}
