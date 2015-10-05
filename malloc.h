#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

#include <stdio.h>
#define BLOCK_SIZE sizeof(struct s_block) //Taille du header

extern void    *base;

struct      s_block {
    size_t      size;
    struct s_block     *next;
    struct s_block     *prev;
    int         free;
    void        *ptr;
    char        data[1];
};
typedef struct s_block *t_block;


void        *malloc(size_t taille);
void        *realloc(void *ptr, size_t taille);
void        free(void *ptr);
void        show_alloc_mem();
int         valid_addr(void *p);
void        split_block(t_block b, size_t s);
t_block     extend_heap(t_block last, size_t s);
t_block		get_block(void *p);
t_block     fusion(t_block b);
void	    *realloc(void *p, size_t size);

#define align4(x) (((((x)-1)>>2)<<2)+4)
  
#endif /*! __MY_MALLOC_H__ */
