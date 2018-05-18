#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

// __PRETTY_FUNCTION__ печатает сигнатуру фкнции

const int dx[8]={2,2,1,-1,-2,-2,-1,1};
const int dy[8]={-1,1,2,2,1,-1,-2,-2};

void print (int A[SIZE][SIZE]) {
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            printf("%3d", A[x][y]);
        }
    printf("\n");
    } 
}

void evristika (int A[SIZE][SIZE], int B[SIZE][SIZE])
{
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            B[x][y]=0;
        }
    } 
    for (int x = 0; x < SIZE; x++)
    {
        for (int y = 0; y < SIZE; y++)
        {
            for (int i = 0; i < 8; i++)          
            {
                int x1 = x + dx[i];
                int y1 = y + dy[i];

                if ((x1 >= 0) && (y1 >= 0) && (x1 < SIZE) && (y1 < SIZE) && (A[x1][y1] == 0))
                {
                    B[x][y]++;
                }
            }
        }
    } 
    //print(B);
    //printf("\n");
}

void turn (int A[SIZE][SIZE], int B[SIZE][SIZE], int x, int y, int step)
{
    A[x][y] = step++;
    int i = 0;
    int j = 0;
    int x1 = 0;
    int y1 = 0;

    for (i = 0; i < 8; i++)          
    {
        int min = 9;
        int min2 = 0;

        if (step > SIZE*SIZE) {
            print(A);
            exit(0);
        }

        evristika(A, B);

        for (j = 0; j < 8; j++)          
        {
            int x1 = x + dx[j];
            int y1 = y + dy[j];
            if ((x1 < 0) || (y1 < 0) || (x1 >= SIZE) || (y1 >= SIZE) || (A[x1][y1] != 0))
            {
                continue;
            }
            if (min > B[x1][y1]) {
                min = B[x1][y1];
                min2 = j;
            }
            
        }
        if (min == 9) {
            A[x1][y1] = 0;
        }else {
            x1 = x + dx[min2];
            y1 = y + dy[min2];

            
            turn(A, B, x1, y1, step);
            //printf("\n");
            //print(A);
            A[x1][y1] = 0;
        }
    }
}

int main ()
{
    int A[SIZE][SIZE];
    int B[SIZE][SIZE];
    int x = 0;
    int y = 0;
    for (x = 0; x < SIZE; x++)
    {
        for (y = 0; y < SIZE; y++)
        {
            A[x][y]=0;
            B[x][y]=0;
        }
    } 

    printf("Print X and Y: ");
    scanf("%d %d", &x, &y);

    turn(A, B, x, y, 1);
    print(A);
}