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
typedef struct node node_t;

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

/// Insert an item in the tree
///
///
/// \param tree pointer to the tree
/// \param key pointer to the name which will be stored
/// \param data pointer to data which will be stored
/// \returns: true if succsess
bool tree_insert(tree_t *tree, char *key, void *data);

/// We don't have this function
///
/// \param tree
/// \param key
/// \param data
void return_void_tree_insert(tree_t *tree, char *key, void *data);

/// Check if the key in the tree
///
/// \param tree pointer to the tree
/// \param key pointer to the key
/// \returns: true if there is the key in the tree
bool is_key_in_tree(tree_t *tree, char *key);

/// Check if the data in the tree
///
/// \param tree pointer to the tree
/// \param key pointer to the key
/// \param data pointer to the data
/// \returns: true if there is the data in the tree
bool is_data_in_tree(tree_t *tree, char *key, void *data);

/// Convert tree to the list with keys
///
/// \param tree pointer to the tree
/// \returns: a list with keys
list_t *tree_keys(tree_t *tree);

/// Convert tree to a list of node
///
/// \param tree pointer to the tree
/// \returns: a list with data of node
list_t *list_node_data(tree_t *tree);

/// Convert a tree to the list with data
///
/// \param tree pointer to the tree
/// \returns: a list of data
list_t *list_of_data(tree_t *tree);

/// Convert a list with nodes that have shelf position
///
/// \param tree pointer to tree
/// \returns: a list with nodes-shelf
list_t *list_node_shelf(tree_t *tree);

/// Search data in the tree by using key
///
/// \param tree pointer to tree
/// \param key pointer to key
/// \returns: a pointer to data
void *search_data_in_tree(tree_t *tree, char *key);

/// Check if it is leaf-node
///
/// \param node pointer to node
/// \returns: true or false
bool is_leaf_node(node_t *node);

/// Remove a leaf-node
///
/// \param node double pointer to node
/// \param key pointer to key
/// \returns: true or false
bool remove_leaf_node(node_t **node, char *key);

/// remove a leaf from tree
///
/// \param tree pointer to tree
/// \param key pointer to key
/// \returns: true or false
bool tree_remove_leaf (tree_t *tree, char *key);

/// Remove a node
///
/// \param tree pointer to tree
/// \param key pointer to key
/// \returns: true or false
bool tree_remove(tree_t *tree, char *key);

/// helfer function for balance_tree
///
/// \param list_of_items pointer to the list
/// \param start the starting index
/// \param end the ending index
/// \returns: a node
node_t *balance_tree (list_t *list_of_items, int start, int end);

/// Balance tree
///
/// \param tree pointer to tree
/// \returns: a balanced tree
tree_t *balanced_tree(tree_t *tree);

#endif
