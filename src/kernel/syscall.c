#include <kernel/syscall.h>
#include <stdio.h>

void handle_syscall_request(syscall_id_t id) {
	printf("[DEBUG] kernel syscall: id=%u\n", id);
}
