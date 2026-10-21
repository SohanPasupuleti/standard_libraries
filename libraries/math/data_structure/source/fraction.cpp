#ifndef __FRACTION_CPP__
#define __FRACTION_CPP__
	
	#include <fraction.hpp>
	
	Fraction::Fraction()
	{
		numerator = 0;
		denominator = 1;
		sign = 0;
	}
	
	Fraction::Fraction(size_t initial_numerator, size_t initial_denominator, bool initial_sign)
	{
		numerator = initial_numerator;
		denominator = initial_denominator;
		sign = initial_sign;
	}

	Fraction operator * (const Fraction& fraction_A, const Fraction& fraction_B)
	{
		return Fraction
		(
			fraction_A.numerator * fraction_B.numerator,
			fraction_A.denominator * fraction_B.denominator,
			fraction_A.sign ^ fraction_B.sign
		);
	}

#endif