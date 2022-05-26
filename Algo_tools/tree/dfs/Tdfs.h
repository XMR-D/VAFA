#ifndef TDFS_H_
#define TDFS_H_


#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdlib.h>
#include <stdio.h>



void __Tdfs(Agraph_t* G, Agnode_t* n, int* marks, GVC_t* gvc, FILE* dot);
void Tdfs(Agraph_t * G, GVC_t* gvc, FILE* dot);
void reset(Agraph_t* G, GVC_t* gvc, FILE* dot);


#endif
