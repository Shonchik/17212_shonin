#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

const int MAX_VERTICES = 40;
const int INFINITY = 10000;

int FindPath(int source, int target, int c[MAX_VERTICES][MAX_VERTICES], int f[MAX_VERTICES][MAX_VERTICES], int NUM_VERTICES)
{
        int QP = 0; 
        int QC = 1; 
        int Flow[MAX_VERTICES] = {0};
        int Link[MAX_VERTICES] = {0}; 
        int Queue[MAX_VERTICES] = {0}; 
        Queue[0] = source;
        Link[target] = -1;
        int i;
        int CurVertex;
        Flow[source] = INFINITY;
        while (Link[target] == -1 && QP < QC)
        {
                CurVertex = Queue[QP];
                for (i=0; i<NUM_VERTICES; i++)
                if ((c[CurVertex][i] - f[CurVertex][i])>0 && Flow[i] == 0) 
                {
                        Queue[QC] = i; QC++;
                        Link[i] = CurVertex;
                        if (c[CurVertex][i]-f[CurVertex][i] < Flow[CurVertex])
                             Flow[i] = c[CurVertex][i];
                        else
                             Flow[i] = Flow[CurVertex];
                }
            QP++;
        }
        if (Link[target] == -1) return 0;
        CurVertex = target;
        while (CurVertex != source)
        {
                f[Link[CurVertex]][CurVertex] +=Flow[target];
                CurVertex = Link[CurVertex];
        }
        return Flow[target];
}

int MaxFlow(int source, int target, int c[MAX_VERTICES][MAX_VERTICES], int f[MAX_VERTICES][MAX_VERTICES], int NUM_VERTICES)
{
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            f[i][j] = 0;
        }
    }
    
    int MaxFlow = 0;
    int AddFlow;
    do
    {
            AddFlow = FindPath(source, target, c, f, NUM_VERTICES);
            MaxFlow += AddFlow;
    } while (AddFlow >0);
    return MaxFlow;
}

int main()
{
    int NUM_VERTICES = 0;
    int c[MAX_VERTICES][MAX_VERTICES] = {0};
    int f[MAX_VERTICES][MAX_VERTICES] = {0};

    int source = 0;
    int target = 0;
    scanf("%d", &NUM_VERTICES);
    scanf("%d %d", &source, &target);

    char input[90] = "db2.txt";
    FILE * fo = fopen(input, "r");
    if(fo == 0){
        printf("Error File\n");
        return -1;
    }

    int d1 = 0;
    int d2 = 0;
    int d3 = 0;
    while(fscanf(fo, "%d %d %d", &d1, &d2, &d3) == 3){
        c[d1][d2] = d3;
        c[d2][d1] = d3;
    }
    fclose(fo);

    printf("%d", MaxFlow(source, target, c, f, NUM_VERTICES));
    return 0;
}