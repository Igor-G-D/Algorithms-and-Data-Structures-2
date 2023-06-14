#include <stdio.h>
#include <stdlib.h>
#include "library.h"

int main(int argc, char const *argv[])
{
    int **graph = createGraph(5);
    printGraph(graph, 5);
    return 0;
}
