#include "Global.h"
#include <stdlib.h>
typedef struct treenode {
  Entry  *entry ;
  struct treenode * left ;
  struct treenode * right ;
}TreeNode;

 struct tree {
TreeNode * root ;
int size ;
};
void CreateTree(PTree * ppt)
{  (*ppt)=(struct tree *)malloc(sizeof(struct tree));
    (*ppt)->root=NULL ;
    (*ppt)->size =0 ;
}
int TreeFull(PTree  pt)
{
    return 0 ;
}
int TreeEmpty(PTree  pt)
{
    return !(pt->size) ;
}
int TreeSize(PTree  pt)
{
    return pt->size;
}
int TreeDepthAux(TreeNode * pn)
{
  if(pn)
  {
  int a = TreeDepthAux(pn->right);
  int b = TreeDepthAux(pn->left);
  return a>b ? 1+a : 1+b ;
  }
  else
  return 0 ;

}
int TreeDepth(PTree  pt)
{
  TreeDepthAux(pt->root);
}

void ClearTreeAux(TreeNode * pn)
{
    TreeNode * q = pn;
    while(q)
    {
    ClearTreeAux(q->left);
    ClearTreeAux(q->right);
    }
    free(q->entry->e);
    free(q->entry);
    free(q);
}
void ClearTree(PTree  pt)
{
   ClearTreeAux(pt->root);
   pt->root =NULL;
   pt->size =0 ;
}
int  InsertTree(Entry *pe ,PTree  pt)
{
    TreeNode *q =pt->root,*r=NULL;
    TreeNode * p ;
    int s = pt->size;
    p = (TreeNode*)malloc(sizeof(TreeNode));
    p->entry =(Entry*)malloc(sizeof(Entry));
    p->entry->e =malloc(type(pe->type));
    memcpy(p->entry->e,pe->e,type(pe->type));
    p->entry->type=pe->type ;
    p->left =NULL;
    p->right =NULL;
    while(q)
    {
        r=q ;
       if(pe->type==r->entry->type&&memcmp(r->entry->e,pe->e,pe->type)>0)
             q=q->left;
       else
            q=q->right;

    }
     if(!r)
        pt->root =p;
     else if(pe->type==r->entry->type&&memcmp(r->entry->e,pe->e,pe->type)>0)
        r->left=p;
     else
        r->right=p;
    pt->size++;
    return 1 ;
}
int  FindTree(Entry *pe ,PTree  pt)
{    int found =0 ;
    TreeNode *q =pt->root,*r=NULL;
    while(q &&(pe->type==q->entry->type) &&!(found = !(memcmp(q->entry->e,pe->e,type(pe->type)))))
    {
        r= q ;
     if(pe->type==q->entry->type&&memcmp(q->entry->e,pe->e,type(pe->type))>0)
        q=q->left;
    else
       q=q->right;
    }
   return found ;
}
int  DeleteTree(Entry *pe ,PTree  pt)
{
    int found =0 ;
    TreeNode *q =pt->root,*r=NULL;
     while(q &&(pe->type==q->entry->type) &&!(found = !(memcmp(q->entry->e,pe->e,type(pe->type)))))
    {
        r= q ;
    if(pe->type==q->entry->type&&memcmp(q->entry->e,pe->e,type(pe->type))>0)
        q=q->left;
    else
       q=q->right;
    }
    if(found)
    {
      if(!r)
        DeleteNode(&q);
     else  if(pe->type==r->entry->type&&memcmp(r->entry->e,pe->e,type(pe->type))>0)
        DeleteNode(&r->left);
     else
        DeleteNode(&r->right);
    }
   return found ;
}
void DeleteNode (TreeNode **pn)
{
    TreeNode *q  ,*r ;
 if(!(*pn)->left)
 {
     q=(*pn);
    (*pn)=(*pn)->right;
 }
 else if(!(*pn)->right)
 {   q=(*pn);
     (*pn)=(*pn)->left;
 }
 else
 {
   q=(*pn)->left ;
          if(!q->right)
          {
              memcpy((*pn)->entry->e,q->entry->e,type(q->entry->type));
              (*pn)->entry->type =q->entry->type;
              (*pn)->left=q->left;
          }
          else
          {

          do
          {
              r=q ;
              q=q->right ;

          }while (q->right);
          memcpy((*pn)->entry->e,q->entry->e,type(q->entry->type));
          (*pn)->entry->type =q->entry->type;
          r->right =q->left ;
          }
 }
 free(q->entry->e);
 free(q->entry);
 free(q);
}
void TraverseTreeVLRAux(TreeNode * pn,void (*pf)(Entry))
{   if(pn)
    {
     (*pf)(*(pn->entry));
     TraverseTreeVLRAux(pn->left,pf);
     TraverseTreeVLRAux(pn->right,pf);
    }
}
void TraverseTreeVLR(PTree  pt,void (*pf)(Entry))
{
   TraverseTreeVLRAux(pt->root ,pf);
}
void TraverseTreeLVRAux(TreeNode * pn,void (*pf)(Entry))
{
    if(pn)
    {
     TraverseTreeLVRAux(pn->left,pf);
     (*pf)(*(pn->entry));
     TraverseTreeLVRAux(pn->right,pf);
    }
}
void TraverseTreeLVR(PTree  pt,void (*pf)(Entry))
{
    TraverseTreeLVRAux(pt->root ,pf);
}
void TraverseTreeLRVAux(TreeNode * pn,void (*pf)(Entry))
{
  if(pn)
    {
     TraverseTreeLRVAux(pn->left,pf);
     TraverseTreeLRVAux(pn->right,pf);
    (*pf)(*(pn->entry));
    }
}
void TraverseTreeLRV(PTree  pt,void (*pf)(Entry))
{
 TraverseTreeLRVAux (pt->root ,pf);
}
