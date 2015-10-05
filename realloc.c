/*
** realloc.c for realloc.c in /home/levy_b/rendu/PSU_2014_malloc
** 
** Made by LEVY Alexandre
** Login   <levy_b@epitech.net>
** 
** Started on  Sun Feb 22 20:41:48 2015 LEVY Alexandre
** Last update Sun Feb 22 20:43:07 2015 LEVY Alexandre
*/
#include <sys/types.h>
#include <unistd.h>
#include "malloc.h"

void    *realloc(void *p, size_t size)
{
  size_t s;
  t_block b, new;
  void *newp;
  if (!p)
    return (malloc(size));
  if ( valid_addr(p))
    {
      s = align4(size);
      b = get_block(p);
      if (b->size >= s)
        {
          if (b->size - s >= (BLOCK_SIZE + 4))
            split_block (b, s);
        }
      else
        {
          /* Try fusion with next if possible */
          if (b->next && b->next ->free
              && (b->size + BLOCK_SIZE + b->next ->size) >= s)
            {
              fusion(b);
              if (b->size - s >= (BLOCK_SIZE + 4))
                split_block (b, s);
            }
          else
            {
              /* good old realloc with a new block */
              newp = malloc(s);
              if (!newp)
                /* we’re doomed ! */
                return (NULL);
              /* I assume this work ! */
              new = get_block (newp);
              /* Copy data */
              copy_block (b, new);
              /* free the old one */
              free(p);
              return (newp);
            }
        }
      return (p);
    }
  return (NULL);
}
