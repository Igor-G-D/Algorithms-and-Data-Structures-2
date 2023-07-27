#include <stdio.h>
#include <stdlib.h>
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
            if(nodes[i]->linkArray[j]) {
                free(nodes[i]->linkArray[j]);
            }
        }
        free(nodes[i]);
    }
}

GraphLink ** getLinks(GraphNode * nodes[], int * size) {
    (*size) = 0;
    int temp = 0;
    GraphLink ** links = NULL;

    for (int i = 0; i < 20; i++) {
        temp++;
        for (int j = temp; j < 20; j++) { // temp is there to not read links twice since they are bidirectional, and to also not read loops from one node to itself
            // Check for links between nodes i and j
            if (nodes[i]->linkArray[j] != NULL) {
                if ((*size) == 0) {
                    links = (GraphLink **)malloc(sizeof(GraphLink*));
                } else {
                    GraphLink **tempPointer = (GraphLink **)realloc(links, sizeof(GraphLink*) * ((*size) + 1));
                    if (tempPointer == NULL) {
                        // Memory reallocation failed
                        free(links);
                        return NULL;
                    }
                    links = tempPointer;
                }
                links[*size] = (nodes[i]->linkArray[j]);
                (*size)++;
            }
        }
    }
    return links;
}

void kruskalAlgorithmMST(GraphLink **links, int size, GraphNode * MST[]) {
    int nodeGroup[20];
    int count = 0;

    for (int i = 0; i < 20; i++) {
        MST[i] = NULL; // initialize all as empty
        nodeGroup[i] = -1;
    }

    qsort(links, size, sizeof(GraphLink *), cmpfunc); // sorts the list of links by weight

    for (int i = 0; i < size; i++) { // iterate through all links
        int node1 = nodeGroup[links[i]->source->value];
        int node2 = nodeGroup[links[i]->link->value];

        if (node1 != node2 || node1 == -1 || node2 == -1) { // if they are in different groups, or if they are by themselves
            GraphNode *newMSTNode1 = MST[links[i]->source->value];
            GraphNode *newMSTNode2 = MST[links[i]->link->value];

            if (newMSTNode1 == NULL) {
                newMSTNode1 = (GraphNode *)malloc(sizeof(GraphNode));
                newMSTNode1->value = links[i]->source->value;
                MST[links[i]->source->value] = newMSTNode1;
            }

            if (newMSTNode2 == NULL) {
                newMSTNode2 = (GraphNode *)malloc(sizeof(GraphNode));
                newMSTNode2->value = links[i]->link->value;
                MST[links[i]->link->value] = newMSTNode2;
            }

            GraphLink *newMSTLink1 = (GraphLink *)malloc(sizeof(GraphLink));
            GraphLink *newMSTLink2 = (GraphLink *)malloc(sizeof(GraphLink));

            newMSTLink1->link = newMSTNode2;
            newMSTLink1->source = newMSTNode1;
            newMSTLink1->weight = links[i]->weight;
            newMSTNode1->linkArray[newMSTNode2->value] = newMSTLink1; // link both source and dest to each other in the MST

            newMSTLink2->link = newMSTNode1;
            newMSTLink2->source = newMSTNode2;
            newMSTLink2->weight = links[i]->weight;
            newMSTNode2->linkArray[newMSTNode1->value] = newMSTLink2; // link both source and dest to each other in the MST

            if (node1 != node2) {
                if (node1 == -1) {
                    nodeGroup[links[i]->source->value] = nodeGroup[links[i]->link->value];
                } else {
                    nodeGroup[links[i]->link->value] = nodeGroup[links[i]->source->value];
                }
            } else { // both are -1
                nodeGroup[links[i]->source->value] = count;
                nodeGroup[links[i]->link->value] = count;
                count++; // new group
            }
        } else {
            continue;
        }
    }

    int temp = -1;
    for (int i = 0; i < 20; i++) { // tests to see if there is more than one group, aka, if the original graph was not conex
        if (temp != -1 && nodeGroup[i] != -1 && temp != nodeGroup[i]) {
            freeNodes(MST, 20);
            for (int i = 0; i < 20; i++) {
                MST[i] = NULL; // return empty MST if tree is not conex
            }
            return;
        }
        if (nodeGroup[i] != -1) {
            temp = nodeGroup[i];
        }
    }
}

int cmpfunc(const void *a, const void *b) {
    int weightA = (*(GraphLink**)a)->weight;
    int weightB = (*(GraphLink**)b)->weight;
    return weightA - weightB;
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