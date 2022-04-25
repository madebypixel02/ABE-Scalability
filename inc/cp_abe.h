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
/*   Updated: 2022/04/25 12:10:10 by aperez-b                                 */
/*                                                                            */
/* ************************************************************************** */

#ifndef CP_ABE_H

# define CP_ABE_H

# include <sys/time.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

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

/* Reads a String, and, after ignoring spaces
with ft_isspace, saves the string into an integer */
int			ft_atoi(const char *nptr);

/* Concatenates two strings allocating enough space first */
char		*ft_strjoin(char const *s1, char const *s2);

/* Copies from the n-th char of a string */
char		*ft_substr(char const *s, unsigned int start, size_t len);

/* Saves enough space and duplicates a string */
char		*ft_strdup(const char *s);

/* Copies n - 1 bytes from a source string to a destination string */
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

/* Saves the given number as a string (char array) */
char		*ft_itoa(int n);

/* Prints string to the given file descriptor */
int			ft_putstr_fd(char *s, int fd);

/* Retrieves length of a number in a given base */
int			ft_nbrlen(long n, int base);

/* Retrieves length of a string */
size_t		ft_strlen(const char *s);

/* Prints number to the given file descriptor */
int			ft_putnbr_fd(int n, int fd);

/* Prints a character to the given file descriptor */
int			ft_putchar_fd(char c, int fd);

/* Returns if a character is a form of space (space, tab, etc) */
int			ft_isspace(char c);

#endif
