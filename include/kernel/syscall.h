#ifndef INCLUDE_KERNEL_SYSCALL_H
#define INCLUDE_KERNEL_SYSCALL_H

#include <stdint.h>

typedef uint32_t syscall_id_t;

void handle_syscall_request(syscall_id_t id);

#endif
