#include <stdio.h>

#define MAX_SIZE		1000000/* input array maximum char size */
#define IN_C			1	/* identifies that we are inside C-type comment */
#define IN_CPP			2	/* identifies that we are inside CPP-type comment */
#define OUT				0	/* identifies that we are outside a comment */

int defineCommentStatus(char input[], int in_cnt, int current_status);
int getInput(char input[], int size);

/* program removes all comments from C program
 * handle quoted strings and character constants properly
 * C comments do not nest
 */
int main(void)
{
	int		in_cnt, out_cnt;		/* input and output iteration counters */
	int		last_status;			/* variable for helping identify comments-ending */
	char	input[MAX_SIZE];		/* input array */
	char	output[MAX_SIZE];		/* output array */
	int		comment_status;			/* comment IN-OUT status array */

	while(getInput(input, MAX_SIZE))
	{
		comment_status = OUT;

		/* transcribe text without comments */
		for(in_cnt = 0, out_cnt = 0; input[in_cnt] != '\0'; ++in_cnt)
		{
			last_status = comment_status;
			comment_status = defineCommentStatus(input, in_cnt, comment_status);
			/* compensations in in_cnt when closing comments */
			if(last_status == IN_C && comment_status == OUT)
			{
				in_cnt++; /* in order to skip the '/' after the '*' */
				continue;
			}
			else if(last_status == IN_CPP && comment_status == OUT)
			{
				in_cnt--; /* to compensate and not skip the '\n' */
				continue;
			}
			/* normal case: transcribe from input to output */
			if(comment_status == OUT)
			{
				output[out_cnt] = input[in_cnt];
				out_cnt++;
			}
		}
		output[out_cnt] = '\0';
		printf("\n\n---- OUTPUT ----\n\n%s\n", output);
		return 0;
	}
}

/* defines if inside or outside comment depending on current "comment status" and current chars
 * parameters:		array to analise (input), location of char to analise in array (in_cnt),
 					current in/out comment status (current_status)
 * return (macros): OUT: for when finding end to a comment
 *					IN_C: when entering C-type comment
 *					IN_CPP:	when entering CPP-type comment
 *					current_status: when status was not modified
 */
int defineCommentStatus(char input[], int in_cnt, int current_status)
{
	/* first check for start of comment */ 
	if(current_status == OUT && input[in_cnt] == '/')
	{
		if(input[in_cnt+1] == '*')
			return IN_C;
		else if(input[in_cnt+1] == '/')
			return IN_CPP;
	}
	/* second: if inside comment, check for getting out */
	if(current_status == IN_C && input[in_cnt] == '*' && input[in_cnt+1] == '/')
			return OUT;
	if(current_status == IN_CPP && input[in_cnt] == '\n')
			return OUT;
	return current_status;
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
