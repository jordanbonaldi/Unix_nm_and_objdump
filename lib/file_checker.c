/*
** EPITECH PROJECT, 2018
** file_checker
** File description:
** file_checker
*/

# include "project.h"

static bool magic_number(elf_t *elf)
{
	return (elf->ehdr->e_ident[EI_MAG0] == 0x7f &&
		elf->ehdr->e_ident[EI_MAG1] == 'E' &&
		elf->ehdr->e_ident[EI_MAG2] == 'L' &&
		elf->ehdr->e_ident[EI_MAG3] == 'F') || (
			memcmp(elf->ehdr, "\177ELF", sizeof("\177ELF") - 1));
}

static bool check_shdr_length(void *offsetcompare, elf_t *elf)
{
	return !(offsetcompare > OFFSET);
}

static bool shdr_fill(elf_t *elf)
{
	char *ehdr = elf->datas;
	int size = CALC_SIZE;

	elf->shdr = SHDR;
	if (!ehdr || *ehdr != ELFMAG0 || ehdr[1] != ELFMAG1 ||
		ehdr[2] != ELFMAG2 || ehdr[3] != ELFMAG3 ||
			(ehdr[4] != ELFCLASS64 && ehdr[4] != ELFCLASS32))
			exit(84);
	if (elf->filesize < size && printf("my_nm: %s: File truncated\n",
		elf->filename))
		exit(84);
	if ((int)elf->ehdr->e_shoff < 1 || (size_t)elf->filesize <
		(sizeof(Elf64_Ehdr)) || elf->filesize < size) {
		printf("my_nm: %s: File format not recognized\n",
			elf->filename);
		exit(84);
	}
	return check_shdr_length(elf->shdr, elf) ||
		check_shdr_length(&elf->shdr[elf->ehdr->e_shstrndx], elf) ||
		check_shdr_length(NAME, elf);
}

bool build(elf_t *elf, void *data)
{
	elf->ehdr = data;
	if (!elf->ehdr)
		return false;
	return ((elf->filesize > ((int)sizeof(Elf64_Ehdr)))
			&& magic_number(elf) && shdr_fill(elf));
}

bool get_file(char *filename, elf_t *elf)
{
	void *data;
	int filesize, fd = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0 && printf("my_nm: '%s': No such file\n", filename))
		exit(84);
	if (!strncmp(my_revstr(filename), "c.", 2)) {
		printf("my_nm: %s: File format not recognized\n",
			my_revstr(filename));
		exit(84);
	}
	filesize = lseek(fd, 0, SEEK_END);
	if (filesize < 0)
		exit(84);
	data = mmap(NULL, filesize, PROT_READ, MAP_SHARED, fd, 0);
	elf->is_32 = ((Elf32_Ehdr *)data)->e_ident[EI_CLASS] == ELFCLASS32;
	elf->filename = my_revstr(filename);
	elf->filesize = filesize;
	elf->datas = data;
	return !strncmp(*&elf->datas, ELFMAG, 4);
}
