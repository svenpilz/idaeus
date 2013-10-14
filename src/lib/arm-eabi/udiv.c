/**
 * unsigned integer division
 */
 
/*
// Slow text book division ... O( floor(a/b) )
unsigned int __aeabi_uidiv(unsigned int a, unsigned int b) {
	unsigned int q;
	
	for (q= 0; a >= b; a-=b) {
		++q;
	}
	
	return q;
}
*/

/**
 * Binary long division ... O( sizeof(int) )
 * @todo Use remainder for modulo.
 */
unsigned int __aeabi_uidiv(unsigned int dividend, unsigned int divisor) {
	unsigned int q = 0;
	unsigned int r = 0;
	
	for (int i = sizeof(unsigned int) * 8 - 1; i >= 0; --i) {
		r <<= 1;
		r += (dividend >> i) & 0x1;
		
		if (r >= divisor) {
			r -= divisor;
			q |= 1 << i;
		}
	}
	
	return q;
}

