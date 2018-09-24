#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

int main()
{
  int a[SIZE][SIZE] = {0}; 
  int d[SIZE] = {0};
  int v[SIZE] = {0}; 
  int temp = 0;
  int minindex = 0;
  int min = 0;

  char input[90] = "db2.txt";
  FILE * f = fopen(input, "r");
  if(f == 0){
    printf("Error File\n");
    return -1;
  }

  int d1 = 0;
  int d2 = 0;
  int d3 = 0;
  while(fscanf(f, "%d %d %d", &d1, &d2, &d3) == 3){
    a[d1][d2] = d3;
    a[d2][d1] = d3;
  }
  fclose(f);


  for (int i = 0; i<SIZE; i++)
  {
    for (int j = 0; j<SIZE; j++)
      printf("%5d ", a[i][j]);
    printf("\n");
  }

  for (int i = 0; i<SIZE; i++)
  {
    d[i] = 10000;
    v[i] = 1;
  }
  d[0] = 0;

  do {
    minindex = 10000;
    min = 10000;
    for (int i = 0; i<SIZE; i++)
    { 
      if ((v[i] == 1) && (d[i]<min))
      { 
        min = d[i];
        minindex = i;
      }
    }
    if (minindex != 10000)
    {
      for (int i = 0; i<SIZE; i++)
      {
        if (a[minindex][i] > 0)
        {
          temp = min + a[minindex][i];
          if (temp < d[i])
          {
            d[i] = temp;
          }
        }
      }
      v[minindex] = 0;
    }
  } while (minindex < 10000);


  
  printf("\nlenght\n");
  for (int i = 0; i<SIZE; i++){
    printf("%5d ", d[i]);
  }

  int end = 0;

  printf("\n");

  scanf("%d", &end);

  int ver[SIZE];  
  ver[0] = end; 
  int k = 1; 
  int weight = d[end]; 

  while (end > 0) 
  {
    for(int i = 0; i < SIZE; i++) 
      if (a[end][i] != 0)
      {
        int temp = weight - a[end][i]; 
        if (temp == d[i]) 
        {                 
          weight = temp; 
          end = i;       
          ver[k] = i; 
          k++;
        }
      }
  }

  printf("\nWays\n");
  for (int i = k-1; i>=0; i--){
    printf("%3d ", ver[i]);
  }
  
  return 0;
}