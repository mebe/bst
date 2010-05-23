/*
 * bst.h - a simple binary search tree implementation in C
 * 
 * Header file for bst.c.
 * 
 */
#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

/*
 * A node in the binary search tree. Has pointers
 * to its parent and both childs. Also contains
 * a pointer to the string used as key and
 * the data integer
 */
typedef struct BstNode
{
   struct BstNode *parent;
   struct BstNode *left;
   struct BstNode *right;
   char *key;
   int data;
} BstNode;

/*
 * A binary search tree. Contains a pointer
 * to the root node of the tree
 */
typedef struct BstTree 
{
   BstNode *root;
} BstTree;

/* Function prototypes for binary search tree: */

struct BstNode* bst_newNode(char*, int);
struct BstTree* bst_newTree(void);
void bst_inorderTreeWalk(struct BstTree*, void(*) (BstNode*));
void bst_inorderTreeWalkFromNode(struct BstNode*, void(*) (BstNode*));
void bst_postorderTreeWalk(struct BstTree*, void(*) (BstNode*));
void bst_postorderTreeWalkFromNode(struct BstNode*, void(*) (BstNode*));
void bst_destroyNode(struct BstNode*);
void bst_destroyTree(struct BstTree*);
void bst_insertOrUpdate(struct BstTree*, struct BstNode*);
  
#endif
