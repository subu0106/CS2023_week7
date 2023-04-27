#include <iostream>
using namespace std;

struct node
{
  int key;
  struct node *left, *right;
};

// Inorder traversal
void traverseInOrder(struct node *root)
{
  if (root != NULL)
  {
    traverseInOrder(root->left);
    cout << root->key << " ";
    traverseInOrder(root->right);
  }
}

// Insert a node
struct node *insertNode(struct node *node, int key)
{
  if (node == NULL)
  { // If the tree is empty, return a new node
    struct node *newNode = new struct node;
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }

  // Otherwise, recur down the tree
  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);

  // Return the (unchanged) node pointer
  return node;
}
//min value
struct node *minValueNode(struct node *node)
{
  struct node *current = node;
  while (current->left != NULL) // loop down to find the leftmost leaf
    current = current->left;
  return current;
}

// Deleting a node
struct node *deleteNode(struct node *root, int key)
{
  if (root == NULL) // Base case
    return root;
  if (key < root->key) // Recur down the tree
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  // If the key is the same as root's key, then this is the node to be deleted
  else
  {
    if (root->left == NULL)
    { // node with only one child or no child
      struct node *temp = root->right;
      delete root;
      return temp;
    }
    else if (root->right == NULL)
    {
      struct node *temp = root->left;
      delete root;
      return temp;
    }

    // node with two children: Get the inorder successor (smallest in the right subtree)
    struct node *temp = minValueNode(root->right);

    // Copy the inorder successor's content to this node
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

// Driver code
int main()
{
  struct node *root = NULL;

  int operation;
  int operand;
  cin >> operation;

  while (operation != -1)
  {
    switch (operation)
    {
    case 1: // insert
      cin >> operand;
      root = insertNode(root, operand);
      cin >> operation;
      break;
    case 2: // delete
      cin >> operand;
      root = deleteNode(root, operand);
      cin >> operation;
      break;
    default:
      cout << "Invalid Operator!\n";
      return 0;
    }
  }

  traverseInOrder(root);
}
