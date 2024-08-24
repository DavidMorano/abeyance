/* int_fastdiv HEADER */
/* lang=C++20 */

/* perform specialized fast-integer-division */
/* version %I% last-modified %G% */


/*
 *  Copyright 2014 Maxim Milakov
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/****

	Hacker's Delight, Second Edition, Chapter 10, 
	Integer Division By Constants

****/

#ifndef _INT_FASTDIV_KJGIUHFG
#define _INT_FASTDIV_KJGIUHFG
#ifdef	__cplusplus


#include	<envstandards.h>	/* ordered first to configure */
#include	<algorithm>
#include	<utypedefs.h>
#include	<clanguage.h>


class int_fastdiv {
public:
	/* divisor != 0 */
	int_fastdiv(int divisor = 0) noex : d(divisor) {
		update_magic_numbers();
	}
	int_fastdiv& operator =(int divisor) noex {
		this->d = divisor;
		update_magic_numbers();
		return *this;
	}
	operator int() const noex {
		return d;
	}
	int d;
	int M;
	int s;
	int n_add_sign;
private:
	void update_magic_numbers() noex {
		if (d == 1) {
			M = 0;
			s = -1;
			n_add_sign = 1;
			return;
		} else if (d == -1) {
			M = 0;
			s = -1;
			n_add_sign = -1;
			return;
		}
		int p;
		unsigned int ad, anc, delta, q1, r1, q2, r2, t;
		const unsigned two31 = 0x80000000;
		ad = (d == 0) ? 1 : std::abs(d);
		t = two31 + ((unsigned int)d >> 31);
		anc = t - 1 - t % ad;
		p = 31;
		q1 = two31 / anc;
		r1 = two31 - q1 * anc;
		q2 = two31 / ad;
		r2 = two31 - q2 * ad;
		do {
			++p;
			q1 = 2 * q1;
			r1 = 2 * r1;
			if (r1 >= anc) {
				++q1;
				r1 -= anc;
			}
			q2 = 2 * q2;
			r2 = 2 * r2;
			if (r2 >= ad) {
				++q2;
				r2 -= ad;
			}
			delta = ad - r2;
		} while (q1 < delta || (q1 == delta && r1 == 0));
		this->M = q2 + 1;
		if (d < 0) {
			this->M = -this->M;
		}
		this->s = p - 32;
		if ((d > 0) && (M < 0)) {
			n_add_sign = 1;
		} else if ((d < 0) && (M > 0)) {
			n_add_sign = -1;
		} else {
			n_add_sign = 0;			
		}
	}
	friend int operator/(cint divident,const int_fastdiv& divisor) noex ;
};

int operator/(cint n,const int_fastdiv& divisor) noex {
	int q;
	q = (((unsigned long long)((long long)divisor.M * (long long)n)) >> 32);
	q += n * divisor.n_add_sign;
	if (divisor.s >= 0) {
	    /* we rely on this to be implemented as arithmetic shift */
	    q >>= divisor.s; 
	    q += (((unsigned int)q) >> 31);
	}
	return q;
}

int operator%(cint n,const int_fastdiv& divisor) noex {
	int quotient = n / divisor;
	int remainder = n - quotient * divisor;
	return remainder;
}

int operator/(const unsigned int n,const int_fastdiv& divisor) noex {
	return ((int)n) / divisor;
}

int operator%(const unsigned int n,const int_fastdiv& divisor) noex {
	return ((int)n) % divisor;
}

int operator/(const short n,const int_fastdiv& divisor) noex {
	return ((int)n) / divisor;
}

int operator%(const short n,const int_fastdiv& divisor) noex {
	return ((int)n) % divisor;
}

int operator/(const unsigned short n,const int_fastdiv& divisor) noex {
	return ((int)n) / divisor;
}

int operator%(const unsigned short n,const int_fastdiv& divisor) noex {
	return ((int)n) % divisor;
}

int operator/(const char n,const int_fastdiv& divisor) noex {
	return ((int)n) / divisor;
}

int operator%(const char n,const int_fastdiv& divisor) noex {
	return ((int)n) % divisor;
}

int operator/(const unsigned char n,const int_fastdiv& divisor) noex {
	return ((int)n) / divisor;
}

int operator%(const unsigned char n,const int_fastdiv& divisor) noex {
	return ((int)n) % divisor;
}


#endif /* __cplusplus */
#endif /* _INT_FASTDIV_KJGIUHFG */


