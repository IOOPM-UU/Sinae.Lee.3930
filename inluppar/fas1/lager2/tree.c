# include "tree.h"
# include "list.h"
# include "item.h"

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

int subtree_size(node_t *root)
{
  int size = 0;
  if (root == NULL)
    {
      return 0;
    }

  else // root != NULL
    {
      size = subtree_size(root->left) + 1 + subtree_size(root->right); 
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
      return subtree_size(tree->root);
    }

  else   // tree == NULL
    return 0;
}

int subtree_depth(node_t *node)
{
  if (node != NULL)    //node->left != NULL // node->right != NULL
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

node_t *insert_node (node_t *node, char *key, void *data)
{
  if (node == NULL)
    {
      return new_node(key, data);
    }

  else if (node != NULL)
    {
       // key < node->key
      if (strcmp(key, node->key) < 0)
        {
          if (node->left != NULL)
            {
              node->left = insert_node (node->left, key, data);
            }
          
          else // node->left == NULL
            {
              node->left = new_node(key, data);
            }
        }

      // key > node->key
      else if ( strcmp(key, node->key) > 0)
        {
          if (node->right != NULL)
            {
              node->right = insert_node (node->right, key, data);
            }

          else  // node->right == NULL
            {
              node->right = new_node(key, data);
            }
        }
    }
  return node;
}

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
  if (node)
    {
      return node->key;
    }

  else  // there is no node;
    printf("empty\n");
    return NULL;
}

void *get_node_data(node_t *node)
{
  if (node)
    {
      return node->data;
    }

  else
    printf("no node\n");
    return NULL;
}

char *get_shelf_node(node_t *node, int index)
{
  char *shelf;
  item_t *item = get_node_data(node);
  
  return shelf = get_shelf_nr(item, index);
}

void node_data_list(node_t *node, list_t *list)
{
  if (node == NULL) {return;}
  node_data_list(node->left, list);
  void *data_info = get_node_data(node);
  list_append(list, data_info);
  node_data_list(node->right, list);
}

//för att gör en lista av alla data(item)  
list_t *list_of_data(tree_t *tree)
{
  list_t *list_for_data = list_new();
  if (tree == NULL)
    {
      printf("Tree is empty\n");
    }

  node_data_list(tree->root, list_for_data);
  return list_for_data;
}

void node_shelf_list(node_t *node, list_t *list)
{
  if (node == NULL) {return;}
  node_shelf_list(node->left, list);

  item_t *item = get_node_data(node);
  int length = item_list_length(item);
  for( int index = 0; index<length; ++index)
    {
      char *shelf = get_shelf_node(node, index);
      list_append(list, shelf);
      
    }
   node_shelf_list(node->right, list);
}
  
list_t *list_node_shelf(tree_t *tree) //en lista med alla upptagna hyllor
{
  list_t *shelves = list_new();
  if (tree == NULL)
    {
      printf("\nThe tree is empty\n");
    }
  node_shelf_list(tree->root, shelves);
  return shelves;
}

bool is_key_in_subtree(node_t *node, char *key)
{
  // int ret = strcmp(key, node->key);
  
  if (node == NULL)
    {
      return false;
    }

  else if(strcmp(key, node->key) < 0)
    {
      return is_key_in_subtree(node->left, key);
    }

  else if(strcmp(key, node->key) > 0)
    {
      return is_key_in_subtree(node->right, key);
    }
  else
    {
      key = node->key;
      return true;
    }
}
  
bool is_key_in_tree(tree_t *tree, char *key)
{
  return is_key_in_subtree(tree->root, key);
}


void node_data(node_t *node, list_t *list)
{
  if (node == NULL)
    {
      return;
    }

  node_data(node->left, list);
  storage_t *storage = get_node_data(node);
  list_append(list, storage);
  node_data(node->right, list);
}

list_t *list_node_data(tree_t *tree)
{
  list_t *data = list_new();
  if (tree == NULL)
    {
      printf("tree is empty\n");
    }
  node_data(tree->root, data);
  return data;
}


bool is_data_in_subtree(node_t *node, char *key, void *data)
{
  if(node == NULL)
    {
      return false;
    }

  else if(strcmp(key, node->key) < 0)
    {
      return is_data_in_subtree(node->left, key, data);
    }

  else if(strcmp(key, node->key) > 0)
    {
      return is_data_in_subtree(node->right, key, data);
    }

  else if(strcmp(key, node->key) == 0)
    {
      data = node->data;
      return true;
    }

  else
    {
      return false;
    }
}

bool is_data_in_tree(tree_t *tree, char *key, void *data)
{
  return is_data_in_subtree(tree->root, key, data);
}

void node_keys(node_t *node, list_t *keys) //adds the key in a list, in order
{
	if (node == NULL)
	{
		return;
	}
	node_keys(node->left, keys);
	list_append(keys, node->key);
	node_keys(node->right, keys);
	
}

