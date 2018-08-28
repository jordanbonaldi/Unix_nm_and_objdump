/*
** EPITECH PROJECT, 2018
** Main
** File description:
** Main
*/

# include "project.h"

bool can_print(char c)
{
	return !(c == 'w' || c == 'U');
}

bool contains_c_value(char *value)
{
	return (value[strlen(value) - 2] == '.' &&
			value[strlen(value) - 1] == 'c');
}

void print_symbols(elf_t *elf)
{
	if (elf->is_32)
		sort_symbols32(elf);
	else
		sort_symbols(elf);
	for (size_t i = 0; i < elf->syms_tt; i++) {
		if (elf->is_32 ? can_print(elf->_syms[i].type) :
				can_print(elf->syms[i].type)) {
			if (elf->is_32 && printf("%08x", elf->_syms[i].value));
			else
				printf("%016lx", elf->syms[i].value);
		} else
			printf("%s", elf->is_32 ? "        " :
				"                ");
		if (elf->is_32)
			printf(" %c %s\n",
				elf->_syms[i].type, elf->_syms[i].name);
		else
			printf(" %c %s\n",
				elf->syms[i].type, elf->syms[i].name);
	}
}
