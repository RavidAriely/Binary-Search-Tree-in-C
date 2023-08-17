#include <stdlib.h>     /* malloc */
#include <assert.h>

#include "bst.h"

/* Struct:  bst_node 
 * --------------------
 *   data:  pointer to data stored in the node
 *   right: pointer to left child node
 *   left:  pointer to right child node
 */
struct bst_node
{
	void *data;
	struct bst_node *right;
	struct bst_node *left;
};

/* Struct:  bst_node 
 * --------------------
 *   root:           pointer to root node of bst
 *   compare_func_t: pointer to comparison function for data elements
 */
struct bst
{
	struct bst_node *root;
	int (*compare_func_t)(const void*, const void*);
};

/* Function:  BstCreate 
 * --------------------
 *   creates a new bst management structure
 *
 *   cmp_func: pointer to comparison function
 *
 *   returns: pointer to newly created bst
 */
bst_t *BstCreate(compare_func_t cmp_func)
{
	bst_t *bst = malloc(sizeof(bst_t));                   
	if(NULL == bst)
	{
		return NULL; 
	}
	
	bst -> compare_func_t = cmp_func;                  
	bst -> root = NULL;
	
	return bst;
}

/* Function:  InsertHelper 
 * --------------------
 *   called by BstInsert function to recursively insert a new data element into the bst
 *
 *   cmp_func: pointer to comparison function
 *   node:     pointer to current node
 *   data:     pointer to data element to be inserted
 *
 *   returns: pointer to updated node after insertion
 */
static struct bst_node *InsertHelper(compare_func_t cmp_func, struct bst_node *node, void *data)
{	
	int cmp_val = 0;
	struct bst_node *save_node = node;

	if(NULL == save_node)
	{
		save_node =  malloc(sizeof(struct bst_node));                             
		if(NULL == save_node)                                                   
		{
			return NULL;
		}
		
		save_node -> data = (void*)data;                                                
		save_node -> right = NULL;                                               
		save_node -> left = NULL;                                            
		
		return save_node;                           
	}

	cmp_val = cmp_func(data, node -> data);  
	/* -1 will take to the left pointer, 1 to the right pointer */                             
	if(-1 == cmp_val)                                                                                               
	{
		save_node = InsertHelper(cmp_func, save_node -> left, data);	
		node -> left = save_node;                                                
	}
	else
	{
		save_node = InsertHelper(cmp_func, save_node -> right, data);        
		node -> right = save_node;                                             
	}
	
	return node;
}

/* Function:  BstInsert 
 * --------------------
 *   inserts a new data element into the bst using InsertHelper function
 *
 *   bst:  pointer to the bst
 *   data: pointer to the data element to be inserted
 *
 *   returns: 0 for success, 1 for failure
 */
int BstInsert(bst_t *bst, const void *data)
{
	assert(bst);
	assert(data);

	bst -> root = InsertHelper(bst -> compare_func_t, bst -> root, (void*)data); 

	if(NULL == bst -> root)                                                       
	{
		return 1;
	}

	return 0; 
}

/* Function:  TraverseInOrder 
 * --------------------
 *   recursively traverses the bst in in-order traversal and applies an action on each node
 *   (traverse left subtree -> visit the root -> traverse right subtree)
 *
 *   node:        pointer to current node   
 *   action_func: pointer to action function
 *   param:       action function parameter
 *
 *   returns: 0 for success, -1 for failure
 */
static int TraverseInOrder(struct bst_node *node, action_function_t action_func, void *param)
{
	int ret_val = 0;

	if(NULL == node)
	{
		return 0;
	}

	if(-1 == TraverseInOrder(node -> left, action_func, param))  
	{
		return -1;
	}
	
	ret_val = action_func(node -> data, param);    
	/* if action_func failed once, return failure */               
	if(1 == ret_val)                                            
	{
		return -1;
	}

	if(-1 == TraverseInOrder(node -> right, action_func, param)) 
	{
		return -1;
	}

	return 0;
}

/* Function:  TraversePreOrder 
 * --------------------
 *   recursively traverses the bst in pre-order traversal and applies an action on each node
 *   (visit the root -> traverse left subtree -> traverse right subtree)
 * 
 *   node:        pointer to current node 
 *   action_func: pointer to action function
 *   param:       action function parameter
 *
 *   returns: 0 for success, 1 for failure 
 */
