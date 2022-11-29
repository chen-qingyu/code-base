/*
类型名称：加权图 (Weighted Graph)
对象集：G(V, E) 由一个非空的有限顶点集合 V 和一个有限边集合 E 组成。
操作集：对于任意的图 G ∈ graph_t ，顶点（的编号） V ∈ graph_vertex_t ，边（的权重） E ∈ graph_edge_t
*/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <limits.h>  // INT_MAX
#include <stdbool.h> // bool

#define VERTEX_NUMBER 7

/* 注释掉此行变成无向图 */
// #define UNDIRECTED

typedef int graph_vertex_t; // 顶点（的编号）

typedef int graph_edge_t; // 边（的权重）

typedef struct graph graph_t; // 图

/*************************************************
  Description:    创建一个空图
  Parameter:      空
  Return:         一个指向空图的指针
*************************************************/
graph_t *Graph_Create(void);

/*************************************************
  Description:    销毁一个图 G
  Parameter:      一个指向待销毁图的指针 G
  Return:         空
*************************************************/
void Graph_Destroy(graph_t *G);

/*************************************************
  Description:    以权重 E 链接图 G 的两个顶点 V1 和 V2
  Parameter:      一个指向图的指针 G
                  两个顶点 V1 V2
                  两个顶点连线的权重 E
  Return:         空
*************************************************/
void Graph_Link(graph_t *G, graph_vertex_t V1, graph_vertex_t V2, graph_edge_t E);

/*************************************************
  Description:    断开图 G 的两个顶点 V1 和 V2
  Parameter:      一个指向图的指针 G
                  两个顶点 V1 V2
                  两个顶点连线的权重 E
  Return:         空
*************************************************/
void Graph_Unlink(graph_t *G, graph_vertex_t V1, graph_vertex_t V2);

/*************************************************
  Description:    判断图 G 的两个顶点 V1 和 V2 之间是否链接
  Parameter:      一个指向图的指针 G
                  两个顶点 V1 V2
  Return:         如果两个顶点已链接则返回 true ，否则返回 false
*************************************************/
bool Graph_IsAdjacent(const graph_t *G, graph_vertex_t V1, graph_vertex_t V2);

/*************************************************
  Description:    深度优先遍历图 G
  Parameter:      一个指向图的指针 G
                  遍历起始点 startV
                  一个对遍历到的每个顶点进行操作的函数的指针 pVisit
  Return:         空
*************************************************/
void Graph_DFS(graph_t *G, graph_vertex_t startV, void (*pVisit)(graph_vertex_t V));

/*************************************************
  Description:    广度优先遍历图 G
  Parameter:      一个指向图的指针 G
                  遍历起始点 startV
                  一个对遍历到的每个顶点进行操作的函数的指针 pVisit
  Return:         空
*************************************************/
void Graph_BFS(graph_t *G, graph_vertex_t startV, void (*pVisit)(graph_vertex_t V));

/*************************************************
  Description:    Dijkstra算法遍历图 G
  Parameter:      一个指向图的指针 G
                  距离数组 dist
                  路径数组 path
                  遍历起始点 startV
  Return:         如果成功执行返回 true ，否则返回 false
*************************************************/
bool Graph_Dijkstra(const graph_t *G, graph_edge_t dist[], graph_vertex_t path[], graph_vertex_t startV);

/*************************************************
  Description:    Floyd算法遍历图 G
  Parameter:      一个指向图的指针 G
                  距离数组 dist
                  路径数组 path
  Return:         如果成功执行返回 true ，否则返回 false
*************************************************/
bool Graph_Floyd(const graph_t *G, graph_edge_t dist[][VERTEX_NUMBER], graph_vertex_t path[][VERTEX_NUMBER]);

#endif
