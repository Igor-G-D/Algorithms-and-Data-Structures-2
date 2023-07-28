#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main(int argc, char const *argv[])
{
    GraphNode * nodes[20];
    GraphNode * MST[20];

    while ( 1 ) {
		int choice = menu();
        int sourceNode, destinationNode, weight;
		switch ( choice ) {
            case 1:
                readUserInput(20, 0, &sourceNode, &destinationNode, &weight);
                if(!nodes[sourceNode]) {
                    nodes[sourceNode] = createNode(sourceNode);
                }
                if(!nodes[destinationNode]) {
                    nodes[destinationNode] = createNode(destinationNode);
                }
                alterLink(nodes[sourceNode], nodes[destinationNode], weight);
                break;
            case 2:
                readUserInput(20, 1, &sourceNode, &destinationNode, &weight);
                if(!nodes[sourceNode]) {
                    printf("Node %d isn't in the graph!\n", sourceNode);
                    break;
                }
                if(!nodes[destinationNode]) {
                    printf("Node %d isn't in the graph!\n", destinationNode);
                }
                removeLink(nodes[sourceNode], nodes[destinationNode]);
                break;
            case 3:
                printGraphAdjancencyMatrix(nodes, 20);
                break;
            case 4:
                primAlgorithmMST(nodes, MST);
                if (MST != NULL) {
                    printGraphAdjancencyMatrix(MST, 20);
                } else {
                    printf("Minimum Spanning Tree not found!\n");
                }
                break;
            case 5:
                freeNodes(nodes, 20);
                if (MST != NULL) {
                    freeNodes(MST, 20);
                }
                exit(0);
                break;
            default:
                break;
		}
	}
	return 0;
}

    // printGraphAdjancencyMatrix(nodes, 20);

    // alterLink(nodes[0], nodes[0], 0);
    // alterLink(nodes[0], nodes[1], 1);
    // alterLink(nodes[0], nodes[2], 2);
    // alterLink(nodes[0], nodes[3], 3);
    // alterLink(nodes[0], nodes[4], 4);
    // alterLink(nodes[0], nodes[5], 5);

    // printGraphAdjancencyMatrix(nodes, 20);

    // removeLink(nodes[0], nodes[1]);
    // removeLink(nodes[0], nodes[2]);
    // removeLink(nodes[0], nodes[3]);
    // removeLink(nodes[0], nodes[4]);
    // removeLink(nodes[0], nodes[5]);

    // printGraphAdjancencyMatrix(nodes, 20);

    // freeNodes(nodes, 20);