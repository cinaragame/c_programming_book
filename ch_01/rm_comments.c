/* program removes all comments from C program
 * handle quoted strings and character constants properly
 * C comments do not nest
 */

#define MAX_SIZE	100	/* input array maximum char size */
#define N_CMNTS 	3	/* number of different comment signal types */
#define C_BEGIN		0	/* identifies classic C comment starter:	" /(asterisk) " */
#define C_END		1	/* identifies classic C comment finisher:	" (asterisk)/ " */
#define C_PLUS		2	/* identifies C++ type comments: from " // " till end-of-line */
#define IN_CMNT		1	/* identifies that we are inside a comment */
#define OUT_CMNT	0	/* identifies that we are outside a comment */

int getLine(char line[], int size);
void find_comment(char line[], int size, int comment[]);

int main(void)
{
	int i, line_cnt;
	char input[MAX_SIZE];
	int comment[N_CMNTS];
	int comment_status;

	/* FOR FUTURE IMPROVEMENT: counts each line, so if there are multi line comments, they get identified */
	line_cnt = 0;
	while(getLine(input, MAX_SIZE))
	{
		comment_status = OUT_CMNT;
		/* comment array starter */
		i = 0;
		while (i < N_CMNTS)
		{
			comment[i] = -1;
			i++;
		}
		find_comment(input, MAX_SIZE, comment);

		/* transcribe text without comments */
		i = 0;
		while(input[i] != '\n')
		{
			/* check for comment start */
			if(comment[C_BEGIN] > -1 && comment_status == OUT_CMNT)
				comment_status = IN_CMNT;
		}
	line_cnt++;
	}







}

/* locates start and end of comment
 * parameters: 	array to analyze (line[]), array size (size),
 				array to store comment location (comment[])
 * return: 		no return, but changes "comment[]"
 * limitations:	function doesn't consider nested comments, returning
 				the last seen location of comment-signaling characters
 */
void find_comment(char line[], int size, int comment[])
{
	int i;

	i = 0;
	while(i+1 <= size)
	{
		/* COMMENT STARTERS */
		if(array[i] == '/')
		{
			/* if C++ style comment */
			if(array[i+1] == '/')
				comment[C_PP] = i;	
			/* C style comment starter */
			else if(array[i+1] == '*')
				comment[C_BEGIN] = i;
		}
		/* COMMENT FINISHERS */
		else if(array[i] == '*')
			if(array[i+1] == '/')
				comment[C_END] = i;
		i++;
	}
}

int getLine(char line[], int size)
{
	int i, c;

	i = 0;
	while(i < size && (c = getchar()) != EOF && c != '\n')
	{
		line[i] = c;
		i++;
	}
	if(c == '\n')
	{
		line[i] = c;
		i++;
	}
	
	return i;
}
