#include "../../include/philosopher.h"

void	ft_putstr_fd(char *s, uint8_t fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	print_error(char *s, char *color, uint8_t fd)
{
	ft_putstr_fd(color, fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd(RESET, fd);
}


