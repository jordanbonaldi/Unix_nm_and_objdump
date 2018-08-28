/*
** EPITECH PROJECT, 2018
** types_manager
** File description:
** types_manager
*/

# include "project.h"

static bool contains_c_value(char *value)
{
	return (value[strlen(value) - 2] == '.' &&
			value[strlen(value) - 1] == 'c');
}

static size_t count_lines(elf_t *elf)
{
	int ret = 0;

	for (size_t i = 0; i < elf->sym_nbr; i++)
		if (elf->sym[i].st_name && !contains_c_value(NM_NAME))
			ret++;
	return ret;
}

void fill_symbols(elf_t *elf)
{
	size_t j = 0;
	elf->syms = malloc(sizeof(syms_t) * count_lines(elf));

	elf->syms_tt = count_lines(elf);
	if (!elf->syms_tt) {
		printf("my_nm: %s: no symbols\n", elf->filename);
		exit(84);
	}
	for (size_t i = 0; i < elf->sym_nbr; i++) {
		if (elf->sym[i].st_name && !contains_c_value(NM_NAME)) {
			elf->syms[j].name =  NM_NAME;
			elf->syms[j].type = get_type(elf->sym[i], elf->shdr);
			elf->syms[j++].value = elf->sym[i].st_value;
		}
	}
}

void get_symbols(elf_t *elf)
{
	register Elf64_Shdr shdr;
	bool can_break;

	can_break = false;
	elf->sym_nbr = 0;
	for (size_t i = 0; i < elf->ehdr->e_shnum; i++) {
		shdr = elf->shdr[i];
		if (shdr.sh_type == SHT_SYMTAB) {
			elf->sym = (Elf64_Sym *)(elf->datas + shdr.sh_offset);
			elf->sym_nbr = shdr.sh_size / shdr.sh_entsize;
			can_break = true;
		}
		if (shdr.sh_type == SHT_STRTAB) {
			elf->sym_names = elf->datas + shdr.sh_offset;
			if (can_break)
				break;
		}
	}
}
