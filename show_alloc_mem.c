/*
** show_alloc_mem.c for show_me_mem.c in /home/levy_b/rendu/PSU_2014_malloc
** 
** Made by LEVY Alexandre
** Login   <levy_b@epitech.net>
** 
** Started on  Sun Feb 22 20:43:56 2015 LEVY Alexandre
** Last update Sun Feb 22 21:30:29 2015 LEVY Alexandre
*/
#include <sys/types.h>
#include <unistd.h>
#include "malloc.h"

void            show_alloc_mem()
{
  t_block	tmp;
  int	i;
  
  i = 0;
  tmp = base;
  printf("break: %p\n", sbrk(0));
  while (tmp)
    {
      i++;
      if (tmp->free == 1)
	{
	  printf("%p - %p : %ld octets\n", (void*)tmp + sizeof(t_block),
		 (void*)tmp + sizeof(t_block) + tmp->size, tmp->size);
        }
      tmp = tmp->next;
    }
  printf("%d\n", i);
}
