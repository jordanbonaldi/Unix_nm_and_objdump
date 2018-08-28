/*
** EPITECH PROJECT, 2018
** Main informations
** File description:
** Main informations
*/

# include "project.h"

size_t return_nbr(int nbr, char *base, int idx)
{
	int	a;
	int	base_length;

	base_length = strlen(base);
	if (nbr >= base_length) {
		a = nbr % base_length;
		nbr = ((nbr - a) / base_length);
		return return_nbr(nbr, base, ++idx);
	}
	else
		return ++idx;
}

size_t hexa_counter(int nbr)
{
	return return_nbr(nbr, "0123456789abcdef", 0);
}
