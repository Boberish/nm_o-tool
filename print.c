#include "ft_nm.h"
#include <stdio.h>

void    print_it(t_nm *nm, int header_size, int ncmds)
{
    struct load_command *load_c;
    struct symtab_command *sym;
    int     len;

    len = 1;
    load_c = (void*)nm->header + header_size;
    while (ncmds--)
    {
        if (load_c->cmd == LC_SYMTAB)
        {
            sym = (struct symtab_command*)load_c;
            if (nm->is_64)
                symthings_64(nm,sym->nsyms,sym->symoff, sym->stroff);
            else
                symthings_32(nm,sym->nsyms,sym->symoff, sym->stroff);
        }
        if (load_c->cmd == LC_SEGMENT_64)
            add_segment_64(nm, (struct segment_command_64 *)load_c,  &len);
        else if (load_c->cmd == LC_SEGMENT)
            add_segment_32(nm, (struct segment_command *)load_c,  &len);
        load_c = (void*)load_c + load_c->cmdsize;
    }
    print_alpha(nm->root);
}

void    add_segment_64(t_nm *nm, struct segment_command_64 *segment, int *len)
{
    uint32_t i;
    struct section_64 *section;

    i = 1;
    section = (void *)segment + sizeof(struct segment_command_64);
    while (i <= segment->nsects)
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

void    add_segment_32(t_nm *nm, struct segment_command *segment, int *len)
{
    uint32_t i;
    struct section *section;

    i = 1;
    section = (void *)segment + sizeof(struct segment_command);
    while (i <= segment->nsects)
    {
        if (ft_strcmp(section->sectname, "__text") == 0)
            nm->sec_index[0] = *len;
        else if (ft_strcmp(section->sectname, "__bss") == 0)
            nm->sec_index[1] = *len;
        else if (ft_strcmp(section->sectname, "__data") == 0)
            nm->sec_index[2] = *len;
        *len += 1;
        section = (void *)section + sizeof(struct section);
        i++;
    }
    return ;
}

void    symthings_64(t_nm *nm, int nsyms, int symoff, int stroff)
{
    int i;
    struct nlist_64 *array;
    char *string;
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
        node->type = bit_masking(nm, (struct n_list_64 *)array, array[i].n_type, node->n_sect);
        insert_bt(nm->root, node);
        i++;
    }
}

void    symthings_32(t_nm *nm, int nsyms, int symoff, int stroff)
{
    int i;
    struct nlist *array;
    char *string;
    t_node  *node;

    i = 0;
    array = nm->header + symoff;
    string = nm->header + stroff;
    while (i < nsyms)
    {
        i++;
        // char * tmp;
        // tmp = string + array[i].n_un.n_strx;
        if ((char)*(string + array[i].n_un.n_strx) == '\0')
            continue ;
        
        node = (t_node *)malloc(sizeof(t_node));
        node->seg_name = string + array[i].n_un.n_strx;
        node->value = array[i].n_value;
        node->n_sect = array[i].n_sect;
        node->left = NULL;
        node->right = NULL;
        node->type = array[i].n_type;
        node->type = bit_masking(nm, (struct n_list *)array, array[i].n_type, node->n_sect);
        insert_bt(nm->root, node);
    }
}

char    bit_masking(t_nm *nm, void *array, unsigned char n_type, uint8_t n_sect)
{
    char    return_type;
    char     mask_mask;

    return_type = '?';
    mask_mask = n_type & N_TYPE;
    if (n_type & N_STAB)
        return_type = '-';
    else if (mask_mask == N_UNDF)
        return_type = 'u';  //add if n_value then its a c otherwize a u
    else if (mask_mask == N_ABS)
        return_type = 'a';
    else if  (mask_mask == N_INDR)
        return_type = 'i';
    else if  (mask_mask == N_PBUD)
        return_type = 'u';
    if  (mask_mask == N_SECT)
        return_type = find_sec(nm, array, n_type, n_sect);
    if (n_type & N_EXT)
        return_type = ft_toupper(return_type);
    if (return_type == '?')
        ft_putstr("couldnt figure out return type");
    return (return_type);
}

char    find_sec(t_nm *nm, struct nlist_64 *array, uint8_t type, uint8_t n_sect)
{
    if (n_sect == nm->sec_index[0])
        return ('t');
    else if (n_sect == nm->sec_index[1])
        return ('b');
    else if (n_sect == nm->sec_index[2])
        return ('d');
    else
        return ('s');
}


void print_alpha(t_node *curr)
{
		// if (curr->left != NULL)
        if (curr == NULL)
            return ;
        print_alpha(curr->left);
        if (curr->seg_name[0] == 'm')
            return;
        if (curr->value == 0)
            printf("                ");
        else
		    printf("%016llx",curr->value);
        printf(" %c", curr->type);
        printf(" %s\n", curr->seg_name);
        // printf("%016llx %c %s\n", curr->value, curr->type, curr->seg_name);
		// if (curr->right != NULL)
        print_alpha(curr->right);
		// printf("%x",curr->value);
        // printf(" %c", curr->type);
        // printf(" %s", curr->seg_name);
        return ;
}

