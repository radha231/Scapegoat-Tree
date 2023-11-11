#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
int count = 0, n = 0, q = 0, size1 = 0,flag=0;
int size2;
float alpha=(2.0)/(3.0);


struct NODE
{
    int value;
    struct NODE *left;
    struct NODE *right;
    struct NODE *parent;
};
typedef struct NODE node;
node *groot1=NULL;
void size(node *x)
{
    if (x)
    {
        size(x->left);
        count++;
        size(x->right);
    }
    return;
}

int maxDepth(node* temp)
{
    if (temp == NULL)
        return 0;
    else {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(temp->left);
        int rDepth = maxDepth(temp->right);
 
        /* use the larger one */
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

void inorder(node *root)
{
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
   
}
node *allocate(int k)
{
    node *x = (node *)malloc(sizeof(node));
    x->value = k;
    x->left = NULL;
    x->right = NULL;
    x->parent = NULL;
    return x;
}
node *findscapegoat(node *x)
{
    int sizec, sizep;
    count = 0;
    size(x);
    sizec = count;
    count = 0;
    x = x->parent;
    size(x);
    sizep = count;
    if ( sizec <= ((alpha) * sizep))
    {
        return findscapegoat(x);
    }
    return x;
}
void postorder(int *arr, node *x)
{
    if (x)
    {
        postorder(arr, x->left);
        postorder(arr, x->right);
        arr[size1] = x->value;
        size1++;
        x->right = NULL;
        x->left = NULL;
        x->parent = NULL;
        x = NULL;
        free(x);
    }

}
void BST_build(int k, node *groot)
{
    if(flag==1){
        groot=groot1;
    }
    if(groot==NULL){
        groot = allocate(k);
        groot1 = groot;
    }
    else{
    node *u;
    u=allocate(k);
    node *pre=NULL;
    while (groot != NULL)
    {
       if (u->value < groot->value)
    {
        pre=groot;
        groot=groot->left;

    }
    else if (u->value > groot->value)
    {
        pre=groot;
        groot=groot->right ;
    }
    } 
    if(u->value<pre->value)
    pre->left=u;
    else if(u->value>pre->value)
    pre->right=u;
    u->parent = pre;
    }
}
void split_array(int *arr, int s, int e, node *groot)
{
    int m=1;
    if (s <= e)
    {
        int mid =s+(e-s)/2;
        BST_build(arr[mid], groot);
        split_array(arr, s, mid-1, groot);
        split_array(arr, mid+1, e, groot);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp Aays
    int L[n1], R[n2];

    // Copy data to temp Aays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp Aays back into A[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i=i+1;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    // if there are any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}
void print_array(int *arr, int size)
{    
    for (int i = 0; i < size; i++)
    {
        printf(" %d ", arr[i]);
    }
    printf("\n");
}

void rebuild(node *x,node * root)
{
    
    size1 = 0;
    int *arr = (int *)malloc(sizeof(int)*20000);
    node *groot = x->parent;
    postorder(arr, x);
    if(x->value < groot->value){
        groot->left = NULL;
    }
    else{
        groot->right=NULL;
    }
    x->right = NULL;
        x->left = NULL;
        x->parent = NULL;
        x = NULL;
        free(x);
        int l = 0;
        int r = size1 - 1;
        mergeSort(arr, l, r);
        split_array(arr, 0, size1 - 1, groot);
        free(arr);
        arr=NULL;
}
void rebuilding(node * x){
        node *groot;
        flag = 1;
        size1 = 0;
        int *ar = (int *)malloc(sizeof(int) * 20000);
        postorder(ar, x);
        x->right = NULL;
        x->left = NULL;
        x->parent = NULL;
        x = NULL;
        free(x);
        groot = NULL;
        int l = 0;
        int r = size1 - 1;
        mergeSort(ar, l, r);
        split_array(ar, 0, size1 - 1, groot);
        flag = 0;
}
node* add(int k, node *root)
{
    
    n++;
    q++; // increase number of nodes n and counter q
    int depth = 0;
    node *temp = root;
    node *prev = temp;
    node *x;
    x = allocate(k);
    while (temp != NULL)
    {
        if (temp->value > k)
        {
            prev = temp;
            temp = temp->left;
            depth++;
        }
        else
        {
            prev = temp;
            temp = temp->right;
            depth++;
        }
    }
    if (prev->value < k)
    {
        prev->right = x;
    }
    else
    {
        prev->left = x;
    }
    
    x->parent = prev;
    float c = fabs(log(q) / (log(alpha)));
    if (depth > c)
    {
        node *w = findscapegoat(x);
        if(w->parent==NULL){
            rebuilding(root);
            root = groot1;
            groot1=NULL;
        }
        else{
        rebuild(w,root);}
    }
    return root;
}
node* deleteNode(node* root, int k)
{
    // Base case
    
    if (root == NULL)
        return root;
 
    // Recursive calls for ancestors of
    // node to be deleted
    if (root->value > k) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->value < k) {
        root->right = deleteNode(root->right, k);
        return root;
    }
 
    // We reach here when root is the node
    // to be deleted.
 
    // If one of the children is empty
    if (root->left == NULL) {
        node* temp = root->right;
        free(root);
        return temp;
    }
    else if (root->right == NULL) {
        node* temp = root->left;
        free(root);
        return temp;
    }
 
    // If both children exist
    else {
 
       node* succParent = root;
 
        // Find successor
        node* succ = root->right;
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }
 
        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;
 
        // Copy Successor Data to root
        root->value = succ->value;
 
        // Delete Successor and return root
        free(succ);
        return root;
    }
}
node* search(node* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->value == key)
        return root;
 
    // Key is greater than root's key
    if (root->value< key)
        return search(root->right, key);
 
    // Key is smaller than root's key
    return search(root->left, key);
}
 
int main()
{   double time_taken;
    node *root = NULL;
    int c=0, k;
    int * A,i;
    char name[20];
   int data;
   clock_t t; 
    while (c!=6)
    {
        printf("Enter your choice\n");
        printf("1:INSERT\n");
        printf("2:TRAVERSAL\n");
        printf("3:DELETION\n");
        printf("4:SEARCH\n");
        printf("5:Depth\n");
        printf("6:EXIT\n");
       scanf("%d", &c);
        switch (c)
        {
        case 1:
            printf("Enter the value to insert:");
            scanf("%d", &k);
            if (root == NULL)
            {
                root = allocate(k);
                n++;
                q++;
            }
            else
            {  
                root=add(k, root);
            }
            break;
        case 2:
            inorder(root);
            printf("\n");
            break;
        case 3:
            
            printf("enter data: ");
            scanf("%d", &data);
            root=deleteNode(root, data);
            n--;
            if(n==0){
                printf("NO ELEMENTS LEFT\n");
            }
            else if(2*n<q)
            {   
                rebuilding(root);
                root = groot1;
                groot1=NULL;
                q = n;
            }
            break;
        case 4:
                printf("enter key to be  searched\n");
                scanf("%d", &data);
                search(root, data);
                break;
        
        case 5 :  printf("Height of tree is %d", maxDepth(root)); break;
        default:
           if(c!=6)
            printf("Wrong choice!");
        }
    }
    free(A);
    A=NULL;
}
