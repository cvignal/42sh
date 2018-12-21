/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 12:16:14 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/21 17:56:04 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define PRINTF_ALLOC_SIZE 512

# define HEXA_STRING_CAP "0123456789ABCDEF"
# define HEXA_STRING "0123456789abcdef"
# define OCTAL_STRING "01234567"
# define DECIMAL_STRING "0123456789"

# define PREPEND_OCTAL "0"
# define PREPEND_HEXA_CAP "0X"
# define PREPEND_HEXA "0x"
# define PREPEND_PTR "0x"

# define CONV_START '%'
# define PRECISION_PERIOD '.'

# define FORMAT_STRING 's'
# define FORMAT_LSTRING 'S'
# define FORMAT_PTR 'p'
# define FORMAT_INT 'd'
# define FORMAT_INT_CAP 'D'
# define FORMAT_INT2 'i'
# define FORMAT_OCTAL_INT 'o'
# define FORMAT_OCTAL_INT2 'O'
# define FORMAT_CHARACTER 'c'
# define FORMAT_WCHARACTER 'C'
# define FORMAT_UINT 'u'
# define FORMAT_UINT2 'U'
# define FORMAT_HEXA_INT_CAP 'X'
# define FORMAT_HEXA_INT 'x'
# define FORMAT_DOUBLE 'f'
# define FORMAT_DOUBLE2 'F'
# define FORMAT_NONE '%'

# define MOD_H 'h'
# define MOD_L 'l'
# define MOD_L_CAP 'L'
# define MOD_J 'j'
# define MOD_Z 'z'

# define FLAG_ALTERNATE '#'
# define FLAG_ZERO '0'
# define FLAG_MINUS '-'
# define FLAG_PLUS '+'
# define FLAG_SPACE ' '

# define NULL_PRINT "(null)"
# define NULL_PRINTW L"(null)"
# define NAN_PRINT "nan"
# define NAN_PRINTC "NAN"

# include <stdarg.h>
# include <stdlib.h>

/*
** Types
*/
typedef enum		e_ftype
{
	TYPE_STRING,
	TYPE_LSTRING,
	TYPE_PTR,
	TYPE_INT,
	TYPE_UINT,
	TYPE_INT2,
	TYPE_CHAR,
	TYPE_CHARACTER,
	TYPE_WCHARACTER,
	TYPE_UCHAR,
	TYPE_DOUBLE,
	TYPE_NONE,
	NUMBER_OF_FTYPES
}					t_ftype;

typedef enum		e_mtype
{
	TYPE_MOD_NONE,
	TYPE_MOD_H,
	TYPE_MOD_HH,
	TYPE_MOD_L,
	TYPE_MOD_L_CAP,
	TYPE_MOD_LL,
	TYPE_MOD_Z,
	TYPE_MOD_J,
	NUMBER_OF_MTYPES
}					t_mtype;

/*
** Buffer
*/
typedef struct		s_printf_buffer
{
	char			*data;
	size_t			alloc_size;
	size_t			pos;
	int				error;
}					t_printf_buffer;

t_printf_buffer		*create_buffer(void);
int					add_to_buffer(t_printf_buffer *buffer, char c);
int					add_to_buffer_nstring(t_printf_buffer *buffer,
		const char *s, size_t n);
int					dump_buffer(int fd, t_printf_buffer *buffer);
void				free_buffer(t_printf_buffer *buffer);

/*
** Format description
*/
typedef struct		s_desc
{
	t_ftype			type;
	char			desc;
}					t_desc;

typedef int			(*t_printer)(void *, va_list *, t_printf_buffer *);

typedef struct		s_format
{
	t_printer		printer;
	char			*base;
	size_t			arg_size;
	t_desc			desc;
	char			*prepend;
	int				is_signed;
}					t_format;

/*
** Conversion
*/
typedef struct		s_conv
{
	t_format		*format;
	size_t			arg_size;
	int				type_mod;
	size_t			field_width;
	size_t			precision;
	int				precision_set;
	int				alternate;
	int				left_padded;
	int				zero_padded;
	int				sign;
	int				space;
}					t_conv;

