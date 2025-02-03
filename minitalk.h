#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "libft/libft.h"

// Server Prototypes
void	handle_signal(int sig, siginfo_t *info, void *context);

// Client Prototypes
void	send_bit(int pid, int bit);
void	send_message(int pid, char *str);

#endif
