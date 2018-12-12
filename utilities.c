#include "ft_nm.h"

void    usage_txt(void)
{
    ft_putstr("nm usage: ft_nm [object file]\n");
}

size_t  get_fstat(int fd)
{
    struct stat f_info;
    size_t size;

    if (fstat(fd, &f_info) == -1)
        return (-1);
    size = f_info.st_size;
    return(size);
}