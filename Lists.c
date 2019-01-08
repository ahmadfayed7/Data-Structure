#include "Global.h"
#include <stdlib.h>
//#define MemoryLimited

//int BinRecSearch(Entry *pe , Plist pl);
//int BinIterSearch(Entry *pe , Plist pl);
#ifdef MemoryLimited
typedef struct listnode
{
 Entry * entry ;
 struct listnode * next ;
}ListNode;
typedef struct list{
 ListNode * head ;
 ListNode * currunt ;
 int CurruntPostion;
int size ;
}List;
void CreateList(PList *ppl)
{
    *ppl=(List*)malloc(sizeof(List));
    (*ppl)->head =NULL;
    (*ppl)->size =0;
}
int ListEmpty(PList pl)
{
    return !pl->size ;
}
int ListFull(PList pl)
{
    return 0;
}
int  ListSize(PList pl)
{
    return pl->size ;
}
void InsertList(int pos , Entry *pe , PList pl)
{
    int i;
    ListNode *q;
    ListNode *p =(ListNode*)malloc(sizeof(ListNode));
    p->entry =(Entry*)malloc(sizeof(Entry));
    p->entry->type =pe->type ;
    p->entry->e = malloc(type(pe->type));
    memcpy( p->entry->e,pe->e,type(pe->type) );
    p->next=NULL;
    if(pos==0)
    {
    p->next = pl->head ;
    pl->head = p;
    pl->CurruntPostion=0;
    pl->currunt =pl->head;
    }
    else
    {
        if(pos<=pl->CurruntPostion)
        {
          pl->CurruntPostion=0;
          pl->currunt =pl->head;
        }
        else
        {
         for(; pl->CurruntPostion<pos-1; pl->CurruntPostion++)
               pl->currunt=pl->currunt->next;
         p->next=pl->currunt->next;
         pl->currunt->next=p;
        }
    }
    pl->size++;
}
void DeleteList(int pos , Entry *pe , PList pl)
{
    int i;
    ListNode *q,*temp;
    if(pos==0)
    {
     pe->e=malloc(type(pl->head->entry->type));
     memcpy(pe->e,pl->head->entry->e,type(pl->head->entry->type));
     pe->type =pl->head->entry->type;
     q=pl->head->next ;
     free(pl->head->entry->e);
     free(pl->head->entry);
     free(pl->head);
     pl->head =q;
     pl->CurruntPostion=0;
    pl->currunt =pl->head;
    }
    else
    {
         if(pos<=pl->CurruntPostion)
        {
          pl->CurruntPostion=0;
          pl->currunt =pl->head;
        }
        else
        {
           for(;pl->CurruntPostion<pos-1;pl->CurruntPostion++)
              pl->currunt=pl->currunt->next;
           pe->e=malloc(type(pl->currunt->next->entry->type));
           memcpy(pe->e,pl->currunt->next->entry->e,type(pl->currunt->next->entry->type));
           pe->type =pl->currunt->next->entry->type;
           free(pl->currunt->next->entry->e);
           free(pl->currunt->next->entry);
           temp =pl->currunt->next ;
           pl->currunt->next =pl->currunt->next->next;
           free(temp);
        }
    }
    pl->size--;
}
void TraverseList(PList pl ,void(*pf)(Entry))
{
    ListNode *q =pl->head;
    while (q)
    {
        (*pf)(*(q->entry));
        q=q->next;
    }
}
void ReplaceList(int pos , Entry *pe ,PList pl)
{
     if(pos<=pl->CurruntPostion)
        {
          pl->CurruntPostion=0;
          pl->currunt =pl->head;
        }

     for(;pl->CurruntPostion<pos;pl->CurruntPostion++)
        pl->currunt=pl->currunt->next;
     pl->currunt->entry->e = malloc(type(pe->type));
     memcpy(pl->currunt->entry->e,pe->e,type(pe->type));
     pl->currunt->entry->type=pe->type ;

}
void RetriveList(int pos , Entry *pe , PList pl)
{
     if(pos<=pl->CurruntPostion)
        {
          pl->CurruntPostion=0;
          pl->currunt =pl->head;
        }

     for(;pl->CurruntPostion<pos;pl->CurruntPostion++)
        pl->currunt=pl->currunt->next;
     pe->e = malloc(type(pl->currunt->entry->type));
     memcpy(pe->e,pl->currunt->entry->e,type(pl->currunt->entry->type));
     pe->type=pl->currunt->entry->type ;

}
void DestroyList(PList pl)
{
 ListNode *q =pl->head ;
 while(q)
 {
     pl->head=pl->head->next;
     free(q->entry->e);
     free(q->entry);
     free(q);
     q=pl->head ;
 }
 pl->size=0;
}

