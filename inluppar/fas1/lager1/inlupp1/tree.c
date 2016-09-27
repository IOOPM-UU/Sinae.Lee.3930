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



// create a new node
node_t *new_node(char *key, void *data)
{
  node_t *node = calloc(1, sizeof(node_t));
  node->key = key;
  node->data = data;
  node->left = node->right = NULL;
  return node;
}

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

int node_size(node_t *root)
{
  int size = 0;
  if (root == NULL)
    {
      return 0;
    }

  else // root != NULL
    {
      size = node_size(root->left) + 1 + node_size(root->right); 
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


// https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
// http://stackoverflow.com/questions/19724546/creating-a-binary-search-tree-with-strings
//http://quiz.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
bool insert_node (node_t *node, char *key, void *data)
{
  int ret; //return value
  ret = strcmp(key, node->key);
  
  // if the tree is empty, return a new node

  /*if (node == NULL) 
    {
      new_node(key, data);
    }
  */
  
  // key < node->key
  if (ret < 0)
    {
      if (node->left != NULL)
        {
          insert_node (node->left, key, data);
          return true;
        }

      else // node->left == NULL
        {
          node->left = new_node(key, data);
          return true;
        }
    }

  // key > node->key
  else if (ret > 0)
    {
      if (node->right != NULL)
        {
          insert_node (node->right, key, data);
          return true;
        }

      else  // node->right == NULL
        {
          new_node(key, data);
          return true;
        }
    }
  
  else

    return false;
}

//TODO tree_insert(tree_t *tree, TODO);

tree_t *tree_insert(tree_t *tree, char *key, void *data)
{
  //subtree_insert(tree->root, key, data);

  if (tree->root == NULL)
    {
      tree->root = new_node(key, data);
      return true;
    }

  else if (tree->root != NULL)
    {
      insert_node(tree->root, key, data);
      return true;
    }
  
  else
    return false;
}

char *get_node_key(node_t *node)
{
  if (node != NULL)
    {
      return node->key;
    }

  else  // there is no node;
    return NULL;
}

void print_tree(tree_t *tree)
{
  node_t *current = tree->root;
  while (current != NULL)
    {
      printf("tree : %s\n", current->key);
      current = curr
    }
}


/// This does not need implementation until Assignment 2
//TODO tree_remove(tree_t *tree, TODO);

//MORE MISSING...


 int main()
 {

   tree_t *tree1;
   tree1 = tree_new();

   //int *i1 = calloc(1, sizeof(int));
   // *i1 = 10;

   bool value1 = tree_insert(tree1, "kola", (int *)10);
   printf("if true return %d\n", value1);


   tree_t *tree2 = tree_new();
  

   

   /*
  
   int size;
   size = tree_size();
   printf("size is %d\n", size);

   
   int depth;
   depth = tree_depth(tree3);
   printf("depth is %d\n", depth);
   
   */
  
 }
