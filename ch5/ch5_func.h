#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	EXERCISE_5_1 = 1,
	EXERCISE_5_2,
	EXERCISE_5_3,
	EXERCISE_5_4,
	EXERCISE_5_5,
	EXERCISE_5_6,
	EXERCISE_5_7,
	EXERCISE_5_8,
	EXERCISE_5_9,
	EXERCISE_5_10,
	EXERCISE_5_11,
	EXERCISE_5_12,
	EXERCISE_5_13,
	EXERCISE_5_14,
        EXERCISE_5_15,
        EXERCISE_5_16,
        EXERCISE_5_17,
        EXERCISE_5_18,
        EXERCISE_5_19,
        EXERCISE_5_20,
	CH5_TOTAL_EXER,
	TEST,
};

enum {
	STRNCPY = 0,
	STRNCAT = 1,
	STRNNCMP = 2,
	STRMAX = 3,
};

int EX5_1_main(char* input, int* val);
int EX5_2_main(char* s, double* f);
char* EX5_3_main(char* s, char* t);
int EX5_3_main_test(char* s, char* t, char** st);
int EX5_4_main(char *s, char *t);
int EX5_5_main(char *s, char *t, int mode, int len);
int EX5_6_main(char* s1, char* s2, char* s3);