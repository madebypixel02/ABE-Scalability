/* ************************************************************************** */
/*                                                                            */
/*                                  +###****.                                 */
/*                                  =***@@@+                                  */
/*              *%*   -%%:  -*%%%#     :@@@=:   #%##%%#=-*%%%*:               */
/*              %@%   =@@: #@@*=+*.    -==*@@+  @@@*=+@@@%+=#@@=              */
/*              %@%   -@@:-@@-     .==.    *@@. %@#   =@@:   %@#              */
/*              +@@+-=%@@..%@@+--+..%@@+--*@@*  @@#   +@@:   @@#              */
/*               -*%@@#+.   =#%@@%.  -*%@@%*-   %@*   =@@:   %@*              */
/*                                                                            */
/*   cp_abe.h                                                                 */
/*                                                                            */
/*   By: aperez-b <100429952@alumnos.uc3m.es>                                 */
/*                                                                            */
/*   Created: 2022/04/23 11:43:36 by aperez-b                                 */
/*   Updated: 2022/04/24 12:53:16 by aperez-b                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CP_ABE_H

# define CP_ABE_H

# include <sys/time.h>
# include <fcntl.h>
# include "libft.h"

/* Adds index to user/attribute */
char		*get_str(char *str, int index);

/* Adds stuff before and/or after a string to create command with parameters */
char		*wrap_cmd(char *prev, char *cmd, char *post);

/* Encrypts pdf with all available attributes */
void		encrypt_pdf(int n_attrs);

/* Decrypts pdf with a user's key attributes */
void		decrypt_pdf(int index);

/* Returns current time in miliseconds */
useconds_t	get_time(void);

#endif
