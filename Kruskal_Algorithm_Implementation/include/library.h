struct graphNode;

typedef struct graphLink
{
    struct graphNode* source;
    struct graphNode* link;
    int weight;
} GraphLink;

typedef struct graphNode
{
    int value;
    GraphLink* linkArray[20]; // max 20 Nodes
} GraphNode;

void printGraphAdjancencyMatrix(GraphNode * nodes[], int size);
void readUserInput(int size, int remove, int * sourceNode, int * destinationNode, int * weight);
GraphNode * createNode(int value);
void alterLink(GraphNode * source, GraphNode * destination, int newWeight);
void removeLink(GraphNode * source, GraphNode * destination);
void freeNodes( GraphNode * nodes[], int size );
GraphLink ** getLinks(GraphNode * nodes[], int * size);
void kruskalAlgorithmMST(GraphLink **links, int size, GraphNode * MST[]);
int cmpfunc (const void * a, const void * b);
int menu( );
