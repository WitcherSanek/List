#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
int WORDLENGTH=100;

typedef char* data_t;
enum consts
{
    OK,
    NO_LIST,
    CANT_GO,
    WRONG
};

struct ListElem_t
{
    data_t data;
    ListElem_t* last;
    ListElem_t* next;
};
struct List
{
    ListElem_t* current;
    ListElem_t* first;
    int amount;
};

struct Hash_t
{
List** H;
int hashesamount;
};

int listok(List* L);

int list_ctor(List* L);

int gotofirst(List* L);

int gotonext(List* L);

int gotolast(List* L);

int input(List* L,data_t value); //create element on the right side and move on it's position

int deleteelem(List* L);

int list_dtor(ListElem_t* current);

int readfromfile(FILE *F,List* L);

void dumplist(List* L);

int listcontainsthis(List* L,data_t data);

int listok(List* L);

void hasher(List* L,Hash_t* Hash,int functionnumber);

int hash_ctor(Hash_t *Hash,int amount);
