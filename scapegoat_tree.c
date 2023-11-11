#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int count = 0, n = 0, q = 0, size1 = 0;
float al = 2 / 3; // 0 set again in rebuild
struct NODE
{
    int value;
    struct NODE *left;
    struct NODE *right;
    struct NODE *parent;
};
typedef struct NODE node;
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
    if (3 * sizec <= 2 * sizep)
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
        // printf("psize=%d\n",size1);
        arr[size1] = x->value;
        size1++;
        // printf("posorder arr[%d]=%d \n",size1,arr[size1-1]);
        //arr = (int *)realloc(arr, (size1) * sizeof(int));
        free(x);
    }
}
void BST_build(int k, node *groot)
{
    node *u;
    u=(node*)malloc(sizeof(node));
    u=allocate(k);
    node *pre;
    while(groot!=NULL)
    {
        if (u->value < groot->value)
    {
        //groot->left = BST_build(k, groot->left,p);
        pre=groot;
        groot=groot->left;
    }
    if (u->value > groot->value)
    {
        //groot->left = BST_build(k, groot->left,p);
        pre=groot;
         groot=groot->right ;
    }
    }
    if(u->value<pre->value)
    pre->left=u;
    if(u->value>pre->value)
    pre->right=u;
    /*if (u->value < groot->value)
    {
        groot->left = BST_build(k, groot->left,p);
        groot->left->parent = groot;
    }
    else
    {
        groot->right = BST_build(k, groot->right,p);
        groot->right->parent = groot;
    }*/
    
}
void split_array(int *arr, int s, int e, node *groot)
{
    int m=1;
    printf("asra1 %d\n",arr[m]);
    if (s < e)
    {
        int mid =s+(e-s)/2;
        //printf("m%d %d\n",mid,arr[mid]);
        
        printf("mid %d",arr[mid]);
       // printf("m%d %d\n",mid,arr[mid]);
        
        BST_build(arr[mid], groot);
        printf("mid %d",arr[mid]);
        split_array(arr, s, mid - 1, groot);
        split_array(arr, mid + 1, e, groot);
    }
}
/*void qsort(int * arr,int size){

}*/
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
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
{    printf("printed arr\n");
    for (int i = 0; i < size; i++)
    {
        printf(" %d ", arr[i]);
    }
    printf("\n");
}
void rebuild(node *x)
{

    size1 = 0;
    int *arr = (int *)malloc(sizeof(int)*1000);
    node *groot = x->parent;
    //groot = (node *)malloc(sizeof(node));
    // printf("hello\n");

    postorder(arr, x);
    print_array(arr, size1);
    // printf("size1=%d\n",size1);
    // printf("size=%d,sizeof(arr)=%d,sizeof(arr[0])=%d\n",size1,sizeof(arr),sizeof(arr[0]));
    // print_array(arr,size1);
    // printf("unsorted\n");
    // qsort(arr,size1,sizeof(int),comp);
    int l = 0;
    int r = size1 - 1;
    //printf("size1=%d\n",size1);
    mergeSort(arr, l, r);
    // printf("sorted\n");
    printf("\n");
   //print_array(arr, size1);
    split_array(arr, 0, size1 - 1, groot);
}
void add(int k, node *root)
{
    //printf("yes\n");
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
    // depth++;
    x->parent = prev;
    //printf("depth=%d\n", depth);

    float c = fabs(log(q) / (log(2) - log(3)));
    printf("q=%d,c=%f\n", q, c);
    if (depth > c)
    {
        node *w = findscapegoat(x);
        printf("w=%d\n", w->value);
        rebuild(w);
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
int main()
{
    node *root = NULL;
    int c, k;
   
    while (1)
    {
        printf("Enter your choice\n");
        printf("1:INSERT\n");
        printf("2:TRAVERSAL\n");
        printf("3:EXIT\n");
         
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
                add(k, root);
            }
            break;
        case 2:
            inorder(root);
            printf("\n");
            break;
        default:
            printf("Wrong choice!");
        }
    }
}
