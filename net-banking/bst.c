#include<stdio.h>
#include<stdlib.h>

struct binary_search{
   int data;
   struct binary_search *left,*right;
};

typedef struct binary_search BST;

BST* create(int item)  // Creating a Node in tree
{
   BST *newnode=(BST*)malloc(sizeof(BST));
   newnode->data = item;
   newnode->left = NULL;
   newnode->right = NULL;
   return newnode;
}

BST* insert(BST *root, int item)    // Inserting Data into  Binary Search TREE
{
   if(root==NULL) return create(item);
   
   if(item < root-> data) // If Value is Less than ROOT Then Left Subtree
   {
      root->left = insert(root->left,item);
   }
   else if(item > root-> data) // If value is greater than ROOT Then Right Subtree
   {
      root->right = insert(root->right,item);
   }
   return root;
}
//---------------- TRAVERSAL -----------------
void inorder(BST *root)
{
   if (root != NULL)
   {
      inorder(root->left);
      printf("%d ", root->data);
      inorder(root->right);
   }
}

void preorder(BST *root)
{
   if (root != NULL)
   {
      printf("%d ", root->data);
      preorder(root->left);
      preorder(root->right);
   }
}

void postorder(BST *root)
{
   if (root != NULL)
   {
      postorder(root->left);
      postorder(root->right);
      printf("%d ", root->data);
   }
}

/* Given a non-empty BST, return the node with minimum
 value found in that tree. Note that the entire tree does not
need to be searched. */

BST * minValueNode(BST * node)
{
   BST *temp = node;
   // loop down to find the leftmost leaf 
    while(temp && temp->left != NULL )
        temp = temp->left;
    return temp;
}

//---------------- DELETE -----------------

/* Given a binary search tree and a key, this function deletes the key and returns the new root */
BST* deleteNode(BST *root, int item)
{
    // base case
    if(root == NULL) return root;
    
    // If the item is smaller than the root's key, then it lies in left subtree
    if(item < root->data)
    {
        root->left  = deleteNode(root->left, item);
    }
    // If the key is greater than the root's key, then it lies in right subtree
    else if(item > root->data)
    {
        root->right  = deleteNode(root->right, item);
    }
    // if item = root's value then This node is to be deleted
    else
    {
        // node with only one child or no child
        if(root->left == NULL)
        {
            BST *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            BST *temp = root->left;
            free(root);
            return temp;
        }
        
        // node with two children : Get the inorder successor (smallest in the right subtree)
        
        BST *temp = minValueNode(root->right);

        // Copy the inorder successor's content the node
        root->data = temp->data;
        
        // Delete the inorder successor because it is already swapped
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

//---------------- SEARCH -----------------

BST* search(BST *root, int item)
{
   if (root == NULL || root->data == item)  // If it is found
      return root;
   if (item > root->data) // if it is greater than root then search in right subtree
      return search(root->right, item);
   return search(root->left, item);
}

//----------------------------------------
int main()
{
   BST *root = NULL;  // Initially TREE is empty.
   root=insert(root,50);                  
   root=insert(root,42);                  
   root=insert(root,63);
   root=insert(root,58);
   root=insert(root,41);
   root=insert(root,23);
   root=insert(root,34);
   root=insert(root,5);
   root=insert(root,47);
   root=insert(root,26);
   root=insert(root,31);

   root=deleteNode(root,58);
   root=deleteNode(root,34);
   printf("\n Preorder : ");
   preorder(root);
   printf("\n Inorder ( Sorted Manner ): ");
   inorder(root);
   printf("\n Postorder : ");
   postorder(root);
   
   if(search(root , 23))
      printf("\n Element found");
   else
      printf("\n Element not found"); 
   return 0;
}
