/*
Polar numbers have a phase and a magnitude so we setup the constructor so that the number will have those parameters. To get the mag or phase, we just return the value in the given function. To set them, we make them equal to their given function arguments.
*/
#include "PolarNumber.h"

//to_String converts mag and phase components to string of type a<b
string PolarNumber::to_String(void){

        stringstream my_output;
	my_output << magComponent<< "<"<<180.0*phaseComponent/M_PI;
        return my_output.str();

}

PolarNumber::PolarNumber()
{
	magComponent = 0;
	phaseComponent = 0;
	NumberType = POLAR;
}
		
PolarNumber::PolarNumber(double magnitude, double phase)
{
	magComponent = magnitude;
	phaseComponent = phase;
	NumberType = POLAR;
}

PolarNumber::PolarNumber( const PolarNumber& other )
{
	magComponent = other.magComponent;
	phaseComponent = other.phaseComponent;
	NumberType = POLAR;
}		
void PolarNumber::set_magComponent(double mval)
{
	magComponent = mval;

}
void PolarNumber::set_phaseComponent(double phval)
{
	phaseComponent = phval;

}

double PolarNumber::get_magComponent(void) const
{
	return magComponent;
}


double PolarNumber::get_phaseComponent(void) const
{
	return phaseComponent;
}

void PolarNumber::set_value (double mval, double phval)
{

	magComponent = mval;
	phaseComponent = phval;
	
}

PolarNumber PolarNumber::operator + (const PolarNumber& arg)
{

}
PolarNumber PolarNumber::operator - (const PolarNumber& arg)
{

}
PolarNumber PolarNumber::operator * (const PolarNumber& arg)
{

}
PolarNumber PolarNumber::operator / (const PolarNumber& arg)
{
}

		//Operation overload for PolarNumber (op) RealNumber		
PolarNumber PolarNumber::operator + (const RealNumber& arg)
{

}
PolarNumber PolarNumber::operator - (const RealNumber& arg)
{
}
PolarNumber PolarNumber::operator * (const RealNumber& arg)
{
}
PolarNumber PolarNumber::operator / (const RealNumber& arg)
{
}

		//Operation overload for PolarNumber (op) RationalNumber	
PolarNumber PolarNumber::operator + (const RationalNumber& arg)
{
}
PolarNumber PolarNumber::operator - (const RationalNumber& arg)
{
}
PolarNumber PolarNumber::operator * (const RationalNumber& arg)
{
}
PolarNumber PolarNumber::operator / (const RationalNumber& arg)
{
}




