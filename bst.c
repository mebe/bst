/*
 * bst.c - a simple binary search tree implementation in C
 * 
 * This file contains a binary search tree implementation. The tree's nodes use
 * strings as keys and integers as data stored in the node. A new node isn't
 * inserted into the tree if an existing node happens to have the same key -
 * in this situation we instead increase the existing node's data integer by one.
 * 
 * Only insertion, inorder-tree-walk and postorder-tree-walk algorithms have
 * been implemented - no search or deletion algorithms are available.
 * 
 * Functions defined in this file:
 *     BstNode *bst_newNode(char *key, int data);
 *     BstTree *bst_newTree();
 *     void bst_inorderTreeWalkFromNode(BstNode *node, void (*callback)(BstNode*))
 *     void bst_inorderTreeWalk(BstTree *tree, void (*callback)(BstNode*));
 *     void bst_postorderTreeWalkFromNode(BstNode *node, void (*callback)(BstNode*))
 *     void bst_postorderTreeWalk(BstTree *tree, void (*callback)(BstNode*));
 *     void bst_destroyNode(BstNode *node);
 *     void bst_destroyTree(BstTree *tree);
 *     void bst_insertOrUpdate(BstTree tree*, BstNode *newNode);
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "bst.h"

/*
 * Creates a binary search tree node with the given key and data.
 * The key is expected to be a pointer to a string and data an integer.
 * A copy of the key is created for the node instead of using the original.
 * 
 * Returns a pointer to the freshly created node.
 */
BstNode *bst_newNode(char *key, int data)
{
   BstNode *node;
   char *copyOfKey;
   
#ifndef NDEBUG
   printf("Creating new node with key: '%s'\n", key);
#endif
   
   /* Allocate memory for the node itself */
   if ((node = calloc(1, sizeof(BstNode))) == NULL) 
     {
	fprintf(stderr, "Failed to allocate memory for a new node\n");
	exit(EXIT_FAILURE);
     }
   
   /* Allocate memory for the key in the node - we want a copy of the string rather than just a pointer to the original */
   if ((copyOfKey = calloc(strlen(key)+1, sizeof(char))) == NULL) 
     {
	fprintf(stderr, "Failed to allocate memory for the key of the new node\n");
	exit(EXIT_FAILURE);
     }
   
   strcpy(copyOfKey, key);
   
#ifndef NDEBUG
   printf("Memory allocated and copy of key created succesfully\n");
#endif
   
   /* Set default values */
   node->parent = NULL;
   node->left   = NULL;
   node->right  = NULL;
   node->key    = copyOfKey;
   node->data   = data;
   
#ifndef NDEBUG
   printf("Created new node\n");
#endif
   
   return node;
}

/*
 * Creates a new binary search tree with no nodes.
 *
 * Returns a pointer to the freshly created tree.
 */

BstTree *bst_newTree()
{
   BstTree *tree;

#ifndef NDEBUG
      printf("Creating new empty tree\n");
#endif
   
   /* Allocate memory for the tree */
   if ((tree = calloc(1, sizeof(BstTree))) == NULL)
     {
	
	fprintf(stderr, "Failed to allocate memory for a new tree\n");
	exit(EXIT_FAILURE);
     }
   
#ifndef NDEBUG
      printf("Memory allocated succesfully\n");
#endif
   
   /* Default root of the tree to null */
   tree->root = NULL;
   return tree;
}

/*
 * Inorder-tree-walk algorithm for binary search tree with a small twist.
 * This function receives a pointer to the node we're stepping into as first parameter
 * and a callback (ie. function pointer) as second parameter. The callback
 * is called in place of the usual action in the step.
 * 
 * Doesn't return anything.
 */
void bst_inorderTreeWalkFromNode(BstNode *node, void (*callback)(BstNode*))
{
   if (node) /* Don't wanna try stepping in a null node */
     {

#ifndef NDEBUG
	printf("Stepped into a node with key: '%s'\n", node->key);
#endif
	
	/* Basic inorder-tree-walk with a callback (function pointer) as action performed on the node */
	bst_inorderTreeWalkFromNode(node->left, callback);
	callback(node);
	bst_inorderTreeWalkFromNode(node->right, callback);
     }
}

/*
 * A convenience function to start the inorder-tree-walk from the root
 * of the tree. Expects a pointer to a tree as first parameter and the 
 * callback as second parameter.
 * 
 * See bst_inorderTreeWalkFromNode
 * 
 * Doesn't return anything.
 */
void bst_inorderTreeWalk(BstTree *tree, void (*callback)(BstNode*)) 
{
#ifndef NDEBUG
   printf("Going to inorder-tree-walk...\n");
#endif
   /* Start walk from the root of the tree */
   bst_inorderTreeWalkFromNode(tree->root, callback);
}

/*
 * A function that walks through the tree in postorder. Implemented similarly
 * to bst_inorderTreeWalkFromNode.
 * 
 * See bst_inorderTreeWalkFromNode
 * 
 * Doesn't return anything
 */
