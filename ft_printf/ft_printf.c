#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct s_data
{
	int p_on;
	int p_val;
	int f_on;
	int f_val;
	int n;
	int print;
	int error;
}	t_data;

void	ft_init_struct(t_data *info)
{
	info->p_on = 0;
	info->p_val = 0;
	info->f_on = 0;
	info->f_val = 0;
	info->n = 0;
	info->print = 0;
	info->error = 0;
}

void ft_reset_struct(t_data *info)
{
	info->p_on = 0;
	info->p_val = 0;
	info->f_on = 0;
	info->f_val = 0;
	info->n = 0;
	info->error = 0;
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_hexlen(unsigned int nbr)
{
	unsigned int i;

	i = 1;
	while (nbr >= 16)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}


int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_nbrlen(int nbr)
{
	int i;

	i = 1;
	while (nbr >= 10)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}


void	ft_putnbr_base(char *base, int nbr)
{
	int b_len ;

	b_len = ft_strlen(base);
	if (nbr >= b_len)
		ft_putnbr_base(base, nbr / b_len);
	ft_putchar(base[nbr % b_len]);
}

void	ft_putnbr_hexbase(char *base, unsigned int nbr)
{
	unsigned int b_len ;

	b_len = (unsigned int)ft_strlen(base);
	if (nbr >= b_len)
		ft_putnbr_hexbase(base, nbr / b_len);
	ft_putchar(base[nbr % b_len]);
}
int		ft_atoi(char *str)
{
	int sign;
	int nbr;
	int i;

	sign = 1;
	nbr = 0;
	i = 0;
	if (str[i] == '-'|| str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nbr = nbr * 10 + (str[i]- 48 );
		i++;
	}
	return (nbr * sign);
}
void	ft_print_str(va_list arg, t_data *info)
{
	int len;
	char *str;

	str = va_arg(arg, char*);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (info->p_on &&  info->p_val < len)
		len = info->p_val;
	while (info->f_on && info->f_val> len)
	{
		info->f_val--;
		ft_putchar(' ');
		info->print++;
	}
	while (len > 0)
	{
		ft_putchar(*str);
		str++;
		len--;
		info->print++;
	}
}

void	ft_print_hex(va_list arg, t_data *info)
{
	unsigned int len;
	unsigned int zero_pad;
	unsigned int x;
	int width;

	x = va_arg(arg, unsigned int);
	len = ft_hexlen(x);
	zero_pad = 0;
	if ( x == 0 && info->p_on && info->p_val == 0)
		len = 0;
	if (info->p_on && (unsigned int)info->p_val > len)
		zero_pad = (unsigned int)info->p_val - len;
	width = info->f_val - (zero_pad + len);
	//printf("\nHEX:f_val = %d | zero_pad = %d | len = %d\n", info->f_val, zero_pad, len);
	while (width > 0)
	{
		ft_putchar(' ');
		width--;
		info->print++;
	}
	while (zero_pad > 0)
	{
		ft_putchar('0');
		zero_pad--;
		info->print++;
	}
	if (len == 0)
		return ;
	info->print += len;
	ft_putnbr_hexbase("0123456789abcdef", x);
}




void	ft_print_int(va_list arg, t_data *info)
{
	int len;
	int zero_pad;
	int d;
	int width;

	d = va_arg(arg, int);
	len = ft_nbrlen(d);
	if (d == 0 && info->p_on && info->p_val == 0)
		len = 0;
	zero_pad = 0;
	if (info->p_on && info->p_val > len)
		zero_pad = info->p_val - len;
	if (d < 0)
		len++;
	width = info->f_val - (zero_pad + len);
	//printf("\nf_val = %d | zero_pad = %d | len = %d\n", info->f_val, zero_pad, len);
	while (width > 0)
	{
		ft_putchar(' ');
		width--;
		info->print++;
	}
	if (d < 0)
	{
		d = -d;
		ft_putchar('-');
		info->print++;
	}
	while (zero_pad > 0)
	{
		zero_pad--;
		ft_putchar('0');
		info->print++;
	}
	if (len == 0)
		return ;
	info->print += len;
	ft_putnbr_base("0123456789", d);
}


void	ft_convert(char *str, va_list arg, t_data *info)
{
	int i;

	i = 1;
	while (str[i] == '-' || str[i] == '0')
		i++;
	if (ft_isdigit(str[i]))
	{
		info->f_on = 1;
		info->f_val = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
			i++;
	}
	if (str[i] == '.')
	{
		i++;
		info->p_on = 1;
		info->p_val = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
				i++;
	}
	info->n += i;
	//printf("\nstr[%d] = %c\n", i, str[i]);
	if (str[i] == 'd')
		ft_print_int(arg, info);
	else if (str[i] =='x')
		ft_print_hex(arg, info);
	else if (str[i] == 's')
		ft_print_str(arg, info);
	else
		info->error = 1;
}

int		ft_loop_in_str(char *str, va_list arg, t_data *info)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
			ft_convert(str + i, arg, info);
		else
		{
			ft_putchar(str[i]);
			info->print++;
		}
		i++;
		i += info->n;
		if (info->error == 1)
		{
			write(1, "error\n", 6);
			return (-1);
		}
		ft_reset_struct(info);
	}
	return (info->print);
}

int		ft_printf(char *str, ...)
{
	int ret;
	va_list arg;
	t_data info;

	va_start(arg, str);
	ft_init_struct(&info);
	ret = ft_loop_in_str(str, arg, &info);
	return (ret);
}

int main(void)
{
	char *str;
	int d;
	int x;

	d = 42;
	x = 42;
	str = "Ceci_est_un_test";

	printf("%d\n", printf("le_printf:[%20.5s][%5.d][%5.x]\n", str, d, x));
	printf("%d\n", ft_printf("ft_printf:[%20.5s][%5.d][%5.x]\n", str, d, x));
	return (0);
}
