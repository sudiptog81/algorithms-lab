int max(int a, int b)
{
  return (a > b) ? a : b;
}

template <class T>
class Node
{
public:
  T data;
  int height;
  int balanceFactor;
  Node *left, *right, *parent;
  Node()
  {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 1;
    balanceFactor = 0;
  }
};

class AVLTree
{
public:
  Node<int> *root;

  int *array, index;

  AVLTree()
  {
    root = nullptr;
  }

  int getBalanceFactor(Node<int> *node)
  {
    if (node == nullptr)
      return 0;
    return height(node->right) - height(node->left);
  }

  Node<int> *rightRotate(Node<int> *y)
  {
    Node<int> *x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
      x->right->parent = y;
    x->parent = y->parent;

    if (y->parent == nullptr)
      root = x;
    else if (y == y->parent->right)
      y->parent->right = x;
    else
      y->parent->left = x;

    x->right = y;
    y->parent = x;

    y->height = 1 + max(height(y->left),
                        height(y->right));
    x->height = 1 + max(height(x->left),
                        height(x->right));

    x->balanceFactor = getBalanceFactor(x);
    y->balanceFactor = getBalanceFactor(y);

    return x;
  }

  Node<int> *leftRotate(Node<int> *x)
  {
    Node<int> *y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
      y->left->parent = x;
    y->parent = x->parent;

    if (x->parent == nullptr)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;

    y->left = x;
    x->parent = y;

    y->height = 1 + max(height(y->left),
                        height(y->right));
    x->height = 1 + max(height(x->left),
                        height(x->right));

    x->balanceFactor = getBalanceFactor(x);
    y->balanceFactor = getBalanceFactor(y);

    return y;
  }

  Node<int> *insert(int data, Node<int> *current)
  {
    Node<int> *temp;

    if (current == nullptr)
    {
      temp = new Node<int>;
      temp->data = data;
      return temp;
    }

    if (data < current->data)
    {
      current->left = insert(data, current->left);
      current->left->parent = current;
    }
    else
    {
      current->right = insert(data, current->right);
      current->right->parent = current;
    }

    current->height = 1 + max(height(current->left),
                              height(current->right));

    current->balanceFactor = getBalanceFactor(current);

    if (current->balanceFactor < -1 &&
        data < current->left->data)
      return rightRotate(current);

    if (current->balanceFactor > 1 &&
        data > current->right->data)
      return leftRotate(current);

    if (current->balanceFactor < -1 &&
        data > current->left->data)
    {
      current->left = leftRotate(current->left);
      return rightRotate(current);
    }

    if (current->balanceFactor > 1 &&
        data < current->right->data)
    {
      current->right = rightRotate(current->right);
      return leftRotate(current);
    }

    return current;
  }

  int height(Node<int> *current)
  {
    if (current == nullptr)
      return 0;

    else
    {
      int leftHeight = height(current->left);
      int rightHeight = height(current->right);

      if (leftHeight > rightHeight)
        return (leftHeight + 1);
      else
        return (rightHeight + 1);
    }
  }

  void storePostOrder(Node<int> *root)
  {
    if (root == nullptr)
      return;
    storePostOrder(root->left);
    storePostOrder(root->right);
    this->array[this->index++] = root->data;
  }

  int *getPostOrderArray(int size)
  {
    this->index = 0;
    this->array = new int[2 * size];
    storePostOrder(this->root);
    return array;
  }
};
