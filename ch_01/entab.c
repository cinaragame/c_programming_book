#include <stdio.h>

#define IN_BLANK	1	/* inside blank streak */
#define OUT_BLANK	0	/* outside blank streak */
#define MAX_LEN		100	/* maximum array length */
#define TAB_SIZE	8

/* definitions for tabs and blanks solution array */
#define	TNB			2	/* tabs and blanks */
#define TABS		0	/* position of tabs in TNB array */
#define BLANKS		1	/* position of blanks in TNB array */

int getLine(char line[], int max_len);
void tabsAndBlanksToPosition(int initial, int final, int tab_size, int solution[]);
int insertTabsandBlanks(char output[], int position, int solution[]);

/* replaces blank streaks for the minimum number of tabs and blanks required to maintain formatting of text */
int main(void)
{
	int in, out, c;				/* input & output iteration control & char control */
	int init_pos, target_pos;	/* initial blank position & start of new word position */
	int blank_state;			/* whether we are inside or outside blank streak */
	int tbs[TNB];				/* tabs and blanks solution array */	
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
			}
			/* when leaving blank streak */
			else if(blank_state == IN_BLANK)
			{
				blank_state = OUT_BLANK;
				target_pos = in;
				/* calculating and inserting tabs and blanks */
				tabsAndBlanksToPosition(init_pos, target_pos, TAB_SIZE, tbs);
				out = insertTabsandBlanks(output, out, tbs);
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

/* inserts defined number pf tabs and blanks to the output array
 * parameters:	output array, start position in output array,
 				solution array[TABS, BLANKS] (with tabs and blanks quantity)
 * return:		new position in array
 */
int insertTabsandBlanks(char output[], int position, int solution[])
{
	while(solution[TABS] > 0)
	{
		output[position] = '\t';
		position++;
		solution[TABS]--;
	}
	while(solution[BLANKS] > 0)
	{
		output[position] = ' ';
		position++;
		solution[BLANKS]--;
	}
	return position;
}

/* calculates minimal tabs and blanks needed between initial and final position
 * parameters:	initial position, final position, tab size,
 				solution array[TABS, BLANKS] (with tabs and blanks quantity)
 * return:		no return - answer is given directly in solution array
 */
void tabsAndBlanksToPosition(int initial, int final, int tab_size, int solution[])
{
	int init_tabs, final_tabs;
	/* needed to check if there are tabstops between positions */
	init_tabs = initial / tab_size;
	final_tabs = final / tab_size;
	/* if there are tabstops between positions */
	if(final_tabs > init_tabs)
	{
		solution[TABS] = final_tabs - init_tabs;
		solution[BLANKS] = final - (final_tabs * tab_size);
	}
	/* if there aren't tabstops between positions */
	else
	{
		solution[TABS] = 0;
		solution[BLANKS] = final - initial;
	}
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
