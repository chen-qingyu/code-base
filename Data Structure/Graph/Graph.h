/**
 * @file Graph.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 图 (Graph)
 * @version 0.1
 * @date 2022.01.29
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 图 G(V, E) 由一个非空的有限顶点集合 V 和一个有限边集合 E 组成。
 * 图 G 属于 graph_t ，顶点的编号 V 属于 graph_vertex_t ，边的权重 E 属于 graph_edge_t 。
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h> // bool

#define VERTEX_NUMBER 7

/* 注释掉此行变成无向图 */
// #define UNDIRECTED

typedef int graph_vertex_t; // 顶点的编号

typedef int graph_edge_t; // 边的权重

typedef struct graph graph_t; // 图

/**
 * @brief 创建一个空图
 *
 * @return graph_t* 一个指向空图的指针
 */
graph_t *Graph_Create(void);

/**
 * @brief 销毁一个图 G
 *
 * @param G 一个指向待销毁图的指针
 */
void Graph_Destroy(graph_t *G);

/**
 * @brief 以权重 E 链接图 G 的两个顶点 V1 和 V2
 *
 * @param G 一个指向图的指针
 * @param V1 顶点1
 * @param V2 顶点2
 * @param E 两个顶点之间连线的权重
 */
void Graph_Link(graph_t *G, graph_vertex_t V1, graph_vertex_t V2, graph_edge_t E);

/**
 * @brief 断开图 G 的两个顶点 V1 和 V2
 *
 * @param G 一个指向图的指针
 * @param V1 顶点1
 * @param V2 顶点2
 */
void Graph_Unlink(graph_t *G, graph_vertex_t V1, graph_vertex_t V2);

/**
 * @brief 判断图 G 的两个顶点 V1 和 V2 之间是否链接
 *
 * @param G 一个指向图的指针
 * @param V1 顶点1
 * @param V2 顶点2
 * @return 如果两个顶点已链接则返回 true ，否则返回 false
 */
bool Graph_IsAdjacent(const graph_t *G, graph_vertex_t V1, graph_vertex_t V2);

/**
 * @brief 深度优先遍历图 G
 *
 * @param G 一个指向图的指针
 * @param startV 遍历起始点
 * @param pVisit 一个对遍历到的每个顶点进行操作的函数的指针
 */
void Graph_DFS(graph_t *G, graph_vertex_t startV, void (*pVisit)(graph_vertex_t V));

/**
 * @brief 广度优先遍历图
 *
 * @param G 一个指向图的指针
 * @param startV 遍历起始点
 * @param pVisit 一个对遍历到的每个顶点进行操作的函数的指针
 */
void Graph_BFS(graph_t *G, graph_vertex_t startV, void (*pVisit)(graph_vertex_t V));

/**
 * @brief Dijkstra 算法遍历图
 *
 * @param G 一个指向图的指针
 * @param dist 距离数组
 * @param path 路径数组
 * @param startV 遍历起始点
 * @return 如果执行成功返回 true ，否则返回 false
 */
bool Graph_Dijkstra(const graph_t *G, graph_edge_t dist[], graph_vertex_t path[], graph_vertex_t startV);

/**
 * @brief Floyd 算法遍历图
 *
 * @param G 一个指向图的指针
 * @param dist 距离数组
 * @param path 路径数组
 * @return 如果执行成功返回 true ，否则返回 false
 */
bool Graph_Floyd(const graph_t *G, graph_edge_t dist[][VERTEX_NUMBER], graph_vertex_t path[][VERTEX_NUMBER]);

#endif
