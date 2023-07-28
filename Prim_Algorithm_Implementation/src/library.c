#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "library.h"

void printGraphAdjancencyMatrix(GraphNode * nodes[], int size) { // prints out the graph adjacency matrix
    for( int i = 0 ; i <  size ; i ++ ) {
        for( int j = 0 ; j < size ; j ++ ) {
            if(nodes[i] && nodes[i]->linkArray[j]) {
                printf(" [ %d ] ", nodes[i]->linkArray[j]->weight);
            } else {
                printf(" [ X ] ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void readUserInput(int size, int remove, int * sourceNode, int * destinationNode, int * weight) {
    printf( "=========================================\n" );
    do {
        printf("Choose first node (Nodes are numbered 0 to 19): ");
        scanf("%d", sourceNode);
    } while((*sourceNode) < 0 && (*sourceNode) >= size);
    
    do {
        printf("Choose second node (Nodes are numbered 0 to 19): ");
        scanf("%d", destinationNode);
    } while((*destinationNode) < 0 && (*destinationNode) >= size);

    if(!remove) {
        printf("Choose the weight of the new link : ");
        scanf("%d", weight);
    }
    printf( "=========================================\n" );

}

GraphNode * createNode(int value) {
    GraphNode * new = (GraphNode *) malloc(sizeof(GraphNode));
    for(int i = 0; i < 20 ; i ++) {
        new->linkArray[i] = NULL;
    }
    new->value = value;

    return new;
}

void alterLink(GraphNode * source, GraphNode * destination, int newWeight) {
    if(source->linkArray[destination->value] == NULL) {
        source->linkArray[destination->value] = (GraphLink *) malloc (sizeof(GraphLink));
        source->linkArray[destination->value]->link = destination;
        source->linkArray[destination->value]->source = source;
        source->linkArray[destination->value]->weight = newWeight;

        destination->linkArray[source->value] = (GraphLink *) malloc (sizeof(GraphLink));// this section is to make the connections not pointed in one direction
        destination->linkArray[source->value]->link = source;
        destination->linkArray[source->value]->source = destination;
        destination->linkArray[source->value]->weight = newWeight;
    } else {
        source->linkArray[destination->value]->link = destination;
        source->linkArray[destination->value]->weight = newWeight;

        destination->linkArray[source->value]->link = source;
        destination->linkArray[source->value]->weight = newWeight;
    }
}


void removeLink(GraphNode * source, GraphNode * destination) {
    if(source->linkArray[destination->value]) {
        GraphLink * temp = source->linkArray[destination->value];
        source->linkArray[destination->value] = NULL;
        free(temp);

        temp = destination->linkArray[source->value];
        destination->linkArray[source->value] = NULL;
        free(temp);

        
    }
}

void freeNodes( GraphNode * nodes[], int size ) {
    for( int i = 0 ; i < size ; i ++ ) {
        for( int j = 0 ; j < size ; j ++ ) {
            if(nodes[i] && nodes[i]->linkArray[j]) {
                free(nodes[i]->linkArray[j]);
            }
        }
        free(nodes[i]);
    }
}

void primAlgorithmMST(GraphNode *nodes[], GraphNode *MST[]) {
    int nodesVisited[20];
    for (int i = 0; i < 20; i++) {
        if(nodes[i]) {
            nodesVisited[i] = 0;
        } else {
            nodesVisited[i] = -1;
        }
    }
    for (int i = 0; i < 20; i++) {
        MST[i] = NULL; // starting everything as NULL in the MST
    }

    int isEmpty = 1;
    for (int i = 0; i < 20; i++) {
        if (nodes[i]) {
            isEmpty = 0;
            break;
        }
    }
    if (isEmpty) { // MST is empty if graph is also empty, everything is already set to NULL
        return;
    }
    int baseNode = -1;
    for (int i = 0; i < 20; i++) {
        if (nodes[i]) {
            baseNode = i; // finding the first base node
            break;
        }
    }



    nodesVisited[baseNode] = 1;
    MST[baseNode] = createNode(baseNode); //insert the first node into the MST

    while (1) {
        int minWeight = INT_MAX; // INT_MAX is basically infinity here
        int minEdgeSourceNode = -1;
        int minEdgeDestNode = -1;

        for (int i = 0; i < 20; i++) { // find the lowest value edge
            if (nodesVisited[i] == 1) { 
                for (int j = 0; j < 20; j++) {
                    if (nodesVisited[j] == 0 && nodes[i]->linkArray[j] && nodes[i]->linkArray[j]->weight < minWeight) { // if j node hasn't been visited, and if linkArray[j] exists, and if linkArray[j] is lower than the value already stores
                        minWeight = nodes[i]->linkArray[j]->weight;
                        minEdgeSourceNode = i;
                        minEdgeDestNode = j;
                    }
                }
            }
        }

        if (minEdgeSourceNode == -1 || minEdgeDestNode == -1) { // no valid edge found
            break;
        }


        nodesVisited[minEdgeDestNode] = 1; // mark as visited
        MST[minEdgeSourceNode]->linkArray[minEdgeDestNode] = (GraphLink *)malloc(sizeof(GraphLink));
        MST[minEdgeSourceNode]->linkArray[minEdgeDestNode]->source = MST[minEdgeSourceNode];
        MST[minEdgeSourceNode]->linkArray[minEdgeDestNode]->link = createNode(minEdgeDestNode);
        MST[minEdgeSourceNode]->linkArray[minEdgeDestNode]->weight = minWeight;

        MST[minEdgeDestNode] = createNode(minEdgeDestNode);
        MST[minEdgeDestNode]->linkArray[minEdgeSourceNode] = (GraphLink *)malloc(sizeof(GraphLink)); // insert nodes into MST and add the undirected edge
        MST[minEdgeDestNode]->linkArray[minEdgeSourceNode]->source = MST[minEdgeDestNode];
        MST[minEdgeDestNode]->linkArray[minEdgeSourceNode]->link = createNode(minEdgeSourceNode);
        MST[minEdgeDestNode]->linkArray[minEdgeSourceNode]->weight = minWeight;
    }

    for (int i = 0; i < 20; i++) {
        if (nodesVisited[i] == 0) {
            freeNodes(MST, 20);
            for (int j = 0; j < 20; j++) {
                MST[j] = NULL; // if there is still an unvisited node after the algorithm is run, it means that the graph was not conex and so, the MST doesn't exist
            }
            return;
        }
    }
}


int menu( ) {
    int choice;
	do {
        printf( "=========================================\n" );
		printf( "-- Menu:\n");
		printf( "\t 1. Add or alter a link between nodes\n" );
		printf( "\t 2. Remove a link between nodes\n" );
		printf( "\t 3. Print Adjacency Matrix\n" );
        printf( "\t 4. Print MST Matrix\n" );
        printf( "\t 5. Exit\n" );
		printf( "-- Enter your choice: " );
		scanf( "%d", &choice );
        printf( "=========================================\n" );
	} while ( choice <= 0 || choice > 5 );
	getchar( );
    return choice;
}