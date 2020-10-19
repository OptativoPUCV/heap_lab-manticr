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

void ordenar(Heap * pq)
{
  int padre = 0;
  int hijo1 = padre+1;
  int hijo2 = padre+2;
  while(hijo2 <= pq->size)
  {
    if(pq->heapArray[padre].priority < pq->heapArray[hijo1].priority)
    {
      pq->heapArray[padre].data = pq->heapArray[hijo1].data;
      pq->heapArray[padre].priority = pq->heapArray[hijo1].priority;
    }

    if(pq->heapArray[padre].priority < pq->heapArray[hijo2].priority)
    {
      pq->heapArray[padre].data = pq->heapArray[hijo2].data;
      pq->heapArray[padre].priority = pq->heapArray[hijo2].priority;
    }

    padre++;
    hijo1 = hijo2+1;
    hijo2 = hijo1+1;
  }
}


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

  int pos = 0;
  while(pq->heapArray[pos].data != NULL) pos++;

  pq->heapArray[pos].data = data;
  pq->heapArray[pos].priority = priority;

  ordenar(pq);
}


void heap_pop(Heap* pq)
{
  if(pq == NULL) return;

  heapElem* aux = (heapElem *) malloc (1 * sizeof(heapElem));
  aux->data = pq->heapArray[0].data;
  aux->priority = pq->heapArray[0].priority;

  pq->heapArray[0].data = pq->heapArray[pq->size-1].data;
  pq->heapArray[0].priority = pq->heapArray[pq->size-1].priority;

  pq->heapArray[pq->size-1].data = aux->data;
  pq->heapArray[pq->size-1].priority = aux->priority;
  
  pq->size--;
  ordenar(pq);
}

Heap* createHeap()
{
  Heap* heap = (Heap *) malloc (sizeof(Heap));
  heap->heapArray = (heapElem *) malloc (3* sizeof(heapElem));
  heap->size = 0;
  heap->capac = 3;

  return heap;
}
