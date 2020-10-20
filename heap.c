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
  heapElem * aux1 = (heapElem *) malloc (sizeof(heapElem));
  heapElem * aux2 = (heapElem *) malloc (sizeof(heapElem));
  int prioridad;
  void* data;

  int pos = 0;
  aux1->data = pq->heapArray[pos].data;
  aux1->priority = pq->heapArray[pos].priority;
  while(pq->heapArray[pos+1].data != NULL)
  {
    aux2->data = pq->heapArray[pos+1].data;
    aux2->priority = pq->heapArray[pos+1].priority;
    while(aux2 != NULL)
    {
      if(aux1->priority > aux2->priority)
      {
        prioridad = aux1->priority;
        data = aux1->data;

        aux1->priority = aux2->priority;
        aux1->data = aux2->data;

        aux2->priority = prioridad;
        aux2->data = data;
      }
      pos++;
      aux2->data = pq->heapArray[pos].data;
      aux2->priority = pq->heapArray[pos].priority;
    }
    aux1->data = pq->heapArray[pos-1].data;
    aux1->priority = pq->heapArray[pos-1].priority;
    
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
