#include <stdio.h>
#include <math.h>
#include <time.h>

int main()
{
 long int i;
 double sum=0.0, term, pi;
 clock_t start, end;
 double cpu_time_used;
 start = clock();
 for(i=0;i<10000000;i++)
 {
  term = pow(-1, i) / (2*i+1);
  sum += term;
 }
 pi = 4 * sum;
 end = clock();
 cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
 printf("foo?");
 printf("\nPI = %.6lf\n", pi);
 printf("\ntime = %lf\n", cpu_time_used);
 printf("bar!\n");
 return 0;
}
