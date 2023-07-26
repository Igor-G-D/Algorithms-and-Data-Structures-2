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
            if(nodes[i]->linkArray[j]) {
                free(nodes[i]->linkArray[j]);
            }
        }
        free(nodes[i]);
    }
}

GraphLink * getLinks(GraphNode * nodes[], int * size) {
    (*size) = 0;
    int temp = 0;
    GraphLink * links = NULL;

    for (int i = 0; i < 20; i++) {
        temp++;
        for (int j = temp; j < 20; j++) { // temp is there to not read links twice since they are bidirectional, and to also not read loops from one node to itself
            // Check for links between nodes i and j
            if (nodes[i]->linkArray[j] != NULL) {
                if ((*size) == 0) {
                    links = (GraphLink *)malloc(sizeof(GraphLink));
                } else {
                    GraphLink *tempPointer = (GraphLink *)realloc(links, sizeof(GraphLink) * ((*size) + 1));
                    if (tempPointer == NULL) {
                        // Memory reallocation failed
                        free(links);
                        return NULL;
                    }
                    links = tempPointer;
                }
                links[*size] = *(nodes[i]->linkArray[j]);
                (*size)++;
            }
        }
    }
    return links;
}

int menu( ) {
    int choice;
	do {
        printf( "=========================================\n" );
		printf( "-- Menu:\n");
		printf( "\t 1. Add or alter a link between nodes\n" );
		printf( "\t 2. Remove a link between nodes\n" );
		printf( "\t 3. Print Adjacency Matrix\n" );
        printf( "\t 4. Exit\n" );
		printf( "-- Enter your choice: " );
		scanf( "%d", &choice );
        printf( "=========================================\n" );
	} while ( choice <= 0 || choice > 4 );
	getchar( );
    return choice;
}