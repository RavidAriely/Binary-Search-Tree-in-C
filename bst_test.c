#include <stdio.h>	
#include <string.h>	/* strcmp */

#include "bst.h"
#include "utilities.h"

int Compare(const void *data1, const void *data2)
{
	if(*(int*)data1 > *(int*)data2)
	{
		return 1;
	}

	if(*(int*)data1 < *(int*)data2)
	{
		return -1;
	}

	return 0;
}

int CompareStrings(const void *a, const void *b) 
{
	return strcmp((const char*)a, (const char*)b);
}

int action(void *data, void *parameter)
{
	++*(int*)parameter;
	(void)data;
	return 0;
}

int PrintInt(void *data, void *parameter)
{
	printf("%d ", *(int*)data);
	(void)parameter;
	return 0;
}



int main()
{
	bst_t *bst = NULL;
	int x = 5;
	int y = 10;
	int z = 8;
	int t = 30;
	int b = 2;

	int find_test = 50; 
	int count_param = 0;

	bst_t *string_bst = NULL;
	char str1[5] = "this";
	char str2[3] = "is";
	char str3[3] = "my";
	char str4[4] = "BST";
	char str5[6] = "in c!";
	
	char *find_string_test = "not existing string";
	int count_string_param = 0;

	
	printf("---------------\n");
	printf("   INT TEST");
	printf("\n---------------\n\n");
	
	printf("BST CREATE  : ");
	bst = BstCreate(Compare);
	TESTS(NULL != bst);
	
	printf("IS BST EMPTY: ");
	TESTS(1 == BstIsEmpty(bst));
	
	printf("FIND ELEMENT WHEN BST IS EMPTY: ");
	TESTS(NULL == BstFind(bst, (void*)&x));
	
	printf("\nINSERT:\n\n");
	TESTS(0 == BstInsert(bst, (void*)&x));
	TESTS(0 == BstInsert(bst, (void*)&y));
	TESTS(0 == BstInsert(bst, (void*)&z));
	TESTS(0 == BstInsert(bst, (void*)&t));
	TESTS(0 == BstInsert(bst, (void*)&b));

	printf("\nBST FOR EACH - PRINT IN_ORDER MODE:\n\n");
	TESTS(0 == BstForEach(bst, IN_ORDER, PrintInt, NULL));
	
	printf("\nBST FOR EACH - IN_ORDER MODE:\n\n");
	TESTS(0 == BstForEach(bst, IN_ORDER, action, &count_param));
	TESTS(5 == count_param);
	count_param = 0;
	
	printf("\nBST FOR EACH - PRE_ORDER MODE:\n\n");
	TESTS(0 == BstForEach(bst, PRE_ORDER, action, &count_param));
	TESTS(5 == count_param);
	count_param = 0;
	
	printf("\nBST FOR EACH - POST_ORDER MODE:\n\n");
	TESTS(0 == BstForEach(bst, POST_ORDER, action, &count_param));
	TESTS(5 == count_param);
	count_param = 0;
	
	printf("\nIS EMPTY: ");
	TESTS(0 == BstIsEmpty(bst));

	printf("SIZE    : ");
	TESTS(5 == BstSize(bst))

	printf("\nFIND:\n\n");
	TESTS(5 == *(int*)BstFind(bst, (void*)&x));
	TESTS(8 == *(int*)BstFind(bst, (void*)&z));
	TESTS(2 == *(int*)BstFind(bst, (void*)&b));
	TESTS(NULL == BstFind(bst, (void*)&find_test));

	printf("\nHEIGHT: ");
	TESTS(3 == BstHeight(bst));

	BstRemove(bst, &b);
	printf("REMOVE AND TRY TO FIND THE REMOVED ONE: ");
	TESTS(NULL == BstFind(bst, (void*)&b));

	printf("SIZE AFTER ONE REMOVAL   : ");
	TESTS(4 == BstSize(bst))

	BstRemove(bst, &z);
	BstRemove(bst, &y);
	BstRemove(bst, &t);
	BstRemove(bst, &x);
	
	printf("SIZE AFTER REMOVIG ALL   : ");
	TESTS(0 == BstSize(bst))

	printf("HEIGHT AFTER REMOVING ALL: ");
	TESTS(0 == BstHeight(bst));
	
	BstDestroy(bst);
	
	
	
	
	
	printf("\n\n\n-----------------\n");
	printf("   STRING TEST");
	printf("\n-----------------\n\n");
	
	printf("BST CREATE  : ");
	string_bst = BstCreate(CompareStrings);
	TESTS(NULL != string_bst);
	
	printf("IS BST EMPTY: ");
	TESTS(1 == BstIsEmpty(string_bst));
	
	printf("FIND ELEMENT WHEN BST IS EMPTY: ");
	TESTS(NULL == BstFind(string_bst, (void*)&str1));
	
	
	printf("\nINSERT:\n\n");
	TESTS(0 == BstInsert(string_bst, (void*)&str1));
	TESTS(0 == BstInsert(string_bst, (void*)&str2));
	TESTS(0 == BstInsert(string_bst, (void*)&str3));
	TESTS(0 == BstInsert(string_bst, (void*)&str4));
	TESTS(0 == BstInsert(string_bst, (void*)&str5));

	printf("\nBST FOR EACH - IN_ORDER MODE:\n\n");
	TESTS(0 == BstForEach(string_bst, IN_ORDER, action, &count_string_param));
	TESTS(5 == count_string_param);
	count_string_param = 0;
	
	printf("\nBST FOR EACH - PRE_ORDER MODE:\n\n");
	TESTS(0 == BstForEach(string_bst, PRE_ORDER, action, &count_string_param));
	TESTS(5 == count_string_param);
	count_string_param = 0;
	
	printf("\nBST FOR EACH - POST_ORDER MODE:\n\n");
	TESTS(0 == BstForEach(string_bst, POST_ORDER, action, &count_string_param));
	TESTS(5 == count_string_param);
	count_string_param = 0;
	
	printf("\nIS EMPTY: ");
	TESTS(0 == BstIsEmpty(string_bst));

	printf("SIZE    : ");
	TESTS(5 == BstSize(string_bst))

	printf("\nFIND:\n\n");
	TESTS(0 == strcmp((char*)BstFind(string_bst, (void*)&str1), "this"));
	TESTS(0 == strcmp((char*)BstFind(string_bst, (void*)&str2), "is"));
	TESTS(0 == strcmp((char*)BstFind(string_bst, (void*)&str4), "BST"));
	TESTS(NULL == BstFind(string_bst, (void*)&find_string_test));

	printf("\nHEIGHT: ");
	TESTS(5 == BstHeight(string_bst));

	BstRemove(string_bst, &str3);
	printf("SIZE AFTER ONE REMOVAL     : ");
	TESTS(4 == BstSize(string_bst))

	BstRemove(string_bst, &str1);
	BstRemove(string_bst, &str2);
	BstRemove(string_bst, &str4);
	BstRemove(string_bst, &str5);
	
	printf("TRY TO FIND THE REMOVED ONE: ");
	TESTS(NULL == BstFind(string_bst, (void*)&str3));
	
	printf("SIZE AFTER REMOVIG ALL     : ");
	TESTS(0 == BstSize(string_bst))

	printf("HEIGHT AFTER REMOVING ALL  : ");
	TESTS(0 == BstHeight(string_bst));
	
	BstDestroy(string_bst);

	return 0;
}
