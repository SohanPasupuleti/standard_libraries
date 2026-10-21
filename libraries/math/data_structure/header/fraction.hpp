#ifndef __FRACTION_HPP__
#define __FRACTION_HPP__
	
	#include <stddef.h>
	
	struct Fraction
	{
		public:
			size_t numerator;
			size_t denominator;
			bool sign;
		
			Fraction();
			Fraction(size_t initial_numerator, size_t initial_denominator, bool initial_sign);
			
			friend Fraction operator * (const Fraction& fraction_A, const Fraction& fraction_B);
	};


#endif