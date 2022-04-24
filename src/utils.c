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
/*   utils.c                                                                  */
/*                                                                            */
/*   By: aperez-b <100429952@alumnos.uc3m.es>                                 */
/*                                                                            */
/*   Created: 2022/04/23 12:57:23 by aperez-b                                 */
/*   Updated: 2022/04/24 13:03:23 by aperez-b                                 */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cp_abe.h"

useconds_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	encrypt_pdf(int n_attrs)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = ft_strdup("echo \"");
	while (i++ < n_attrs)
	{
		cmd = wrap_cmd(NULL, cmd, get_str("attr_", i));
		if (i + 1 <= n_attrs)
			cmd = wrap_cmd(NULL, cmd, ft_strdup(" and "));
	}
	cmd = wrap_cmd(NULL, cmd, \
		ft_strdup("\" | cpabe-enc -k master/pub_key ../file.pdf"));
	system(cmd);
	system("mv ../file.pdf.cpabe file-enc.pdf.cpabe");
	free(cmd);
}

void	decrypt_pdf(int index)
{
	char	*cmd;

	cmd = ft_strdup("cpabe-dec -k -o ");
	cmd = wrap_cmd(cmd, get_str("user_", index), ft_strdup("/"));
	cmd = wrap_cmd(cmd, get_str("file_", index), ft_strdup(".pdf "));
	cmd = wrap_cmd(cmd, ft_strdup("master/pub_key "), get_str("user_", index));
	cmd = wrap_cmd(cmd, ft_strdup("/priv "), ft_strdup("file-enc.pdf.cpabe"));
	system(cmd);
	free(cmd);
}

char	*wrap_cmd(char *prev, char *cmd, char *post)
{
	char	*aux;

	aux = prev;
	prev = ft_strjoin(prev, cmd);
	free(aux);
	free(cmd);
	aux = prev;
	cmd = ft_strjoin(prev, post);
	free(aux);
	free(post);
	return (cmd);
}

char	*get_str(char *str, int index)
{
	char	*aux;
	char	*n;

	if (!str)
		return (NULL);
	n = ft_itoa(index);
	aux = ft_substr(str, 0, 5);
	str = ft_strjoin(aux, n);
	free(aux);
	free(n);
	return (str);
}
