#ifndef GBFS_H_
#define GBFS_H_


#include <stdlib.h>
#include <stdio.h>
#include "../../queue/queue.h"
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

void __Gbfs(Agraph_t* G, Agnode_t* n, int* marks, GVC_t* gvc, FILE* dot);
void Gbfs(Agraph_t* G,GVC_t* gvc, FILE* dot);


#endif
