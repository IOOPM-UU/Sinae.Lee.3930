#include "tree.h"

// nycklarna i sökträdet är varunamn
//Varor med samma namn anses vara identiska
//Varje vara har informationen från föregående uppgift, och dessutom en pekare till en lista med lagerplatser där varan finns lagrad

/// Define struct tree in your .c file not here! (why?)
typedef struct tree tree_t;

typedef struct node node_t;

struct tree{
  node_t *root;
};

struct node{
  char *key;
  void *data;
  node_t *left;
  node_t *right;
};

/// \file tree.h
///
/// \author Tobias Wrigstad
/// \version 1.0
/// \date 2015-08-28
/// \bug This file is partial. (On purpose.)


/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new();



node_t *new_node(char *key, void *data);



/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size(tree_t *tree);

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree);

TODO tree_insert(tree_t *tree, TODO);

/// This does not need implementation until Assignment 2
TODO tree_remove(tree_t *tree, TODO);

MORE MISSING...

#endif
