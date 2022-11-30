#include "WeightedGraph.h"
#include "../Queue/ArrayQueue.h"

#include <stdio.h>
#include <stdlib.h>

#define NOT_FOUND (-1)

#define NO_PATH INT_MAX

struct graph
{
    int vertexNum;
    int edgeNum;
    graph_edge_t matrix[VERTEX_NUMBER][VERTEX_NUMBER]; // 邻接矩阵
};

static bool visited[VERTEX_NUMBER] = {false};

/*******************************
Helper functions implementation.
*******************************/

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void *pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

static void clean_visited_flag(void)
{
    for (graph_vertex_t i = 0; i < VERTEX_NUMBER; i++)
    {
        visited[i] = false;
    }
}

static void dfs(graph_t *G, graph_vertex_t startV, void (*pVisit)(graph_vertex_t V))
{
    pVisit(startV);
    visited[startV] = true;

    for (graph_vertex_t V1 = 0; V1 < G->vertexNum; V1++)
    {
        if (Graph_IsAdjacent(G, startV, V1) && !visited[V1])
        {
            dfs(G, V1, pVisit);
        }
    }
}

static graph_vertex_t find_min_dist(const graph_t *G, graph_edge_t dist[])
{
    graph_vertex_t minV;
    int minDist = NO_PATH;

    for (graph_vertex_t V = 0; V < G->vertexNum; V++)
    {
        if (!visited[V] && dist[V] < minDist)
        {
            minDist = dist[V];
            minV = V;
        }
    }

    return minDist < NO_PATH ? minV : NOT_FOUND;
}

/*******************************
Interface functions implementation.
*******************************/

graph_t *Graph_Create(void)
{
    graph_t *G = (graph_t *)malloc(sizeof(graph_t));
    check_pointer(G);

    G->vertexNum = VERTEX_NUMBER;
    G->edgeNum = 0;

    for (graph_vertex_t V1 = 0; V1 < G->vertexNum; V1++)
    {
        for (graph_vertex_t V2 = 0; V2 < G->vertexNum; V2++)
        {
            G->matrix[V1][V2] = NO_PATH;
        }
    }

    return G;
}

void Graph_Destroy(graph_t *G)
{
    free(G);
}

void Graph_Link(graph_t *G, graph_vertex_t V1, graph_vertex_t V2, graph_edge_t E)
{
    G->matrix[V1][V2] = E;
#ifdef UNDIRECTED
    G->matrix[V2][V1] = E;
#endif
}

void Graph_Unlink(graph_t *G, graph_vertex_t V1, graph_vertex_t V2)
{
    G->matrix[V1][V2] = NO_PATH;
#ifdef UNDIRECTED
    G->matrix[V2][V1] = NO_PATH;
#endif
}

bool Graph_IsAdjacent(const graph_t *G, graph_vertex_t V1, graph_vertex_t V2)
{
    return G->matrix[V1][V2] != NO_PATH ? true : false;
}

void Graph_DFS(graph_t *G, graph_vertex_t startV, void (*pVisit)(graph_vertex_t V))
{
    clean_visited_flag();

    dfs(G, startV, pVisit);
}

void Graph_BFS(graph_t *G, graph_vertex_t startV, void (*pVisit)(graph_vertex_t V))
{
    clean_visited_flag();

    pVisit(startV);
    visited[startV] = true;

    queue_t *Q = ArrayQueue_Create();
    ArrayQueue_Enqueue(Q, startV);
    while (!ArrayQueue_IsEmpty(Q))
    {
        graph_vertex_t V1 = ArrayQueue_Dequeue(Q);
        for (graph_vertex_t V2 = 0; V2 < G->vertexNum; V2++)
        {
            if (!visited[V2] && Graph_IsAdjacent(G, V1, V2))
            {
                pVisit(V2);
                visited[V2] = true;
                ArrayQueue_Enqueue(Q, V2);
            }
        }
    }
    ArrayQueue_Destroy(Q);
}

bool Graph_Dijkstra(const graph_t *G, graph_edge_t dist[], graph_vertex_t path[], graph_vertex_t startV)
{
    clean_visited_flag();

    // init array state
    for (graph_vertex_t V1 = 0; V1 < G->vertexNum; V1++)
    {
        dist[V1] = G->matrix[startV][V1];
        path[V1] = dist[V1] < NO_PATH ? startV : NOT_FOUND;
    }

    dist[startV] = 0;
    visited[startV] = true;

    while (1)
    {
        graph_vertex_t V1 = find_min_dist(G, dist);
        if (V1 == NOT_FOUND)
        {
            break;
        }
        visited[V1] = true;
        for (graph_vertex_t V2 = 0; V2 < G->vertexNum; V2++)
        {
            if (visited[V2] == false && G->matrix[V1][V2] < NO_PATH)
            {
                if (G->matrix[V1][V2] < 0)
                {
                    return false;
                }
                if (dist[V1] + G->matrix[V1][V2] < dist[V2])
                {
                    dist[V2] = dist[V1] + G->matrix[V1][V2];
                    path[V2] = V1;
                }
            }
        }
    }

    return true;
}

bool Graph_Floyd(const graph_t *G, graph_edge_t dist[][VERTEX_NUMBER], graph_vertex_t path[][VERTEX_NUMBER])
{
    for (graph_vertex_t i = 0; i < G->vertexNum; i++)
    {
        for (graph_vertex_t j = 0; j < G->vertexNum; j++)
        {
            dist[i][j] = G->matrix[i][j];
            path[i][j] = NOT_FOUND;
        }
    }

    for (graph_vertex_t k = 0; k < G->vertexNum; k++)
    {
        for (graph_vertex_t i = 0; i < G->vertexNum; i++)
        {
            for (graph_vertex_t j = 0; j < G->vertexNum; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    if (i == j && dist[i][j] < 0)
                    {
                        return false;
                    }
                    path[i][j] = k;
                }
            }
        }
    }

    return true;
}