list_t *tree_keys(tree_t *tree) 
{
	list_t *keys = list_new();
	if (tree == NULL)
	{
		printf("\nThe tree is empty\n");
	}
	node_keys(tree->root, keys);
	return keys;
}



void *search_data_in_subtree(node_t *node, char *key)
{
  //int ret = strcmp(node->key, key);
  
  if(node != NULL)
    {
      if (strcmp(node->key, key) == 0)
        {
          return node->data;
        }

      else if (strcmp(node->key, key) < 0)
        {
          return search_data_in_subtree(node->right, key);
        }

      else
        {
          return search_data_in_subtree(node->left, key);
        }
    }

  else
    
    {
      printf("There is no such keyE\n");
      return NULL;
    }
}

void *search_data_in_tree(tree_t *tree, char *key)
{
  return search_data_in_subtree(tree->root, key);
}

bool is_leaf_node(node_t *node)
{
  if (node->left == NULL && node->right == NULL)
    {
      return true;
    }

  else
    {
      return false;
    }
}


bool remove_leaf_node(node_t **node, char *key)
{
  bool leaf_node = is_leaf_node(*node);
  
  if (*node == NULL)
    {
      return false;
    }

  else if (leaf_node == true)
    {
      if(strcmp(key, (*node)->key) == 0)
        {
          free((*node)->key);
          free ((*node)->data);
          free(*node);
          *node = NULL;
          return true;
        }
      else {return false;}
    }

  else if (strcmp(key, (*node)->key) < 0)
    {
      return remove_leaf_node(& ( (*node)->left), key);
    }

  else if (strcmp(key, (*node)->key) > 0)
    {
      return remove_leaf_node(& ( (*node)->right), key);
    }

  else  {return false;}
}


bool tree_remove_leaf (tree_t *tree, char *key)
{
  if (tree != NULL)
    {
      return remove_leaf_node(& (tree->root), key);
    }

  else {return false;}
}

// http://www.geeksforgeeks.org/sorted-array-to-balanced-bst/
node_t *balance_tree (list_t *list_of_items, int start, int end)
{

  if (start > end) {return NULL;}
  int mid = (start + end)/2;

  item_t *item = list_get(list_of_items, mid);
  char *key = get_name(item);
  
  node_t *root = new_node(key, item);
  
  root->left = balance_tree(list_of_items, start, mid-1);
  
  root->right = balance_tree(list_of_items, mid+1, end);
  
  return root;
}

tree_t *balanced_tree(tree_t *tree)
{
	list_t *list_of_items = list_of_data(tree);
	int end = list_length(list_of_items);
	node_t *root = balance_tree(list_of_items, 0, end-1);
	//behöver free:a alla items först i original trädet
	//och sen peka till nya root.
	// behöver freea listan också
	tree->root = root;
	return tree;
}

node_t *find_mini_node (node_t *root)
{
  while (root->left != NULL) root = root->left;
  return root;
}

node_t *remove_node (node_t *root, char *key)
{
  if (root == NULL) {return root;}
 
  if (strcmp(key, root->key) < 0)
    {
      root->left = remove_node(root->left, key); 
    }
  else if (strcmp(key, root->key) > 0)
    {
      root->right = remove_node(root->right, key);
    }

  else if (strcmp(key, root->key) == 0)
    {
      if (root->left == NULL && root->right == NULL)
        {
          free(root->data);
          free(root);
          root = NULL;
        }
      else if (root->left == NULL)
        {
          free(root->data);
          free(root);
          root = root->right;
        }
      else if (root->right == NULL)
        {
          free(root->data);
          free(root);
          root = root->left;
        }
      else
        {
          node_t *mini = find_mini_node(root->right);
          free(root->data);
          root = mini;
          root->right = remove_node(root->right, mini->key);
        }
    }
  return root;
}
  
bool tree_remove(tree_t *tree, char *key)
{
  bool in_tree = is_key_in_tree(tree, key);
  if (in_tree == true)
    {
      tree->root = remove_node(tree->root, key);
      return true;
    }
  else {return false; printf("the key isn't in the tree\n");}
}

/*

int main()
{
  tree_t *tree = tree_new();

  tree_insert(tree, "apple", "red");
  tree_insert(tree, "kiwi", "green");
  tree_insert(tree, "banana", "yellow");
  tree_insert(tree, "pear", "green");
  tree_insert(tree, "fox", "brown");
  tree_insert(tree, "rabbit", "white");
  tree_insert(tree, "cow", "milk");
  tree_insert(tree, "pig", "pinky");
  tree_insert(tree, "cat", "mjau");

  int size = tree_size(tree);
  printf("size is %d\n", size);

  list_t *key_list = tree_keys(tree);

  print_list(key_list);
  

  return 0;
  
}*/