int SeqSearch(Entry *pe , PList pl)
{
    int current ;
    ListNode *q ;
    for(current=0 ,q=pl->head;current<pl->size;current++)
    {
        if(!memcmp(q->entry->e,pe->e,type(pe->type)))
           return current ;
        q=q->next;
    }
    return -1 ;
}
#else
 struct list{
Entry * entry [MAXLIST];
int size ;
};
void CreateList(PList *ppl)
{
  (*ppl)=( struct list*)malloc(sizeof( struct list));
   (*ppl)->size = 0 ;
}
int ListEmpty(PList pl)
{
    return !pl->size ;
}
int ListFull(PList pl)
{
    return pl->size ==MAXLIST ;
}
int  ListSize(PList pl)
{
    return pl->size;
}
void InsertList(int pos , Entry *pe , PList pl)
{
    Entry * element = (Entry *)malloc(sizeof(Entry));
    element->e = malloc(type(pe->type));
    element->type =pe->type;
    memcpy(element->e,pe->e,type(pe->type));
    int  i ;
    for (i=pl->size -1;i>=pos ;i-- )
        pl->entry[i+1]=pl->entry[i];
    pl->entry[pos]=element;
    pl->size++;
}
void DeleteList(int pos , Entry *pe , PList pl)
{
    int i;
    pe->e = malloc(type(pl->entry[pos]->type));
    memcpy(pe->e,pl->entry[pos]->e,type(pl->entry[pos]->type));
    free(pl->entry[pos]->e);
    free(pl->entry[pos]);
    for(i = pos ;i<pl->size-1;i++)
         pl->entry[i]=pl->entry[i+1];
    pl->size--;
}
void TraverseList(PList pl ,void(*pf)(Entry))
{    int i = 0;
    while(i< pl->size)
    {
        (*pf)(*(pl->entry[i]));
        i++;
    }
}
void ReplaceList(int pos , Entry *pe , PList pl)
{
    pl->entry[pos]->e=pe->e;
    pl->entry[pos]->type=pe->type;
}
void RetriveList(int pos , Entry *pe , PList pl)
{
 pe->e = pl->entry[pos]->e;
 pe->type =pl->entry[pos]->type;
}
void DestroyList(PList pl)
{
    pl->size =0 ;
}
int SeqSearch(Entry *pe , PList pl)
{
    int current ;
    for(current=0;current<pl->size;current++)
    {
        if(!memcmp(pl->entry[current]->e,pe->e,type(pe->type)))
           return current ;
    }
    return -1 ;
}
void InsertOrder( Entry *pe , PList pl)
{
   int current ;
    for(current=0;current<pl->size;current++)
    {
        if(memcmp(pl->entry[current]->e,pe->e,type(pe->type))>0)
           break;
    }
    InsertList(current,pe,pl);
}
int BinRecSearch2(Entry *pe , PList pl,int bottom,int top )
{
    int middle;
    if(bottom<=top)
    {
        middle =(top+bottom)/2 ;
        if(!memcmp(pl->entry[middle]->e,pe->e,type(pe->type)))
           return middle ;
        else if(memcmp(pl->entry[middle]->e,pe->e,type(pe->type))<0)
        return BinRecSearch2(pe,pl,middle+1,top);
        else if(memcmp(pl->entry[middle]->e,pe->e,type(pe->type))>0)
        return BinRecSearch2(pe,pl,bottom,middle-1);


    }
    return -1;
}
int BinRecSearch(Entry *pe , PList pl)
{
  BinRecSearch2(pe,pl,0,pl->size-1);
}
int BinIterSearch(Entry *pe , PList pl)
{
    int middle,bottom=0,top=pl->size-1;
    while(bottom<=top)
    {
        middle =(top+bottom)/2 ;
        if(!memcmp(pl->entry[middle]->e,pe->e,type(pe->type)))
           return middle ;
        else if(memcmp(pl->entry[middle]->e,pe->e,type(pe->type))<0)
         bottom =middle+1;
        else
        top =middle-1 ;
    }
    return -1;
}
#endif
