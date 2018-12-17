#include "ft_nm.h"


int load_file(t_nm *nm)
{
    nm->f_size = get_fstat(nm->fd);
    if (nm->f_size == -1)
        return (ft_error_msg("problem with fstat"));
    nm->file = mmap(0, nm->f_size, PROT_READ,MAP_PRIVATE, nm->fd, 0);
    nm->end = nm->file + nm->f_size;
    if (nm->file == MAP_FAILED)
        return (ft_error_msg("problem loading file with MMAP"));

    load_info(nm);
}

int load_info(t_nm *nm)
{
    uint32_t    magic;
    int         ret;

    if (close(nm->fd) < 0)
        return (ft_error_msg("problem closing file"));
    nm->magic = *(uint32_t*)nm->file;
    ret = check_magic(nm);
    check_swap(nm);
    check_arch(nm);
    if (ret == 1)
       normal_magic(nm);
    else if (ret == 2)
        fat(nm);   // fat(nm);
    else
        return (0); 
    return(1);
}

int check_swap(t_nm *nm)
{
    if (nm->magic == MH_CIGAM || nm->magic == MH_CIGAM_64 || nm->magic == FAT_CIGAM || nm->magic == FAT_CIGAM_64)
        nm->is_swapped = 1;
    else
        nm->is_swapped = 0;
}

int normal_magic(t_nm *nm)
{
    if (nm->is_64)
        load_64(nm);
    else
        load_32(nm);
}

int check_arch(t_nm *nm)
{
    if (nm->magic == MH_CIGAM_64 || nm->magic == MH_MAGIC_64 || nm->magic == FAT_MAGIC_64 || nm->magic == FAT_CIGAM_64)
        nm->is_64 = 1;
    else
        nm->is_64 = 0;
}

int fat(t_nm *nm)
{
    struct fat_arch *arch_file;
    struct fat_header *fat_file;
    void   *mach;
    uint32_t num;

    nm->if_fat = 1;
    fat_file = nm->file;
    num = fat_file->nfat_arch;
    arch_file = (void*)fat_file + sizeof(struct fat_header);
    while (num--)
    {
        if (arch_file->cputype ==  CPU_TYPE_X86_64)
        {
            nm->file += arch_file->offset;
            nm->end = nm->file + arch_file->size;
            load_info(nm);
        }
        arch_file += 1;
    }
    // ft_nm(nm);




}

int     check_magic(t_nm *nm)
{
    if (nm->magic == MH_MAGIC_64 || nm->magic == MH_CIGAM_64 || nm->magic ==  MH_CIGAM || nm->magic == MH_MAGIC)
        return (1);
    if (nm->magic == FAT_MAGIC_64 || nm->magic == FAT_MAGIC ||\
		nm->magic == FAT_CIGAM || nm->magic == FAT_CIGAM_64)
        return (2);
    else
        return (ft_error_msg("error, unknown file type"));
    // if (!ft_strncmp((char *)ptr, ARMAG, SARMAG));
}

int     is_64(uint32_t magic)
{
    if (magic == MH_MAGIC_64)
        return (64);
    if (magic == MH_CIGAM_64)
        return (64);
    if (magic == MH_CIGAM)
        return (32);
    if (magic == MH_MAGIC)
        return (32);
}

int     is_swapped(uint32_t magic)
{
    return (magic == MH_CIGAM || magic == MH_CIGAM_64);
}

int    ft_error_msg(char *msg)
{
    ft_putstr_fd(msg, 2);
    return (0);
}
