#ifndef BST_H
#define BST_H

#include <stddef.h> /* size_t */

typedef enum {IN_ORDER, PRE_ORDER, POST_ORDER} traversal_t;

typedef struct bst bst_t;

/* returns: integer indicating the result of the action (0 for success and 1 for failure) */
typedef int (*action_function_t)(void *data, void *parameter);

/* returns: integer indicating the result of the comparison (0 for equal, negative if data1 is less than data2 and positive if data1 is greater than data2) */
typedef int (*compare_func_t)(const void *data1, const void *data2);

/* creates a new bst management structure */
bst_t *BstCreate(compare_func_t cmp_func);

/* destroys the bst by freeing memory associated with nodes */
void BstDestroy(bst_t *bst);

/* removes data element from the bst using */
void BstRemove(bst_t *bst,void *data);

/* inserts a new data element into the bst */
int BstInsert(bst_t *bst, const void *data);

/* calculates the height of the bst */
size_t BstHeight(const bst_t *bst);

/* counts number of nodes in the bst */
size_t BstSize(const bst_t *bst);

/* checks if the bst is empty */
int BstIsEmpty(const bst_t *bst);

/* searches for a data element in the bst  */
void *BstFind(bst_t *bst, const void *data);

/* traverses the bst and performs an action on each node based on the specified traversal mode */
int BstForEach(bst_t *bst, traversal_t mode, action_function_t action_func, void *param);



#endif /* BST_H*/
