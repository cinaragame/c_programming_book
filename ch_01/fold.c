/* trailing blanks, tabs ? */
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
	int i;
	int in_cnt, out_cnt;
	int in_size;
	int column, blank;
	char input[MAX_SIZE], output[MAX_SIZE];

// !!!!!!!!!!!!!!! have to insert tab size in questions
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
			/* blank for current line size smaller or equal max column */
			/* makes filling up until the n-th column with a visible char possible */
			/* useful for limit case example a 20 char + new line ("This is a short text\n") in max 20 column output */
			/*if((out_cnt + N_COLUMN) < column)//((in_size - out_cnt) <= N_COLUMN) // what if out_cnt + N_COLUMN < column
				blank = in_size+1; /* puts blank after last valid char */
			/* else */
			/*else
			{*/
				blank = findBlank(input, in_size, column);
				if(blank < out_cnt)
					blank = column;
			//}
			/* copy from out_cnt until blank */
			for( ; out_cnt < blank; in_cnt++, out_cnt++)
				output[out_cnt] = input[in_cnt];
			output[out_cnt] = '\n';
			out_cnt++;
			if(input[in_cnt] == ' ')
				in_cnt++;
			column = blank + N_COLUMN;// + 1;
		}
		//is this necessary? check GDB
		output[out_cnt] = '\0';
		out_cnt++;

		/**** OUTPUT ****/
		/* printing table */
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
	if(array[column] == ' ')
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
