#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "D:\Timkuo\The C new\ch4\ch4_func.h"
#include "D:\Timkuo\The C new\include\common.h"
#include "D:\Timkuo\The C new\include\errno.h"
#include "D:\Timkuo\The C new\include\of_bit.h"

static exercise_info ch4_exercise_infos[CH4_TOTAL_EXER] = {
	EXERCISE(0, NULL),
	EXERCISE(EXERCISE_4_1, NULL),
	EXERCISE(EXERCISE_4_2, NULL),
	EXERCISE(EXERCISE_4_3, NULL),
	EXERCISE(EXERCISE_4_4, NULL),
	EXERCISE(EXERCISE_4_5, NULL),
	EXERCISE(EXERCISE_4_6, NULL),
	EXERCISE(EXERCISE_4_7, NULL),
	EXERCISE(EXERCISE_4_8, NULL),
	EXERCISE(EXERCISE_4_9, NULL),
	EXERCISE(EXERCISE_4_10, "D:/Timkuo/The C new/exercise/EX4_10.txt"),
	EXERCISE(EXERCISE_4_11, NULL),
	EXERCISE(EXERCISE_4_12, NULL),
	EXERCISE(EXERCISE_4_13, NULL),
};

int main()
{
	exercise_info exer = ch4_exercise_infos[EXERCISE_4_13];
	//char *ex4_2_s[] = { "123.45e-6", "-1.2e-3", "-1.2E3", "-1.2e03"};
	//char *ex4_2_s[] = { "123.45e-6"};
	char ex4_3456_s[IDX_MAX_LENGTH] = "12+4*6*2*";
	char ex4_2_s[IDX_MAX_LENGTH] = "123.45e-6";
	char ex4_789_s[IDX_MAX_LENGTH];
	char ex4_12_s[IDX_MAX_LENGTH];
	char ex4_13_s[IDX_MAX_LENGTH];
	char *ex4_1_s1, *ex4_1_s2;
	EX4_10_INPUT_MODE mode;
	int ret, val;
	FILE* ptr;

	printf("hello ch4...\n");

	if (!fileOpen(&exer, &ptr)) {
		printf("[Error] fail to open %s...\n", exer.file_name);
		return -ENOFILEFOUND;
	}

	switch (exer.exer_num)
	{
		case EXERCISE_4_1:
			ex4_1_s1 = "apppppppple";
			ex4_1_s2 = "pppp";
			ret = EX4_1_main(ex4_1_s1, ex4_1_s2);
			if (ret >= 0)
				printf("%s occurs at the rightmost %d in %s", ex4_1_s2, ret, ex4_1_s1);
			else
				printf("%s doesn't exist in %s\n", ex4_1_s2, ex4_1_s1);
			break;

		case EXERCISE_4_2:
			ret = EX4_2_main(ex4_2_s);
			if (ret)
				goto fail;

			break;

		case EXERCISE_4_3:
		case EXERCISE_4_4:
		case EXERCISE_4_5:
		case EXERCISE_4_6:
			ret = EX4_3_main(ex4_3456_s);
			if (ret)
				goto fail;

			break;

		case EXERCISE_4_7:
		case EXERCISE_4_8:
		case EXERCISE_4_9:
			printf("Plz enter str input\n");
			scanf("%s", ex4_789_s);

			ret = EX4_7_main(ex4_789_s, exer.exer_num);
			if (ret)
				goto fail;

			break;

		case EXERCISE_4_10:
			/*
			 * Todo :
			 *	Just need another stack to save input stack for correct txt line order.
			 *	Maybe can design a api for registering stack, pushing, popping...etc
			*/
			printf("Choose mode:\n");
			printf("\t* getch   : 0\n");
			printf("\t* getline : 1\n");
			scanf("%d", &mode);

			ret = EX4_10_main(&ptr, mode);
			if (ret)
				goto fail;
			break;

		case EXERCISE_4_12:
			printf("Plz enter int input \n");
			scanf("%d", &val);

			ret = EX4_12_main(val, ex4_12_s);
			if (ret)
				goto fail;
			else
				printf("Int %d has translated to char %s successfully!\n", val, ex4_12_s);

			break;

		case EXERCISE_4_13:
			printf("Plz enter str input \n");
			scanf("%s", ex4_13_s);
			printf("Input : ", ex4_12_s);

			ret = EX4_13_main(ex4_13_s);
			if (ret)
				goto fail;
			else
				printf("has been reversed to char %s successfully!\n", ex4_13_s);

			break;

		default:
			printf("plz assign an exer...\n");
			break;
	}

	return 0;

fail:
	printf("[Err] Exercise stop!\n");
	return 0;
};