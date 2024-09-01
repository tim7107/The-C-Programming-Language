#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "D:\Timkuo\The C new\include\errno.h"
#include "D:\Timkuo\The C new\ch5\ch5_func.h"
#include "D:\Timkuo\The C new\include\common.h"

int EX5_1_main(char* input, int* val)
{
        int sum = 0, need_allNum = 0, ret = 0;
	int sign = POSITIVE;
	int c, i;

	for (i = 0; input[i] != '\0'; i++) {
		c = input[i];

                /* whitespace & sign can only appear in the beginning of char */
		if (c == ' ') {
                        if (need_allNum)
                                return -EINVCHARIN;
                        continue;
                }
		
		if (c == '+' || c == '-') {
                        if (need_allNum)
                                return -EINVCHARIN;
                        sign = (c == '-') ? NEGATIVE : POSITIVE;
			continue;
		}

		if (!Is_Digits(c))
			return -EINVCHARIN;

                need_allNum = 1;
		sum = sum * 10 + (c - '0');
	}

	if (sign == NEGATIVE)
		sum *= -1;

	*val = sum;

	return ret;
}

int EX5_2_main(char* s, double* f)
{
	int has_fraction = FALSE, sign = POSITIVE;
	int fraction_idx = 1, ret = 0;
	double sum = 0;
	double frac;
	int i, c;

	pr_info("Start getting float from char(%s)...\n", s);
	for (i = 0; s[i] != '\0'; i++) {
		c = s[i];

		if (c == ' ')
			continue;

		if (c == '+' || c == '-') {
			sign = (c == '-') ? NEGATIVE : POSITIVE;
			continue;
		}

		if (c == '.') {
			has_fraction = TRUE;
			continue;
		}

		if (!Is_Digits(c))
			return -EINVCHARIN;

		if (!has_fraction)
			sum = sum * 10 + (c - '0');
		else {
			frac = pow(10, fraction_idx++);
			sum = sum + ((c - '0') / frac);
		}

		pr_info("%d\n", sum);
	}

	if (sign == NEGATIVE)
		sum *= -1;

	*f = sum;

	return ret;
}


char* EX5_3_main(char* s, char* t)
{
	int ret = 0;
	char *save, *tmp;

	save = (char *) malloc(sizeof(char) * (strlen(s) + strlen(t) + 1));
	if (!save) {
		pr_err("No enough space for strcat!\n", NULL);
		return NULL;
	}

	tmp = save;

	while (*s != '\0')
		*save++ = *s++;
	
	while(*t != '\0')
		*save++ = *t++;

	pr_info("%s\n", tmp);

	return tmp;
}

int EX5_3_main_test(char* s, char* t, char** st)
{
	int ret = 0;
	char *save, *tmp;

	save = (char *) malloc(sizeof(char) * (strlen(s) + strlen(t) + 1));
	if (!save) {
		pr_err("No enough space for strcat!\n", NULL);
		return -ENULLPTR;
	}

	tmp = save;

	while (*s != '\0')
		*save++ = *s++;
	
	while(*t != '\0')
		*save++ = *t++;

	*st = tmp;

	return 0;
}

int EX5_4_main(char *s, char *t)
{
	int s_len = strlen(s), t_len = strlen(t);
	int ret = MATCH, i = 0;

	if (s_len < t_len)
		return MISMATCH;

	while (i < (s_len - t_len)) {
		s++;
		i++;
	}

	while (*t != '\0') {
		if (*s != *t) {
			ret = MISMATCH;
			break;
		}

		t++;
		s++;
	}

	if (*s != '\0')
		ret = MISMATCH;

	return ret;
}

char* EX5_5_strncpy(char *dst, char *src, int len)
{
	char *start;

	if (dst == NULL || src == NULL)
		return NULL;

	start = dst;

	while(len > 0){
		*dst++ = *src++;
		len--;
	}

	if (!Is_Ascii(*dst))
		*dst = '\0';

	return start;
}

char* EX5_5_strncat(char *dst, char *src, int len)
{
	char *start, *buf;

	start = dst;

	while(*dst != '\0')
		dst++;
	
	while(len > 0 && *src != '\0') {
		*dst++ = *src++;
		len--;
	}

	*dst = '\0';

	return start;
}

int EX5_5_strncmp(char *s, char *t, int len)
{
	int ret = EQUAL;

	if (len > strlen(s) || len > strlen(t))
		len = min(strlen(s), strlen(t));

	while(len > 0) {
		if (*s != *t) {
			ret = NEQUAL;
			break;
		}

		s++;
		t++;
		len--;
	}

	return ret;
}


int EX5_5_main(char *s, char *t, int mode, int len)
{
	int ret = 0;
	char* tmp;
	int cmp;

	tmp = (char *) malloc(sizeof(strlen(s) + strlen(t) + 1));

	switch (mode)
	{
		case STRNCPY:
			tmp = EX5_5_strncpy(s, t, len);
			if (tmp == NULL) {
				pr_err("strncpy fail!\n", NULL);
				ret = -ENULLPTR;
			}

			pr_info("strncpy ok! output = %s\n", tmp);
			break;

		case STRNCAT:
			tmp = EX5_5_strncat(s, t, len);
			if (tmp == NULL) {
				pr_err("strncat fail!\n", NULL);
				ret = -ENULLPTR;
			}

			pr_info("strncat ok! output = %s\n", tmp);
			break;

		case STRNNCMP:
			cmp = EX5_5_strncmp(s, t, len);
			if (cmp != 0)
				pr_info("%s != %s for first n bytes\n", s, t);
			
			if (cmp == 0)
				pr_info("%s = %s", s, t);

			break;
		default:
			pr_err("please enter valid mode 0:strncpy, 1:strncat, 2:strncmp\n", NULL);
			ret = -EINVMODE;
			break;
	}

	return ret;
}

int EX5_6_main(char* s1, char* s2, char* s3)
{
	char* itoaP_out;
	int ret = 0;
	int val;

	/* atoi */
	ret = atoiP(s1, &val);
	if (ret) {
		pr_err("atoi fail...\n", NULL);
		goto end;
	}

	pr_info("atoi(%s) = %d\n", s1, val);

	/* itoa */
	itoaP_out = (char *) malloc(sizeof(char) * INTMAX_OFFSET);
	if (!itoaP_out) {
		pr_err("Null pointer!\n", NULL);
		goto end;
	}

	ret = itoaP(val, itoaP_out);
	if (ret) {
		pr_err("itoa fail...\n", NULL);
		goto end;
	}

	pr_info("itoa(%d) = %s\n", val, itoaP_out);

	/* reverse */
	pr_info("String %s will be reversed to\n", s2);
	str_reverseP(s2);
	pr_info("%s\n", s2);

	/* stridx */
	

	return ret;

end:
	return -EEXERFAIL;
}