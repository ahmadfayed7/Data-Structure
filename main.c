#include <stdio.h>
#include <stdlib.h>
#include "Global.h"

void Display(Entry e)
{
     switch (e.type)
         {
             case 'f' :   printf("%f\n",*((float*)e.e));break;
             case 'c' :   printf("%c\n",*((char*)e.e));break;
             case 'i' :   printf("%i\n",*((int*)e.e));break;
             case 'd' :   printf("%f\n",*((double*)e.e));break;
         }
}
int main()
{
    Entry e ;
    int z;
    int e11 = 51 ;
    int e22 = 52 ;
    int e33 = 53 ;
    int e44=54 ;
    char c ;
    Entry e1;
    e1.e =(void*)&e11;
    e1.type='i';
    Entry e2;
    e2.e =(void*)&e22;
    e2.type='i';
    Entry e3;
    e3.e =(void*)&e33;
    e3.type='i';
    Entry e4;
    e4.e =(void*)&e44;
    e4.type='i';
    //////////////////////////////////////Stack code test//////////////////////////////////////////////////
    PStack s;
    CreateStack(&s);
    Push(&e3,s);
    Push(&e4,s);
    Pop(&e,s);
    TraverseStack(s,&Display);
     ///////////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////Queue code test//////////////////////////////////////////////////
    PQueue q ;
    CreateQueue(&q);
    Append(&e2,q);
    Append(&e1,q);
    Serve(&e,q);
    TraveseQueue(q,&Display);
     ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////List code test//////////////////////////////////////////////////
    PList l;
    CreateList(&l);
    InsertList(0,&e1,l);
    InsertList(1,&e1,l);
    InsertOrder(&e2,l);
    DeleteList(0,&e,l);
    TraverseList(l,&Display);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////Tree code test//////////////////////////////////////////////////
    PTree t ;
    CreateTree(&t);
    InsertTree(&e , t);
    InsertTree(&e2 , t);
    DeleteTree(&e3,t);
    TraverseTreeVLR(t ,&Display);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    return 0;
}
