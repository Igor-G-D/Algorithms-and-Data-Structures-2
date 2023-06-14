#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int **createGraph(int size) {
    int **matrix = (int **)malloc(sizeof(int*)*size); // n graph nodes

    for( int i = 0 ; i <  size ; i ++ ) {
        matrix[i] = (int *)malloc(sizeof(int)*size); 
        for( int j = 0 ; j < size ; j ++ ) {
            matrix[i][j] = 0;// initialize everything with 0 since there are no connections by default;
        }
    }

    return matrix;
}

void printGraph(int** matrix, int size) { // prints out the graph adjacency matrix
    for( int i = 0 ; i <  size ; i ++ ) {
        for( int j = 0 ; j < size ; j ++ ) {
            printf(" [ %d ] ", matrix[i][j]);
        }
        printf("\n");
    }
}

void readUserInput(int size, int * sourceNode, int * destinationNode, int * weight) {
    
    do {
        printf("Choose source node (Nodes are numbered 0 to %d): ", (size)-1);
        scanf("%d", sourceNode);
    } while(sourceNode < 0 && sourceNode >= size);
    
    do {
        printf("Choose destination node (Nodes are numbered 0 to %d): ", (size)-1);
        scanf("%d", destinationNode);
    } while(destinationNode < 0 && destinationNode >= size);

    do {
        printf("Choose the weight of the new link (must be positive) : ");
        scanf("%d", weight);
    } while(weight <= 0);

}