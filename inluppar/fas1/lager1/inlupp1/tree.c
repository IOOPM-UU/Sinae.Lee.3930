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
  //node->left = node->right = NULL;
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

  if (node == NULL)
    {
      new_node(key, data);
      return true;
    }
   
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
          node->right = new_node(key, data);
          return true;
        }
    }

  else
    
    return false;

}

//TODO tree_insert(tree_t *tree, TODO);

bool tree_insert(tree_t *tree, char *key, void *data)
{
  if (tree->root == NULL)
    {
      tree->root = new_node(key, data);
      return true;
    }

  else if(tree->root != NULL)
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






/// This does not need implementation until Assignment 2
//TODO tree_remove(tree_t *tree, TODO);

//MORE MISSING...


 int main()
 {

   node_t *root = new_node("kola", (int *)10);
   root->left = new_node("cool", (int *)8);
   root->right = new_node("apple", (int *)11);
   root->left->left = new_node("bee", (int *)12);
   root->left->right = new_node("cee", (int *)13);

   tree_t *tree1;
   tree1 = tree_new();

   tree_t *tree2;
   tree2 = tree_new();

   bool answer = tree_insert(tree1, "cake", (int *)9);
   printf("true 1 = %d\n", answer);

  
   
   int size;
   size = node_size(root);
   printf("%d\n", size);
   
   int depth;
   depth = subtree_depth(root);
   printf("%d \n", depth);
 
   
}
