#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void Dijkstra(int Graph[MAX][MAX], int n, int start, int *distance) {
    int cost[MAX][MAX], pred[MAX];
    int visited[MAX], count, minimumDistance, nextNode, i, j;

    for (i = 0; i < n; i++){ // cost matrix for all nodes
        for (j = 0; j < n; j++){
            if (Graph[i][j] == 0) {
                cost[i][j] = INFINITY; // no connection
            } else {
                cost[i][j] = Graph[i][j]; // has a connection
            }
        }
    }

    for (i = 0; i < n; i++) {
        distance[i] = cost[start][i]; // distance initially is the edge from the start node to that node
        pred[i] = start; // first predecessor is the start node
        visited[i] = 0; // no nodes have been visited yet
    }

    distance[start] = 0; // distance to the start node to itself is 0
    visited[start] = 1; // start node is visited
    count = 1; // visited 1 node, the start node

    while (count < n) { // until all nodes are visited
        minimumDistance = INFINITY; // reset after each loop
        nextNode = -1; // initialize nextNode

        for (i = 0; i < n; i++){
            if (distance[i] < minimumDistance && !visited[i]) { // If the stored distance is smaller, and it hasn't been visited yet
                minimumDistance = distance[i];
                nextNode = i;
            }
        }

        if (nextNode == -1) {
            // This means there are unreachable nodes from the start node.
            break;
        }

        visited[nextNode] = 1; // next node is visited
        for (i = 0; i < n; i++) {
            if (!visited[i]) {
                if (minimumDistance + cost[nextNode][i] < distance[i]) { // update distance if the new path is smaller
                    distance[i] = minimumDistance + cost[nextNode][i];
                    pred[i] = nextNode; // update previous node
                }
            }
        }
        count++;
    }
}
