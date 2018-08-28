/*
** EPITECH PROJECT, 2018
** Main
** File description:
** Main
*/

# include "project.h"

void launch(elf_t *elf, void *data)
{
	if (elf->is_32) {
		build32(elf, data);
		print_main_informations32(elf);
		print_file32(elf);
	} else {
		build(elf, data);
		print_main_informations(elf);
		print_file(elf);
	}
}

void handle_file(char *file)
{
	elf_t elf;

	libchecker(&elf, get_file(file, &elf), launch);
}

bool check_file(char c)
{
	return c != 'o' || c != 'a';
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		handle_file(strdup("a.out"));
		return 0;
	}
	++argv;
	while (*argv) {
		handle_file(*argv);
		++argv;
	}
	return (0);
}
