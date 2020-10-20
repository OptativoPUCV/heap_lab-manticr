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

void cambio(int *a, int *b)
{
  int temp = *b;
  *b = *a;
  *a = temp;
}

void ordenar(Heap * pq, int size, int i)
{
  if (size == 1) return;
  else 
  {
    int mas_largo = i;
    int hijo1 = 2 * i + 1;
    int hijo2 = 2 * i + 2;
    if (hijo1 < size && pq->heapArray[hijo1].priority > pq->heapArray[mas_largo].priority)
      mas_largo = hijo1;
    if (hijo2 < size && pq->heapArray[hijo2].priority > pq->heapArray[mas_largo].priority)
      mas_largo = hijo2;

    if (mas_largo != i) 
    {
      cambio(&pq->heapArray[i].priority, &pq->heapArray[mas_largo].priority);
      ordenar(pq, size, mas_largo);
    }
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
  pq->size++;
  
  for (int i = pq->size / 2 - 1; i >= 0; i--)
  {
    ordenar(pq, pq->size, i);
  }

  for (int x = 0; x < pq->size; x++)
    printf("%d ", pq->heapArray[x].priority);
  printf("\n");
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
  for (int i = pq->size / 2 - 1; i >= 0; i--)
  {
    ordenar(pq, pq->size, i);
  }
}

Heap* createHeap()
{
  Heap* heap = (Heap *) malloc (sizeof(Heap));
  heap->heapArray = (heapElem *) malloc (3* sizeof(heapElem));
  heap->size = 0;
  heap->capac = 3;

  return heap;
}
