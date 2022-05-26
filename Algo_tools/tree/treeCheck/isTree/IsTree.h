#ifndef DFS_H_
#define DFS_H_


#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdlib.h>
#include <stdio.h>


int __IsCycle(Agraph_t* G, Agnode_t* n, int* marksD);
int IsCycle(Agraph_t * G);

void __IsConnexe(Agraph_t* G, Agnode_t* n, int* marks);
int IsConnexe(Agraph_t* G);


#endif
