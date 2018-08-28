##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = gcc

RM = rm -f

CFLAGS += -W -Wextra -Wall -Werror -g3

CFLAGS += -Iinclude/

NAMEOBJ = objdump

NAMENM = nm

SRCSOBJ =  objdump/main.c \
	objdump/top_informations.c \
	objdump/top_informations32.c \
	objdump/print_file.c \
	objdump/print_file32.c \

SRCSNM =  nm/main.c \
	nm/print_symbols.c\
	nm/symbols_manager.c\
	nm/symbols_manager32.c\
	nm/types_manager.c \
	nm/sort_manager.c \
	nm/sort_manager32.c \

LIBS = lib/file_checker.c \
	lib/file_checker32.c \
	lib/hexa_counter.c \
	lib/librarychecker.c

OBJSOBJ = $(SRCSOBJ:.c=.o)

OBJSNM = $(SRCSNM:.c=.o)

LIBSOBJ = $(LIBS:.c=.o)

all: $(NAMENM) $(NAMEOBJ)

$(NAMENM): $(LIBSOBJ) $(OBJSNM)
	ar rc lib/libnm.a $(LIBSOBJ)
	$(CC) $(OBJSNM) -o my_$(NAMENM) -Llib/ -lnm

$(NAMEOBJ): $(LIBSOBJ) $(OBJSOBJ)
	ar rc lib/libnm.a $(LIBSOBJ)
	$(CC) $(OBJSOBJ) -o my_$(NAMEOBJ) -Llib/ -lnm


clean:
	$(RM) $(OBJSNM)
	$(RM) $(OBJSOBJ)
	$(RM) $(LIBSOBJ)

fclean: clean
	$(RM) my_$(NAMEOBJ)
	$(RM) my_$(NAMENM)
	$(RM) lib/libnm.a

re: fclean all

.PHONY: all clean fclean re