void bst_postorderTreeWalkFromNode(BstNode *node, void (*callback)(BstNode*)) 
{
   if (node) /* Don't wanna try stepping in a null node */
     {	
#ifndef NDEBUG
	printf("Stepped into a node with key: '%s'\n", node->key);
#endif
	
	/* Basic postorder-tree-walk with a callback (function pointer) as action performed on the node */
	bst_postorderTreeWalkFromNode(node->left, callback);
	bst_postorderTreeWalkFromNode(node->right, callback);
	callback(node);
     }
}

/*
 * A convenience function to start the postorder-tree-walk from the root
 * of the tree. Expects a pointer to a tree as first parameter and the
 * callback as second parameter.
 *
 * See bst_postorderTreeWalkFromNode
 *
 * Doesn't return anything.
 */
void bst_postorderTreeWalk(BstTree *tree, void (*callback)(BstNode*))
{
   
   #ifndef NDEBUG
      printf("Going to postorder-tree-walk...\n");
   #endif
      /* Start walk from the root of the tree */
      bst_postorderTreeWalkFromNode(tree->root, callback);
}

/*
 * Destroys a binary search tree node by freeing all the memory
 * reserved for it. A pointer to the node to be destroyed is
 * expected as parameter.
 * 
 * This doesn't mean we're removing the node from a tree
 * (ie. not a binary search tree delete algrotihm)!!
 * 
 * Doesn't return anything.
 */
void bst_destroyNode(BstNode *node) 
{
#ifndef NDEBUG
   printf("Destroying node with key '%s'\n", node->key);
   printf("Freeing the memory reserved for the key\n");
#endif

   free(node->key);

#ifndef NDEBUG
   printf("And freeing the memory reserved for the node itself\n");
#endif

   free(node);

#ifndef NDEBUG
   printf("That node is no more...\n");
#endif
}

/*
 * Destroys a complete binary search tree by destroying
 * its nodes and then freeing the tree itself. Parameter is
 * a pointer to the tree we're destroying.
 * 
 * See bst_postorderTreeWalk, bst_destroyNode
 * 
 * Doesn't return anything.
 */
void bst_destroyTree(BstTree *tree) 
{
#ifndef NDEBUG
   printf("Destroying tree by walking through it\n");
#endif

   /* Walk through in postorder with bst_destryNode as action performed on each node */
   bst_postorderTreeWalk(tree, bst_destroyNode);

#ifndef NDEBUG
   printf("All nodes have been destroyed, so freeing the memory reserved for the tree itself\n");
#endif

   free(tree);

#ifndef NDEBUG
   printf("That tree is history!\n");
#endif
}

/*
 * Insert a new node to the binary search tree or if the key
 * already exists in the tree, updates the data of the existing
 * node. First parameter is a pointer to the tree we're dealing 
 * with and the second one a pointer to the new node we're trying
 * to insert.
 * 
 * Doesn't return anything.
 */
void bst_insertOrUpdate(BstTree *tree, BstNode *newNode) 
{
   BstNode *node;
   int cmpResult;
   
   /* I hope you're not trying to insert a null node! */
   assert(newNode != NULL);
   
#ifndef NDEBUG
   printf("Trying to insert node with key: '%s'\n", newNode->key);
   printf("Starting from the root of the tree\n");
#endif

   node = tree->root;
   
#ifndef NDEBUG
   printf("Checking if the tree happens to be empty... ");
#endif

   if (!node)
     {

#ifndef NDEBUG
	printf("Oh, yes - setting node as root\n");
#endif

	tree->root = newNode;
	return;
     } 
   else 
     {

#ifndef NDEBUG
	printf("Nope, scanning for the right place for the node...\n");
#endif
	
	while (node) 
	  {
	     newNode->parent = node;

#ifndef NDEBUG
	     printf("Comparing keys: '%s' with '%s'... ", newNode->key, node->key);
#endif

	     cmpResult = strcmp(newNode->key, node->key);
	     if (cmpResult < 0)
	       {

#ifndef NDEBUG
		  printf("Was smaller, going left\n");
#endif

		  node = node->left;
	       }
	     else if (cmpResult > 0) 
	       {

#ifndef NDEBUG
		  printf("Was larger, going right\n");
#endif

		  node = node->right;
	       }
	     else 
	       {

#ifndef NDEBUG
		  printf("Was exact match! Updating existing node instead of inserting new\n");
#endif
		  
		  node->data++;
		  
#ifndef NDEBUG
		  printf("Destroying the (now useless) new node\n");
#endif
		  bst_destroyNode(newNode);
		  
		  /* No node to insert any longer, so let's return */
		  return;  
	       }
	  }

#ifndef NDEBUG
	printf("Inserting the new node... ");
#endif
	
	/* The parent of our new node can't be null at this point */
	assert(newNode->parent != NULL);
	
	/* Let's check where we needed to insert the node again... */
	if (cmpResult < 0)
	  {

#ifndef NDEBUG
	     printf("On the left of the parent\n");
#endif
	     
	     newNode->parent->left = newNode;
	  }
	else 
	  {

#ifndef NDEBUG
	     printf("On the right of the parent\n");
#endif
	     
	     newNode->parent->right = newNode;
	  }
     }
}