/*
** Flags
*/
typedef void		(*t_flag_op)(t_conv *);

typedef struct		s_flag
{
	char			desc;
	t_flag_op		flag_op;
}					t_flag;

t_flag_op			get_flag_op(char c);

void				flag_minus(t_conv *conv);
void				flag_alternate(t_conv *conv);
void				flag_plus(t_conv *conv);
void				flag_zero(t_conv *conv);
void				flag_space(t_conv *conv);
void				apply_flags(t_conv *conv);

/*
** Modifiers description
*/
typedef int			(*t_conv_mod)(t_conv *);

typedef struct		s_modifier
{
	t_conv_mod		conv_mod;
	char			desc;
}					t_modifier;

/*
** ft_printf/printers/
*/
int					printer_string(void *conv, va_list *vl,
		t_printf_buffer *buffer);
int					printer_lstring(void *conv, va_list *vl,
		t_printf_buffer *buffer);
int					printer_ptr(void *conv, va_list *vl,
		t_printf_buffer *buffer);
int					printer_character(void *conv, va_list *vl,
		t_printf_buffer *buffer);
int					printer_generic_number(void *conv, va_list *vl,
		t_printf_buffer *buffer);
int					printer_double(void *conv, va_list *vl,
		t_printf_buffer *buffer);
int					printer_none(void *conv, va_list *vl,
		t_printf_buffer *buffer);

size_t				number_len(t_conv *conv, long long nbr);
size_t				print_flags(t_conv *conv, long long nbr,
		t_printf_buffer *buffer);
unsigned long long	get_arg_signed(t_conv *conv, va_list *vl);
unsigned long long	get_arg_unsigned(t_conv *conv, va_list *vl);
size_t				print_prepend(t_conv *conv, long long nbr,
		int after_padding, t_printf_buffer *buffer);
size_t				print_padding_left(t_conv *c, size_t max_len,
		long long arg, t_printf_buffer *buffer);
size_t				print_padding_right(t_conv *c, size_t max_len,
		long long arg, t_printf_buffer *buffer);
size_t				print_sign(t_conv *conv, long long arg,
		int after_padding, t_printf_buffer *buffer);

size_t				ft_putldnbr_base_buffer(long double nb, const char *base,
		unsigned int precision, t_printf_buffer *buffer);
size_t				ft_putullnbr_base_buffer(unsigned long long nb,
		const char *base, t_printf_buffer *buffer);
int					ft_putcharw_buffer(t_printf_buffer *buffer, wchar_t c);

size_t				print_padding_double(t_conv *conv, size_t len,
		t_printf_buffer *buffer);
size_t				print_flags_double_left(t_conv *conv, long double nbr,
		size_t len, t_printf_buffer *buffer);
size_t				print_flags_double_right(t_conv *conv, long double nbr,
		size_t len, t_printf_buffer *buffer);
int					get_padding_length_double(t_conv *conv, long double nbr);

/*
** ft_printf/modifiers/
*/
int					mod_h(t_conv *conv);
int					mod_l(t_conv *conv);
int					mod_l_cap(t_conv *conv);
int					mod_j(t_conv *conv);
int					mod_z(t_conv *conv);
int					apply_modifiers(t_conv *conv);
t_conv_mod			get_conv_mod(char c);

/*
** ft_printf/print.c
*/
int					print_normal(const char *format, int *pos,
		t_printf_buffer *buffer);
int					print_conv(const char *format, int *pos, void *vl,
		t_printf_buffer *buffer);

/*
** ft_printf/format.c
*/
t_format			*get_format(char c);
t_format			*new_format(char c);

/*
** ft_printf/conversion.c
*/
int					conv_flags(const char *format, int *pos, t_conv *conv);
int					conv_field_width(const char *format, int *pos,
		t_conv *conv, va_list *ap);
int					conv_precision(const char *format, int *pos, t_conv *conv,
		va_list *ap);
int					conv_mod(const char *format, int *pos, t_conv *conv);

#endif
