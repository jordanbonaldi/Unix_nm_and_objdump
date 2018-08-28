/*
** EPITECH PROJECT, 2018
** Main informations
** File description:
** Main informations
*/

# include "project.h"

static void get_bsd_flags(elf_t *elf)
{
	elf->flags = 0;
	elf->flags |= elf->_ehdr->e_type == ET_EXEC ? EXEC_P : 0;
	elf->flags |= elf->_ehdr->e_type == ET_EXEC ? D_PAGED : 0;
	elf->flags |= elf->_ehdr->e_type == ET_DYN ? DYNAMIC : 0;
	elf->flags |= elf->_ehdr->e_type == ET_DYN ? D_PAGED : 0;
	elf->flags |= elf->_ehdr->e_type == ET_REL ? HAS_RELOC : 0;
	for (size_t i = 0; i < elf->_ehdr->e_shnum; ++i)
		elf->flags |= elf->_shdr[i].sh_type == SHT_SYMTAB ?
					HAS_SYMS : 0;
}

static void print_flag(int *add, char *flag)
{
	if (!*add) {
		(*add)++;
		printf("%s", flag);
	} else
		printf(", %s", flag);
}

static void print_flags(elf_t *elf)
{
	int add = 0;

	if (!elf->flags) {
		print_flag(0, "BFD_NO_FLAGS");
		return;
	}
	if (elf->flags & HAS_RELOC)
		print_flag(&add, "HAS_RELOC");
	if (elf->flags & EXEC_P)
		print_flag(&add, "EXEC_P");
	if (elf->flags & HAS_LINENO)
		print_flag(&add, "HAS_LINENO");
	if (elf->flags & HAS_DEBUG)
		print_flag(&add, "HAS_DEBUG");
	if (elf->flags & HAS_SYMS)
		print_flag(&add, "HAS_SYMS");
	if (elf->flags & HAS_LOCALS)
		print_flag(&add, "HAS_LOCALS");
	if (elf->flags & DYNAMIC)
		print_flag(&add, "DYNAMIC");
	if (elf->flags & WP_TEXT)
		print_flag(&add, "WP_TEXT");
	if (elf->flags & D_PAGED)
		print_flag(&add, "D_PAGED");
}

void print_main_informations32(elf_t *elf)
{
	get_bsd_flags(elf);
	printf("\n%s:     file format elf32-i386\n", elf->filename);
	printf("architecture: i386, flags 0x%08x:\n", elf->flags);
	print_flags(elf);
	printf("\nstart address 0x%08lx\n\n", (size_t)elf->_ehdr->e_entry);
}
