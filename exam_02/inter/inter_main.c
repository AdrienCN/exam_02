#include <unistd.h>

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_isdoublon(char c, char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	char *s1;
	char *s2;
	int i;
	int s2_len;

	if (argc != 3)
		return (write(1, "\n", 1));
	i = 0;
	s1 = argv[1];
	s2 = argv[2];
	s2_len = ft_strlen(s2);
	while (s1[i])
	{
		if (ft_isdoublon(s1[i], s2, s2_len) && !ft_isdoublon(s1[i], s1, i))
			write(1, &s1[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
