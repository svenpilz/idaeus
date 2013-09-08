#include <bitmap.h>
#include <string.h>

static const bit_position_t bits_per_bucket = sizeof(bitmap_bucket_t) * 8;

size_t bitmap_bucket_count(bit_position_t number_of_bits) {
	if (number_of_bits % bits_per_bucket == 0) {
		// number_of_bits is a multiple if bits_per_bucket
		return number_of_bits / bits_per_bucket;
	} else {
		// round up
		return number_of_bits / bits_per_bucket + 1;
	}
}

void bitmap_unset_all(bitmap_t* m) {
	memset(m->buckets, 0, m->number_of_buckets * sizeof(bitmap_bucket_t));
}

void bitmap_set_all(bitmap_t* m) {
	memset(m->buckets, 0xff, m->number_of_buckets * sizeof(bitmap_bucket_t));
}

int bitmap_unset(bitmap_t* m, bit_position_t b) {
	return bitmap_unset_range(m, b, 1);
}

int bitmap_set(bitmap_t* m, bit_position_t b) {
	return bitmap_set_range(m, b, 1);
}

int bitmap_unset_range(bitmap_t* m, bit_position_t b, bit_position_t number_of_bits) {
	if ((b+number_of_bits-1)/bits_per_bucket >= m->number_of_buckets) {
		return -1;
	}
	
	for (bit_position_t i = b; i < b + number_of_bits; ++i) {
		m->buckets[i/bits_per_bucket] ^= (1 << i % bits_per_bucket);
	}
	
	return 0;
}

int bitmap_set_range(bitmap_t* m, bit_position_t b, bit_position_t number_of_bits) {
	if ((b+number_of_bits-1)/bits_per_bucket >= m->number_of_buckets) {
		return -1;
	}

	for (bit_position_t i = b; i < b + number_of_bits; ++i) {
		m->buckets[i/bits_per_bucket] |= (1 << i % bits_per_bucket);
	}
	
	return 0;
}

int bitmap_is_set(bitmap_t* m, bit_position_t b) {
	return (m->buckets[b/bits_per_bucket] & (1 << b % bits_per_bucket)) != 0;
}

int bitmap_first_unset(bitmap_t* m, bit_position_t* b) {
	return bitmap_first_unset_range(m, b, 1);
}

int bitmap_first_set(bitmap_t* m, bit_position_t* b) {
	return bitmap_first_set_range(m, b, 1);
}

int bitmap_first_unset_range(bitmap_t* m, bit_position_t* b, bit_position_t number_of_bits) {
	if ((number_of_bits-1)/bits_per_bucket >= m->number_of_buckets) {
		return -1;
	}

	uint in_string = 0;
	bit_position_t current_range = 0;
	for (size_t bucket = 0; bucket < m->number_of_buckets; ++bucket) {
		if (m->buckets[bucket] == 0) {
			// all bits are unset
			
			if (!in_string) {
				*b = bucket*bits_per_bucket;
			}
			
			in_string = 1;
			current_range += bits_per_bucket;
		} else if (m->buckets[bucket] == ~0) {
			// all bits are set
			
			in_string = 0;
			current_range = 0;
			
			continue;
		} else {
			// some are set, some are unset
			for (bit_position_t i = bucket*bits_per_bucket;
				i < bucket*bits_per_bucket + bits_per_bucket; ++i) {
				
				if (!bitmap_is_set(m, i)) {
					if (!in_string) {
						*b = i;
					}
					
					in_string = 1;
					++current_range;
				} else {
					in_string = 0;
					current_range = 0;
				}
				
				if (current_range >= number_of_bits) {
					break;
				}
			}
		}
		
		if (current_range >= number_of_bits) {
			break;
		}
	}
	
	if (current_range >= number_of_bits) {
		return 0;
	} else {
		// no range found
		return -1;
	}
}

int bitmap_first_set_range(bitmap_t* m, bit_position_t* b, bit_position_t number_of_bits) {
	if ((number_of_bits-1)/bits_per_bucket >= m->number_of_buckets) {
		return -1;
	}

	uint in_string = 0;
	bit_position_t current_range = 0;
	for (size_t bucket = 0; bucket < m->number_of_buckets; ++bucket) {
		if (m->buckets[bucket] == 0) {
			// all bits are unset
			
			in_string = 0;
			current_range = 0;
			
			continue;
			
			
		} else if (m->buckets[bucket] == ~0) {
			// all bits are set
			
			if (!in_string) {
				*b = bucket*bits_per_bucket;
			}
			
			in_string = 1;
			current_range += bits_per_bucket;
		} else {
			// some are set, some are unset
			for (bit_position_t i = bucket*bits_per_bucket;
				i < bucket*bits_per_bucket + bits_per_bucket; ++i) {
				
				if (bitmap_is_set(m, i)) {
					if (!in_string) {
						*b = i;
					}
					
					in_string = 1;
					++current_range;
				} else {
					in_string = 0;
					current_range = 0;
				}
				
				if (current_range >= number_of_bits) {
					break;
				}
			}
		}
		
		if (current_range >= number_of_bits) {
			break;
		}
	}
	
	if (current_range >= number_of_bits) {
		return 0;
	} else {
		// no range found
		return -1;
	}
}

bit_position_t bitmap_count_unset(bitmap_t* m) {
	bit_position_t count = 0;
	
	for (size_t bucket = 0; bucket < m->number_of_buckets; ++bucket) {
		if (m->buckets[bucket] == 0) {
			count += bits_per_bucket;
		} else if (m->buckets[bucket] == ~0) {
			continue;
		} else {
			for (bit_position_t i = bucket*bits_per_bucket;
				i < bucket*bits_per_bucket + bits_per_bucket; ++i) {
				
				if (!bitmap_is_set(m, i)) {
					++count;
				}
			}
		}
		
	}
	
	return count;
}

bit_position_t bitmap_count_set(bitmap_t* m) {
	bit_position_t count = 0;
	
	for (size_t bucket = 0; bucket < m->number_of_buckets; ++bucket) {
		if (m->buckets[bucket] == 0) {
			continue;
		} else if (m->buckets[bucket] == ~0) {
			count += bits_per_bucket;
		} else {
			for (bit_position_t i = bucket*bits_per_bucket;
				i < bucket*bits_per_bucket + bits_per_bucket; ++i) {
				
				if (bitmap_is_set(m, i)) {
					++count;
				}
			}
		}
		
	}
	
	return count;
}

