#ifndef slist_h
#define slist_h

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

typedef struct snode snode;
struct snode {
  int data;
  snode* next;
};

typedef struct slist slist;
struct slist {
  snode* head;
  snode* tail;
  size_t size;
};

snode* snode_create(int data, snode* next){
  snode* p = (snode*)malloc(sizeof(snode));
  p->data = data;
  p->next = next;
  return p;
}
slist* slist_create(void){
  slist* p = (slist*)malloc(sizeof(slist));
  p->head = NULL;
  p->tail = NULL;
  p->size = 0;
}

bool slist_empty(slist* list){return list->size==0;}
size_t slist_size(slist* list){ return list->size;}

void slist_popfront(slist* list){
  if(slist_empty(list)){printf("list is empty!!"); return;}
  snode* p = list->head;
  list->head = list->head->next;
  free(p);
  --list->size;
}
void slist_popback(slist* list){
  if(slist_empty(list)){printf("list is empty!!"); return;}
  if(list->size==1){slist_popfront(list); return;}
    
  snode* p = list->head;
  while(p->next!= list->tail){
      p=p->next;
  }
  p->next=NULL;
  free(list->tail);
  list->tail = p;
  --list->size;
}

void slist_pushfront(slist* list, int data){
  snode* p = snode_create(data,list->head);
  list->head = p;
  if(slist_empty(list)){
      list->tail=p;
  }
  ++list->size;
}
void slist_pushback(slist* list, int data){
  if(slist_empty(list)){slist_pushfront(list,data); return;}
  snode* p = snode_create(data,NULL);
  list->tail->next=p;
  list->tail = p;
  ++list->size;
}

void slist_clear(slist* list){
  if(slist_empty(list)){printf("list is empty!!"); return;}
  while(!slist_empty(list)){
      slist_popfront(list);
  }
}

void slist_print(slist* list, const char* msg){
  if(slist_empty(list)){printf("list is empty!!"); return;}
  printf("%s\n",msg);
  snode* p = list->head;
  while(p!=NULL){
      printf("%d --> %p\n",p->data,p->next);
      p=p->next;
  }
}

int slist_front(slist* list){
    if(slist_empty(list)){printf("list is empty!!"); exit(1);}
  return list->head->data;
}
int slist_back(slist* list){
    if(slist_empty(list)){printf("list is empty!!"); exit(1);}
  return list->tail->data;
}

//-------------------------------------------------
static void slist_check_frontback(slist* list, int front, int back) {
  printf("assert front of list is: %d\n", front);
  assert(slist_front(list) == front);
  printf("assert back of list is: %d\n", back);
  assert(slist_back(list) == back);
}

//-------------------------------------------------
static void slist_test_once(slist* list, int start, int end, int step, void (*fp)(slist*, int)) {
  for (int i = start; i < end; i += step) {
    fp(list, i);
  }
  slist_print(list, "list is created and is...");
  printf("list size is: %zu\n", slist_size(list));
  printf("list is empty? %s\n\n", yesorno(slist_empty(list)));

  int firstadded = start;
  int lastadded = start;
  while (lastadded + step < end) {
    lastadded += step;
  }
  if (fp == slist_pushback)  { slist_check_frontback(list, firstadded, lastadded);  }
  if (fp == slist_pushfront) { slist_check_frontback(list, lastadded, firstadded ); }

  slist_clear(list);
  printf("after clearing the list, is the list is now empty? %s\n\n", yesorno(slist_empty(list)));
}

//-------------------------------------------------
void slist_test() {
  printf("\n//===================== TESTING SLIST =========================\n\n");
  slist* list = slist_create();
  slist_test_once(list, 10, 50, 10, slist_pushfront);
  slist_test_once(list, 10, 100, 20, slist_pushback);

  printf("\n    All Assertions passed!...\n");
  free(list);
  printf("//===================== END TESTING SLIST =========================\n\n");
}


#endif /* slist_h */