struct graphNode;

typedef struct graphLink
{
    struct graphNode* link;
    int weight;
} GraphLink;

typedef struct graphNode
{
    int value;
    GraphLink* linkArray[20]; // max 20 Nodes
} GraphNode;


void printGraphAdjancencyMatrix(GraphNode * nodes[], int size);
GraphNode * createNode(int value);
void alterLink(GraphNode * source, GraphNode * destination, int newWeight);
void removeLink(GraphNode * source, GraphNode * destination);

