#include "yp_graph.h"
#include <stdlib.h>

yp_graph* graph_create() {
    yp_graph* graph = NULL;
    graph = (yp_graph*)malloc(sizeof(yp_graph));
    if (!graph) {
        return NULL;
    }
    graph->buckets    = NULL;
    graph->bucketsize = 0;
    graph->arcnum     = 0;
    graph->vexnum     = 0;
    graph->kind       = 0;
    graph->print_v_node = NULL;
    return graph;
}

yp_graph* graph_add_vertexs(yp_graph* graph, void**p, int len) {
    int i = 0;
    yp_v_node* buckets = NULL, *node = NULL;
    if (graph == NULL) {
        return NULL;
    }
    buckets = (yp_v_node*)malloc(sizeof(yp_v_node) * len);
    node = buckets;
    for(i = 0; i < len; ++i) {
        node = node + i;
        node->value = *(p + i);
        node->firstarc = NULL;
    }
    graph->buckets = buckets;
    graph->vexnum = len;
    graph->bucketsize = len;
    

}