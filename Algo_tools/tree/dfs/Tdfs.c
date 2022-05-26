#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdlib.h>
#include <stdio.h>



void reset(Agraph_t* G, GVC_t* gvc, FILE* dot)
{
    Agnode_t* n;
    for(n=agfstnode(G);n;n=agnxtnode(G,n))
        agsafeset(n,"color","black","");   //change node color to red
    gvLayout(gvc,G,"dot"); // new dot with node color changed
    gvRender(gvc, G, "dot", dot); // new render


}


void __Tdfs(Agraph_t* G, Agnode_t* n, int* marks, GVC_t* gvc, FILE* dot)
{
    Agedge_t* e;
    *(marks+atoi(agget(n,"id"))) = 1;
    agsafeset(n,"color","red","");   //change node color to red
    gvLayout(gvc,G,"neato"); // new dot with node color changed
    gvRender(gvc, G, "dot", dot); // new render
    for(e=agfstedge(G,n);e;e=agnxtedge(G,e,n))
    {
        if(*(marks+atoi(agget(aghead(e),"id"))) == 0
            && *(marks+atoi(agget(aghead(e),"id"))) == 0)
        {
            __Tdfs(G,aghead(e),marks, gvc, dot);
        }
    }
}


void Tdfs(Agraph_t* G, GVC_t* gvc, FILE* dot)
{
    Agnode_t *node;
    int *marks = calloc(sizeof(int*),agnnodes(G));
    memset(marks,0,agnnodes(G));
    //printf("id = %s\n",agget(n,"id"));
    for(node=agfstnode(G);node;node=agnxtnode(G,node))
    {
        if(*(marks+atoi(agget(node,"id"))) == 0)
        {
            agsafeset(node,"color","red","");   //change node color to red
            gvLayout(gvc,G,"neato"); // new dot with node color changed
            gvRender(gvc, G, "dot", dot); // new render
            __Tdfs(G, node, marks, gvc, dot);
        }
    }
    //reset(G,gvc,dot);
    free(marks);
}

