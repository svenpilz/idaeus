#include "mailbox.h"
#include <stdio.h>

/*
 * Address  | Size | Name          | Description                 | R/W
 * ---------|------|---------------|-----------------------------|----
 * 2000B880 |    4 | Read          | Receiving mail.             | R
 * 2000B890 |    4 | Poll          | Receive without retrieving. | R
 * 2000B894 |    4 | Sender        | Sender information.         | R
 * 2000B898 |    4 | Status        | Information.                | R
 * 2000B89C |    4 | Configuration | Settings.                   | RW
 * 2000B8A0 |    4 | Write         | Sending mail.               | W
 */

#define MAILBOX_BASE_ADDRESS 0x2000B880
const uint32_t MAILBOX_READ_ADDRESS = MAILBOX_BASE_ADDRESS;
const uint32_t MAILBOX_POLL_ADDRESS = MAILBOX_BASE_ADDRESS + 0x10;
const uint32_t MAILBOX_SENDER_ADDRESS = MAILBOX_BASE_ADDRESS + 0x14;
const uint32_t MAILBOX_STATUS_ADDRESS = MAILBOX_BASE_ADDRESS + 0x18;
const uint32_t MAILBOX_CONFIG_ADDRESS = MAILBOX_BASE_ADDRESS + 0x1C;
const uint32_t MAILBOX_WRITE_ADDRESS = MAILBOX_BASE_ADDRESS + 0x20;

void mailbox_write(uint8_t mailbox, void* mail) {
	if ((uint32_t)mail & 0xF != 0) {
		puts("[ERROR] mailbox_write: pointer not aligned.");
		return;
	}
	
	if (mailbox > 15) {
		puts("[ERROR] mailbox_write: mailbox > 15.");
		return;
	}
	
	uint32_t* write = (uint32_t*)MAILBOX_WRITE_ADDRESS;
	uint32_t* status = (uint32_t*)MAILBOX_STATUS_ADDRESS;
	mail += 0x40000000 + mailbox;
	
	while (*status & 0x80000000 == 0) {
	
	}
	
	*write = (uint32_t)mail;
	
}

int mailbox_read(uint8_t mailbox, uint32_t* mail) {
	if (mailbox > 15) {
		puts("[ERROR] mailbox_write: mailbox > 15.");
		return -1;
	}
	
	uint32_t* read = (uint32_t*)MAILBOX_READ_ADDRESS;
	uint32_t* status = (uint32_t*)MAILBOX_STATUS_ADDRESS;
	
	//do {
		//while ((*status & 0x40000000) == 0) {
	
		//}
	
		*mail = *read;
	//} while ((*mail & 0xF) != mailbox);
	
	*mail &= 0xFFFFFFF0;
	return 0;
}
