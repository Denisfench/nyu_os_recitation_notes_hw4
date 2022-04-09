#include <stdio.h>
#include <time.h>


struct A {
  int x;
  double z;
  short int y;
}; //


struct B {
  double z;
  int x;
  short int y;
};

int main() {
  time_t rawtime;
  struct tm *info;
  time(&rawtime);
  info = gmtime(&rawtime);

  /* Get GMT time */
  printf("%d\\%d\\%d\t%d\\%d\\%d\n", info->tm_mon + 1, info->tm_mday, 1900 + info->tm_year,\
         info->tm_hour, info->tm_min, info->tm_sec);


  // https://www.geeksforgeeks.org/is-sizeof-for-a-struct-equal-to-the-sum-of-sizeof-of-each-member/

  //    printf("sizeof(int) %ld \n", sizeof(int));
  //    printf("sizeof(double) %ld \n", sizeof(double));
  //    printf("sizeof(short int) %ld \n\n\n", sizeof(short int));
  //
  //    printf("Size of struct A is: %ld \n", sizeof(struct A));
  ////
  //    printf("\n *********** \n");
  ////
  ////    printf("sizeof(int) %ld \n", sizeof(int));
  ////    printf("sizeof(double) %ld \n", sizeof(double));
  ////    printf("sizeof(short int) %ld \n\n\n", sizeof(short int));
  ////
  //    printf("Size of struct B is: %ld \n", sizeof(struct B));
  return 0;
}
