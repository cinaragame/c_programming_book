
/* !!!!!!! trailing blanks, tabs ? !!!!!!! */

#include <stdio.h>

#define N_COLUMN 20 /* character limit for breaking column */
#define TAB_SIZE 8 /* how many blanks make a tab */
#define MAX_SIZE 500 /* maximum input size */

int getLine(char line[], int size);
int findBlank(char array[], int size, int column);

/* breaks long input lines into two or more shorter lines after last non-blank
character that occurs before N_COLUMN
 * if very lomg lines:
 * if no blanks or tabs before N_COLUMN
 */
int main(void)
{
	int 	i;					/* for output table printing */
	int 	in_cnt, out_cnt;	/* input and output array char-counters */
	int 	in_size;			/* input size */
	int		column, blank;		/* position of last possible char (column) and closest blank in each iteration */
	char	input[MAX_SIZE];		/* input string */
	char 	output[MAX_SIZE];	/* output string */

	while(in_size = getLine(input, MAX_SIZE))
	{
		/* guard clause: excludes final '\n' from input size */
		if(input[in_size-1] == '\n')
			in_size = in_size - 1;

		in_cnt = out_cnt = 0;
		column = N_COLUMN;

		/* while there's room in output array */
		/* && while we haven't finished reading the input array */
		while(out_cnt < MAX_SIZE-1 && in_cnt < in_size)
		{
			blank = findBlank(input, in_size, column);
				if(blank < out_cnt)
					blank = column;
			/* copy from out_cnt until blank */
			for( ; out_cnt < blank; in_cnt++, out_cnt++)
				output[out_cnt] = input[in_cnt];
			output[out_cnt] = '\n';
			out_cnt++;
			if(input[in_cnt] == ' ')
				in_cnt++;
			column = blank + N_COLUMN + 1;
		}
		//is this necessary? check GDB
		output[out_cnt] = '\0';
		out_cnt++;

		/**** OUTPUT ****/
		/* printing table */
		printf("\n");
		for(i = 0; i < N_COLUMN; i++)
			printf("%d", (i+1)%10);
		/* printing resulting output */
		printf("\n%s", output);
	}
}

/* finds first blank in array before n-th column
 * parameters: array to search, array size, n-th column
 * return: place of first blank before of n-th column
 * -1 if no blanks found
 * -2 if size < column
 */
int findBlank(char array[], int size, int column)
{
	/* guard clause not to access non-string memory */
	if(size < column)
		return -2;

	/* >= or just > ? */
	while(column >= 0)
	{
	if(array[column] == ' ' || array[column] == '\n')
        return column;
	column--;
	}
    
	return -1;
}
    
/* gets user input and stores it in array
 * parameters: array to store input
 * maximum array size * return: number of chars in array
 */
int getLine(char line[], int size)
{
	int c, i;

	i = 0;
	while(i < size-1 && (c = getchar()) != EOF && c != '\n')
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
