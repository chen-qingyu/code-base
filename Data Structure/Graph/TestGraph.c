#include "Graph.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

char str[64] = {0};

void Visit(graph_vertex_t V)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", V);
    strcat(str, tmp);
}

void TestGraph(void)
{
    graph_t *G = Graph_Create();

    Graph_Link(G, 0, 1, 2);
    Graph_Link(G, 0, 3, 1);
    Graph_Link(G, 1, 4, 10);
    Graph_Link(G, 1, 3, 3);
    Graph_Link(G, 2, 0, 4);
    Graph_Link(G, 2, 5, 5);
    Graph_Link(G, 3, 2, 2);
    Graph_Link(G, 3, 4, 2);
    Graph_Link(G, 3, 5, 8);
    Graph_Link(G, 3, 6, 4);
    Graph_Link(G, 6, 5, 1);

    //       +--+   2    +--+
    //       |V0|------->|V1|
    //       +--+        +--+
    //    +--^  | 1    3 |  |  10
    //   4|     +--v  v--+  +--v
    // +--+    2   +--+   2    +--+
    // |V2|<-------|V3|------->|V4|
    // +--+        +--+        +--+
    //   5|      8 |  | 4      |6
    //    +--v  v--+  +--v  v--+
    //       +--+   1    +--+
    //       |V5|<-------|V6|
    //       +--+        +--+

    assert(Graph_IsAdjacent(G, 0, 1) == true);
    assert(Graph_IsAdjacent(G, 0, 6) == false);
    assert(Graph_IsAdjacent(G, 6, 0) == false);

    Graph_Link(G, 0, 6, 99);
    assert(Graph_IsAdjacent(G, 0, 6) == true);
#ifndef UNDIRECTED
    assert(Graph_IsAdjacent(G, 6, 0) == false);
#else
    assert(Graph_IsAdjacent(G, 6, 0) == true);
#endif

    Graph_Unlink(G, 0, 6);
    assert(Graph_IsAdjacent(G, 0, 6) == false);

    Graph_DFS(G, 0, Visit);
    assert(strcmp(str, "0 1 3 2 5 4 6 ") == 0);
    memset(str, 0, sizeof(str));

    Graph_BFS(G, 0, Visit);
    assert(strcmp(str, "0 1 3 4 2 5 6 ") == 0);
    memset(str, 0, sizeof(str));

    int dist[VERTEX_NUMBER];
    int path[VERTEX_NUMBER];
    Graph_Dijkstra(G, dist, path, 0);

    assert(dist[0] == 0);
    assert(dist[1] == 2);
    assert(dist[2] == 3);
    assert(dist[3] == 1);
    assert(dist[4] == 3);
    assert(dist[5] == 6);
    assert(dist[6] == 5);

    assert(path[0] == -1);
    assert(path[1] == 0);
    assert(path[2] == 3);
    assert(path[3] == 0);
    assert(path[4] == 3);
    assert(path[5] == 6);
    assert(path[6] == 3);

    Graph_Destroy(G);

    printf("Graph Test OK.\n");
}

int main(void)
{
    TestGraph();

    return 0;
}
