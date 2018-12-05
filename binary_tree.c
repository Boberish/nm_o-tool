#include "ft_nm.h"

t_node    *insert_bt(t_node *root, t_node *node)
{
    if (root == NULL)
        return(node);
    if (ft_strcmp(root->seg_name, node->seg_name) < 0)
        root->left = insert_bt(root->left, node);
    else if (ft_strcmp(root->seg_name, node->seg_name) > 0)
        root->right = insert_bt(root->right, node);
    else
    {
        if (root->addr > node->addr)
            root->left = insert_bt(root->left, node);
        else if (root->addr < node->addr)
            root->right = insert_bt(root->right, node);
    }
    return(node);

}