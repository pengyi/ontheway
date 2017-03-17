#ifndef YP_GRAPH_H
#define YP_GRAPH_H

typedef struct _yp_arc_node {
    int adjvex;
    struct _yp_arc_node* nextarc;
    void* info;
} yp_arc_node;

typedef struct _yp_v_node {
    void* value;
    yp_arc_node* firstarc;
} yp_v_node;

typedef struct _yp_graph {
    yp_v_node* buckets;
    int vexnum;
    int arcnum;
    int bucketsize;
    int kind;
    void (*print_v_node)(yp_v_node* node);
} yp_graph;
#endif