#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph/dfs/Gdfs.h"
#include "graph/bfs/Gbfs.h"
#include "tree/dfs/Tdfs.h"
#include "tree/bfs/Tbfs.h"
#include "tree/treeCheck/isTree/IsTree.h"
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

int GrAlgo(char* path, int mode)
{
    // Graph init
    Agraph_t* G;
    Agnode_t* node;
    GVC_t* gvc;
    //Agsym_t* attr;
    FILE* fp;
    FILE* dot;
    int i;
    char str[50];

    dot = fopen("result/result.dot","w");
    if ((fp = fopen(path,"r")) == NULL)
        return 1;
    G = agread(fp,0);
    gvc = gvContext(); // CREATE CONTEXT
    Agnode_t* n = agfstnode(G); //FIRST NODE
    //attr = agattr(G,AGNODE,"id","0");
    agattr(G,AGNODE,"id","0");
    agattr(G,AGNODE,"color","black");
    agattr(G,AGRAPH,"bgcolor","white");
    i = 0;

    // Init node id
    for(node = n;node;node=agnxtnode(G,node))
    {
        sprintf(str,"%d",i);
        agset(node,"id",str);
        i++;
    }


    // Function call
    if(mode == 0)
    {
        Gdfs(G,gvc,dot);
        if(system("neato -Tpng result/result.dot -O") != 0)
            return 1;
    }
    if(mode == 1)
    {
        Gbfs(G,gvc,dot);
        if(system("neato -Tpng result/result.dot -O") != 0)
            return 1;
    }
    if(mode == 2)
    {
        if( IsConnexe(G) == 1 || IsCycle(G) == 1)
            return 1;
        Tdfs(G,gvc,dot);
        if(system("dot -Tpng result/result.dot -O") != 0)
            return 1;

    }
    if(mode == 3)
    {
        if( IsConnexe(G) == 1 || IsCycle(G) == 1)
            return 1;
        Tbfs(G,gvc,dot);
        if(system("dot -Tpng result/result.dot -O") != 0)
            return 1;

    }

    // Transform dot file into gif
    if(system("convert -resize 768x576 -delay 100 -loop 1  $(ls -v result/*.png) result/result.gif") != 0)
        return 1;
    if (system("rm result/*.png") != 0)
        return 1;
    agclose(G);
    fclose(fp);
    fclose(dot);
    if(system("eog result/result.gif") != 0)
        return 1;


    return 0;
}