static int TraversePreOrder(struct bst_node *node, action_function_t action, void *parameter)
{
	int ret_val = 0;

	if (NULL == node)
	{
		return 0;
	}

	ret_val = action(node -> data, parameter);    
	/* if action_func failed once, return failure */            
	if (ret_val)                                              
	{
		return 1;
	}

	if (TraversePreOrder(node -> left, action, parameter))     
	{
		ret_val = 1;
	}

	if (TraversePreOrder(node -> right, action, parameter))   
	{
		ret_val = 1;
	}

	return ret_val;
}

/* Function:  TraversePostOrder 
 * --------------------
 *   recursively traverses the bst in post-order traversal and applies an action on each node
 *   (traverse left subtree -> traverse right subtree -> visit the root)
 * 
 *   node:        pointer to current node
 *   action_func: pointer to action function
 *   param:       action function parameter
 *
 *   returns: 0 for success, 1 for failure 
 */
static int TraversePostOrder(struct bst_node *node, action_function_t action_func, void *param)
{	
	int ret_val = 0;

	if(NULL == node)
	{
		return 0;
	}

	if(TraversePostOrder(node -> left, action_func, param))          
	{
		ret_val = 1;
	}

	if(TraversePostOrder(node -> right, action_func, param))          
	{
		ret_val = 1;
	}
	
	if(ret_val)
	{
		return 1;
	}

	ret_val = action_func(node -> data, param);                        
	/* if action_func failed once, return failure */            
	if (ret_val)                                              
	{
		return 1;
	}
	
	return ret_val;
}

/* Function:  BstForEach 
 * --------------------
 *   traverses the bst and performs an action on each node based on the specified traversal mode
 * 
 *   bst:          pointer to the bst
 *   mode:         traversal mode (IN_ORDER, PRE_ORDER, POST_ORDER)
 *   action_func:  pointer to action function
 *   param:        action function parameter
 *
 *   returns: 0 for success, -1 for failure
 */
int BstForEach(bst_t *bst, traversal_t mode, action_function_t action_func, void *param)
{
	int ret_val = -1;

	assert(bst);
	assert(action_func);

	if(mode == IN_ORDER)                                                                 
	{
		ret_val = TraverseInOrder(bst -> root, action_func, param);
	}
	else if(mode == PRE_ORDER)
	{
		ret_val = TraversePreOrder(bst -> root, action_func, param);
	}
	else if(mode == POST_ORDER)
	{
		ret_val = TraversePostOrder(bst -> root, action_func, param);
	}

	return ret_val;
}

/* Function:  BstIsEmpty 
 * --------------------
 *   checks if the bst is empty
 * 
 *   bst: pointer to the bst
 *
 *   returns: 1 if the tree is empty, 0 if it is not
 */
int BstIsEmpty(const bst_t *bst)
{
	assert(bst);

	if(NULL == bst -> root)
	{
		return 1;
	}

	return 0;
}

/* Function:  counter_func 
 * -------------------- 
 *   action function used for counting nodes during traversal
 *
 *   data:      pointer to data element of current node (not used)
 *   parameter: pointer to an integer parameter for storing the count
 *
 *   returns: 0 to continue traversal
 */
static int counter_func(void *data, void *parameter)
{
	++*(int*)parameter;
	(void)data;

	return 0;
}

/* Function:  BstSize 
 * --------------------
 *   counts number of nodes in the bst using TraverseInOrder function
 * 
 *   bst: pointer to the bst
 *
 *   returns: number of nodes in the tree
 */
size_t BstSize(const bst_t *bst)
{	
	size_t size = 0;

	assert(bst);

	TraverseInOrder(bst -> root, counter_func, &size);           

	return size;
}

/* Function:  DestroyHelper 
 * --------------------
 *   called by BstDestroy function to recursively free memory associated with nodes
 * 
 *   node: pointer to current node
 *
 *   returns: no return value
 */
static void DestroyHelper(struct bst_node *node)
{
	if(NULL == node)
	{
		return;
	}

	DestroyHelper(node -> left);
	DestroyHelper(node -> right);
	free(node);
}

/* Function:  BstDestroy 
 * --------------------
 *   destroys the bst by freeing memory associated with nodes using DestroyHelper function
 * 
 *   bst: pointer to the bst
 *
 *   returns: no return value
 */
void BstDestroy(bst_t *bst)
{
	assert(bst);

	if(0 == BstIsEmpty(bst))
	{
		DestroyHelper(bst -> root);
		bst -> root = NULL;
	}	

	free(bst);
}

