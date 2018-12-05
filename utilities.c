#include "ft_nm.h"

void    usage_txt(void)
{
    ft_putstr("nm usage: ft_nm [object file]\n");
}

size_t  get_fstat(int fd)
{
    struct stat f_info;
    size_t size;

    fstat(fd, &f_info);
    size = f_info.st_size;
    return(size);
}