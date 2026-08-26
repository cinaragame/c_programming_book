#include <stdio.h>

/*
	Function prints Fahrenheit(F)-Celsius(C) table
	for fahr = 0, 20, ..., 300
*/
int main()
{
	//Temperature variables
	float fahr, cels;
	//Fahr limit variables
	int lower, higher, increase;
	
	lower = 0;		//start temperature
	higher = 300;	//ending temperature
	increase = 20;	//increase size

	//Heading of the table
	printf("Fahrenheit\tCelsius\n");

	//Table
	fahr = lower;

	while (fahr <= higher)
	{
		cels = 5.0*(fahr-32.0)/9.0;
		printf("%7.0f\t\t%6.1f\n", fahr, cels);
		fahr += increase;
	}
}

