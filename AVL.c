#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int size1;
struct NODE{
      int data;
      int h;
      struct NODE* left;
      struct NODE* right;
      struct NODE * p;
};
typedef struct NODE node;  
int flag=0;


int bfact(node * x){   
     node * y=x->left;int b1,b2;
     if(y==NULL){
        b1=0;
     }
     else{
     b1=(y->h)+1;}
     y=x->right;
     if(y==NULL){
        b2=0;
     }
     else{
     b2=(y->h)+1;}
     return (b1-b2);
}

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get height of the tree
int height1(node *N)
{
	if (N == NULL)
		return 0;
	return N->h;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
	return (a > b)? a : b;
}

/* Given a non-empty binary search tree, return the
node with minimum key value found in that tree.
Note that the entire tree does not need to be
searched. */
node * minValueNode(node* node1)
{
	node * current = node1;

	/* loop down to find the leftmost leaf */
	while (current->left != NULL)
		current = current->left;

	return current;
}


node *rightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->h = max(height1(y->left), height1(y->right))+1;
    x->h = max(height1(x->left), height1(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
node *leftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->h = max(height1(x->left), height1(x->right))+1;
    y->h = max(height1(y->left), height1(y->right))+1;
 
    // Return new root
    return y;
}
 // Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
node* deleteNode(node* root, int key)
{
	// STEP 1: PERFORM STANDARD BST DELETE

	if (root == NULL)
		return root;

	// If the key to be deleted is smaller than the
	// root's key, then it lies in left subtree
	if ( key < root->data )
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the
	// root's key, then it lies in right subtree
	else if( key > root->data )
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is
	// the node to be deleted
	else
	{
		// node with only one child or no child
		if( (root->left == NULL) || (root->right == NULL) )
		{
			node *temp = root->left ? root->left :
											root->right;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case
			*root = *temp; // Copy the contents of
							// the non-empty child
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder
			// successor (smallest in the right subtree)
			node* temp = minValueNode(root->right);

			// Copy the inorder successor's data to this node
			root->data = temp->data;

			// Delete the inorder successor
			root->right = deleteNode(root->right, temp->data);
		}
	}

	// If the tree had only one node then return
	if (root == NULL)
	return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
	root->h = 1 + max(height1(root->left),
						height1(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
	// check whether this node became unbalanced)
	int balance = bfact(root);

	// If this node becomes unbalanced, then there are 4 cases

	// Left Left Case
	if (balance > 1 && bfact(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case
	if (balance > 1 && bfact(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case
	if (balance < -1 && bfact(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case
	if (balance < -1 && bfact(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
void inorder(node * root){
    if(root){
    inorder(root->left);
    printf("%d ",root->data);
    inorder(root->right);
    }
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
node * insert1(int x,node * root){
      int flag=0,flag1=0,count;
      node * temp=root,*prev,*p1,*temp1;
      p1=(node*)malloc(sizeof(node));
      p1->data=x;
      p1->left=NULL;
      p1->right=NULL;
      p1->h=0;
      while(temp!=NULL){
      if((temp->data)>x){
              
              flag=1;
              prev=temp;
              temp=temp->left;
      }
      else{
        flag=0;
        prev=temp;
        temp=temp->right;
      }
      }
      p1->p=prev;
     if(flag==1)
     {
        prev->left=p1;
     }
     else{
        prev->right=p1;
     }
     temp=root;
     while(temp!=NULL){
        flag1=0;
        count=0;
        temp1=temp;
        while(temp1!=NULL){
        if((temp1->data)>x){
            temp1=temp1->left;
             if(flag1==0){flag1=1; temp=temp1;}
            count++;
        }
        else if((temp1->data)<x){
            temp1=temp1->right;
            if(flag1==0){flag1=1; temp=temp1;}
            count++;
        }
        else{
            break;
        }
        }
        
        if((temp->p->h)<count){
            temp->p->h=count;
        }
        if(count==0){temp=NULL;}
     }
     return p1;
}
void height(node * root,int x){
    node * temp,*temp1;
    int count,flag1;
    temp=root;
     while(temp!=NULL){
        flag1=0;
        count=0;
        temp1=temp;
        while(temp1!=NULL){
        if((temp1->data)>x){
            temp1=temp1->left;
             if(flag1==0){flag1=1; temp=temp1; }
            count++;
        }
        else if((temp1->data)<x){
            temp1=temp1->right;
            if(flag1==0){flag1=1; temp=temp1;}
            
            count++;}
        
        else{
            break;
        }
        }
       
       if(count==0){
        temp=NULL;
        }
       else{ 
        temp->p->h=count;}
        }
    }

node * rr(node * A,node *root,int x){
    node * p1=A->p,*B;
    B=A->right;
    A->p=B;
    if(p1!=NULL){
    if((p1->left)==A)
    {
        p1->left=B;
        B->p=p1;
    }
    else{
        p1->right=B;
        B->p=p1;
    }}
    else{
        B->p=NULL;
        root=B;
    }
    if((B->left)!=NULL){
       A->right=B->left;
       A->right->p=A;
       
    }
    else{
        A->right=NULL;
    }
    B->left=A;
    if(flag==0){
    A->h=(A->h)-2;
    
    height(root,x);}
   
   return root;
    
}
node * ll(node * A1,node * root,int x){
    node * p2,*B1;
    p2=A1->p;
    B1=A1->left;
    A1->p=B1;
    if(p2!=NULL){
    if((p2->left)==A1)
    {
        p2->left=B1;
         B1->p=p2;
    }
    else{
        p2->right=B1;
         B1->p=p2;
    }}
    else{
        B1->p=NULL;
        root=B1;
    }
    
    if((B1->right)!=NULL){
       A1->left=B1->right;
       A1->left->p=A1;
    }
    else{
        A1->left=NULL;
   }
    B1->right=A1;
    if(flag==0){
    A1->h=(A1->h)-2;
    height(root,x);}
   
    return root;
}
node * lr(node * A,node * root,int x){
    int flag2=0;
    flag=1;
    node * C,*B,*temp;
    B=A->left;
    if(B->right->data!=x){
        flag2=1;
    }
    root=rr(B,root,x);
    C=A->left;
    root=ll(A,root,x);
    A->h=A->h-2;
    if(flag2==0){
    height(root,B->data);
     B->h=(B->h)-1;
     }
    else{
        height(root,x);
    temp=root;
    int b;
    while(temp!=NULL){
        if(temp->data==B->data){
            b=B->data;
        }
        else{
            b=x;
        }
         if((temp->data)>x){
            temp=temp->left;
         }
         else if((temp->data)<x){
            temp=temp->right;
         }
        
         else{
            break;
         }

    }
    if(b!=B->data){
          B->h=(B->h)-1;
    }
    }
    return root;
    
}
node * rl(node * A,node * root,int x){
    int flag2=0;
    flag=1;
    node * C,*B,*temp;
    B=A->right;
    if(B->left->data!=x){
        flag2=1;
    }
    root=ll(B,root,x);
    C=A->right;
    root=rr(A,root,x);
    A->h=A->h-2;
    if(flag2==0){
    height(root,B->data);
    B->h=(B->h)-1;}
    else{
        height(root,x);
        temp=root;
    int b;
    while(temp!=NULL){
        if(temp->data==B->data){
            b=B->data;
        }
        else{
            b=x;
        }
         if((temp->data)>x){
            temp=temp->left;
         }
         else if((temp->data)<x){
            temp=temp->right;
         }
        
         else{
            break;
         }

    }
    if(b!=B->data){
          B->h=(B->h)-1;
    }
    }
  return root;
}
node * insert(int x,node * root){
    node * n,*prev,*A,*temp1,*temp,*B;flag=0;
    char R[2];
    int b,count,flag1;
    n=insert1(x,root);
    n=n->p;
    do{
    b=bfact(n);
    prev=n;
    n=n->p;
    }while((b==1 || b==-1 || b==0)&&(n!=NULL));

    if (n==NULL && ((b==1) || (b==0) || (b==-1)) ){ // if the tree is still AVL tree after the insertion
        return root;
    }
    A=prev;
    if((A->data)>x){
        prev=prev->left;
        R[0]='L';
       if((prev->data)>x){
        prev=prev->left;
        R[1]='L';
        root=ll(A,root,x);
         }
        else{
        prev=prev->right;
        R[1]='R';
         root=lr(A,root,x);
        }
    }
    else{
        prev=prev->right;
        R[0]='R';
        if((prev->data)>x){
        prev=prev->left;
        R[1]='L';
         root=rl(A,root,x);
        }
        else{
        prev=prev->right;
        R[1]='R';
         root=rr(A,root,x);
        }
    }
   
     return root;
}

void preorder(node * root){
    if(root){
    printf("%d ",root->data);
    preorder(root->left);
    preorder(root->right);
    }
}

void search(int x, node * root){
    node * temp=root;
    
    while(temp!=NULL)
    {  
      if((temp->data)>x){
              temp=temp->left;
      }
      else if((temp->data)<x){
        temp=temp->right;
      }
      else{
        break;
      }
      }
      if(temp==NULL){
        printf("Not present");
        return;
      }
     // printf("Balance Factor of %d is %d\n",x,bfact(temp));
      //printf("Height of %d in AVL tree is %d",x,temp->h);
     
}
int main(){
    clock_t t; 
    int * arr;
    node * root,*root1;int i,x;
    char c[2],e;
    root=(node*)malloc(sizeof(node));
    root->data=0;
    root->p=NULL;
    root->left=NULL;
    root->right=NULL;
    root->h=0;
    
    do{
      printf("Enter your choice:");
      scanf("%2s",&c);
      switch(c[0]){
        case 'i':
                printf("Element to be inserted:");
                scanf("%d",&x);
                root=insert(x,root);
                break;
        case 's':
                printf("Enter data you want to search:");
                scanf("%d",&x); 
                 search(x,root);
                 break;
        case 'p':printf("Inorder\n");
                 inorder(root);
                 printf("\n");
                 printf("Preorder\n");
                 preorder(root);break;
        case 'd':printf("Height of tree is %d", maxDepth(root)); break;
        case 'r':
               printf("Element to be deleted:");
                scanf("%d",&x);
                root = deleteNode(root, x);
                break;
        default :
           if(c[0]!='q'){
            printf("wrong choice!");
        }
    
      }
    }while(c[0]!='q');
}
