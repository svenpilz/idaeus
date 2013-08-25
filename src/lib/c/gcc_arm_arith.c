/**
 * unsigned integer division
 */
unsigned int __aeabi_uidiv(unsigned int a, unsigned int b) {
	unsigned int q;
	
	for (q= 0; a > b; a-=b) {
		++q;
	}
	
	return q;
}

