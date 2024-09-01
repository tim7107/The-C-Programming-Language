#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "D:\Timkuo\The C new\ch5\ch5_func.h"
#include "D:\Timkuo\The C new\include\common.h"
#include "D:\Timkuo\The C new\include\errno.h"
#include "D:\Timkuo\The C new\include\of_bit.h"

static exercise_info ch5_exercise_infos[CH5_TOTAL_EXER] = {
        EXERCISE(0, NULL),
        EXERCISE(EXERCISE_5_1, NULL),
        EXERCISE(EXERCISE_5_2, NULL),
        EXERCISE(EXERCISE_5_3, NULL),
        EXERCISE(EXERCISE_5_4, NULL),
        EXERCISE(EXERCISE_5_5, NULL),
        EXERCISE(EXERCISE_5_6, NULL),
};  

int main()
{
        char *ex5_1_s, *ex5_2_s, *ex5_3_s1, *ex5_3_s2, *ex5_3_s3;
        char *ex5_4_s1, *ex5_4_s2, *ex5_5_s1, *ex5_5_s2, *ex5_6_s1;
        char *ex5_6_s2, *ex5_6_s3, *ex5_6_so;
        int ex5_6_int;
        int exer = EXERCISE_5_6;
        exercise_info *exer_tbl;
        int ret = 0, val = 0;
        double fval;
        FILE *ptr;
        int len;

        pr_info("Hi, now in Ch5 exer%d\n", exer);
        exer_tbl = &ch5_exercise_infos[exer];

        if (!fileOpen(exer_tbl, &ptr)) {
                pr_err("fail to open %s...\n", exer_tbl->file_name);
                ret = -ENOFILEFOUND;
                goto end;
        }

        switch (exer_tbl->exer_num)
        {
                case EXERCISE_5_1:
			ex5_1_s = " -1211155";
			
			ret = EX5_1_main(ex5_1_s, &val);
			if (ret) {
                                pr_err("Exer5-1 fail...\n", NULL);
                                ret = -EEXERFAIL;
                                goto end;
                        }

			pr_info("Val = %d\n", val);
                        break;

                case EXERCISE_5_2:
			ex5_2_s = " -55422.5410";

			ret = EX5_2_main(ex5_2_s, &fval);
			if (ret)
				goto end;

			pr_info("val = %f\n", fval);
			break;

                case EXERCISE_5_3:
			ex5_3_s1 = "GGGG132";
			ex5_3_s2 = "TTTT321";

                        /* Ex5-3 we provide 2 different way to get ex5_3_s3.
                         * One is returning char* and assign to ex5_3_s3. Another is
                         * sending ptr of char* (i.e char**) to assign it in main function.
                         * If you just pass char* to main function and want to assign the
                         * val there, it seems doesn't work and you will get null ptr.
                         */
			ex5_3_s3 = EX5_3_main(ex5_3_s1, ex5_3_s2);
                        // ret = EX5_3_main_test(ex5_3_s1, ex5_3_s2, &ex5_3_s3);
                        if (!ex5_3_s3)
                                goto end;

			pr_info("Output: %s\n", ex5_3_s3);
			break;

                case EXERCISE_5_4:
			ex5_4_s1 = "GGGG132132";
			ex5_4_s2 = "GG132132";
			val = EX5_4_main(ex5_4_s1, ex5_4_s2);

			if (val == MISMATCH)
				pr_info("Mismatch! %s isn't at the end of %s", ex5_4_s2, ex5_4_s1);
                        
                        if (val == MATCH)
				pr_info("Match! %s is at the end of %s", ex5_4_s2, ex5_4_s1);
			
                        break;

                case EXERCISE_5_5:
                        ex5_5_s1 = (char *) malloc(sizeof(char) * STR_MAXLEN);
                        ex5_5_s2 = (char *) malloc(sizeof(char) * STR_MAXLEN);

                        strncpy(ex5_5_s1, "YYY1234", strlen("YYY1234") + 1);
                        strncpy(ex5_5_s2, "ZZZZYYZ456", strlen("ZZZZYYZ456") + 1);
                        pr_info("Input strs are %s & %s\n", ex5_5_s1, ex5_5_s2);

                        val = min(strlen(ex5_5_s1), strlen(ex5_5_s2));
                        len = 3;

                        ret = EX5_5_main(ex5_5_s1, ex5_5_s2, STRNNCMP, val);
                        if (ret)
                                goto end;

                        ret = EX5_5_main(ex5_5_s1, ex5_5_s2, STRNCPY, len);
                        if (ret)
                                goto end;

                        ret = EX5_5_main(ex5_5_s1, ex5_5_s2, STRNCAT, val);
                        if (ret)
                                goto end;

                        break;

                case EXERCISE_5_6:
                        ex5_6_s1 = (char *) malloc(sizeof(char) * STR_MAXLEN);
                        ex5_6_s2 = (char *) malloc(sizeof(char) * STR_MAXLEN);
                        ex5_6_s3 = (char *) malloc(sizeof(char) * STR_MAXLEN);
                        if (!ex5_6_s1) {
                                pr_err("Null pointer!\n", NULL);
                                goto end;
                        }

                        if (!ex5_6_s2) {
                                pr_err("Null pointer!\n", NULL);
                                goto end;
                        }

                        if (!ex5_6_s3) {
                                pr_err("Null pointer!\n", NULL);
                                goto end;
                        }

                        strncpy(ex5_6_s1, "123456", strlen("123456") + 1);
                        strncpy(ex5_6_s2, "reverse_test", strlen("reverse_test") + 1);
                        strncpy(ex5_6_s3, "apppppple", strlen("apppppple") + 1);

                        ret = EX5_6_main(ex5_6_s1, ex5_6_s2, ex5_6_s3);
                        if (ret)
                                goto end;

                        break;

                default:
                        pr_err("Plz enter correct exer!\n", exer);
                        goto end;
        }

        return ret;

end:
        pr_err("Exercise%d stop..\n", exer);
        return ret;
}