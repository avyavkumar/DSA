#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
enum { VAL_SUCC = 0, VAL_ERR = 1};
 
typedef struct queue
{
  int num;
  struct queue* next;
  struct queue* prev;
} dlqueue;
 
typedef struct qlist
{
  struct queue* head;
  struct queue* tail;
} dlqlist;
  
int enqueue(dlqlist*, int);
int dequeue(dlqlist*);
dlqueue* front(dlqlist*);
void makenull( dlqlist*);
int empty( dlqlist*);
void print_queue( dlqlist* );
// int dequeue_anywhere( dlqlist*s , int numd);

void remove_element( dlqlist* s,  dlqueue* d);
 
int main(void)
{	
  dlqlist* s = malloc(1 * sizeof *s);
  if(NULL == s)
    {
      fprintf(stderr,"IN: %s @%d: Out of Memory\n", __FILE__, __LINE__);
      return EXIT_FAILURE;
    }
  else
    {
      s->head = s->tail = NULL;		// Got to initialise the head and tail of the queue in the main function only
    }
  enqueue(s,10);
  enqueue(s,11);
  enqueue(s,12);
  enqueue(s,13);
  print_queue(s);
  //dequeue_anywhere(s,12);
  //printf("\n\n----------------------------\n");
  //print_queue(s);
 
  /*
  dequeue(s);
  printf("\n\n----------------------------\n");
  print_queue(s);
 
  dequeue(s);
  printf("\n\n----------------------------\n");
  print_queue(s);
 
 
  dequeue(s);
  printf("\n\n----------------------------\n");
  print_queue(s);
  */
  return EXIT_SUCCESS;
}
 
/* Adds an element to tail of Queue */
int enqueue( dlqlist* s, int i)
{
  int ret;
  if(NULL == s)
    {
      fprintf(stderr, "IN: %s @ %d: Invalid Args\n", __FILE__, __LINE__);
      ret = VAL_ERR;
    }
  else if(NULL == s->head && NULL == s->tail)
    {
       dlqueue* p = malloc(1 * sizeof *p);
      if(NULL == p)
    {
      fprintf(stderr,"IN: %s @%d: Out of Memory\n", __FILE__, __LINE__);
      ret = VAL_ERR;
    }
      else
    {
      p->num = i;
      p->prev = p->next = NULL;
 
      s->head = s->tail = p;
      ret = VAL_SUCC;
    }
    }
  else if(NULL == s->head || NULL == s->tail)
    {
      fprintf(stderr, "IN: %s @%d: Serious error.", __FILE__, __LINE__);
      fprintf(stderr,"List one of the list's head/tail is null while other is not\n");
      ret = VAL_ERR;
    }
  else
    {
       dlqueue* p = malloc(1 * sizeof *p);
      if(NULL == p)
 	{
	      fprintf(stderr,"IN: %s @%d: Out of Memory\n", __FILE__, __LINE__);
	      ret = VAL_ERR;
    	}
      else
    	{
	      p->num = i;
	      p->prev = p->next = NULL;
	      s->tail->next = p;
	      p->prev = s->tail;
	      s->tail = p;
	      ret = VAL_SUCC;
    	}
    }
  return ret;
}
 
int dequeue( dlqlist* s)
{
  int ret;
  if(NULL == s)
    {
      fprintf(stderr, "IN: %s @ %d: Invalid Args\n", __FILE__, __LINE__);
      ret = VAL_ERR;
    }
  else if(NULL == s->head && NULL == s->tail)
    {
      printf("Nothing to Dequeue()\n");
      ret = VAL_SUCC;
    }
  else if(NULL == s->head || NULL == s->tail)
    {
      fprintf(stderr, "IN: %s @%d: Serious error.", __FILE__, __LINE__);
      fprintf(stderr,"List one of the list's head/tail is null while other is not\n");
      ret = VAL_ERR;
    }
  else
    {
       dlqueue* p = s->head;
      if(NULL == s->head->next && NULL == s->tail->next) /* if last element */
    {
      s->head = s->tail = NULL;
    }
      else
    {
      s->head = s->head->next;
    }
 
      free(p);
      ret = VAL_SUCC;
    }
  return ret;
}
 
/*
int dequeue_anywhere( dlqlist*s , int numd)
{
  int ret;
  if(NULL == s)
    {
      fprintf(stderr, "IN: %s @ %d: Invalid Args\n", __FILE__, __LINE__);
      ret = VAL_ERR;
    }
  else if(NULL == s->head && NULL == s->tail)
    {
      printf("Nothing to Dequeue()\n");
      ret = VAL_SUCC;
    }
  else if(NULL == s->head || NULL == s->tail)
    {
      fprintf(stderr, "IN: %s @%d: Serious error.", __FILE__, __LINE__);
      fprintf(stderr,"List one of the list's head/tail is null while other is not\n");
      ret = VAL_ERR;
    }
  else
    {
       dlqueue* p = s->head;
      for(; p; p = p->next)
    {
      if(numd == p->num)
        {
          remove_element(s,p);
        }
    }
      ret = VAL_SUCC;
    }
 
  return ret;
}
*/ 
 
void remove_element( dlqlist* s,  dlqueue* d)
{
  if(NULL == d->next && (NULL == s->head->next && NULL == s->tail->next)) /* only one element in queue */
    {
      s->head = s->tail = NULL;
    }
  else if((NULL == d->next) && d->prev) /* removing tail */
    {
      s->tail = d->prev;
      d->prev->next = NULL;
    }
  else if(d->next && (NULL == d->prev)) /* removing head */
    {
      s->head = d->next;
      s->head->prev = NULL;
    }
  else /* removing from center or somewhere */
    {
      d->prev->next = d->next;
      d->next->prev = d->prev;
    }
  free(d);
}
 
void remove_element_2( dlqlist* s,  dlqueue* d)
{
  if(NULL == d->next)
    {
      s->tail = d->prev;
    }
  else
    {
      d->next->prev = d->prev;
    }
 
  if(NULL == d->prev)
    {
      s->head = d->next;
    }
  else
    {
      d->prev->next = d->next;
    }
  free(d);
}
 
void print_queue( dlqlist* s)
{
  if(NULL == s)
    {
      fprintf(stderr, "IN: %s @ %d: Invalid Args\n", __FILE__, __LINE__);
     }
  else if(NULL == s->head && NULL == s->tail)
    {
      printf("Nothing to print\n");
    }
  else if(NULL == s->head || NULL == s->tail)
    {
      fprintf(stderr, "IN: %s @%d: Serious error.", __FILE__, __LINE__);
      fprintf(stderr,"List one of the list's head/tail is null while other is not\n");
    }
  else
    {
      dlqueue* p = s->head;
      while(p)
      {
      	printf("num = %d\n", p->num);
      	p = p->next;
      }
    }
}
