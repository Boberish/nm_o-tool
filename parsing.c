#include "ft_nm.h"

void    parse_args(int argc, char **argv)
{
    int i;

    i = 1;
    if (argc < 1)
    {
        ft_putstr_fd("Error: wrong number of arguments", 2);
        usage_txt();
    }
    // if (argv > 3)
    // {
    //     ft_printf("\n%s:\n", argv[i]);//either add something that parses argv or if you dont need to do taht, just delete this and dont pass argv here
    //     i++;
    // }
}




