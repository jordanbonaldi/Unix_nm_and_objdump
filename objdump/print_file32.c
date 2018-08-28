/*
** EPITECH PROJECT, 2018
** Main informations
** File description:
** Main informations
*/

# include "project.h"

static bool check_shdr_type(Elf32_Shdr shdr)
{
	return shdr.sh_type == SHT_SYMTAB ||
		shdr.sh_type == SHT_NOBITS ||
		shdr.sh_type == SHT_STRTAB ||
		!shdr.sh_size;
}

static size_t hexa_rec(register uint8_t *data, int size,
			register int idx, bool ascii)
{
	if (idx > SIZE - 1) {
		printf("%s", ascii ? "\n" : " ");
		if (!ascii)
			return hexa_rec(data, size, 0, true);
		return 0;
	}
	if (idx < size)
		if (!ascii)
			printf("%02x", data[idx]);
		else
			printf("%c", data[idx] >= (SIZE * 2) &&
				data[idx] <= ((SIZE * 8) - (SIZE / 8)) ?
				data[idx]  : '.');
	else
		printf("%s", ascii ? " "  : "  ");
	if (!ascii)
		printf("%s", !((idx + 1) % 4) ? " " : "");
	return hexa_rec(data, size, ++idx, ascii);
}

static void count_zeros(size_t offset, register Elf32_Shdr shdr,
		size_t *zeros)
{
	int tmp;

	*zeros = 0;
	for (; offset < SH_SIZE; offset += SIZE) {
		tmp = ADDR + offset - shdr.sh_offset;
		if (offset + SIZE >= shdr.sh_offset + shdr.sh_size)
			*zeros = hexa_counter(tmp);
	}
}

void print_file32(elf_t *elf)
{
	register Elf32_Shdr shdr;
	size_t offset;
	size_t zeros = 0;

	for (size_t i = 0; i < elf->_ehdr->e_shnum; i++) {
		shdr = elf->_shdr[i];
		if (check_shdr_type(shdr) &&
			strcmp(&((char *)NAME32)[shdr.sh_name], ".dynstr"))
			continue;
		printf("Contents of section %s:\n",
				&((char *)NAME32)[shdr.sh_name]);
		offset = shdr.sh_offset;
		count_zeros(shdr.sh_offset, shdr, &zeros);
		for (; offset < SH_SIZE; offset += SIZE) {
			printf(" %0*x ", (int)zeros < 4 ? 4 : (int)zeros,
				(uint32_t)(ADDR + offset - shdr.sh_offset));
			hexa_rec((uint8_t *)elf->_ehdr + offset,
						SH_SIZE - offset, 0, false);
		}
	}
}
