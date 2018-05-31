#ifndef LINLINKLST_H
#define LINLINKLST_H

struct elemList {
    int data;
    struct elemList *next;
};

typedef struct elemList typeNodeList;
typedef typeNodeList *typeList;


/* 
 * Basic Operations on Linked Linear Structure (LLS)
 * =================================================
 * Operations that involve a single node, the first.
 */

/* Add a node at the first position of the LLS */
void addNode(typeList *lis, int n);

/* Remove the first node of the LLS */
void delNode(typeList *lis);

/*
 * Recursive Visits
 * ================
 * I - Operations that don't modify the LLS.
 */

/* Check if the LLS is empty */
int emptyList(typeList lis);

/* Write the node data type (integer) on the standard output */
void writeDataType(int data);

/* Write the node data type (integer) through a file */
void writeDataTypeF(FILE *f, int data);

/* Read the node data type (integer) from standard input*/
int readDataType(int *data);

/* Read the node data type (integer) through a file */
int readDataTypeF(FILE *f, int *data);

/* Write the LLS on the screen */
void writeNode(typeList lis);

/* Write the LLS on a file */
void writeNodeF(char *infile, typeList lis);

/* Recursive version of writeNodeF() */
void writeNodeF_r(FILE *outfile, typeList lis);

/* Read LLS from each node */
void readNode(typeList *lis); /* It doesn't work very well */

/* Find the integer 'val' within the LLS. It returns: 
   1 (true) if it exists;
   0 if doesn't exists or it is empty.
*/
int findinList(typeList lis, int val);

/* Find a node that contains the integer val inside. It returns:
   a pointer to the node (true);
   NULL otherwise.
*/
void findList(typeList lis, int val, typeList *res);

/* Compute how many nodes there are in the LLS */
int lengthList(typeList lis);

/* Compute how many occurences of the integer 'val' there are within the LLS */
int occurenceElemList(typeList lis, int val);

/*
 * Recursive Visits
 * ================
 * II - Functions that change the contents of the Linked Linear Structure (LLS)
 *      (They modify the integer field 'data')
 */

/* Find and replace the first occurence of the integer 'val' with 'new_val' */
void substElemList(typeList lis, int val, int new_val);

/* Find and replace all the occurences of the integer 'val' with 'new_val' */
void substAllElemList(typeList lis, int val, int new_val);

/* Build a new LLS of 'n' nodes */
void buildLS(typeList *lis, int n, int val);

/* Read and add all the elements (integers) */
void readAdd(typeList *lis);

/* Recursive version of readNodeF() */
void readNodeF_r(FILE *infile, int *val, typeList *lis);

/* Read LLS from a file */
void readNodeF(char *nfile, int *val, typeList *lis);

/* Copy LLS from source to destination */
void copyList(typeList lis_src, typeList *lis_dest);

#endif
