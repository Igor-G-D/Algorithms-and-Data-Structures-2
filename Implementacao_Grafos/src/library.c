#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void printGraphAdjancencyMatrix(GraphNode * nodes[], int size) { // prints out the graph adjacency matrix
    for( int i = 0 ; i <  size ; i ++ ) {
        for( int j = 0 ; j < size ; j ++ ) {
            if(nodes[i]->linkArray[j]) {
                printf(" [ %d ] ", nodes[i]->linkArray[j]->weight);
            } else {
                printf(" [ X ] ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void readUserInput(int size, int * sourceNode, int * destinationNode, int * weight) {
    
    do {
        printf("Choose source node (Nodes are numbered 0 to 19): ");
        scanf("%d", sourceNode);
    } while((*sourceNode) < 0 && (*sourceNode) >= size);
    
    do {
        printf("Choose destination node (Nodes are numbered 0 to 19): ");
        scanf("%d", destinationNode);
    } while((*destinationNode) < 0 && (*destinationNode) >= size);

    printf("Choose the weight of the new link : ");
    scanf("%d", weight);

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
        source->linkArray[destination->value]->weight = newWeight;
    } else {
        source->linkArray[destination->value]->link = destination;
        source->linkArray[destination->value]->weight = newWeight;
    }
}


void removeLink(GraphNode * source, GraphNode * destination) {
    if(source->linkArray[destination->value]) {
        GraphLink * temp = source->linkArray[destination->value];
        source->linkArray[destination->value] = NULL;
        free(temp);
    }
}