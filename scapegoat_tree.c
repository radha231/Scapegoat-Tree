#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<time.h>
#include<string.h>
int count = 0, n = 0, q = 0, size1 = 0,flag=0;
int size2;
float alpha=0.8500;


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
int * acommand(char name[20]){
    int i=0,j;
    int ch;//char name[20];
     int * A;FILE * fp;
    //printf("Enter the text file name along with extension '.txt': ");
    //scanf("%s",name);
    fp=fopen(name,"r");                     // the give file is opened only to read the values.
    if(fp==NULL){
        printf("Error file opening.\n");
    }
    else{
        while(!feof(fp)){                     // Values are read until the end of file is reached , which is specified by 'feof'.
            fscanf(fp,"%d",&ch);i++;}
        A=(int *)malloc(i*sizeof(int));
        rewind(fp);j=0;
        while(!feof(fp)){
            fscanf(fp,"%d",&ch);
            A[j]=ch;
            j++;    
        }
        fclose(fp);
    }
    printf("The Aay size is :%d\n",i);
    size2=i;
    return A;
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
    //printf("end \n");
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
        
        
        //printf("psize=%d\n",size1);
        arr[size1] = x->value;
        //printf("aaa %d \n", arr[size1]);
        size1++;
        

        // printf("posorder A[%d]=%d \n",size1,A[size1-1]);
        //A = (int *)realloc(A, (size1) * sizeof(int));
       
        x->right = NULL;
        x->left = NULL;
        x->parent = NULL;
        x = NULL;
        free(x);
    }

}
void BST_build(int k, node *groot)
{
    //printf("mid value: %d\n", k);
    if(flag==1){
        groot=groot1;
        //flag = 0;
    }
    if(groot==NULL){
        //printf("helooo?\n");
        groot = allocate(k);
        //printf("groot=%d\n",groot->value);
        groot1 = groot;
    }
    //printf("display:");
    //inorder(groot);
    else{
    node *u;
    //printf("loop1\n");
    //u=(node*)malloc(sizeof(node));
    u=allocate(k);
    node *pre=NULL;
    //printf("loop2\n");
    //printf("groot_value %d",u->value);

    while (groot != NULL)
    {
        //printf("upgroot_value %d\n u_value %d\n",groot->value,u->value);

        if (u->value < groot->value)
    {
        //printf("HELLO WORLD");

        //groot->left = BST_build(k, groot->left,p);
        pre=groot;
        groot=groot->left;
         //printf("groot_value %d,radha %d",groot->value,pre->value);
         //exit(-1);
    }
    else if (u->value > groot->value)
    {
        //groot->left = BST_build(k, groot->left,p);
       // printf("HELLO WORLDghjghjx");
        pre=groot;
         groot=groot->right ;
         //printf("loop6\n");
    }
    //printf("loop634\n");
    } 
    //printf("loop67\n");
    //printf("groot_value %d", groot->value);
    if(u->value<pre->value)
    pre->left=u;
    else if(u->value>pre->value)
    pre->right=u;
    u->parent = pre;
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
    //printf("DISPLAY: ");
    //inorder(groot);
    //printf("\n");
    }
}
void split_array(int *arr, int s, int e, node *groot)
{
    int m=1;
    //printf("asra1 %d\n",arr[m]);
    if (s <= e)
    {
        int mid =s+(e-s)/2;
        //printf("m%d %d\n",mid,A[mid]);
        
        //printf("mid %d",arr[mid]);
       // printf("m%d %d\n",mid,A[mid]);
        
        BST_build(arr[mid], groot);
        //printf("mid %d",arr[mid]);
        split_array(arr, s, mid-1, groot);
        split_array(arr, mid+1, e, groot);
    }
}
/*void qsort(int * A,int size){

}*/
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
{    printf("printed array\n");
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
    //groot = (node *)malloc(sizeof(node));
    // printf("hello\n");

    postorder(arr, x);
   // printf("x %d\n\n", x->value);
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
        //print_array(arr, size1);
        /*printf("jyoti\n");
        inorder(root);*/
        // printf("size1=%d\n",size1);
        // printf("size=%d,sizeof(A)=%d,sizeof(A[0])=%d\n",size1,sizeof(A),sizeof(A[0]));
        // print_Aay(A,size1);
        // printf("unsorted\n");
        // qsort(A,size1,sizeof(int),comp);
        int l = 0;
        int r = size1 - 1;
        // printf("size1=%d\n",size1);
        mergeSort(arr, l, r);
        // printf("sorted\n");
       // printf("\n");
        // print_Aay(A, size1);
        split_array(arr, 0, size1 - 1, groot);
        free(arr);
        arr=NULL;
}
void rebuilding(node * x){
    //printf("rebuilding\n");
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
        //printf("size1=%d\n",size1);
        mergeSort(ar, l, r);
       // printf("sorted\n");
        //printf("\n");
      // print_array(ar, size1);
        split_array(ar, 0, size1 - 1, groot);
        //printf("thfgdjjjjjjj\n");
        flag = 0;
       //inorder(groot1);
}
node* add(int k, node *root)
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

    //float c = fabs(log(q) / (log(2) - log(3)));

    float c = fabs(log(q) / (log(alpha)));

    //printf("q=%d,c=%f,depth=%d\n", q, c,depth);
    if (depth > c)
    {
        node *w = findscapegoat(x);
        //printf("w=%d\n", w->value);
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
    strcpy(name,"sorted.txt");
    A=acommand(name);
    /*for(i=0;i<size2;i++){
        printf("%d ",A[i]);
    }*/
    printf("size2=%d\n",size2);
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
             
            t = clock(); 
            /*printf("Enter the value to insert:");
            scanf("%d", &k);
            if (root == NULL)
            {
                root = allocate(k);
                n++;
                q++;
            }
            else
            {   printf("\nelse%d \n",k);
                root=add(k, root);
            }*/
           for(i=0;i<size2;i++){
                k=A[i];
            if (root == NULL)
            {
                root = allocate(k);
                n++;
                q++;
            }
            else
            {   //printf("\nelse%d \n",k);
                root=add(k, root);
            }
            }
            t = clock() - t; 
             time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
 
            printf("Scapegoat insertion  took %f seconds to execute \n", time_taken); 
            free(A);
            A=NULL;
            break;
        case 2:
            inorder(root);
            printf("\n");
            break;
        case 3:
            
            //printf("enter data: ");
            //scanf("%d", &data);
             strcpy(name,"sorteds.txt");
            A=acommand(name);
            for(i=0;i<size2;i++){
                printf("%d ",A[i]);
            }
            printf("\n");
            t = clock(); 
           for(i=size2-1;i>=0;i--){
                data=A[i];
                //printf("data=%d\n",data);
            root=deleteNode(root, data);
            n--;
            //printf("back %d\n",root->value);
            //inorder(root);
           // printf(" n %d\n", n);
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
            //if(i>3)
            //return 0;
            }
             t = clock() - t; 
             time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
 
            printf("Scapegoat deletion  took %f seconds to execute \n", time_taken); 
            
            break;
        case 4:{
                printf("enter key to be  searched\n");
                scanf("%d", &data);
                t = clock();
                search(root, data);
                if (search(root, data) == NULL)

                printf("%d not found\n", data);
                else
                printf("%d found\n", data);
                t = clock() - t; 
                 time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
 
                printf("scapegoat search  took %f seconds to execute \n", time_taken); 
                break;
        }
        case 5 :  printf("Height of tree is %d", maxDepth(root)); break;
        default:
            printf("Wrong choice!");
        }
    }
    free(A);
    A=NULL;
}
