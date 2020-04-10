#ifndef dlist_h
#define dlist_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"

//-------------------------------------------------
typedef struct dnode dnode;
struct dnode {
  int data;
  dnode* prev;
  dnode* next;
};

typedef struct dlist dlist;
struct dlist {
  dnode* head;
  dnode* tail;
  size_t size;
};

//-------------------------------------------------
dnode* dnode_create(int data, dnode* next, dnode* prev){
  dnode* p = (dnode*)malloc(sizeof(dnode));
  p->data = data;
  p->prev = prev;
  p->next = next;
  return p;
}
dlist* dlist_create(void){
  dlist* p = (dlist*)malloc(sizeof(dlist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;
}

bool dlist_empty(dlist* list){return list->size==0;}
size_t dlist_size(dlist* list){return list->size;}

void dlist_popfront(dlist* list){
  if(dlist_empty(list)){printf("list is empty!!"); return;}
  dnode* p = list->head;
  // if(p->next!=NULL){
  //   p->next->prev = NULL;
  // }
  list->head = list->head->next;
  free(p);
  --list->size;
}
void dlist_popback(dlist* list){
  if(dlist_empty(list)){printf("list is empty!!"); return;}
  dnode* p = list->tail;
  dnode* p2 = p->prev;
  if(p2 != NULL){
    p2->next = NULL;
  }
  list->tail = p2;
  free(p);
  --list->size;
}
void dlist_pushfront(dlist* list, int data){
  dnode* p = dnode_create(data,list->head,NULL);
  list->head = p;
  if(dlist_empty(list)){
      list->tail=p;
  }
  ++list->size;
}
void dlist_pushback(dlist* list, int data){
  if(dlist_empty(list)){dlist_pushfront(list,data); return;}
  dnode* p = dnode_create(data,NULL,list->tail);
  list->tail->next=p;
  list->tail = p;
  ++list->size;
}

void dlist_clear(dlist* list){
  if(dlist_empty(list)){printf("list is empty!!"); return;}
  while(!dlist_empty(list)){
      dlist_popfront(list);
  }
};
void dlist_print(dlist* list, const char* msg){
  if(dlist_empty(list)){printf("list is empty!!"); return;}
  printf("%s\n",msg);
  dnode* p = list->head;
  while(p!=NULL){
      printf("%p <-- %d (%p) --> %p\n",p->prev,p->data,p,p->next);
      p=p->next;
  }
}


int dlist_front(dlist* list){
  if(dlist_empty(list)){printf("List is empty");return;}
  return list->head->data;
}
int dlist_back(dlist* list){
  if(dlist_empty(list)){printf("List is empty");return;}
  return list->tail->data;
};


//-------------------------------------------------
static void dlist_check_frontback(dlist* list, int front, int back) {
  printf("assert front of list is: %d\n", front);
  assert(dlist_front(list) == front);
  printf("assert back of list is: %d\n", back);
  assert(dlist_back(list) == back);
}

//-------------------------------------------------
static void dlist_test_once(dlist* list, int start, int end, int step, void (*fp)(dlist*, int)) {
  for (int i = start; i < end; i += step) {
    fp(list, i);
  }
  dlist_print(list, "list is created and is...");
  printf("list size is: %zu\n", dlist_size(list));
  printf("list is empty? %s\n", yesorno(dlist_empty(list)));

  int firstadded = start;
  int lastadded = start;
  while (lastadded + step < end) {
    lastadded += step;
  }
  if (fp == dlist_pushback)  { dlist_check_frontback(list, firstadded, lastadded);  }
  if (fp == dlist_pushfront) { dlist_check_frontback(list, lastadded, firstadded ); }

  dlist_clear(list);
  printf("after clearing the list, is the list is now empty? %s\n\n", yesorno(dlist_empty(list)));
}

//-------------------------------------------------
void dlist_test() {
  printf("//===================== TESTING DLIST =========================\n\n");
  dlist* list = dlist_create();
  dlist_test_once(list, 10, 50, 10, dlist_pushfront);
  dlist_test_once(list, 10, 100, 20, dlist_pushback);
  dlist_test_once(list, 0, 100, 1, dlist_pushback);

  printf("      All Assertions passed!...\n");
  free(list);
  printf("//===================== END TESTING DLIST =========================\n\n");
}

#endif /* dlist_h */
