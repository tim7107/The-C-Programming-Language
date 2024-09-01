#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	MODE_GETCH = 0,
	MODE_GETLINE = 1,
} EX4_10_INPUT_MODE;

enum {
	EXERCISE_4_1 = 1,
	EXERCISE_4_2,
	EXERCISE_4_3,
	EXERCISE_4_4,
	EXERCISE_4_5,
	EXERCISE_4_6,
	EXERCISE_4_7,
	EXERCISE_4_8,
	EXERCISE_4_9,
	EXERCISE_4_10,
	EXERCISE_4_11,
	EXERCISE_4_12,
	EXERCISE_4_13,
	EXERCISE_4_14,
	CH4_TOTAL_EXER,
	TEST,
};


int EX4_1_main(char* s, char* t);
int EX4_2_main(char* testCase);
int EX4_3_main(char* input);
int EX4_7_main(char* input, int Exer);
int EX4_10_main(FILE** ptr, int mode);
int EX4_12_main(int val, char *s);
int EX4_13_main(char* s);