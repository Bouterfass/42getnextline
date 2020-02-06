#include "get_next_line.h"

char	*line_filler(char *stock, int i)
{
	char	*new;
	int		len;

	if (stock == NULL)
		return (ft_strdup("\0"));
	len = ft_strlen(stock);
	if (i == -1)
		new = ft_substr(stock, 0, len);
	else
		new = ft_substr(stock, 0, i);
	return (new);
}

char	*update_stock(char *stock, int i)
{
	char	*temp;
	int		len;

	len = ft_strlen(stock);
	if (i == -1)
		i++;
	temp = ft_substr(stock, i + 1, len);
	free(stock);
	stock = temp;
	return (stock);
}

char	*set_stock(char *stock, char *buf)
{
	char *temp;

	if (stock == NULL)
		stock = ft_strdup(buf);
	else
	{
		temp = ft_strjoin(stock, buf);
		free(stock);
		stock = temp;
	}
	return (stock);
}

int		update_all(char **stock, char **line)
{
	int i;

	if ((i = backslash_n(*stock)) > 0)
	{
		*line = line_filler(*stock, i - 1);
		*stock = update_stock(*stock, i - 1);
		return (i);
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			bytes_r;
	int			i;
	static char	*stock = NULL;
	char		buf[BUFFER_SIZE + 1];

	if (!(fd >= 0 && BUFFER_SIZE > 0 && line != NULL && !read(fd, buf, 0)))
		return (-1);
	while ((bytes_r = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bytes_r] = '\0';
		stock = set_stock(stock, buf);
		if ((i = update_all(&stock, line)))
			return (1);
	}
	if ((i = update_all(&stock, line)))
		return (1);
	*line = line_filler(stock, i - 1);
	free(stock);
	stock = NULL;
	return (0);
}