#include <unistd.h>
#include <stdio.h>

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
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	char *s1;
	char *s2;
	int	 l1;
	int i;

	if (argc != 3)
		return (write(1, "\n", 1));
	
	s1 = argv[1];
	s2 = argv[2];
	l1 = ft_strlen(s1);

	i = 0;
	while (s1[i])
	{
		if (!ft_isdoublon(s1[i], s1, i))
			write(1, &s1[i], 1);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		if (!ft_isdoublon(s2[i], s1, l1) && !ft_isdoublon(s2[i], s2, i))
				write(1, &s2[i], 1);
		i++;
	}
	write (1, "\n", 1);
	return (0);
}
