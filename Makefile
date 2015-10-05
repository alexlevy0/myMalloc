##
## Makefile for Makefile in /home/levy_b/rendu/PSU_2014_malloc
## 
## Made by LEVY Alexandre
## Login   <levy_b@epitech.net>
## 
## Started on  Sun Feb 22 20:55:32 2015 LEVY Alexandre
## Last update Sun Feb 22 21:04:23 2015 LEVY Alexandre
##

ifndef HOSTTYPE
	HOSTTYPE=i386-linux
endif

SRCS =  malloc.c \
	opti.c \
	realloc.c \
	show_alloc_mem.c \

RM      = rm -f

NAME 	= libmy_malloc_$(HOSTTYPE).so

CC      = cc -fPIC -shared -lm -g3

OBJS    = $(SRCS:.c=.o)

LN      = ln -sf libmy_malloc_$(HOSTTYPE).so libmy_malloc.so

all:     $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):$(OBJS)
	$(CC) $(OBJS) -o $(NAME)
	$(LN)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) libmy_malloc.so

re: fclean all
