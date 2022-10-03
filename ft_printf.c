#include "ft_printf.h"
// #include "libft/libft.h"

int check_type(char *fmt, va_list args)
{
    char *str;
    int len;

    if (*fmt == '%')
        str = convert_c('%');
    else if (*fmt == 'c') 
        str = convert_c(va_arg (args, int));
    else if (*fmt == 's')
        str = convert_s(va_arg (args, char *));
        // str = convert_s(va_arg (args, char *));
    else if (*fmt == 'p') 
        str = convert_p(va_arg (args, unsigned long));
    else if (*fmt == 'd' || *fmt == 'i')
        str = convert_id(va_arg (args, int));
    else if (*fmt == 'u') 
        str = convert_u(va_arg (args, unsigned int));
    else if (*fmt == 'x' || *fmt == 'X') 
        str = convert_x(fmt, va_arg (args, unsigned int));
    else 
        str = "";
        
    if (!str)
        str = "(null)";
    if (*fmt == 'c' || *fmt == '%')
        ft_putchar_fd(*str, 1);
    else
        ft_putstr_fd(str, 1);
    len = (int)ft_strlen(str);
    if (*str == '\0' && *fmt == 'c')
        len = 1;
    if (*fmt != 's') 
        free(str);
    return (len);
}
int printfmt(const char *format, va_list args)
{
    char *fmt;
    int len;

    len = 0;
    fmt = (char *)format;
    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            len += check_type(fmt, args);
        } 
        else 
        {
            ft_putchar_fd(*fmt, 1);
            len++;
        }
        fmt++;
    }
    return (len);
}
int ft_printf(const char *fmt, ...)
{
    // char *fmt;
    // fmt = (char *)format;
    va_list args;
    int len;

    if (!fmt)
        return (0);
    va_start(args, fmt);
    len = printfmt(fmt, args);
    va_end(args);

    return len;
}
