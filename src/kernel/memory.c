#include "memory.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <bitmap.h>

#define SYMBOL(n) ((unsigned int)&__kernel_##n)

typedef unsigned int memory_page_number_t;
static bitmap_t pages;
static bit_position_t number_of_pages;
static platform_information_t* platform;

static memory_page_number_t address_to_page(unsigned int address) {
	return address / platform->memory_page_size;
}

static uint number_of_bytes(uint start_address, uint end_address) {
	return end_address - start_address + 1;
}

static void mark_pages_used(memory_page_number_t start, memory_page_number_t end) {
	bitmap_set_range(&pages, start, end-start+1);
}

int kernel_memory_init(platform_information_t* platform_information) {
	platform = platform_information;
	
	printf("kernel memory: text=0x%x - 0x%x (%u bytes), rodata=0x%x - 0x%x (%u bytes),\n"
		"               data=0x%x - 0x%x (%u bytes), bss=0x%x - 0x%x (%u bytes),\n"
		"               total size=%u bytes.\n",
		SYMBOL(text_start), SYMBOL(text_end), number_of_bytes(SYMBOL(text_start), SYMBOL(text_end)),
		SYMBOL(rodata_start), SYMBOL(rodata_end), number_of_bytes(SYMBOL(rodata_start), SYMBOL(rodata_end)),
		SYMBOL(data_start), SYMBOL(data_end), number_of_bytes(SYMBOL(data_start), SYMBOL(data_end)),
		SYMBOL(bss_start), SYMBOL(bss_end), number_of_bytes(SYMBOL(bss_start), SYMBOL(bss_end)),
		number_of_bytes(SYMBOL(start), SYMBOL(end)));
		
	if (platform->memory_size % platform->memory_page_size != 0) {
		return -1;
	}
	
	number_of_pages = platform->memory_size / platform->memory_page_size;
	pages.buckets = (bitmap_bucket_t*)SYMBOL(end);
	pages.number_of_buckets = bitmap_bucket_count(number_of_pages);
	bitmap_unset_all(&pages);
	
	mark_pages_used(0, address_to_page(SYMBOL(end)));
	mark_pages_used(address_to_page((uint)pages.buckets), address_to_page((uint)pages.buckets + pages.number_of_buckets * sizeof(bitmap_bucket_t)));
	
	uint free = bitmap_count_unset(&pages);
	printf("free %u/%u, used %u\n", free, number_of_pages, number_of_pages - free);
	
	return 0;
}
