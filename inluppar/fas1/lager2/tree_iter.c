
#include<stdio.h>
#include<stdlib.h>


// mål: iteration vs recursion

typedef struct node node_t;


struct node{
  int key;
  node_t *left, *right;
};


node_t *new_node(int key)
{
  node_t *temp = calloc(1, sizeof(node_t));
  temp->key = key;
  temp->left = temp->right = NULL;
  return temp;
}

//iteration
void traversal (node_t *root)
{
  node_t *current;
  node_t *pre;

  if (root == NULL)
    {
      return;
    }
  current = root;

  printf("\nNu itererar jag\n");
  while(current != NULL)
    {
      if (current->left == NULL)
        {
          printf("%d ", current->key);
          current = current->right;
        }
      else
        {
          pre = current->left;
          while(pre->right != NULL && pre->right != current)
            pre = pre->right;
          if(pre->right == NULL)
            {
              pre->right = current;
              current = current->left;
            }

          else 
            {
              pre->right = NULL;
              printf("%d ",current->key);
              current = current->right;      
            } 
        }
    }
}



void traverse_rec(node_t *root)
{
    if (root != NULL)
    {
        
        traverse_rec(root->left);
        printf("%d ", root->key);
        traverse_rec(root->right);
    }
}
 
node_t *insert(node_t *node, int key)
{
    if (node == NULL) return new_node(key);
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    
    return node;
}


/*
node_t *min_value_node(node_t *node)
{
    node_t *current = node;
 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
node_t *delete_node(node_t *root, int key)
{
    if (root == NULL) return root;

    if (key < root->key)
        root->left = delete_node(root->left, key);
 
    else if (key > root->key)
        root->right = delete_node(root->right, key);

    else
    {
        if (root->left == NULL)
        {
            node_t *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node_t *temp = root->left;
            free(root);
            return temp;
        }
 
        node_t *temp = min_value_node(root->right);
 
        root->key = temp->key;

        root->right = delete_node(root->right, temp->key);
    }
    return root;
}
*/




int main()
{
  
  node_t *root = NULL;
  root = insert(root, 4);
  root = insert(root, 2);
  root = insert(root, 1);
  root = insert(root, 3);
  root = insert(root, 5);

  node_t *node = NULL;
  node = insert(node, 4);
  node = insert(node, 2);
  node = insert(node, 1);
  node = insert(node, 3);
  node = insert(node, 5);
  
 
  /*

       1
     /    \
    2      3
  /   \
  4   5

   */

  traversal(node);
  
  
  printf("\nUsing recursion\n");
  traverse_rec(root);
  printf("\n\n");

  /*
  printf("\nDelete 2\n");
  root = delete_node(root, 2);
  printf("After delete \n");
  inorder(root);
  printf("\n");
  
  printf("\nDelete 3\n");
  root = delete_node(root, 3);
  printf("After delete\n");
  inorder(root);
  printf("\n");
  
  printf("\nDelete 5\n");
  root = delete_node(root, 5);
  printf("After delete \n");
  inorder(root);
  printf("\n\n");
  */
  
  return 0;
}

