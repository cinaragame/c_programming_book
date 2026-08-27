#include <stdio.h>

#define IN_BLANK	1	/* inside blank streak */
#define OUT_BLANK	0	/* outside blank streak */
#define MAX_LEN		100	/* maximum array length */
#define TAB_SIZE	4
#define	TNB			2	/* tabs and blanks */
#define TABS		0	/* position of tabs in TNB array */
#define BLANKS		1	/* position of blanks in TNB array */

int getLine(char line[], int max_len);
void tabsAndBlanksToPosition(int initial, int final, int tab_size, int solution[]);

/* replaces blank streaks for the minimum number of tabs and blanks required to maintain formatting of text */
int main(void)
{
	int in, out, c;				/* input & output iteration control & char control variables */
	int init_pos, target_pos;	/* initial blank position & start of new word position */
	int blank_state;			/* whether we are inside or outside blank streak */
	int tbs[TNB];				/* tabs and blanks */	
	char input[MAX_LEN];		/* stores original input */
	char output[MAX_LEN];		/* stores resulting output */

	while(getLine(input, MAX_LEN))
	{
		blank_state = OUT_BLANK;
		for(in = 0, out = 0; (c = input[in]) != '\0'; in++)
		{
			/* when entering or staying in blank streak */
			if(c == ' ')
			{
				if(blank_state == OUT_BLANK)
				{
					blank_state = IN_BLANK;
					init_pos = in;
				}
				else continue;
			}
			/* when leaving blank streak */
			else if(blank_state == IN_BLANK)
			{
				blank_state = OUT_BLANK;
				target_pos = in;
				/* calculating tabs and blanks to insert */
				tabsAndBlanksToPosition(init_pos, target_pos, TAB_SIZE, tbs);
				/* inserting tabs and blanks */
				while(tbs[TABS] > 0)
				{
					output[out] = '\t';
					out++;
					tbs[TABS]--;
				}
				while(tbs[BLANKS] > 0)
				{
					output[out] = ' ';
					out++;
					tbs[BLANKS]--;
				}
				output[out] = c;
				out++;
			}
			/* when outside blank streak */
			else
			{
				output[out] = c;
				out++;
			}
		}
		output[out] = '\0';
		printf("%s", output);
	}
}

/* calculates how many tabs can be used between initial and final position
 * parameters:	initial position, final position, tab size
 * return:		number of tabs that fit between initial and final positions
 */
void tabsAndBlanksToPosition(int initial, int final, int tab_size, int solution[])
{
	int i, rest;

	/* find out how many multiples of tab size there are between initial and final */
	i = 0;
	solution[TABS] = 0;
	while(initial + i <= final)
	{
		rest = (initial + i) % tab_size;
		if(rest == 0)
			solution[TABS]++;
		i++;
	}
	solution[BLANKS] = rest;
}

/* stores input from stdin in array, respecting string formatting (ending with \0)
 * parameters:	array to store input, array size
 * return:		input length
 */
int getLine(char line[], int max_len)
{
	int i, c;

	i = 0;
	while(i < max_len-1 && (c = getchar()) != EOF && c != '\n')
	{
		line[i] = c;
		i++;
	}
	if(c == '\n')
	{
		line[i] = c;
		i++;
	}
	line[i] = '\0';

	return i;
}
