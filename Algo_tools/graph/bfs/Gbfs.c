#include <stdlib.h>
#include <stdio.h>
#include "../../queue/queue.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

void __Gbfs(Agraph_t* G, Agnode_t* n, int* marks, GVC_t* gvc, FILE* dot)
{
    Agedge_t* e;
    struct queue* q = createQueue();
    enqueue(q,n);
    *(marks+atoi(agget(n,"id"))) =1;
    agsafeset(n,"color","red","");// CHANGE NODE COLOR TO red
    gvLayout(gvc,G,"circo"); // NEW DOT WITH NODE COLOR CHANGED
    gvRender(gvc, G, "dot", dot); // NEW RENDER

    while(!isEmpty(q))
    {
        n = dequeue(q);
        for(e=agfstedge(G,n);e;e=agnxtedge(G,e,n))
        {
            if(*(marks+atoi(agget(aghead(e),"id"))) == 0)
            {
                *(marks+atoi(agget(n,"id"))) =1;
                enqueue(q,aghead(e));
                agsafeset(n,"color","red","");// CHANGE NODE COLOR TO red
                gvLayout(gvc,G,"circo"); // NEW DOT WITH NODE COLOR CHANGED
                gvRender(gvc, G, "dot", dot); // NEW RENDER
            }
        }
    }
    while (q->front != q->rear)
    {
        Agnode_t* freeNode = dequeue(q);
        free(freeNode);
    }
    free(q);

}



void Gbfs(Agraph_t* G, GVC_t* gvc, FILE* dot)
{
    Agnode_t* node;
    int *marks = calloc(sizeof(int*),agnnodes(G));
    memset(marks,0,agnnodes(G));
    for(node=agfstnode(G);node;node=agnxtnode(G,node))
    {
        if(*(marks+atoi(agget(node,"id"))) == 0)
            __Gbfs(G,node,marks,gvc,dot);
    }
    gvLayout(gvc,G,"circo"); // NEW DOT WITH NODE COLOR CHANGED
    gvRender(gvc, G, "dot", dot); // NEW RENDER
    free(marks);



}
