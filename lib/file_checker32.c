/*
** EPITECH PROJECT, 2018
** file_checker
** File description:
** file_checker
*/

# include "project.h"

static bool magic_number(elf_t *elf)
{
	return (elf->_ehdr->e_ident[EI_MAG0] == 0x7f &&
		elf->_ehdr->e_ident[EI_MAG1] == 'E' &&
		elf->_ehdr->e_ident[EI_MAG2] == 'L' &&
		elf->_ehdr->e_ident[EI_MAG3] == 'F') || (
			memcmp(elf->ehdr, "\177ELF", sizeof("\177ELF") - 1));
}

static bool check_shdr_length(void *offsetcompare, elf_t *elf)
{
	return !(offsetcompare > OFFSET);
}

static bool shdr_fill(elf_t *elf)
{
	char *ehdr = elf->datas;
	int size = elf->_ehdr->e_ehsize +
		(elf->_ehdr->e_phnum * elf->_ehdr->e_phentsize) +
		(elf->_ehdr->e_shnum * elf->_ehdr->e_shentsize);
	elf->_shdr = SHDR32;

	if (!ehdr || *ehdr != ELFMAG0 || ehdr[1] != ELFMAG1
		|| ehdr[2] != ELFMAG2 || ehdr[3] != ELFMAG3
			|| (ehdr[4] != ELFCLASS64 && ehdr[4] != ELFCLASS32))
			exit(84);
	if ((size_t)elf->filesize < sizeof(Elf64_Ehdr) || elf->filesize < size
			|| (int)elf->_ehdr->e_shoff < 1)
		exit(84);
	return check_shdr_length(elf->_shdr, elf) ||
		check_shdr_length(&elf->_shdr[elf->_ehdr->e_shstrndx], elf) ||
		check_shdr_length(NAME32, elf);
}

bool build32(elf_t *elf, void *data)
{
	elf->_ehdr = data;
	if (!elf->_ehdr)
		return false;
	return ((elf->filesize > ((int)sizeof(Elf32_Ehdr)))
			&& magic_number(elf) && shdr_fill(elf));
}
