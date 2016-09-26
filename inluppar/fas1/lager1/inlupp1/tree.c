#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
# include "tree.h"

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
  void *data;  //info
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
tree_t *tree_new()
{
  tree_t *tree = calloc(1, sizeof(tree_t));
  if (tree == NULL)
    return NULL;
  tree->root = NULL;
  return tree;
}


// create a new node
node_t *new_node(char *key, void *data)
{
  node_t *node = calloc(1, sizeof(node_t));
  node->key = key;
  node->data = data;
  node->left = node->right = NULL;
  return node;
}

int node_size(node_t *root)
{
  int size = 0;
  if (root)
    {
      size++;
      size = size + node_size(root->left);
      size = size + node_size(root->right);
    }

  return size;
}
/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size(tree_t *tree)
{
  if (tree != NULL)
    {
      return node_size(tree->root);
    }

  else   // tree == NULL
    return 0;
}

int subtree_depth(node_t *node)
{
  if (node != NULL)
    {
      int l_depth = subtree_depth(node->left);
      int r_depth = subtree_depth(node->right);

      if (l_depth > r_depth)
        return (l_depth + 1);

      else
        return (r_depth + 1);
    }

  else    // node == NULL
    return 0;
}

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree)
{
  if (tree == NULL)
    {
      return 0;
    }

  else
    return subtree_depth(tree->root);
}



//TODO tree_insert(tree_t *tree, TODO);
/*
tree_t *tree_insert(tree_t *tree, char *key, void *data)
{
  if (tree->root != NULL)
    {
      
    }

  else //tree->root == NULL
    return tree_insert(tree->root, new_node(key, data));
}
*/
/// This does not need implementation until Assignment 2
//TODO tree_remove(tree_t *tree, TODO);

//MORE MISSING...


 int main()
 {
   char *c1 = calloc(1, sizeof(char));
   *c1 = 'c';

   int *i1 = calloc(1, sizeof(int));
   *i1 = 1;
   
   node_t *root = new_node(c1, i1);

   char *c2 = calloc(1, sizeof(char));
   *c1 = 'b';

   int *i2 = calloc(1, sizeof(int));
   *i2 = 2;
   root->left = new_node(c2, i2);

   char *c3 = calloc(1, sizeof(char));
   *c3 = 'd';

   int *i3 = calloc(1, sizeof(int));
   *i3 = 3;
   root->right = new_node(c3, i3);

   char *c4 = calloc(1, sizeof(char));
   *c4 = 'e';

   int *i4 = calloc(1, sizeof(int));
   *i4 = 4;
   root->left->left = new_node(c4, i4);

   char *c5 = calloc(1, sizeof(char));
   *c5 = 't';

   int *i5 = calloc(1, sizeof(int));
   *i5 = 5;
   root->left->right = new_node(c5, i5);

   int size;
   size = node_size(root);
   printf("size is %d\n", size);

   
   int depth;
   depth = subtree_depth(root);
   printf("depth is %d\n", depth);
   
 }
