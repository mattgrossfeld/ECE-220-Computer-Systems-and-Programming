/*
Our program takes inputs omega1, omega2, omegac and uses them to get N, T, and dt.
We then make Voutcur = 0 if N is less than 0. Then, we use a for loop to that uses the equation
we were given to calculate Voutnew, Voutprev, and Voutcur for n number of steps. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	double omega1, omega2, omegac, T, dt;
	int N ;

	//Scan the inputs from the user.
	scanf("%lf %lf %lf", &omega1, &omega2, &omegac);
	
	T = 3 * 2 * M_PI / omega1;      // Total time
    	N = 20 * T / (2 * M_PI / omega2);   // Total number of time steps
    	dt = T / N;             // Time step

	int i,n = 0;
	double Voutnew = 0, Voutcur = 0, Voutprev = 0;

	//Write your code here!


	if(N < 0)						// Check if N < 0 
	{
		Voutcur = 0;				// Set Voutcur = 0 if N <0 
		return 0;		
	}
	
	for(i = 0; i < N - 1; i++)		// Calculate the values for Voutnew at every increment
									
	{


		Voutnew = (1/((1/(sqrt(2)*dt*omegac))+(1/(dt*dt*omegac*omegac)))*(((2/(dt*dt*omegac*omegac))-1)*Voutcur + ((1/(sqrt(2)*dt*omegac))-(1/(dt*dt*omegac*omegac)))*Voutprev + sin(omega1*(n-1)*dt) + 0.5*sin(omega2*(n-1)*dt)));
														// Equation for Voutnew
		Voutprev = Voutcur;								// Set Voutprev to Voutcur for next iteration
		Voutcur = Voutnew;								// Set Voutcur to Voutnew for next iteration
		n = n + 1;										// increment n
		printf("%lf\n",Voutcur);						// Print out values for Voutcur
		
		
		
	}
		
	
	return 0;
}
