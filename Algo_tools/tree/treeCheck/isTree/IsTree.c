#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdlib.h>
#include <stdio.h>

int __IsCycle(Agraph_t* G, Agnode_t* n, int* marks)
{

    Agedge_t* e;
    *(marks+atoi(agget(n,"id"))) = 1;
    for(e=agfstedge(G,n);e;e=agnxtedge(G,e,n))
    {
        if(*(marks+atoi(agget(aghead(e),"id"))) == 1 && agtail(e) != n)
            return 1;
        if(*(marks+atoi(agget(aghead(e),"id"))) == 0)
            __IsCycle(G,aghead(e),marks);
    }
    return 0;
}


int IsCycle(Agraph_t* G)
{
    Agnode_t *node= agfstnode(G);
    int *marks = calloc(sizeof(int*),agnnodes(G));
    memset(marks,0,agnnodes(G));
    int isCycle = __IsCycle(G, node, marks);
    free(marks);
    return isCycle;
}



void __IsConnexe(Agraph_t* G, Agnode_t* n, int* marks)
{
    Agedge_t* e;
    *(marks+atoi(agget(n,"id"))) = 1;
    for(e=agfstedge(G,n);e;e=agnxtedge(G,e,n))
    {
        if(*(marks+atoi(agget(aghead(e),"id"))) == 0)
            __IsConnexe(G,aghead(e),marks);
    }
}


int IsConnexe(Agraph_t* G)
{
    Agnode_t *node;
    int *marks = calloc(sizeof(int*),agnnodes(G));
    int connexe = 0;
    memset(marks,0,agnnodes(G));
    if(*(marks+atoi(agget(agfstnode(G),"id"))) == 0)
        __IsConnexe(G, agfstnode(G), marks);
    for(node=agfstnode(G);node;node=agnxtnode(G,node))
    {
        if (*(marks+atoi(agget(node,"id"))) == 1)
            connexe++;
    }
    free(marks);
    return connexe;
}
