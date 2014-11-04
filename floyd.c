#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct {
    double pathLength;
    int nextNodeOnPath;
} LengthAndNext;

typedef struct {
    int outDegree, *adjList;
    double *linkCost;
} GraphNode;
int numNodes;
GraphNode *node;

int main()
{   readGraph();
    cout << fixed << setprecision(1);
    PrintFloydOutput(Floyd(), numNodes);
    return 0;
}

LengthAndNext** Floyd()
{   cout << "----------------------------------------------------------" << endl;
    double inf = 0;
    for (int i = 0; i < numNodes; i++)
        for (int j = 0; j < node[i].outDegree; j++)
            inf += node[i].linkCost[j];
    inf++;
    LengthAndNext **matrix;
    matrix = new LengthAndNext *[numNodes];
    for (int i = 0; i < numNodes; i++)
    {   matrix[i] = new LengthAndNext[numNodes];
        for (int j = 0; j < numNodes; j++)
        {   matrix[i][j].nextNodeOnPath = j;
            matrix[i][j].pathLength = inf;
        }
        matrix[i][i].pathLength = 0;
        for (int j = 0; j < node[i].outDegree; j++)
            matrix[i][node[i].adjList[j]].pathLength = node[i].linkCost[j];
    }
    for (int k = 0; k < numNodes; k++)
    {   cout << "New paths looked at from i to j via k = " << k << endl;
        for (int i = 0; i < numNodes; i++)
            for (int j = 0; j < numNodes; j++)
            {   cout << i << "," << j << " path looked at: ";
                cout << "<" << i;
                int t, r, w;
                t = i;
                r = k;
                while (matrix[t][k].nextNodeOnPath != k)
                    cout << ", " << (t = matrix[t][k].nextNodeOnPath);
                cout << ", " << k;
                while (matrix[r][j].nextNodeOnPath != j)
                    cout << ", " << (r = matrix[r][j].nextNodeOnPath);
                cout << ", " << j << ">";
                if (matrix[i][j].pathLength > (matrix[i][k].pathLength + matrix[k][j].pathLength))
                {   matrix[i][j].pathLength = matrix[i][k].pathLength + matrix[k][j].pathLength;
                    matrix[i][j].nextNodeOnPath = matrix[i][k].nextNodeOnPath;
                    cout << ", new dist = " << matrix[i][j].pathLength;
                }
                cout << endl;
                if(0 > matrix[i][j].pathLength)
                {   cout << "Negative Cycle Detected" << endl;
                    exit(1);
                }
            }
        cout << endl;
    }
    cout << endl;
    return matrix;
}

void PrintFloydOutput(LengthAndNext **matrix, int numNodes)
{   cout << "----------------------------------------------------------" << endl;
    cout.width(9);
    int i = 0;
    cout << i;
    for (i = 1; i < numNodes; i++)
    {   cout.width(11);
        cout << i;
    }
    cout << endl;
    for (i = 0; i < numNodes; i++)
    {   cout << i;
        for (int j = 0; j < numNodes; j++)
        {   cout.width(8);
            cout << matrix[i][j].pathLength <<  ": " << matrix[i][j].nextNodeOnPath;
        }
        cout << endl;
    }
}
void SkipToTheEndOfLine(ifstream &inFile)
{   while (!inFile.eof() && inFile.get() != '\n');
}

void readGraph()
{   ifstream in;
    in.open("input.dat");
    char temp;
    in >> numNodes;
    node = new GraphNode[numNodes];
    SkipToTheEndOfLine(in);
    for (int i = 0; i < numNodes; i++)
    {   in >> temp >> temp >> node[i].outDegree >> temp >> temp;
        node[i].adjList = new int[node[i].outDegree];
        node[i].linkCost = new double[node[i].outDegree];
        for (int j = 0; j < node[i].outDegree; j++)
            in >> node[i].adjList[j] >> temp >> node[i].linkCost[j] >> temp;
    }
    cout << "Input Graph: " << endl;
    cout << "numNodes = " << numNodes << endl;
    for(int i = 0; i<numNodes; i++)
    {   cout <<  i << " (";
        cout << node[i].outDegree << "): ";
        for(int j = 0; j < node[i].outDegree; j++)
            cout << node[i].adjList[j] << " (" << node[i].linkCost[j] << ") ";
        cout << endl;
    }
}