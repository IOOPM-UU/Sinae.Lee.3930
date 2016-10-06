#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "list.h"



/// Define struct tree in your .c file not here! (why?)
typedef struct tree tree_t;



/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new();

/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size(tree_t *tree);

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree);

//TODO tree_insert(tree_t *tree, TODO);
bool tree_insert(tree_t *tree, char *key, void *data);


void return_void_tree_insert(tree_t *tree, char *key, void *data);

tree_t *tree_insert2(tree_t *tree, char *key, void *data);

/// This does not need implementation until Assignment 2
//TODO tree_remove(tree_t *tree, TODO);

//MORE MISSING...
//void *get_tree_key(tree_t *tree);

bool is_key_in_tree(tree_t *tree, char *key);

bool is_data_in_tree(tree_t *tree, char *key, void *data);


list_t *tree_keys(tree_t *tree);

list_t *list_node_data(tree_t *tree);

list_t *list_node_shelf(tree_t *tree);


#endif
