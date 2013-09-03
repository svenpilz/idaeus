#include <kernel/error_handler.h>
#include <stdio.h>

void handle_cpu_error() {
	printf("[ERROR] kernel: handle_cpu_error called!\n");
	while(1){ }
}
