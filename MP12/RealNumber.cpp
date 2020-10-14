/*
For the RealNumber derived class, we made constructors that defined the numbertype and the value specified. To set the value, we simply set value = to the argument given. To get the value, we return the value in the function. The magnitude is simply the value, but if the value is negative, we change it to positive. The real (op) real functions change the values by performing the operation between the current value and the argument.
*/
#include "RealNumber.h"

//to_String converts real and imaginary components to string of type a+bi
string RealNumber::to_String(void){
	stringstream my_output;
	my_output << value;
	return my_output.str();
}


// Constructors

RealNumber::RealNumber()
{
	value = 0;
	NumberType = REAL;

}

RealNumber::RealNumber(double rval)
{
	value = rval;
	NumberType = REAL;
}

RealNumber::RealNumber(const RealNumber& other) 
{
	
	value = other.value;
	NumberType = REAL;
}

//setter and getter functions

void RealNumber::set_value(double rval)
{

	value = rval;

}


double RealNumber::get_value(void) const
{
	return value;

}

double RealNumber::magnitude()
{
	if(value < 0)
		value = value * -1;
	return value;
}


// Overload functions 


//Real
RealNumber RealNumber::operator+(const RealNumber& arg){

	RealNumber sum = value + arg.value;
	return sum;
}

RealNumber RealNumber::operator-(const RealNumber& arg){

	RealNumber sub = value - arg.value;
	return sub;
}

RealNumber RealNumber::operator*(const RealNumber& arg){

	RealNumber mult = value * arg.value;
	return mult;
}

RealNumber RealNumber::operator/(const RealNumber& arg){

	RealNumber div = value / arg.value;
	return div;
}


//Polar

PolarNumber RealNumber::operator+(const PolarNumber& arg){

	PolarNumber sum;
	return sum;

}

PolarNumber RealNumber::operator-(const PolarNumber& arg){

	PolarNumber sub;
	return sub;
}

PolarNumber RealNumber::operator*(const PolarNumber& arg){

	PolarNumber mult;
	return mult;
}

PolarNumber RealNumber::operator/(const PolarNumber& arg){

	PolarNumber div;
	return div;
}


//Rational

RealNumber RealNumber::operator + (const RationalNumber& arg)
{
	RealNumber sum = value + (arg.get_numerator() / arg.get_denominator());
	return sum;
}

RealNumber RealNumber::operator - (const RationalNumber& arg)
{
	RealNumber sub = value - (arg.get_numerator() / arg.get_denominator());
	return sub; 
}

RealNumber RealNumber::operator * (const RationalNumber& arg)
{
	RealNumber mult = value * (arg.get_numerator() / arg.get_denominator());
	return mult;
}

RealNumber RealNumber::operator / (const RationalNumber& arg)
{
	RealNumber div = value / (arg.get_numerator() / arg.get_denominator());
	return div;

}




