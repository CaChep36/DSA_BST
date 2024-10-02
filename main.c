#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    struct Node *left;
    int data;
    struct Node *right;
} Node;

void Create_Node(Node **node, int data)
{
    *node = (Node *)malloc(sizeof(Node));
    (*node)->data = data;
    (*node)->left = NULL;
    (*node)->right = NULL;
}

void Insert_Tree(Node **root, int data)
{
    if (data <= -1) 
    {
        return;
    }

    if (*root == NULL)
    {
        Create_Node(root, data);
    }
    else if (data < (*root)->data)
    {
        Insert_Tree(&((*root)->left), data);
    }
    else
    {
        Insert_Tree(&((*root)->right), data);
    }
}

void Pre_Order(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    Pre_Order(root->left);
    Pre_Order(root->right);
}

void Free_Tree(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    Free_Tree(root->left);
    Free_Tree(root->right);
    free(root);
}

int Search_Tree(Node *root, int target)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->data == target)
    {
        return 1;
    }

    if (target < root->data)
    {
        return Search_Tree(root->left, target);
    }
    else
    {
        return Search_Tree(root->right, target);
    }
}

Node *Find_Min(Node *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

void Delete_Node(Node **root, int key)
{
    if (*root == NULL)
    {
        return;
    }

    if (key < (*root)->data)
    {
        Delete_Node(&((*root)->left), key);
    }
    else if (key > (*root)->data)
    {
        Delete_Node(&((*root)->right), key);
    }
    else
    {
        if ((*root)->left == NULL)
        {
            Node *temp = (*root)->right;
            free(*root);
            *root = temp;
        }
        else if ((*root)->right == NULL)
        {
            Node *temp = (*root)->left;
            free(*root);
            *root = temp;
        }
        else
        {
            Node *temp = Find_Min((*root)->right);

            (*root)->data = temp->data;

            Delete_Node(&((*root)->right), temp->data);
        }
        return;
    }
}

int main()
{
    Node *Root = NULL;

    int n, k;
    scanf("%d %d", &n, &k); 

    if (n <= 0) 
    {
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        int a;
        scanf("%d", &a);     
        if (!Search_Tree(Root, a)) 
        {
            Insert_Tree(&Root, a);
        }
    }

    Delete_Node(&Root, k); 

    Pre_Order(Root); 
    Free_Tree(Root); 

    return 0;
}
