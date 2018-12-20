/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 02:59:22 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 21:15:07 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	skip_whitespace(const char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\v'
			|| s[i] == '\f' || s[i] == '\r')
		++i;
	return (i);
}

static int	handle_sign(const char *s, int *i)
{
	int	sign;

	sign = 0;
	while (s[*i] == '+' || s[*i] == '-')
	{
		if (sign)
			return (0);
		else if (s[*i] == '+')
			sign = 1;
		else
			sign = -1;
		*i = *i + 1;
	}
	if (!sign)
		return (1);
	return (sign);
}

static int	get_pow(const char *s, int *i)
{
	int	size;
	int	pow;

	size = 0;
	pow = 1;
	while (s[*i] == '0')
		*i += 1;
	while (s[size + *i] >= '0' && s[size + *i] <= '9')
		++size;
	while (size - 1 > 0)
	{
		pow *= 10;
		--size;
	}
	return (pow);
}

int			ft_atoi(const char *s)
{
	int	i;
	int	sign;
	int	pow;
	int	result;

	result = 0;
	i = skip_whitespace(s);
	sign = handle_sign(s, &i);
	if (!sign)
		return (0);
	pow = get_pow(s, &i);
	while (s[i] >= '0' && s[i] <= '9')
	{
		result += (s[i] - '0') * pow * sign;
		pow /= 10;
		++i;
	}
	return (result);
}
