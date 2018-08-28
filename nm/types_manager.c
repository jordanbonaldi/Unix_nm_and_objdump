/*
** EPITECH PROJECT, 2018
** types_manager
** File description:
** types_manager
*/

# include "project.h"

void get_type32_bind(Elf32_Sym sym, char *c)
{
	if (ELF32_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		*c = 'u';
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK) {
		*c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			*c = 'w';
	}
	else if (ELF32_ST_BIND(sym.st_info) == STB_WEAK
		&& ELF32_ST_TYPE(sym.st_info) == STT_OBJECT) {
		*c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			*c = 'v';
	} else if (sym.st_shndx == SHN_UNDEF)
		*c = 'U';
	else if (sym.st_shndx == SHN_ABS)
		*c = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		*c = 'C';
}

char get_type32(Elf32_Sym sym, Elf32_Shdr *shdr)
{
	char  c;

	if (is_bind)
		get_type32_bind(sym, &c);
	else if (TYPE_CMP(SHT_NOBITS, (SHF_ALLOC | SHF_WRITE)))
		c = 'B';
	else if (TYPE_CMP(SHT_PROGBITS, SHF_ALLOC))
		c = 'R';
	else if (TYPE_CMP(SHT_PROGBITS, (SHF_ALLOC | SHF_WRITE)))
		c = 'D';
	else if (TYPE_CMP(SHT_PROGBITS, (SHF_ALLOC | SHF_EXECINSTR)))
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = !sym.st_value ? 'n' : 't';
	return ELF32_ST_BIND(sym.st_info) == STB_LOCAL &&
					c != 't' && c != 'n' ? c + 32 : c;
}

void get_type64_bind(Elf64_Sym sym, char *c)
{
	if (ELF64_ST_BIND(sym.st_info) == STB_GNU_UNIQUE)
		*c = 'u';
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK) {
		*c = 'W';
		if (sym.st_shndx == SHN_UNDEF)
			*c = 'w';
	}
	else if (ELF64_ST_BIND(sym.st_info) == STB_WEAK
		&& ELF64_ST_TYPE(sym.st_info) == STT_OBJECT) {
		*c = 'V';
		if (sym.st_shndx == SHN_UNDEF)
			*c = 'v';
	} else if (sym.st_shndx == SHN_UNDEF)
		*c = 'U';
	else if (sym.st_shndx == SHN_ABS)
		*c = 'A';
	else if (sym.st_shndx == SHN_COMMON)
		*c = 'C';
}

char get_type(Elf64_Sym sym, Elf64_Shdr *shdr)
{
	char  c;

	if (is_bind)
		get_type64_bind(sym, &c);
	else if (TYPE_CMP(SHT_NOBITS, (SHF_ALLOC | SHF_WRITE)))
		c = 'B';
	else if (TYPE_CMP(SHT_PROGBITS, SHF_ALLOC))
		c = 'R';
	else if (TYPE_CMP(SHT_PROGBITS, (SHF_ALLOC | SHF_WRITE)))
		c = 'D';
	else if (TYPE_CMP(SHT_PROGBITS, (SHF_ALLOC | SHF_EXECINSTR)))
		c = 'T';
	else if (shdr[sym.st_shndx].sh_type == SHT_DYNAMIC)
		c = 'D';
	else
		c = !sym.st_value ? 'n' : 't';
	return ELF64_ST_BIND(sym.st_info) == STB_LOCAL &&
					c != 't' && c != 'n' ? c + 32 : c;
}
