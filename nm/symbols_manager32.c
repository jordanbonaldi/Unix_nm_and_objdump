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
		if (elf->_sym[i].st_name && !contains_c_value(NM_NAME32))
			ret++;
	return ret;
}

void fill_symbols32(elf_t *elf)
{
	size_t j = 0;
	elf->_syms = malloc(sizeof(syms_t) * count_lines(elf));

	elf->syms_tt = count_lines(elf);
	for (size_t i = 0; i < elf->sym_nbr; i++) {
		if (elf->_sym[i].st_name && !contains_c_value(NM_NAME32)) {
			elf->_syms[j].name = NM_NAME32;
			elf->_syms[j].type =
				get_type32(elf->_sym[i], elf->_shdr);
			elf->_syms[j++].value = elf->_sym[i].st_value;
		}
	}
}

void get_symbols32(elf_t *elf)
{
	register Elf32_Shdr shdr;
	bool can_break;

	can_break = false;
	elf->sym_nbr = 0;
	for (size_t i = 0; i < elf->_ehdr->e_shnum; i++) {
		shdr = elf->_shdr[i];
		if (shdr.sh_type == SHT_SYMTAB) {
			elf->_sym = (Elf32_Sym *)(elf->datas + shdr.sh_offset);
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
