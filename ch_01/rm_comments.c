#include <stdio.h>

#define MAX_SIZE		100	/* input array maximum char size */
#define NTYPE_CMNTS 	3	/* number of different comment signal types */
#define C_BEGIN			0	/* identifies classic C comment starter:	" /(asterisk) " */
#define C_END			1	/* identifies classic C comment finisher:	" (asterisk)/ " */
#define CPP				2	/* identifies C++ type comments: from " // " till end-of-line */
#define IN_C			1	/* identifies that we are inside C-type comment */
#define IN_CPP			2	/* identifies that we are inside CPP-type comment */
#define OUT				0	/* identifies that we are outside a comment */

int getInput(char input[], int size);
void find_comment(char array[], int size, int comment[]);

/* FOR NOW, PROGRAM DOES NOT DEAL WITH MULTIPLE COMMENTS, MAYBE WE DON'T NEED THE 
	FIND COMMENT FUNCATION AS WE DESIGNED IF */

/* program removes all comments from C program
 * handle quoted strings and character constants properly
 * C comments do not nest
 */
int main(void)
{
	int		i;						/* generic iteration counter */
	int		in_cnt, out_cnt;		/* input and output iteration counters */
	char	input[MAX_SIZE];		/* input array */
	char	output[MAX_SIZE];		/* output array */
	int		comment[NTYPE_CMNTS];	/* comment placement array */
	int		comment_status;			/* comment IN-OUT status array */

	while(getInput(input, MAX_SIZE))
	{
		comment_status = OUT;
		/* comment array starter */
		i = 0;
		while (i < NTYPE_CMNTS)
		{
			comment[i] = -1;
			i++;
		}
		find_comment(input, MAX_SIZE, comment);

		/* transcribe text without comments */
		for(in_cnt = 0, out_cnt = 0; input[in_cnt] != '\0'; ++in_cnt)
		{
			/* first check for start of comment */ 
			if(comment_status == OUT)
			{
				if(in_cnt == comment[C_BEGIN])
					comment_status = IN_C;
				else if(in_cnt == comment[CPP])
					comment_status = IN_CPP;
			}
			/* second: if inside comment, check for getting out */
			if(comment_status == IN_C)
			{
				if(in_cnt == comment[C_END])
				{
					comment_status = OUT;
					in_cnt++; /* in order to skip the '/' after the '*' */
				}
				continue;
			}
			if(comment_status == IN_CPP)
			{
				if(input[in_cnt] == '\n')
				{
					comment_status = OUT;
					in_cnt--; /* to compensate and not skip the '\n' */
				}
				continue;
			}
			/* normal case: transcribe from input to output */
			output[out_cnt] = input[in_cnt];
			out_cnt++;
		}
		output[out_cnt] = '\0';
		printf("\n\n---- OUTPUT ----\n\n%s\n", output);
		return 0;
	}
}

/* locates start and end of comment
 * parameters: 	array to analyze (line[]), array size (size),
 				array to store comment location (comment[])
 * return: 		no return, but changes "comment[]"
 * limitations:	function doesn't consider nested comments, returning
 				the last seen location of comment-signaling characters
 */
void find_comment(char array[], int size, int comment[])
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
				comment[CPP] = i;	
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

int getInput(char input[], int size)
{
	int i, c;

	i = 0;
	while(i < size-1 && (c = getchar()) != EOF)
	{
		input[i] = c;
		i++;
	}
	input[i] = '\0';	
	return i;
}
