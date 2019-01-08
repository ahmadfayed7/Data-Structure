#include "Global.h"
#include <stdlib.h>
#ifndef LimitMemory
typedef struct stack {
    int top ;
   Entry *entry[MAXSTACK];
};
void CreateStack(PStack *pps)
{
    *pps =(struct stack *)malloc(sizeof(struct stack));
    (*pps)->top=0;
}
void Push(Entry *pe,PStack ps)
{
    Entry *ptr  = (Entry*)malloc(sizeof(Entry));
    ptr->e = malloc(sizeof(pe->type));
    memcpy(ptr->e ,pe->e ,type(pe->type));
    ptr->type=pe->type;
    ps->entry[ps->top++] = ptr ;
}
int  StackFull(PStack ps)
{
    return ps->top >=MAXSTACK ;
}
void Pop(Entry *pe,PStack ps)
{   pe->e =malloc(sizeof(type(ps->entry[ps->top-1]->type)));
    memcpy( pe->e,ps->entry[ps->top-1]->e ,type(ps->entry[ps->top-1]->type) );
    pe->type = ps->entry[ps->top-1]->type ;
    free(ps->entry[ps->top-1]->e);
     free(ps->entry[--ps->top]);

}
int  StackEmpty(PStack ps)
{
    return ps->top == 0 ;
}
void StackTop(Entry *pe,PStack ps)
{
    pe->e =malloc(sizeof(type(ps->entry[ps->top-1]->type)));
    memcpy( pe->e,ps->entry[ps->top-1]->e ,type(ps->entry[ps->top-1]->type) );
    pe->type = ps->entry[ps->top-1]->type ;
}
int  StackSize(PStack ps)
{
    return ps->top ;
}
void ClearStack(PStack ps)
{   int i ;
    Entry element ;
    for(i = ps->top ;i>0 ;i--)
    {
        free(ps->entry[i-1]->e);
        free(ps->entry[i-1]);
    }
    ps->top =0 ;
}
void TraverseStack(PStack ps ,void (*pf)(Entry))
{
    int i ;
    Entry element ;
    for(i = ps->top ;i>0 ;i--)
    {
          (*pf)(*(ps->entry[i-1]));
    }
}
#else
typedef struct stacknode {
   Entry * entry;
    struct stacknode * next ;
}StackNode;
typedef struct stack {
    StackNode * top ;
    int StackSize ;
};
void CreateStack(PStack *pps)
{
     *pps =(struct stack *)malloc(sizeof(struct stack));
    (*pps)->top =NULL;
    (*pps)->StackSize =0;
}
void Push(Entry *pe,PStack ps)
{
    StackNode * pn=(StackNode *)malloc(sizeof(StackNode));
    pn->entry =(Entry*)malloc(sizeof(Entry));
    pn->entry->e = malloc(sizeof(type(pe->type)));
    memcpy(pn->entry->e,pe->e,type(pe->type));
    pn->entry->type=pe->type ;
    pn ->next = ps->top ;
    ps->top = pn ;
    ps->StackSize++;
}
int  StackFull(PStack ps)
{
    return 0 ;
}
void Pop(Entry *pe,PStack ps)
{
    StackNode *pn ;
    pe->e =malloc(sizeof(type(ps->top->entry->type)));
    memcpy(pe->e,ps->top->entry->e,type(ps->top->entry->type));
    pe->type =ps->top->entry->type;
    free(ps->top->entry->e);
    pn =ps->top;
    ps->top = ps->top->next;
    free(pn->entry->e);
    free(pn->entry);
    free(pn);
    ps->StackSize--;
}
int  StackEmpty(PStack ps)
{
    return ps->top == NULL;
}
void StackTop(Entry *pe,PStack ps)
{
    pe->e =malloc(sizeof(type(ps->top->entry->type)));
    memcpy(pe->e,ps->top->entry->e,type(ps->top->entry->type));
    pe->type =ps->top->entry->type;
}
int  StackSize(PStack ps)
{
    return ps->StackSize ;
}
void ClearStack(PStack ps)
{
    StackNode * pn = ps->top;
    while (pn)
    {   pn = pn->next ;
        free(pn->entry->e);
        free(pn->entry);
        free(ps->top);
        ps->top = pn ;
    }
    ps->StackSize =0 ;
}
void TraverseStack(PStack ps ,void (*pf)(Entry))
{
    StackNode *pn = ps ->top ;
   while(pn)
   {
       (*pf)(*(pn->entry));
       pn=pn->next ;
   }

}
#endif
