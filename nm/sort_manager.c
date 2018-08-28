/*
** EPITECH PROJECT, 2018
** Main
** File description:
** Main
*/

# include "project.h"

int s_strcmp(char *s1, char *s2)
{
	int i = 0, j = 0;
	char *name1 = s1;
	char *name2 = s2;

	while (name1[i] && name2[j]) {
		if (name1[i] && !isalnum(name1[i]) && ++i)
			continue;
		if (name2[j] && !isalnum(name2[j]) && ++j)
			continue;
		if (tolower(name1[i]) != tolower(name2[j]))
			break;
		i++;
		j++;
	}

	return tolower(name1[i]) - tolower(name2[j]);
}

int spec_strcmp(const void *s1, const void *s2)
{
	return s_strcmp(((syms_t *)s1)->name, ((syms_t *)s2)->name) ?
		s_strcmp(((syms_t *)s1)->name, ((syms_t *)s2)->name) :
		(int)(strlen(((syms_t *)s2)->name) -
			strlen(((syms_t *)s1)->name));
}

void sort_symbols(elf_t *elf)
{
	qsort(elf->syms, elf->syms_tt, sizeof(syms_t), spec_strcmp);
}
