/*
This is for Rational numbers and we first constructed the contructors and then we finished the setter and getter functions for rational numbers and then the operator overloads for each different operation like Rational Real or Rational Polar or Rational Rational operations.
*/
#include "RationalNumber.h"

//to_String converts numerator and denominator to string of type num/denom
string RationalNumber::to_String(void){
	stringstream my_output;
	my_output << numerator << "/" << denominator;
	return my_output.str();
}

RationalNumber::RationalNumber()
{
	numerator = 0;
	denominator = 0;
	NumberType = RATIONAL;
}

RationalNumber::RationalNumber(int numer, int denom)
{
	numerator = numer;
	denominator = denom;
	NumberType = RATIONAL;
}

RealNumber::RationalNumber( const RationalNumber& other )
{
	numerator = other.numerator;
	denominator = other.denominator;
	NumberType = RATIONAL;
}

//setter and getter functions

void RationalNumber::set_numerator(int numer)
{
	numerator = numer;

}
void RationalNumber::set_denominator(int denom)
{
	denominator = denom;

}
int RationalNumber::get_numerator(void) const
{
	return numerator;

}

int RationalNumber::get_denominator(void) const
{
	return denominator;

}

void RationalNumber::set_value (int numer, int denom)
{

	numerator = numer;
	denominator = denom;
}
int RationalNumber::gcd(int a, int b)
{
	while(a!=b)
	{
		if(a > b)
			a  = a - b;
		else
			b = b - a;
	}
	return a;
}
double RationalNumber::magnitude()
{
	if((numerator/denominator) < 0)
		return (-1) * (numerator/denominator);
	return (numerator/denominator);
}
double RationalNumber::decimal_value() const
{
	
	return numerator/denominator;

}


RationalNumber RationalNumber::operator + (const RationalNumber& arg)
{
	RationalNumber sum = (double)numerator/(double)denominator + (arg.get_numerator()/arg.get_denominator());
	return sum;
}
RationalNumber RationalNumber::operator - (const RationalNumber& arg)
{
	RationalNumber sub = (double)numerator/(double)denominator - (arg.get_numerator()/arg.get_denominator());
	return sub;
}
RationalNumber RationalNumber::operator * (const RationalNumber& arg)
{
	RationalNumber mult = (double)numerator/(double)denominator * (arg.get_numerator()/arg.get_denominator());
	return mult;
}
RationalNumber RationalNumber::operator / (const RationalNumber& arg)
{
	RationalNumber div = ((double)numerator/(double)denominator) / (arg.get_numerator()/arg.get_denominator());
	return div;
}

	
PolarNumber RationalNumber::operator + (const PolarNumber& arg)
{

}
PolarNumber RationalNumber::operator - (const PolarNumber& arg)
{
}
PolarNumber RationalNumber::operator * (const PolarNumber& arg)
{

}
PolarNumber RationalNumber::operator / (const PolarNumber& arg)
{

}

		
RealNumber RationalNumber::operator + (const RealNumber& arg)
{
	RealNumber sum = (double)numerator/(double)denominator + (arg.get_value());
	return sum;
}
RealNumber RationalNumber::operator - (const RealNumber& arg)
{
	RealNumber sum = (double)numerator/(double)denominator - (arg.get_value());
	return sum;
}
RealNumber RationalNumber::operator * (const RealNumber& arg)
{
	RealNumber sum = (double)numerator/(double)denominator * (arg.get_value());
	return sum;
}
RealNumber RationalNumber::operator / (const RealNumber& arg)
{
	RealNumber sum = (double)numerator/(double)denominator / (arg.get_value());
	return sum;
}







