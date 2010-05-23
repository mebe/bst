/*
 * sl.c - Sanalaskuri
 * 
 * Sanalaskuri is a word counting program that counts number of
 * occurences of words in the given input stream. A word is defined as being
 * at least two consecutive alphabetical characters as recognized by
 * C's standard isalpha()-implementation.
 * 
 * The program accepts up to two command line parameters. First one
 * defines the input file to be used and the second one the output file.
 * If the second one is omitted, stdout will be used for output.
 * If the first one is omitted, stdin will be used for input.
 *
 * Functions defined in this file:
 *     int main(int argc, char *argv[])
 *     void printNode(BstNode *node)
 * 
 * Dependencies:
 *   The implementation of sl depends on the existence of bst.c and bst.h.
 *   The binary search tree implementation provided by these files is used
 *   to store the words found and their counts.
 * 
 *   Functions accessed from bst:
 *     BstNode *bst_newNode(char *key, int data);
 *     BstTree *bst_newTree();
 *     void bst_inorderTreeWalk(BstTree *tree, void (*callback)(BstNode*));
 *     void bst_destroyTree(BstTree *tree);
 *     void bst_insertOrUpdate(BstTree tree*, BstNode *newNode);
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "bst.h"
#include "sl.h"

/* This needs to be accessible globally from all the functions */
FILE *output;

/*
 * The main program for sl.
 * 
 * Returns exit status.
 */
int main(int argc, char *argv[]) 
{
   FILE *input = stdin;
   char word[MAX_WORD_LENGTH+1];
   int charCounter = 0;
   int c;
   BstTree *tree;
   BstNode *node;
   
   /* Default output to stdout */
   output = stdout; 
   
   tree = bst_newTree();
   
   /* Let's make sure the tree really is empty */
   assert(tree->root == NULL); 
   
   /* Let's check for command line parameters */
   if (argc == 1)
     {
#ifndef NDEBUG
	printf("Using stdin and stdout\n");
#endif
     }
   else
     {
	/* We want to use first command line parameter as input file */

#ifndef NDEBUG
	printf("Trying to open '%s' for reading\n", argv[1]);
#endif

	if ((input = fopen(argv[1], "r")) == NULL) 
	  { 
	     fprintf(stderr, "Error opening ");
	     perror(argv[1]);
	     bst_destroyTree(tree);
	     return EXIT_FAILURE;
	  }

#ifndef NDEBUG
	printf("Input file opened succesfully\n");
#endif

	if (argc > 2)
	  {
	     /* We also have a second command line parameter so we'll use that for output. Rest are ignored. */

#ifndef NDEBUG
	     printf("Trying to open '%s' for writing\n", argv[2]);
#endif

	     if ((output = fopen(argv[2], "w")) == NULL)
	       {
		  fprintf(stderr, "Error opening ");
		  perror(argv[2]);
		  bst_destroyTree(tree);
		  return EXIT_FAILURE;
	       }
	  }
	
#ifndef NDEBUG
	else 
	  {
	     /* We didn't have a second command line parameter, so let's default to stdout. */
	     printf("Using stdout\n");
	  }
	printf("Output file opened succesfully\n");
	printf("Let's scan the input file...\n");
#endif
	
     }
   
   /* Read a character at a time... */
   while ((c = fgetc(input)) != EOF)
     {
	/*... and see if it's alphabetical */
	if (isalpha(c))
	  {
	     if (charCounter < MAX_WORD_LENGTH)
	       /* If the word is longer than the maximum word length, we just ignore the rest of it. */
	       { 
		  
		  /* Store the letter. */
		  
#ifndef NDEBUG
		  printf("%c...", c);
#endif
		  
		  word[charCounter] = c;
		  charCounter++;
	       }
#ifndef NDEBUG
	     else 
	       {
		  printf("Word is unfortunately too long, ignoring letter...");
	       }
	     
#endif
	  }
	else 
	  {
	     /* Character wasn't alphabetical so end the word and reset the counter */ 
	     word[charCounter] = '\0';
	     charCounter = 0;
	     
#ifndef NDEBUG
	     printf("\nGot word: '%s'\n", word);
#endif
	     
	     /* Words need to be atleast two characters long */
	     if (strlen(word) < 2) 
	       {
		  
#ifndef NDEBUG
		  printf("Too short, skipping\n");
#endif		       
		  
	       }
	     else
	       {
		  /* Create a new BST node with the word as key and 1 as data */
		  node = bst_newNode(word, 1);

		  /* Make sure the node has correct data in it */
		  assert(node->parent == NULL && node->left == NULL && node->right == NULL && node->data == 1 && (strcmp(node->key, word) == 0));

#ifndef NDEBUG
		  printf("Trying to update the tree...\n");
#endif

		  bst_insertOrUpdate(tree, node);
		  
		  /* Under no circumstances can the root of the tree be null at this point anymore */
		  assert(tree->root != NULL);
	       }
	  }
     }
   
   if (ferror(input)) 
     {
	/* In case we have an error while reading the file instead of hitting EOF */
	perror("Error");
	bst_destroyTree(tree);
	return EXIT_FAILURE;
     }
   
#ifndef NDEBUG
   printf("Let's print the tree now, then. This will look ugly with all the debug information\n");
#endif
   
   /* call bst_inorderTreeWalk with the tree as parameter and printNode function as callback (function pointer) to print it out */
   bst_inorderTreeWalk(tree, printNode);
   
#ifndef NDEBUG
   printf("We're done here, let's get rid of that tree... ");
#endif
   
   bst_destroyTree(tree);
   
   /* Close the input and output files */
   
   if ((fclose(input)) == EOF) 
     {
	perror("Error");
	return EXIT_FAILURE;
     }

   if ((fclose(output)) == EOF) 
     {
	perror("Error");
	return EXIT_FAILURE;
     }
   
   return EXIT_SUCCESS;
}

/*
 * A callback function for bst_inorderTreeWalk. Tries to print
 * the node's key and data to the defined output stream.
 * 
 * Doesn't return anything.
 */
void printNode(BstNode *node)
{
   if ((fprintf(output, "%s: %d\n", node->key, node->data)) < 0) 
     {
	perror("Error");
	exit(EXIT_FAILURE);
     }
}
