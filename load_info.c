#include "ft_nm.h"

void     load_info(t_nm *nm, int fd)
{
    uint32_t magic;

    nm->file = mmap(0, get_fstat(fd), PROT_READ,MAP_PRIVATE, fd, 0);
    magic = *(uint32_t*)nm->file;
    load_header(nm, is_64(magic), is_swapped(magic));

}

void     load_header(t_nm *nm, int is_64, int is_swapped)
{
    // struct  mach_header *header32;

    if (is_64)
        load_64(nm);
    if (is_swapped)
        ;
}

int     is_64(uint32_t magic)
{
    return (magic == MH_MAGIC_64 || magic == MH_CIGAM_64);
}

int     is_swapped(uint32_t magic)
{
    return (magic == MH_CIGAM || magic == MH_CIGAM_64);
}

