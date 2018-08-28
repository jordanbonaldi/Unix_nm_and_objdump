/*
** EPITECH PROJECT, 2018
** file_checker
** File description:
** file_checker
*/

# include "project.h"

char *my_revstr(char *str)
{
	int i = 0;
	int j = strlen(str) - 1;
	char c;

	while (i < ((int)strlen(str)) / 2) {
		c = str[i];
		str[i] = str[j];
		str[j] = c;
		i++;
		j--;
	}
	return (str);
}

static char *find_binary_name(char *content, int i)
{
	char *name = malloc(255);
	int j = -1;

	if (!name)
		exit(84);
	while (i > 0 && content[i] != '/' && content[i - 1] != 'o' &&
							content[i - 2] != '.')
		--i;
	i++;
	while (--i > 0 && content[i])
		name[++j] = content[i];
	name[++j] = 0;
	return (my_revstr(name));
}

bool libchecker(elf_t *elf, bool fs, void fnc(elf_t *, void *))
{
	if (fs) {
		fnc(elf, elf->datas);
		return true;
	}
	for (size_t i = 0; i < (size_t)elf->filesize - 4; i++)
		if (!strncmp(&elf->datas[i], ELFMAG, 4)) {
			printf("%s:\n", find_binary_name(&elf->datas[i], i));
			fnc(elf, &elf->datas[i]);
		}
	return true;
}
