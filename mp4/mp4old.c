#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


double abs_double(double y)
{
    //Change this to return the absolute value of y i.e |y|

	double absolute_value = fabs(y);
    return absolute_value;
}

double fx_val(double a, double b, double c, double d, double e, double x)
{

    //Change this to return the value of the polynomial at the value x

	double y;
	y = a * (x*x*x*x) + b * (x*x*x) + c * (x*x) + d * x + e;
    return y;
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{

    //Change this to return the value of the derivative of the polynomial at the value x

	double y_derivative;
	y_derivative = 4*a*(x*x*x) + 3*b*(x*x) + 2*c*x + d;
    return y_derivative;
}

double fx_ddval(double a, double b, double c, double d, double e, double x)
{

    //Change this to return the value of the double derivative of the polynomial at the value x

	double y_derivative2;
	y_derivative2 = 12*a*(x*x) +6*b*x + 2*c;
    return y_derivative2;
}


double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the root found starting from the initial point x
	double xnew;

	
	xnew = x - (2*fx_dval(a,b,c,d,e,x) * fx_ddval(a,b,c,d,e,x))/(2*(fx_dval(a,b,c,d,e,x) * 
	fx_dval(a,b,c,d,e,x)) - (fx_dval(a,b,c,d,e,x) * fx_ddval(a,b,c,d,e,x)));
		
    return xnew;
}

int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
	//Change this to return the upper bound on the number of roots of the polynomial in the interval (l, r)
	
	
	
	int Vl = 0; 
	int Vr = 0; 
	int findRoots;

		// Left Bound
		if ( (a > 0 && (4*a*l+b) < 0) || (a < 0 && (4*a*l+b) > 0) )
			Vl++;

		if (( (4*a*l+b) > 0 && (6*a*l*l+ 3*b*l+c) < 0 ) || ( (4*a*l+b) < 0 && (6*a*l*l + 3*b*l+c) > 0) )
			Vl++;

	    if (( (6*a*l*l+ 3*b*l+c) > 0 && (4*a*l*l*l+3*b*l*l+2*c*l+d) < 0 ) || ( (6*a*l*l+ 3*b*l+c) < 0 && (4*a*l*l*l+3*b*l*l+2*c*l+d) > 0) )
			Vl++;

	    if ( ( (4*a*l*l*l+3*b*l*l+2*c*l+d) > 0 && (a*l*l*l*l+b*l*l*l+c*l*l+d*l+e) < 0 ) || ( (4*a*l*l*l+3*b*l*l+2*c*l+d) < 0 && (a*l*l*l*l+b*l*l*l+c*l*l+d*l+e) > 0) )
			Vl++;

		// Right Bound
		if ( ( a > 0 && (4*a*r+b) < 0 ) || ( a < 0 && (4*a*r+b) > 0) )
			Vr++;

	    if ( ( (4*a*r+b) > 0 && (6*a*r*r+ 3*b*r+c) < 0 ) || ( (4*a*r+b) < 0 && (6*a*r*r + 3*b*r+c) > 0) )
			Vr++;

	    if (( (6*a*r*r+ 3*b*r+c) > 0 && (4*a*r*r*r+3*b*r*r+2*c*r+d) < 0 ) || ( (6*a*r*r+ 3*b*r+c) < 0 && (4*a*r*r*r+3*b*r*r+2*c*r+d) > 0 ) )
			Vr++;

		if ( ( (4*a*r*r*r+3*b*r*r+2*c*r+d) > 0 && (a*r*r*r*r+b*r*r*r+c*r*r+d*r+e) < 0 ) || ( (4*a*r*r*r+3*b*r*r+2*c*r+d) < 0 && (a*r*r*r*r+b*r*r*r+c*r*r+d*r+e) > 0 ))
			Vr++;

		    //Return difference of roots

		findRoots = Vl - Vr;

	    if (findRoots < 0)
			findRoots = -findRoots;

	return findRoots;

}

int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	FILE *in;

	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);
    
    //The values are read into the variable a, b, c, d, e, l and r.
    //You have to find the bound on the number of roots using rootbound function.
    //If it is > 0 try to find the roots using newrfind function.
    //You may use the fval, fdval and fddval funtions accordingly in implementing the halleys's method.
    

	
	// Initalize counters
	
	int total_roots = 0;
	int endroots = l-1;
	int bound_on_roots = rootbound(a,b,c,d,e,r,l);
	double roots = 0;
	double k, i;
	double iteration;

	if (bound_on_roots == 0)
	{
		printf("The polynomial has no roots in the given interval.\n");
	}

	else
	{
		for(i = l; i <= r; i += 0.5)
		{
			bound_on_roots = rootbound(a,b,c,d,e,i + 0.5, i);
		
			if ( bound_on_roots != 0) 
			{
			
	          	  for (k = 1; k <= bound_on_roots; k++)
				{
					iteration = i + k * 0.5/ bound_on_roots;
	            		        roots = newrfind_halley(a,b,c,d,e,iteration);
			
	             			   if (roots - endroots >= 0.01)
						{
	                   				 printf ("Root found: %lf\n", roots);
	                  				  total_roots++;
	                  				  endroots = roots;
			
						}
				}
			}
	}
	

		if(total_roots == 0)
		{
			printf("No roots found.\n");
		}
	
	}

    fclose(in);
    
    return 0;
}
