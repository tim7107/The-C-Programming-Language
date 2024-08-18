#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "D:\Timkuo\The C new\include\errno.h"
#include "D:\Timkuo\The C new\include\common.h"

int Stack_idx;
int Stack[IDX_MAX_LENGTH];

/* file */
int fileOpen(exercise_info* exer, FILE** pptr)
{
	if (exer->file_name == NULL)
		return SUCCESS;

	printf("Opening file %s\n", exer->file_name);
	*pptr = fopen(exer->file_name, "r");

	if (*pptr != NULL) 
		return SUCCESS;
        else 
		return FAIL;
}

/* char */
int Is_Digits(int x)
{
	if (x >= '0' && x <= '9')
		return TRUE;

	return FALSE;
}

int Is_Letters(int x)
{
	if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z'))
		return TRUE;
	else
		return FALSE;
}

/* 
 * For ascii talbe : 0 ~ 127
 * For further table : 128 ~ 255 are IBM specific
 */
int Is_Ascii(int x)
{
	if (x >= 0 && x <= 127)
		return TRUE;

	return FALSE;
}

void itoa_recursive(int n, char* s)
{
	if (n) {
		*s++ = abs(n % 10) + '0';
		*s = '\0';
		n /= 10;
		itoa_recursive(n, s);
	}

	return;
}

/* String related */
int str_IsWhiteSpace(char* s, int idx)
{
	if (s[idx] == SPACE)
		return TRUE;
	else
		return FALSE;
}

int str_GetSign(char* s, int idx)
{
	int ret = 0;

	if (s[idx] == '+')
		ret = POSITIVE;
	else if (s[idx] == '-')
		ret = NEGATIVE;
	else
		printf("Invalid char %s found...\n", s[idx]);

	return ret;
}

int str_IsDigits(char* s, int i)
{
	if (s[i] >= '0' && s[i] <= '9')
		return TRUE;
	else
		return FALSE;
}

void str_reverse(char s[])
{
	int c, i, j;
	j = strlen(s) - 1;
	if (INT_MIN <= j <= INT_MAX) {
		for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
			c = s[i];
			s[i] = s[j];
			s[j] = c;
		}
	}
}

void str_reverse_recur(char* s, int left, int right)
{
	int tmp;

	if (left < right && (s != NULL)) {
		tmp = s[right];
		s[right] = s[left];
		s[left] = tmp;
		str_reverse_recur(s, ++left, --right);
	}
}

/*
 * - Stack
 *	@Description:
 *		The followings are the implementation about stack using C programming.
 */
void Stack_push(int data) {
	if ((data > INT_MAX || data < INT_MIN) && data != EOF)
		return;
	if (Stack_idx < IDX_MAX_LENGTH)
		Stack[++Stack_idx] = data;
	else
		C_PRINTF(C_DEBUG, "[%s] Stack Full!!!\n", __FUNCTION__);
}

int Stack_pop(int *x)
{
	int ret = 0;

	if (Stack_idx != -1) {
		*(x) = Stack[Stack_idx];
		Stack_idx--;
	} else {
		C_PRINTF(C_DEBUG, "[%s] Stack Empty!!!\n", __FUNCTION__);
		return -ESPOP;
	}

	return ret;
}

void Stack_top(int *x)
{
	if (Stack_idx >= 0) {
		*(x) = Stack[Stack_idx];
		Stack_idx--;
	} else
		C_PRINTF(C_DEBUG, "[%s] Stack is empty\n", __FUNCTION__);
}

void Stack_print(void) {
	int i = 0;
	printf("---------------------\n");
	printf("|");
	for (; i <= Stack_idx; i++) {
		printf("%d ", Stack[i]);
	}
	printf("\n");
	printf("---------------------\n");
}

void Stack_show_top(void) {
	if (Stack_idx >= 0)
		printf("Stack top = %d\n", Stack[Stack_idx]);
	else
		printf("Stack is empty\n");
}

void Stack_init(void) {
	memset(Stack, 0, sizeof(sizeof(Stack[0]) * IDX_MAX_LENGTH));
	Stack_idx = -1;
	printf("Stack init!\n");
	return;
}

void Stack_duplicate(void)
{
	int a;
	
	Stack_pop(&a);
	Stack_push(a);
	Stack_push(a);
	printf("Duplicate complete!\n");
	return;
}

void Stack_clear(void)
{
	memset(Stack, 0, sizeof(sizeof(Stack[0]) * IDX_MAX_LENGTH));
	Stack_idx = -1;
	printf("Stack clear!\n");
	return;
}

int Stack_isEmpty(void)
{
	return (Stack_idx >= 0) ? FALSE : TRUE;
}

int Stack_getLength(void)
{
	return (Stack_idx >= 0) ? (Stack_idx + 1) : 0;
}

void Stack_swap_top_two_ele(void)
{
	int a, b;
	if (Stack_idx >= 1) {
		Stack_pop(&a);
		Stack_pop(&b);
		Stack_push(a);
		Stack_push(b);
	} else
		printf("Stack swap the top two ele fail!\n");
}

/*
 * [Input related]
 * 	- getline
 *		@Description:
 *			Get each line from a txt.
 * 		@return:
 *			Length of cur line.
*/
int getline_from_txt(FILE** pptr, char* input)
{
	int idx = 0;
	int c;

	if (*pptr == NULL) {
		C_PRINTF(C_DEBUG, "[%s] NULL Pointer!\n", __FUNCTION__);
		return -ENOFILEFOUND;
	}

	memset(input, 0, sizeof(sizeof(input[0]) * LINE_MAX_LENGTH));
	while ((c = fgetc(*pptr)) != EOF && c != '\n')
		input[idx++] = c;

	input[idx] = '\0';

	return idx;
}

int getchar_from_txt(FILE** pptr, char* ch)
{
	int ret = FALSE;
	int c;

	if (*pptr == NULL) {
		C_PRINTF(C_ERROR, "[%s] NULL Pointer!\n", __FUNCTION__);
		return -EINVCHARIN;
	}

	//if ((c = fgetc(*pptr)) != EOF && c != '\n')
	c = fgetc(*pptr);
	if (c != EOF && Is_Ascii(c))
	{
		*ch = c;
		ret = TRUE;
	}

	return ret;
}