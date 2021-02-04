#include "h_printf.h"

typedef	struct s_data
{
	int prec_on;
	int prec_val;
	int field_on;
	int field_val;
	int printed;
	int error;
	int i;
}

void	ft_put_onechar(char c, t_data *info)
{
	write(1, &c, 1);
	info->n++;
	info->printed++
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_init_struct(t_data *info)
{
	info->prec_on = 0;
	info->prec_val = 0;
	info->field_val = 0;
	info->field_on = 0;
	info->n = 0;
	info->printed = 0;
	info->error = 0;
}
void	ft_reset_struct(t_data *info)
{
	info->prec_on = 0;
	info->prec_val = 0;
	info->field_val = 0;
	info->field_on = 0;
	info->i = 0;
	info->error = 0;
}	t_data;

int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		ft_nbrlen(int n)
{
	int i;

	i = 0;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

int		ft_hexlen(unsigned int n)
{
	unsigned int i;

	i = 0;
	while (n >= 16)
	{
		i++;
		n = n / 16;
	}
	return (n);
}

void	ft_putnbr_base(int nbr, char *str)
{
	int b_len;

	b_len = ft_strlen(str);
	if (nbr >= b_len)
		ft_putnbr_base(nbr / b_len, str);
	write(1, &str[nbr % b_len], 1);
}

void	ft_putnbr_hexbase(unsigned int nbr, char *str)
{
	int b_len;

	b_len = ft_strlen(str);
	if (nbr >= b_len)
		ft_putnbr_hexbase(nbr / b_len, str);
	write (1, &str[nbr % b_len], 1);
}

int		ft_atoi(char *str)
{
	int sign;
	int nbr;

	sign = 1;
	nbr = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nbr = nbr * 10 + (*str - 48);
		str++;
	}
	return (nbr * sign);
}


void	ft_print_hex(t_data *info, va_list arg);
{
	unsigned int x;
	int zero_pad;
	int len;
	int width;

	x = va_arg(arg, unsigned int);
	len = ft_hexlen(d);
	zero_pad = (info->prec_on == 1 && prec_val > len ? prec_val - len : 0);
	width = info->field_val - (zero_pad + len)
	while (width++ > 0)
	{
		write(1, " ", 1);
		info->printed++;
	}
	info->printed += len + zero_pad;
	while (zero_pad-- > 0)
		write(1, '0', 1);
	if (x == '0' && info->prec_val)
		return;
	ft_putnbr_hexbase(x, "0123456789");
}



void	ft_print_str(t_data *info, va_list arg)
{
	int len;
	char *str;

	str = va_arg(arg, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (info->prec_on && info->prec_val < len)
	   len = info->prec_val;
	while (info->field_on && info-field_val > info->prec_val)
	{
		write(1, " ", 1);
		info->printed++;
		info->field_val--;
	}
	while (info->prec_val > 0)
	{
		write(1, " ", 1);
		info->printed++;
	}
}

void	ft_print_int(t_data *info, va_list arg)
{
	int d;
	int zero_pad;
	int len;
	int width;

	d = va_arg(arg, int);
	len = ft_nbrlen(d);
	if (d < 0)
		len++;
	zero_pad = (info->prec_on == 1 && prec_val > len ? prec_val - len : 0);
	width = info->field_val - (zero_pad + len)
	while (width++ > 0)
	{
		write(1, " ", 1);
		info->printed++;
	}
	info->printed += len + zero_pad;
	if (d < 0)
	{
		d = -d;
		write(1, "-", 1);
	}
	while (zero_pad-- > 0)
		write(1, '0', 1);
	if (d == '0' && info->prec_val)
		return;
	ft_putnbr_base(d, "0123456789");
}

int		ft_printf(char *str, ...)
{
	int		ret;
	va_list arg;
	t_data	info;
	va_start(arg, str);
	ft_init_struct(&info);
	ret = ft_loop_in_str(str, arg, &info);
	return (ret);
}

int		ft_loop_in_str(char *str, va_list arg, t_data *info)
{
	int i;
	
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			ft_convert(str + i, arg, info);
		else
			ft_put_onechar(str + i, info);
		i += info->n;
		if (info->error == -1)
			return (-1);
		ft_reset_struct(info);
	}
	return (info->printed);
}

void	ft_convert(char *str, va_list arg, t_data *info)
{
	int i;

	i = 1;
	while (str[i] == '-' || str[i] == '0')
		i++;
	if (ft_isdigit(str[i]))
	{
		info->field_on = 1;
		info->field_val = ft_atoi(str + i);
		while (ft_isdigit(str[i]))
			i++;
	}
	if (str[i] == '.')
	{
		i++;
		info->prec_on = 1;
		info->prec_val = ft_atoi(str[i]);
		if (str[i] == '-')
			i++;
		while (ft_isdigit(str[i]))
			i++;
		if (info->prec_val < 0)
			info->prec_on = 0;
	}
	info->n += i;
	if (info->type == 'd')
		ft_print_int(info, arg);
	else if (info->type == 's')
		ft_print_str(info, arg);
	else if (info->type == 'x')
		ft_print_hex(info, arg);
	else
		info->error == 1;
}
