#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "D:\Timkuo\The C new\include\errno.h"
#include "D:\Timkuo\The C new\ch4\ch4_func.h"
#include "D:\Timkuo\The C new\include\common.h"

int EX4_1_main(char* s, char* t)
{
	int ret = -1;
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;

		if (t[k] == '\0') 
			ret = i;
	}
	return ret;
}

double atof_EX4_2(char* s, double *val)
{
	double fragment_scale = 0.1;
	double cur_scale, exp_scale;
	int integar_scale = 10;
	int sign, exp_sign;
	double retval = 0;
	int exp = 0;
	int ret = 0;
	int i = 0;

	if (s == NULL)
		return -EINVCHARIN;

	/* check white space */
	while (str_IsWhiteSpace(s, i))
		i++;

	/* check sign */
	if (Is_Digits(s[i]))
		sign = POSITIVE;
	else {
		sign = str_GetSign(s, i);
		if (!sign)
			return -EINVCHARIN;
		i++;
	}

	/* calculate the integer part */
	while (str_IsDigits(s, i)) {
		retval *= integar_scale;
		retval += (s[i++] - '0');
	}

	/* Calculate the fractional part */
	if (s[i] == '.') {
		i++;
		cur_scale = fragment_scale;
		while (str_IsDigits(s, i)) {
			retval += cur_scale * (s[i] - '0');
			i++;
			cur_scale *= fragment_scale;
		}
	}

	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		exp_sign = str_GetSign(s, i);
		if (Is_Digits(s[i]))
			exp_sign = POSITIVE;
		else {
			exp_sign = str_GetSign(s, i);
			if (!exp_sign)
				return -EINVCHARIN;
			i++;
		}

		while (s[i] == '0')
			i++;

		while (str_IsDigits(s, i)) {
			exp *= integar_scale;
			exp += (s[i] - '0');
			i++;
		}

		if (exp_sign > 0)
			exp_scale = 10;
		else
			exp_scale = 0.1;

		while (exp > 0) {
			retval *= exp_scale;
			exp--;
		}
	}

	*val = retval;

	return ret;
}

int EX4_2_main(char* testCase)
{
	double val;
	int i = 0;
	int ret = 0;

	ret = atof_EX4_2(testCase, &val);
	if (ret)
		return -EINVCHARIN;

	printf("[%s , %g]\n", testCase, val);

	return ret;

}

int do_EX4_3(char* input, int* val) {
	int a = 0, b = 0;
	int ch, cur_len;
	int ret = 0;
	int i = 0;

	if (input == NULL) {
		printf("No input detected!\n");
		return -EINVCHARIN;
	}

	Stack_init();

	while ((ch = input[i]) != '\0') {
		switch (ch) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				Stack_push(ch - '0');
				break;

			case '+':
				if ((cur_len = Stack_getLength()) < 2)
					return -EINVCHARIN;

				Stack_pop(&a);
				Stack_pop(&b);
				Stack_push(a + b);
				break;

			case '*':
				if ((cur_len = Stack_getLength()) < 2)
					return -EINVCHARIN;

				Stack_pop(&a);
				Stack_pop(&b);
				Stack_push(a * b);
				break;

			case '-':
				if ((cur_len = Stack_getLength()) < 2)
					return -EINVCHARIN;

				Stack_pop(&a);
				Stack_pop(&b);
				Stack_push(b - a);
				break;

			case '/':
				if ((cur_len = Stack_getLength()) < 2)
					return -EINVCHARIN;

				Stack_pop(&a);
				Stack_pop(&b);
				if(a != 0)
					Stack_push(b / a);
				break;

			case '%':
				if ((cur_len = Stack_getLength()) < 2)
					return FALSE;

				Stack_pop(&a);
				Stack_pop(&b);
				if (a != 0)
					Stack_push(b % a);
				break;

			case SIN:
				if (Stack_isEmpty())
					return -EINVCHARIN;

				Stack_pop(&a);
				Stack_push(sin(a));
				break;

			case EXP:
				if (Stack_isEmpty())
					return -EINVCHARIN;

				Stack_pop(&a);
				Stack_push(exp(a));
				break;

			case POW:
				if ((cur_len = Stack_getLength()) < 2)
					return -EINVCHARIN;

				Stack_pop(&a);
				Stack_pop(&b);

				if (pow(b, a) > INT_MAX ||  pow(b, a) < INT_MIN) {
					printf("pow overflow or underflow\n");
					return -EOVERFLOW;
				}

				Stack_push(pow(b, a));
				break;

			default:
				return -EINVCHARIN;
		}
		i++;
	}

	Stack_pop(val);

	if (!Stack_isEmpty()) {
		Stack_print();
		ret = -EINVCHARIN;
	}

	return ret;
}

int EX4_3_main(char* input)
{
	int val = 0;
	int ret = 0;

	ret = do_EX4_3(input, &val);
	if (ret) {
		printf("[ERROR] Invalid input!\n");
		return -EINVCHARIN;
	}

	printf("[Input , output] = [%s, %d]\n", input, val);
	Stack_clear();

	return ret;
}

int EX4_7_main(char* input, int Exer)
{
	int ret = 0;
	int i = 0;
	int c;

	if (Exer == EXERCISE_4_8) {
		if (sizeof(input) > 1)
			return -EINVCHARIN;
	}

	Stack_init();

	/* EX4_9, we take EOF as a stop char */
	while (i < sizeof(input) && input[i] != '\0')
		Stack_push(input[i++]);

	while (!Stack_pop(&c))
		printf("[Output] : %c\n", c);

	return ret;
}

int EX4_10_main(FILE** ptr, int mode)
{
	int i = 0, line = 0, ret = 0;
	char input[LINE_MAX_LENGTH];
	int ch, len;

	Stack_init();

	if (mode == MODE_GETLINE) {
		while ((len = getline_from_txt(ptr, input)) > 0) {
			i = 0;
			printf("Line%d:", line++);

			/* Push */
			while (i < len && input[i] != '\0')
				Stack_push(input[i++]);

			/* Pop */
			while (!Stack_pop(&ch))
				printf("%c", ch);
		}
	} else {
		while (getchar_from_txt(ptr, &ch))
			Stack_push(ch);

		while (!Stack_pop(&ch))
				printf("%c", ch);
	}

	return ret;
}

int EX4_12_main(int val, char *s)
{
	char res[IDX_MAX_LENGTH];
	int idx = 0, ret = 0;
	char* ptr = res;

	if ((val < INT_MIN)  || (val > INT_MAX))
		return -EOVERFLOW;
	
	if (val < 0) {
		val *= -1;
		*s++ = '-';
	}

	itoa_recursive(val, s);
	str_reverse(s);

	printf("val in string is %s\n", s);

	return ret;
}

int EX4_13_main(char* s)
{
	int length = strlen(s);
	int ret = 0;

	str_reverse_recur(s, 0, length - 1);

	return ret;
}