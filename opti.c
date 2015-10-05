/*
** opti.c for opti.c in /home/levy_b/rendu/PSU_2014_malloc
** 
** Made by LEVY Alexandre
** Login   <levy_b@epitech.net>
** 
** Started on  Sun Feb 22 20:38:03 2015 LEVY Alexandre
** Last update Sun Feb 22 21:36:13 2015 LEVY Alexandre
*/
#include <sys/types.h>
#include <unistd.h>
#include "malloc.h"

t_block     extend_heap(t_block last, size_t s)
{
  t_block     b;

  b = sbrk(0);
  if (sbrk(BLOCK_SIZE + s) == (void*) -1)
    return(NULL);
  b->size = s;
  b->next = NULL;
  if (last)
    last->next = b;
  b->free = 0;
  return (b);
}

t_block         fusion(t_block b)
{
  if (b->next && b->next->free)
    {
      b->size += BLOCK_SIZE + b->next->size;
      b->next = b->next->next;
      if (b->next)
        b->next->prev = b;
    }
  return (b);
}


void        split_block(t_block b, size_t s)
{
  t_block     new;

  //    new       = b->data + s;                                                
  new->size = b->size - s - BLOCK_SIZE;
  new->next = b->next;
  new->free = 1;
  b->size   = s;
  b->next   = new;
}

