#include "ft_nm.h"

void    print_it(t_nm *nm, int header_size)
{
    int i;
    int ncmds;
    struct load_command *load_c;
    struct symtab_command *sym;
    // struct segment_command_64 *segment;
    char    *sec_list;
    int     len;

    sec_list = (char*)malloc(sizeof(char *) * 2);
    sec_list[1] = 0;
    i = 0;
    len = 1;
    ncmds = ((struct mach_header_64*)(nm->header))->ncmds;
    while (i < ncmds)
    {
        load_c = (void*)nm->header + header_size;
    

        if (load_c->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command*)load_c;
            symthings(nm,sym->nsyms,sym->symoff, sym->stroff);
        }
        if (load_c->cmd == LC_SEGMENT_64)
        {
            add_segment(nm, (struct segment_command_64 *)load_c, sec_list, &len);
        }
        header_size += load_c->cmdsize;
        i++;
    }

}



void    add_segment(t_nm *nm, struct segment_command_64 *segment, char *sec_list, int *len)
{
    uint32_t i;
    struct section_64 *section;

    i = 1;
    section = (void *)segment + sizeof(struct segment_command_64);
    while (i < segment->nsects)
    {
        if (ft_strcmp(section->sectname, "__text") == 0)
            nm->sec_index[0] = *len;
        else if (ft_strcmp(section->sectname, "__bss") == 0)
            nm->sec_index[1] = *len;
        else if (ft_strcmp(section->sectname, "__data") == 0)
            nm->sec_index[2] = *len;
        *len += 1;
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
    // int tbits;
    t_node  *node;

    i = 0;
    array = nm->header + symoff;
    string = nm->header + stroff;
    while (i < nsyms)
    {
        node = (t_node *)malloc(sizeof(t_node));
        node->seg_name = string + array[i].n_un.n_strx;
        node->value = array[i].n_value;
        node->n_sect = array[i].n_sect;
        node->left = NULL;
        node->right = NULL;
        node->type = array[i].n_type;
        bit_masking(nm, node->type, node->n_sect);

        
        // ft_putnbr(array[i].n_sect);
        // // ft_putstr(string + array->n_value);
        // ft_putstr("     : ");
        // tbits = array[i].n_type;
        // bit_masking(tbits);
        // ft_putnbr(array[i].n_type);
        // ft_putstr("    :    ");
        
        // ft_putstr(string + array[i].n_un.n_strx);
        // ft_putchar('\n');
        insert_bt(nm->root, node);
        i++;
    }
}

void    bit_masking(t_nm *nm, uint8_t n_type, uint8_t n_sect)
{
    char    return_type;
    char     mask_mask;

    mask_mask = n_type & N_TYPE;
    if (n_type & N_STAB)
        return_type = '-';
    if (mask_mask == N_UNDF)
        return_type = 'u';  //add if n_value then its a c otherwize a u
    if (mask_mask == N_ABS)
        return_type = 'a';
    if  (mask_mask == N_INDR)
        return_type = 'i';
    if  (mask_mask == N_PBUD)
        return_type = 'u';
    // if  (mask_mask == N_SECT)
        // return_type = find_sec(nm, n_type, n_sect);

    
}

// char    find_sec(t_nm *nm, uint8_t type, uint8_t n_sect)
// {

// }

// void    add_segment(t_nm *nm, struct segment_command_64 *segment)
// {
//     uint32_t i;
//     struct section_64 *section;
//     t_node  *node;

//     i = 1;
//     section = (void *)segment + sizeof(struct segment_command_64);
//     while (i < segment->nsects)
//     {
//         node = (t_node *)malloc(sizeof(t_node));
//         node->seg_name = section->sectname;
//         // node->addr = section->addr;
//         // node->size = section->size;
//         // node->offset = section->offset;
//         // node->left = NULL;
//         // node->right = NULL;
//         // insert_bt(nm->seg_root, node);
//         section = (void *)section + sizeof(struct section_64);
       
//        i++;
//     }
//     return ;
// }