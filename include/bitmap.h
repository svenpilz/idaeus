#ifndef INCLUDE_BITMAP_H
#define INCLUDE_BITMAP_H

#include <stdint.h>

typedef unsigned int bit_position_t;
typedef unsigned int bitmap_bucket_t;

typedef struct {
	bitmap_bucket_t* buckets;
	size_t number_of_buckets;
} bitmap_t;

size_t bitmap_bucket_count(bit_position_t number_of_bits);

void bitmap_unset_all(bitmap_t* m);
void bitmap_set_all(bitmap_t* m);

int bitmap_is_set(bitmap_t* m, bit_position_t b);

int bitmap_unset(bitmap_t* m, bit_position_t b);
int bitmap_set(bitmap_t* m, bit_position_t b);

int bitmap_unset_range(bitmap_t* m, bit_position_t b, bit_position_t number_of_bits);
int bitmap_set_range(bitmap_t* m, bit_position_t b, bit_position_t number_of_bits);

int bitmap_first_unset(bitmap_t* m, bit_position_t* b);
int bitmap_first_set(bitmap_t* m, bit_position_t* b);

int bitmap_first_unset_range(bitmap_t* m, bit_position_t* b, bit_position_t number_of_bits);
int bitmap_first_set_range(bitmap_t* m, bit_position_t* b, bit_position_t number_of_bits);

bit_position_t bitmap_count_unset(bitmap_t* m);
bit_position_t bitmap_count_set(bitmap_t* m);

#endif
