#include "../../include/philosopher.h"

static void	handle_mutex_error(int status, t_mtxcode mtxcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == mtxcode || UNLOCK == mtxcode))
		exit_error("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == mtxcode)
		exit_error("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		exit_error("A deadlock would occur if the thread "
			"blocked waiting for mutex.");
	else if (EPERM == status)
		exit_error("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		exit_error("The process cannot allocate enough memory"
			" to create another mutex.");
	else if (EBUSY == status)
		exit_error("Mutex is locked");
}

void	exit_error(char *strerr)
{
	print_error(strerr, RED, 2);
	exit(EXIT_FAILURE);
}
