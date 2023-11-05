# Scapegoat-Tree
Instructions for code 
1)How to Run?
  Open a C compiler or IDE that supports C code, such as GCC.
  Create a new C file and copy the provided code into the file.
  Save the file with a .c extension, for example scapegoat_tree.c.
2)What option would pop up?
  Choose an operation by entering the corresponding number
  1: Insert a value into the tree.
  2: Traverse the tree (prints elements in ascending order).
  3: Delete a value from the tree.
  4: Search for a value in the tree.
  5: Get the height of the tree.
  6: Exit the program.
3)EXAMPLE
 Choose the operation you want :
 1:INSERT
 2:TRAVERSAL
 3:DELETION
 4:SEARCH
 5:Depth
 6:EXIT
 Enter your choice : 1
 Enter the value to insert: 42

 Choose the operation you want :
 1:INSERT
 2:TRAVERSAL
 3:DELETION
 4:SEARCH
 5:Depth
 6:EXIT
 Enter your choice : 2
 The elements in ascending order are : 42

 ENTER YOUR CHOICE :
 1:INSERT
 2:TRAVERSAL
 3:DELETION
 4:SEARCH
 5:Depth
 6:EXIT
 Enter your choice : 3
 enter data: 42
 n= 0
 NO ELEMENTS LEFT

 Choose the operation you want :
 1:INSERT
 2:TRAVERSAL
 3:DELETION
 4:SEARCH
 5:Depth
 6:EXIT
 Enter your choice : 6
4)
Insertion (Operation 1):

When you choose this option, you'll be prompted to enter a value that you want to insert into the Scapegoat Tree.
After entering the value, the program will perform the insertion operation.
If it's the first element being inserted, it will become the root of the tree.
Subsequent insertions will follow the rules of a binary search tree (smaller values to the left, larger values to the right).

Traversal (Operation 2):

Choosing this option will print out the elements in ascending order. This is achieved through an inorder traversal of the tree.
For example, if you've inserted values 5, 3, 7, and 2, choosing this option will print 2 3 5 7.

Deletion (Operation 3):

You'll be prompted to enter the value you want to delete from the tree.
If the value is found in the tree, it will be removed.
If the tree becomes unbalanced after the deletion (i.e., 2*n < q condition is met), the tree will be rebuilt.

Search (Operation 4):

You can enter a value that you want to search for in the tree.
The program will then check if the value is present in the tree and let you know if it's found.

Depth (Operation 5):

This option will return the height or depth of the tree. The height of the tree is the longest path from the root to a leaf.

Exit (Operation 6):

Choosing this option will terminate the program.

