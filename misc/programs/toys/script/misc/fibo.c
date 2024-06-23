#include <stdio.h>

int fibo(int n)
{
  if (n <= 0)
    return (0);
  if (n <= 2)
    return (1);
  return (fibo(n - 1) + fibo(n - 2));
}

int main(void)
{
  int i;

  for (i = 0; i < 1000; ++i)
    printf("%d\n", fibo(25));
  return (0);
}
