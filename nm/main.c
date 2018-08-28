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
		get_symbols32(elf);
		fill_symbols32(elf);
		if (!elf->syms_tt)
			return;
	} else {
		build(elf, data);
		get_symbols(elf);
		fill_symbols(elf);
		if (!elf->syms_tt)
			return;
	}
	print_symbols(elf);
}

void handle_file(char *file, int argc)
{
	bool fs;
	elf_t elf;

	fs = get_file(file, &elf);
	if (argc > 3)
		printf("\n%s:\n", file);
	libchecker(&elf, fs, &launch);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		handle_file(strdup("a.out"), argc);
		return 0;
	}
	++argv;
	while (*argv) {
		handle_file(*argv, argc);
		++argv;
	}
	return (0);
}
