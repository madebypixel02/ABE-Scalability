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
/*   main.c                                                                   */
/*                                                                            */
/*   By: aperez-b <100429952@alumnos.uc3m.es>                                 */
/*                                                                            */
/*   Created: 2022/04/23 11:29:43 by aperez-b                                 */
/*   Updated: 2022/04/25 19:38:58 by aperez-b                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cp_abe.h"
#include <unistd.h>

void	parse_args(char **argv, int *n_usrs, int *n_attrs, int *n_rep)
{
	*n_usrs = ft_atoi(argv[1]);
	*n_attrs = ft_atoi(argv[2]);
	*n_rep = ft_atoi(argv[3]);
	if (*n_usrs <= 0 || *n_usrs > 50)
		*n_usrs = 5;
	if (*n_attrs <= 0 || *n_attrs > 50)
		*n_attrs = 5;
	if (*n_rep <= 0 || *n_rep > 50)
		*n_rep = 20;
}

void	create_dirs(void)
{
	system("rm -rf tests");
	system("mkdir -p tests/master");
	chdir("tests/master");
	system("cpabe-setup");
	chdir("..");
}

void	config_dirs(int n_usrs, int n_attrs)
{
	int		ij[2];
	char	*cmd;

	ij[0] = 0;
	while (ij[0]++ < n_usrs)
	{
		cmd = wrap_cmd(ft_strdup("mkdir -p "), get_str("user_", ij[0]), NULL);
		system(cmd);
		free(cmd);
		cmd = wrap_cmd(ft_strdup("cp -r master/pub_key "), \
			get_str("user_", ij[0]), NULL);
		system(cmd);
		free(cmd);
		ij[1] = 0;
		cmd = wrap_cmd(ft_strdup("cpabe-keygen -o "), get_str("user_", ij[0]), \
			ft_strdup("/priv master/pub_key master/master_key"));
		while (ij[1]++ < n_attrs)
			cmd = wrap_cmd(cmd, ft_strdup(" "), get_str("attr_", ij[1]));
		system(cmd);
		free(cmd);
	}
}

useconds_t	crypt_pdf(int n_usrs, int n_attrs, int n_rep, int logfile)
{
	int			ij[2];
	useconds_t	start_time;
	useconds_t	end_time;

	ij[0] = 0;
	start_time = get_time();
	end_time = 0;
	while (ij[0]++ < n_rep)
	{
		ft_putstr_fd("Starting encryption no. ", logfile);
		ft_putnbr_fd(ij[0], logfile);
		ft_putstr_fd("...\n", logfile);
		encrypt_pdf(n_attrs);
		ft_putstr_fd("Encryption complete. Starting decryption...\n", logfile);
		ij[1] = 0;
		while (ij[1]++ < n_usrs)
		{
			decrypt_pdf(ij[1]);
			ft_putstr_fd("Decrypted file from user_", logfile);
			ft_putnbr_fd(ij[1], logfile);
			ft_putstr_fd(".\n", logfile);
		}
		end_time += get_time() - (start_time + end_time);
	}
	return (end_time);
}

int	main(int argc, char **argv)
{
	int			n_usrs;
	int			n_attrs;
	int			n_rep;
	int			logfile;
	useconds_t	time;

	if (argc != 4)
	{
		ft_putstr_fd("usage: ", 2);
		ft_putstr_fd("cp_abe <n_users> <n_attributes> <n_repetitions>\n", 2);
		return (1);
	}
	parse_args(argv, &n_usrs, &n_attrs, &n_rep);
	create_dirs();
	config_dirs(n_usrs, n_attrs);
	logfile = open("log.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
	time = crypt_pdf(n_usrs, n_attrs, n_rep, logfile);
	printf("Job done for %d user(s) with %d attribute(s) ", n_usrs, n_attrs);
	printf("(%d repetition(s)).\nTook: %0.3lf seconds (avg).\n", \
		n_rep, (double)(time) / (1000 * n_rep));
	close(logfile);
	return (0);
}
