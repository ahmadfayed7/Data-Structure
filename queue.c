#include "Global.h"
#include <stdlib.h>
#ifndef LimitMemory
typedef struct queue {
int size;
int front;
int rear ;
Entry *entry[MAXQUEUE];
};
void CreateQueue(PQueue* ppq)
{   *ppq=(struct queue*)malloc(sizeof(struct queue));
    (*ppq)->front =0;
    (*ppq)->rear=-1;
    (*ppq)->size=0;
}
void Append(Entry *pe ,PQueue pq )
{
    pq->rear=(pq->rear+1)%MAXQUEUE;
    pq->entry[pq->rear]= malloc(sizeof(Entry));
    pq->entry[pq->rear]->e = malloc(type(pe->type));
    memcpy( pq->entry[pq->rear]->e,pe->e,type(pe->type));
    pq->entry[pq->rear]->type = pe->type ;
    pq->size++;
}
void Serve(Entry *pe ,PQueue pq )
{  char t =pq->entry[pq->front]->type ;
   pe->e =malloc(type(pq->entry[pq->front]->type));
   memcpy(pe->e,pq->entry[pq->front]->e,type(pq->entry[pq->front]->type));
   pe->type = pq->entry[pq->front]->type ;
   free(pq->entry[pq->front]->e);
   free(pq->entry[pq->front]);
   pq->front=(pq->front+1)%MAXQUEUE;
   pq->size--;
}
int QueueEmpty(PQueue pq)
{
    return pq->size==0;
}
int QueueFull(PQueue pq)
{
    return pq->size == MAXQUEUE ;
}
int  QueueSize(PQueue pq)
{
    return pq->size ;
}
void ClearQueue(PQueue pq)
{
    int i,s ;
    for(i=pq->front,s=0;s<pq->size;s++)
    {
        free(pq->entry[i]->e);
        free(pq->entry[i]);
        i=(i+1)%MAXQUEUE;
    }
    pq->front =0 ;
    pq->rear=-1;
    pq->size=0;
}
void TraveseQueue(PQueue pq,void(*pf)(Entry e))
{
    int i,s ;
    for(i=pq->front,s=0;s<pq->size;s++)
    {
     (*pf)(*(pq->entry[i]));
     i=(i+1)%MAXQUEUE;
    }
}
#else
typedef struct queuenode
{
   Entry* entry;
   struct queuenode * next;
}QueueNode;
typedef struct queue {
int size;
QueueNode * front;
QueueNode * rear ;
};
void CreateQueue(PQueue* ppq)
{
   *ppq=(struct queue *)malloc(sizeof(struct queue));
    (*ppq)->front =NULL;
    (*ppq)->rear=NULL;
    (*ppq)->size=0;
}
void Append(Entry *pe ,PQueue pq )
{
  QueueNode * pn = (QueueNode*)malloc(sizeof(QueueNode));
  pn->entry =(Entry*)malloc(sizeof(Entry));
  pn->entry->e =malloc(type(pe->type));
  memcpy(pn->entry->e,pe->e,type(pe->type));
  pn->entry->type =pe->type ;
  pn->next =NULL;
  if(!pq->size)
   pq->front=pn;
  else
   pq->rear->next=pn ;
  pq->rear=pn;
    pq->size++;
}
void Serve(Entry *pe ,PQueue pq )
{   QueueNode * pn ;
    pe->e =malloc(type(pq->front->entry->type));
    memcpy(pe->e,pq->front->entry->e,type(pq->front->entry->type));
    pe->type = pq->front->entry->type ;
    free(pq->front->entry->e);
    free(pq->front->entry);
    pn =pq->front;
    pq->front =pq->front->next;
    free(pn->entry->e);
    free(pn->entry);
    free(pn);
    if(!pq->front)
        pq->rear=NULL;
   pq->size--;
}
int QueueEmpty(PQueue pq)
{
    return pq->size==0;
}
int QueueFull(PQueue pq)
{
    return pq->size == MAXQUEUE ;
}
int  QueueSize(PQueue pq)
{
    return pq->size ;
}
void ClearQueue(PQueue pq)
{
    while(pq->front)
    {
        pq->rear=pq->front->next ;
        free(pq->front->entry->e);
        free(pq->front->entry);
        free(pq->front);
        pq->front =pq->rear ;
    }
    pq->size =0 ;
}
void TraveseQueue(PQueue pq,void(*pf)(Entry e))
{
    QueueNode *pn =pq->front ;
    while (pn)
    {
        (*pf)(*(pn->entry));
        pn=pn->next;
    }

}
#endif