/* Function:  FindHelper 
 * --------------------
 *   called by BstFind function to recursively search for a data element in the bst
 *   
 *   node: pointer to current node
 *   data: pointer to data element to search
 *
 *   returns: data if found, NULL otherwise
 */
static void *FindHelper(struct bst_node *node, const void *data)
{
	 void *result = NULL;

	if(NULL == node)
	{
		return NULL;
	}

	/* stops at node with the searched data */
	if(data == node -> data)                                          
	{
			return node -> data;
	}

	result = FindHelper(node -> left, data);                          
	if(NULL != result)
	{
		return result;
	}

	result = FindHelper(node -> right, data);                      
	if(NULL != result)
	{
		return result;
	}

	return NULL;
}

/* Function:  BstFind 
 * --------------------
 *   searches for a data element in the bst using FindHelper function
 * 
 *   bst:  pointer to the bst
 *   data: pointer to data element to search
 *
 *   returns: data if found, NULL otherwise
 */
void *BstFind(bst_t *bst, const void *data)
{
	assert(bst);
	assert(data);

	return FindHelper(bst -> root, data);
}

/* Function:  HeightHelper 
 * --------------------
 *   called by BstHeight function to recursively calculate the height of the bst
 *   
 *   node:  pointer to tcurrent node
 *
 *   returns: height of subtree rooted at current node
 */
size_t HeightHelper(struct bst_node *node)
{
	size_t left_height = 0;
	size_t right_height = 0;
	
	if (NULL == node)
	{
		return 0;
	}
	else 
	{
		left_height = HeightHelper(node -> left);   
		right_height = HeightHelper(node -> right); 
		
		/* checks which subtree is heigher */
		if (left_height >= right_height)              
		{
			return left_height + 1;
		}
		else
		{
			return right_height + 1;                 
		}
	}
}

/* Function:  BstHeight 
 * --------------------
 *   calculates the height of the bst using HeightHelper function
 * 
 *   bst:  pointer to the bst
 *
 *   returns: height of the tree
 */
size_t BstHeight(const bst_t *bst)
{
	assert(bst);
	
	return HeightHelper(bst -> root);
}

/* Function:  GetNode 
 * --------------------
 *   called by RemoveHelper to traverse to the rightmost leaf node in the given subtree
 *   
 *   node: pointer to current node
 *
 *   returns: pointer to rightmost leaf node
 */
static struct bst_node *GetNode(struct bst_node *node)
{
	struct bst_node *curr = node;

	while(NULL != curr && curr -> right)                        
	{
		curr = curr -> right;
	}

	return curr;
}

/* Function:  RemoveHelper 
 * --------------------
 *   called by BstRemove function to recursively remove data element from the bst
 * 
 *   node:     pointer to current node
 *   data:     pointer to data element to be removed
 *   cmp_func: pointer to comparison function
 *
 *   returns: pointer to updated node after removal
 */
static struct bst_node* RemoveHelper(struct bst_node *node, void *data, compare_func_t cmp_func)
{
	struct bst_node *tmp = NULL;
	int cmp_val = cmp_func(data, node -> data);                  

	if(NULL == node)
	{
		return NULL;
	}

	/* checks data in node to decide a path to find the data to be removed */
	if(-1 == cmp_val)                                             
	{
		node -> left = RemoveHelper(node -> left, data, cmp_func);
	}
	else if(1 == cmp_val)                                   
	{
		node -> right = RemoveHelper(node -> right, data, cmp_func);
	}
	else
	{
		if(NULL == node -> left)                                
		{
			tmp = node -> right;                               
			free(node);                                         
			return tmp;                                            
		}
		else if(NULL == node -> right)                             
		{
			tmp = node -> left;                             
			free(node);                                                   
			return tmp;
		}

		tmp = GetNode(node -> left);                              
		node -> data = tmp -> data;                             
		node -> left = RemoveHelper(node -> left, tmp -> data, cmp_func); 
	}

	return node;
}

/* Function:  BstRemove 
 * --------------------
 *   removes data element from the bst using RemoveHelper function
 * 
 *   bst:  pointer to the bst
 *   data: pointer to data element to be removed
 *
 *   returns: no return value 
 */
void BstRemove(bst_t *bst, void *data)
{
	assert(bst);
	assert(data);

	bst -> root = RemoveHelper(bst -> root, data, bst -> compare_func_t);     
}





