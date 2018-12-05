#include "ft_nm.h"

void    print_it(t_nm *nm, int header_size)
{
    int i;
    int ncmds;
    struct load_command *load_c;
    struct symtab_command *sym;
    // struct segment_command_64 *segment;

    i = 0;
    ncmds = ((struct mach_header_64*)(nm->header))->ncmds;
    while (i < ncmds)
    {
        load_c = (void*)nm->header + header_size;
    

        if (load_c->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command*)load_c;
            // symthings(nm,sym->nsyms,sym->symoff, sym->stroff);
        }
        if (load_c->cmd == LC_SEGMENT_64)
        {
            add_segment(nm, (struct segment_command_64 *)load_c);
        }
        header_size += load_c->cmdsize;

    }
}

void    add_segment(t_nm *nm, struct segment_command_64 *segment)
{
    uint32_t i;
    struct section_64 *section;
    t_node  *node;

    i = 1;
    node = (t_node *)malloc(sizeof(t_node));
    section = (void *)segment + sizeof(struct segment_command_64);
    while (i < segment->nsects)
    {
        node->seg_name = section->sectname;
        node->addr = section->addr;
        node->size = section->size;
        node->offset = section->offset;
        node->left = NULL;
        node->right = NULL;
        insert_bt(nm->root, node);
        section = (void *)section + sizeof(struct section_64);
       
       i++;
    }
    return ;
}


void    symthings(t_nm *nm, int nsyms, int symoff, int stroff)
{
    int i;
    struct nlist_64 *array;
    char *string;
    int tbits;

    i = 0;
    array = nm->header + symoff;
    string = nm->header + stroff;
    while (i < nsyms)
    {
        ft_putnbr(array[i].n_sect);
        // ft_putstr(string + array->n_value);
        ft_putstr("     : ");
        tbits = array[i].n_type;
        bit_masking(tbits);
        ft_putnbr(array[i].n_type);
        ft_putstr("    :    ");
        
        ft_putstr(string + array[i].n_un.n_strx);
        ft_putchar('\n');
        i++;
    }
}

void    bit_masking(int n_type)
{
    char    return_type;
    char     mask_mask;

    mask_mask = n_type & N_TYPE;
    if (n_type & N_STAB)
        return_type = '-';
    if (mask_mask & N_UNDF)
        return_type = 'u';
    if (mask_mask & N_ABS)
        return_type = 'a';
    if  (mask_mask & N_INDR)
        return_type = 'i';

    
}