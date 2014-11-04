#include <stdio.h>
#include <stdlib.h>
void PrintIntArray(int *, int);
void readGraph();
void SkipToEndOfLine(FILE *fpInp);
void depthFirstTraverse(int startNode);
typedef struct{
    int degree, *adjList; 
} GraphNode;
int numNodes;
int startNode = 0;
GraphNode *nodes;
int main(void)
{   readGraph();
    depthFirstTraverse(startNode);
    return 0;
}
void depthFirstTraverse(int startNode)
{   int lastDflabel = 0;
    int *nextToVisit = (int*)calloc(numNodes, sizeof(int));
    int *dfLabel = (int*)calloc(numNodes, sizeof(int));
    int *parent = (int*)malloc(numNodes*sizeof(int));
    int curNode, nextNode;
    curNode = startNode;
    dfLabel[curNode] = ++lastDflabel;
    parent[curNode] = curNode;
    printf("-------------------------------\n");
    printf("startNode = %d, dflabel(%d) = %d\n",curNode,curNode,dfLabel[curNode]);
    while(curNode != startNode || nextToVisit[startNode] < nodes[startNode].degree)
    {    while( nextToVisit[curNode] < nodes[curNode].degree)
         {    nextNode = nodes[curNode].adjList[nextToVisit[curNode]++];
              printf("processing(%d,%d): " ,curNode,nextNode);
              if(0 == dfLabel[nextNode])
              {  parent[nextNode] = curNode;
                 curNode = nextNode;
                 dfLabel[curNode] = ++lastDflabel;
                 printf("tree-edge, dfLabel(%d) = %d\n", curNode, dfLabel[curNode]);
              }
        else if(dfLabel[nextNode]< dfLabel[curNode])
        {      if(nextNode == parent[curNode])
                  printf("tree-edge 2nd-visit\n");
                  else
                      printf("back-edge\n");
        }
        else if(dfLabel[nextNode] > dfLabel[curNode])
            printf("back-edge 2nd-visit\n");
    }
        printf("backtracking %d -> %d\n", curNode, parent[curNode]);
        curNode = parent[curNode];
    }
    printf("-------------------------------");
}
void PrintIntArray(int *arr, int n)
{   int i;
    printf("%d", arr[0]);
    for (i=1; i<n; i++)
        printf(" %d", arr[i]);    
    printf("\n");
}
void SkipToEndOfLine(FILE *fpInp)
{ while(getc(fpInp) != '\n');
}
void readGraph()
{   int i, j, degree, nodeNum;
    FILE *fpInp;
    if(NULL == (fpInp = fopen("graph.dat", "r")))
    { fprintf(stderr, "Cannot open %s\n", "graph.dat"); exit(1);}
    fscanf(fpInp, "%d", &numNodes); SkipToEndOfLine(fpInp);
    nodes = (GraphNode *)malloc(numNodes*sizeof(GraphNode));
    for (i=0; i<numNodes; i++)
    {   fscanf(fpInp, "%d (%d):", &nodeNum, &degree);
        nodes[nodeNum].degree = degree;
        nodes[nodeNum].adjList = (int *)malloc(degree*sizeof(int));
        for (j=0; j<degree; j++)
           fscanf(fpInp, "%d", &nodes[nodeNum].adjList[j]);
        SkipToEndOfLine(fpInp);
    }
    fclose(fpInp);
    printf("numNodes = %d\n", numNodes);
    //printf("nodeNum (degree): adjNodes\n");
    for (i=0;i<numNodes; i++)
    {   printf("%d (%d): ", i, nodes[i].degree);
        PrintIntArray(nodes[i].adjList, nodes[i].degree);
    }
}