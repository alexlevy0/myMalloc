#include <sys/types.h>
#include <unistd.h>
#include "malloc.h"

void	*base = NULL;

t_block         find_block(t_block *last, size_t size)
{
  t_block     b;

  b = base;
  while (b && !(b->free && b->size >= size ))
  {
    *last = b;
    b = b->next;
  }
  return (b);
}

void            *malloc(size_t  size)
{
  t_block     b;
  t_block     last;
  size_t      s;
  
  s = align4(size); // taille a allouer + metadonné
  if (base)
    {
      /* First find a block */
      last = base;
      b = find_block(&last, s);
      if (b) 
	{
	  /* can we split */
	  if ((b->size - s) >= (BLOCK_SIZE + 4))
	    split_block (b, s);
	  b->free = 0;
	} else {
	/* No fitting block , extend the heap */
	b = extend_heap(last, s);
	if (!b)
	  return(NULL);
      }
    } else {
    /* first time */
    b = extend_heap(NULL, s);
    if (!b)
      return(NULL);
    base = b;
  }
  return(b->data);
}

void            free(void *p)
{
  t_block     b;

  if (valid_addr(p))
  {
    b = get_block(p);
    b->free = 1;
    /* fusion with previous if possible */
    if(b->prev && b->prev->free)
      b = fusion(b->prev);
    /* then fusion with next */
    if (b->next)
      fusion(b);
    else {
      /* free the end of the heap */
      if (b->prev)
        b->prev ->next = NULL;
      else
        /* No more block !*/
        base = NULL;
      brk(b);
    }
  }
}

//Define the block size since the sizeof will be wrong
t_block		get_block(void *p)
{
  char	*tmp;

  tmp = p;
  return (p = tmp -= BLOCK_SIZE);
}

/* Valid addr for free */
int	valid_addr(void *p)
{
  if (base)
  {
    if (p > base && p < sbrk(0))
    {
      return (p == (get_block(p))->ptr);
    }
  }
  return(0);
}
