#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct nodo{
   void* data;
   int priority;
}heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;


void* heap_top(Heap* pq)
{
  if(pq == NULL || pq->size == 0) return NULL;
  int pos = 0;

  return pq->heapArray[pos].data;
}



void heap_push(Heap* pq, void* data, int priority)
{
  if(pq == NULL) return;
  if(pq->size == pq->capac) pq->heapArray = realloc(pq->heapArray, pq->capac * 2 + 1);

  heapElem* aux = (heapElem *) malloc(pq->capac * sizeof(heapElem));
  int pos = 0;
  while(pq->heapArray[pos].data != NULL)
  {
    aux[pos+1] = pq->heapArray[pos];
    pos++;
  }

  aux[0].data = data;
  aux[0].priority = priority;

  pq->heapArray = aux;

}


void heap_pop(Heap* pq)
{
  if(pq == NULL) return;

  heapElem* aux = 0;;
  aux->data = pq->heapArray[0].data;
  aux->priority = pq->heapArray[0].priority;

  pq->heapArray[0].data = pq->heapArray[pq->size].data;
  pq->heapArray[0].priority = pq->heapArray[pq->size].priority;

  pq->heapArray[pq->size].data = aux->data;
  pq->heapArray[pq->size].priority = aux->priority;
  
  pq->size--;
}

Heap* createHeap()
{
  Heap* heap = (Heap *) malloc (sizeof(Heap));
  heap->heapArray = (heapElem *) malloc (3* sizeof(heapElem));
  heap->size = 0;
  heap->capac = 3;

  return heap;
}
