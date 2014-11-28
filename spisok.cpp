
#include "spisok.h"
int list_ctor(List* L)
{
    assert(L);
    L->first = (ListElem_t*) calloc (1, sizeof(ListElem_t));
    assert(L->first);
    L->first->last=NULL;
    L->first->next=NULL;
    L->current=L->first;
    L->amount=0;
    return 0;
}

int gotofirst(List* L)
{

    assert(L);
    if (L->first==NULL)return NO_LIST;
    L->current=L->first;
    return OK;
}

int gotonext(List* L)
{

    assert(L);
    if (L->current->next!=NULL)
    {
        L->current=L->current->next;
        return OK;
    }
    return CANT_GO;
}

int gotolast(List* L)
{
    if (listok(L)!=OK)return WRONG;
    if (L->current->last!=NULL)
    {
        L->current=L->current->last;
        return OK;
    }
    return CANT_GO;
}


int input(List* L,data_t value) //create element on the right side and move on it's position
{
    assert(L);
    if (L->current==NULL)return NO_LIST;
    ListElem_t* buffer=(ListElem_t*) calloc (1, sizeof(ListElem_t));
    assert(buffer);

    if (L->current->next==NULL)
    {

        buffer->next=NULL;
        buffer->last=L->current;
        L->current->next=buffer;
    }
    else
    {
        buffer->next=L->current->next;
        buffer->last=L->current;
        L->current->next->last=buffer;
        L->current->next=buffer;
    }
    (L->current->next->data)=value;
    L->amount++;
    gotonext(L);
    return OK;
}

int deleteelem(List* L)
{
    assert(L);
    if (L->current!=L->first)
    {
        if (L->current->next!=NULL)
            L->current->next->last=L->current->last;
        L->current->last->next=L->current->next;
        L->current=L->current->last;
        L->amount--;
        return OK;
    }
}


int list_dtor(ListElem_t* current)
{
    assert(current);
    if (current->next!=NULL)list_dtor(current->next);
    free(current);
    return OK;
}


int readfromfile(FILE *F,List* L)
{
    assert(F&&L);
    char* buf=(char*)calloc(WORDLENGTH, sizeof(char));
    if (fscanf(F,"%s",buf)!=EOF)
    {

        input(L,buf);
    }
    return OK;
}

void dumplist(List* L)
{
    printf("_______________________DUMP________________________\n\n");
    assert(L);
    if (listok(L)!=OK)
    {
        printf("SOMETHINK IS WRONG!");
        return;
    }
    gotofirst(L);
    while (L->current->next!=NULL)
    {
        gotonext(L);
        printf("%20s  %p\n",L->current->data,L->current);
    }
    printf("amount:%d\n\n_______________________DUMP________________________\n\n\n",L->amount);
}




int listcontainsthis(List* L,data_t data)
{

    gotofirst(L);
    while (L->current->next!=NULL)
    {
        gotonext(L);
        if (strcmp(L->current->data,data)==0)  return 1;
    }
    return 0;
}

#define ATTACHED_CODE

#define CHECK(cond, str, code)  \
if (!(cond))                    \
{                               \
    fprintf("%s\n", str);       \
    ATTACHED_CODE               \
    return code;                \
}                               \


#undef ATTACHED_CODE

#define ATTACHED_CODE free(ptr);

int f ()
{


}
#undef ATTACHED_CODE

int listok(List* L)
{
    if (L==NULL)
    {
        printf("INCORRECT POINTER TO THE LIST,LOOKS LIKE LIST DOESNT EXIST!");
        return NO_LIST;
    }
    if (L->first==NULL)
    {
        printf("INCORRECT POINTER TO THE FIRST ELEMENT!");
        return WRONG;
    }
    gotofirst(L);
    int amount=0;
    while (L->current->next!=NULL)
    {
        gotonext(L);
        amount++;
    }
    if (amount!=L->amount)
    {
        printf("WRONG ELEMENT AMOUNT %d %d",amount,L->amount);
        return WRONG;
    }
    return OK;
}


int gethash(data_t data,int functionnumber,int hashamount)
{
    if (functionnumber==1)return 1;

    if (functionnumber==2)return abs((data[0]) % hashamount);

    if (functionnumber==3)return strlen(data)%hashamount;

    if (functionnumber==4)
    {
        int sum=0;
        for (int i=0; i<strlen(data); i++)
        {
            sum += abs(data[i]);
        }

        return sum % hashamount;
    }

    if (functionnumber == 5)
    {
        int h = abs(data[0]);
        for (int i = 1; i < strlen(data); i++)
        {
            h = ((h << 1) ^ abs(data[i])) % hashamount;//printf("%d\n",h);
        }

        return h % hashamount;
    }

}

//if (listcontainsthis(H[hash_val],
//                    L->current->data) == 0)

void hasher(List* L,Hash_t* Hash,int functionnumber)
{
    assert(L);
    assert(Hash);
    gotofirst(L);
    while (L->current->next!=NULL)
    {
        gotonext(L);
        int hash_val = gethash(L->current->data, functionnumber,Hash->hashesamount);
        if(listcontainsthis (    Hash->H  [ gethash   (  L->current->data, functionnumber,Hash->hashesamount  ) ]    ,L->current->data   )  ==0)
//      if ()
        {
            input   (  Hash->H    [   gethash (    L->current->data,  functionnumber ,Hash->hashesamount )   ]   ,   L->current->data    );   //printf("%d\n",gethash(L->current->data,functionnumber));
        }
    }
}

int hash_ctor(Hash_t *Hash,int amount)
{
    assert(Hash);
    Hash->H=(List**) calloc (amount, sizeof(List*));
    Hash->hashesamount=amount;
    for(int i = 0; i < amount; i++)
    {
        Hash->H[i]=(List*) calloc (1, sizeof(List));
        assert(Hash->H[i]);
        list_ctor(Hash->H[i]);//printf("i=%5d  %d\n",i,Hash->H[i]->amount);
    }

}

int main()
{
    List* L = NULL;


    Hash_t* Hash1=(Hash_t*)calloc(1,sizeof(Hash_t));
    hash_ctor(Hash1,100);

    L = (List*) calloc (1, sizeof(List));
    assert(L);
    list_ctor(L);
    FILE* F = NULL;

    F = fopen("1.txt","r");
    assert(F);
    while(!feof(F))
        readfromfile(F,L);
    fclose(F);
    F=fopen("2.txt","w");
    assert(F);

    hasher(L,Hash1,5);


    for (int i=0; i<Hash1->hashesamount; i++)
    {
        printf("i=%5d  %d\n",i,Hash1->H[i]->amount);
        //fprintf(F,"%d ",Hash1->H[i]->amount);
    }



}
