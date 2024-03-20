#include "../../include/philosopher.h"

void	ft_putstr_fd(char *s, uint8_t fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}



