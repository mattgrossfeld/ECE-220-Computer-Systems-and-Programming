#include <stdio.h>
#include <math.h>
#define PI 3.14159

int main()
{
	int i, n;
	double omega1, omega2, x, y;

	//Print prompt to terminal
	// %d = integer, %f = floating, %lf = double

	printf("Enter a value for n, omega1, and omega2:\n");
	scanf("%d %lf %lf", &n, &omega1, &omega2);
	printf("n = %d , omega1 = %lf , omega2 = %lf\n", n, omega1, omega2);
	

	for (i=0; i <= n-1; i++)
	{
		x = (i * PI)/n;		
		y = sin(omega1 * x) + ((1/2) * sin(omega2 * x));
	
		printf("(%lf , %lf)\n", x, y);	 


	}
	
	return 0;
}
