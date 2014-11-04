#include <stdio.h>
#include <stdlib.h>
void PrintIntArray(int *arr, int n, int *link);
void readDiGraph();
void SkipToEndOfLine(FILE *fpInp);
int *MinSpanTree(int startNode);
typedef struct {
    int outDegree, *adjList;
    int *linkCost;
} GraphNode;
GraphNode *nodes; 
int numNodes;
int  **weights;
int startNode = 0;
int max=0;
int main(void)
{
    readDiGraph();
   MinSpanTree(startNode);
 return 0;
}
int *MinSpanTree(int startNode)
{   int i,j, *bestWeight, *best, *S;
    best = (int *)malloc(numNodes*sizeof(int));
    bestWeight = (int *)malloc(numNodes*sizeof(int));
    weights = (int **)malloc(numNodes*sizeof(int*));
    S = (int *)malloc(numNodes*sizeof(int));
    
    int inf, min,temp;
    
    for( i = 0; i <numNodes; i++)
        for(j = 0; j<nodes[i].outDegree;j++)
            inf += nodes[i].linkCost[j];
    inf++;
    for (i = 0; i < numNodes; i++)
    {   weights[i] = (int *)malloc(numNodes*sizeof(int));
        for(j = 0; j < numNodes; j++)
            weights[i][j] = inf;
        weights[i][i] = 0;
    }
    //S[startNode] = 1;
    for (i=0;i<numNodes;i++)
    {   for(j=0;j<nodes[i].outDegree;j++)
        {   weights[i][nodes[i].adjList[j]] = nodes[i].linkCost[j];
            weights[nodes[i].adjList[j]][i] = nodes[i].linkCost[j];
        }
        //weights[i][i] = 0;
    }
    for ( i = 0; i < numNodes; i++)
        S[i] = 0;
    for (i=0; i < numNodes; i++)
    {    bestWeight[i] = weights[startNode][i];
        bestWeight[i] = startNode;
    }
    bestWeight[startNode] = 0;
    //bestWeight[numNodes-1]=inf;
    S[startNode] = 1;
    for(i=1; i < numNodes;i++)
    {   min = inf;
        for(j = 0; j < numNodes;j++)
            if(0 == S[j])
                if(weights[startNode][j] < bestWeight[j])
                {  bestWeight[j] = weights[startNode][j];
                    best[j] = startNode;
                }
        if(bestWeight[j] < min)
        {  min = bestWeight[j];
            temp =j;
        }
        S[temp] = 1;
        startNode = temp;
        printf("Edge added(%d,%d), ",temp,best[temp]);
        printf("Weight[%d,%d] = %d\n", best[temp], temp, bestWeight[temp]);
    }
    
    for (i=0;i<numNodes;i++)
    {   printf(" %d" , i);
        for(j=0;j<numNodes;j++)
    {   printf(" %d  ", weights[i][j]);
    }
        printf("\n");
    }
}
void PrintIntArray(int *arr, int n, int *link)
{   int i;
    printf("%d ( %d )", arr[0], link[0]);
    for (i=1; i<n; i++)
        printf(" %d ( %d )", arr[i], link[i]);    
    printf("\n");
}
void SkipToEndOfLine(FILE *fpInp)
{ while(getc(fpInp) != '\n');
}
void readDiGraph()
{   int i,j,outDegree, nodeNum,num;
    FILE *fpInp;
    if(NULL == (fpInp = fopen("minspantree.dat", "r")))
    { fprintf(stderr, "Cannot open %s\n", "minspantree.dat"); exit(1);}
    fscanf(fpInp, "%d", &numNodes); SkipToEndOfLine(fpInp);
    nodes = (GraphNode *)malloc(numNodes*sizeof(GraphNode));
    for (i=0; i<numNodes; i++)
    {   fscanf(fpInp, "%d (%d):", &nodeNum, &outDegree);
        nodes[nodeNum].outDegree = outDegree;
        nodes[nodeNum].adjList = (int *)malloc(outDegree*sizeof(int));
        nodes[nodeNum].linkCost = (int *)malloc(outDegree*sizeof(int));
        for (j=0; j<outDegree; j++)
        {   fscanf(fpInp, "%d( %d )", &nodes[nodeNum].adjList[j], &nodes[nodeNum].linkCost[j]);
            if (nodes[nodeNum].linkCost[j] > max)
                max = nodes[nodeNum].linkCost[j];
            //printf("nodeNum = %d, num = %d linkCost = %d \n",nodeNum, nodes[nodeNum].adjList[j],nodes[nodeNum].linkCost[j]);
        }
        SkipToEndOfLine(fpInp);
    }
    fclose(fpInp);
    printf("numNodes = %d\n", numNodes);
    for (i=0;i<numNodes;i++)
    {
        printf("%d (%d): ", i, nodes[i].outDegree);
        PrintIntArray(nodes[i].adjList ,nodes[i].outDegree,nodes[i].linkCost);
    }
}
