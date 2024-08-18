/* definition */
#define SUCCESS		(1)
#define TRUE		(1)
#define FAIL		(0)
#define FALSE		(0)

#define POSITIVE	(1)
#define NEGATIVE	(-1)
#define NOSIGN		(0)

#define LINE_MAX_LENGTH  (1000)
#define IDX_MAX_LENGTH   (1000)

#define SPACE		' '

#define LOG_LEVEL	(0)

#define C_PRINTF(level, fmt, ...) \
	do {					\
		if (level <= LOG_LEVEL) {	\
			switch (level) {	\
				case C_ERROR:					\
					printf("[C_ERROR]" fmt, __VA_ARGS__);	\
					break;					\
				case C_WARNING:					\
					printf("[C_WARNING]" fmt, __VA_ARGS__); \
					break;					\
				case C_DEBUG:					\
					printf("[C_DEBUG]" fmt, __VA_ARGS__);	\
					break;					\
				default :					\
					break;					\
			}							\
		}								\
	} while (0);

#define pr_err(fmt, ...) \
	do {		\
		printf("[Err]" fmt, __VA_ARGS__);\
	} while(0);

#define pr_info(fmt, ...) \
	do {		\
		printf("[Info]" fmt, __VA_ARGS__);\
	} while(0);

#define EXERCISE(_exer, _file) \
{	\
	.exer_num = _exer, \
	.file_name = _file \
}

enum {
	C_ERROR    = 0,
	C_WARNING  = 1,
	C_DEBUG    = 2,
};

typedef struct {
	int exer_num;
	char* file_name;
} exercise_info;

/* file */
int fileOpen(exercise_info* exer, FILE** pptr);

/* char */
int Is_Digits(int x);
int Is_Letters(int x);
int Is_Ascii(int x);
void itoa_recursive(int n, char* s);

/* String related */
int str_IsWhiteSpace(char* s, int idx);
int str_GetSign(char* s, int idx);
int str_IsDigits(char* s, int i);
void str_reverse(char s[]);
void str_reverse_recur(char* s, int left, int right);

/* Stack */
void  Stack_init(void);
void  Stack_push(int data);
int   Stack_pop(int *x);
void  Stack_top(int *x);
int   Stack_isEmpty(void);
int   Stack_getLength(void);
void  Stack_print(void);
void  Stack_show_top(void);
void  Stack_clear(void);
void  Stack_swap_top_two_ele(void);
void  Stack_duplicate(void);


int getline_from_txt(FILE** pptr, char* input);
int getchar_from_txt(FILE** pptr, char* ch);