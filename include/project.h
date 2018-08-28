/*
** EPITECH PROJECT, 2018
** Main Project.h
** File description:
** Main Project.h
*/

#ifndef H_CHECK
	# define H_CHECK

# include <elf.h>
# include <ctype.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <strings.h>
# include "flags.h"

# define SIZE 16
# define ADDR ((int)(shdr.sh_addr))
# define SH_SIZE ((size_t)(shdr.sh_offset + shdr.sh_size))
# define OFFSET ((void *) elf->ehdr + elf->filesize)
# define SHDR ((void *) elf->datas + elf->ehdr->e_shoff)
# define SHDR32 ((void *) elf->_ehdr + elf->_ehdr->e_shoff)
# define CALC_SIZE elf->ehdr->e_shoff + \
	(elf->ehdr->e_shnum * elf->ehdr->e_shentsize)
# define CATNAME &((char *)NAME)[shdr.sh_name]
# define NAME ((void *) elf->ehdr + \
		elf->shdr[elf->ehdr->e_shstrndx].sh_offset)
# define NAME32 ((void *) elf->_ehdr + \
			elf->_shdr[elf->_ehdr->e_shstrndx].sh_offset)
# define NM_NAME32 ((char *) elf->sym_names + elf->_sym[i].st_name)
# define NM_NAME ((char *) elf->sym_names + elf->sym[i].st_name)
# define NM_NAME_S(S) (((syms_t *)S)->name)
# define TYPE_CMP(A, B) shdr[sym.st_shndx].sh_type == A \
	&& shdr[sym.st_shndx].sh_flags == B
# define is_bind ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE || \
			ELF64_ST_BIND(sym.st_info) == STB_WEAK || \
			(ELF32_ST_BIND(sym.st_info) == STB_WEAK && \
			ELF32_ST_TYPE(sym.st_info) == STT_OBJECT) || \
			sym.st_shndx == SHN_UNDEF || sym.st_shndx == SHN_ABS \
			|| sym.st_shndx == SHN_COMMON

typedef struct syms_s
{
	char *name;
	char type;
	Elf64_Addr value;
} syms_t;

typedef struct syms32_s
{
	char *name;
	char type;
	Elf32_Addr value;
} syms32_t;

typedef struct elf_s
{
	Elf64_Ehdr *ehdr;
	Elf64_Shdr *shdr;
	Elf64_Sym *sym;
	Elf32_Ehdr *_ehdr;
	Elf32_Shdr *_shdr;
	Elf32_Sym *_sym;
	syms_t *syms;
	syms32_t *_syms;
	size_t syms_tt;
	char *datas;
	size_t sym_nbr;
	char *sym_names;
	char *filename;
	int filesize;
	uint16_t flags;
	bool is_32;
} elf_t;

void sort_symbols32(elf_t *elf);
char *my_revstr(char *str);
bool libchecker(elf_t *elf, bool fs, void fnc(elf_t *, void *));
bool build(elf_t *elf, void *data);
bool build32(elf_t *elf, void *data);
void fill_symbols(elf_t *elf);
void fill_symbols32(elf_t *elf);
void sort_symbols(elf_t *elf);
void print_symbols(elf_t *elf);
void get_symbols(elf_t *elf);
void get_symbols32(elf_t *elf);
char get_type(Elf64_Sym sym, Elf64_Shdr *shdr);
char get_type32(Elf32_Sym sym, Elf32_Shdr *shdr);
size_t hexa_counter(int nbr);
bool is_32(bool value);
bool get_file(char *, elf_t *elf);
void print_file32(elf_t *elf);
void print_main_informations32(elf_t *elf);
void print_main_informations(elf_t *elf);
void print_file(elf_t *elf);

#endif
