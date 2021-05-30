#include <bitset>
#include <chrono>
#include <string>
#include "tools.hpp"

#define JOYCON_VENDOR 0x057e
#define JOYCON_L_BT 0x2006
#define JOYCON_R_BT 0x2007
#define PRO_CONTROLLER 0x2009
#define JOYCON_CHARGING_GRIP 0x200e
#define L_OR_R(lr) (lr == 1 ? 'L' : (lr == 2 ? 'R' : '?'))


using namespace std;

// global var
bool bluetooth = true;
int global_count = 0;


int test0(int v) {
	return v * 2;
}


u8 mcu_crc8_calc(u8* buf, u8 size) { //CTCAER
	u8 crc8 = 0x0;

	for (int i = 0; i < size; ++i) {
		crc8 = mcu_crc8_table[(u8)(crc8 ^ buf[i])];
	}
	return crc8;
}

u8 ringmcu_crc8_calc(u8* buf, u8 size) {
	u8 crc8 = 0x0;

	for (int i = 0; i < size; ++i) {
		crc8 = ringmcu_crc8_table[(u8)(crc8 ^ buf[i])];
	}
	return crc8;
}

//
// 本来はHIDデバイスとの通信用関数であるが
// 単なるbufferダンプ関数に改造した．
//
void hid_write(unsigned char* buf, int len) {		
	printf("-------------------------------\n");
	printf("# data length : %02d (bytes)\n", len);
	printf("-------------------------------\n");
	for (int idx = 0; idx < len; idx++) {
		if ((idx > 0) && (idx % 10 == 0))
			printf("\n");
		printf(" %02X", buf[idx]);
	}
	printf("\n");
	printf("-------------------------------\n");
}

//
// 本来はHIDデバイスとの通信用関数であるが
// 単なるbufferダンプ関数に改造した．
//
void hid_exchange(unsigned char* buf, int len) {

	hid_write(buf, len);

	//int res;
	//res = hid_write(handle, buf, len);

	//if (res < 0) {
	//	printf("Number of bytes written was < 0!\n");
	//} else {
	//	printf("%d bytes written.\n", res);
	//}

	//// set non-blocking:
	//hid_set_nonblocking(handle, 1);

	//res = hid_read(handle, buf, 0x40);

	//if (res < 1) {
	//	printf("Number of bytes read was < 1!\n");
	//} else {
	//	printf("%d bytes read.\n", res);
	//}
}

void send_command(int command, uint8_t* data, int len) {
	unsigned char buf[0x40];
	memset(buf, 0, 0x40);

	if (!bluetooth) {
		buf[0x00] = 0x80;
		buf[0x01] = 0x92;
		buf[0x03] = 0x31;
	}

	buf[bluetooth ? 0x0 : 0x8] = command;
	if (data != nullptr && len != 0) {
		memcpy(buf + (bluetooth ? 0x1 : 0x9), data, len);
	}

	hid_exchange(buf, len + (bluetooth ? 0x1 : 0x9));

	if (data) {
		memcpy(data, buf, 0x40);
	}
}


void send_subcommand(int command, int subcommand, uint8_t* data, int len) {
	unsigned char buf[0x40];
	memset(buf, 0, 0x40);

	uint8_t rumble_base[9] = { (++global_count) & 0xF, 0x00, 0x01, 0x40, 0x40, 0x00, 0x01, 0x40, 0x40 };
	memcpy(buf, rumble_base, 9);

	if (global_count > 0xF) {
		global_count = 0x0;
	}

	// set neutral rumble base only if the command is vibrate (0x01)
	// if set when other commands are set, might cause the command to be misread and not executed
	//if (subcommand == 0x01) {
	//	uint8_t rumble_base[9] = { (++global_count) & 0xF, 0x00, 0x01, 0x40, 0x40, 0x00, 0x01, 0x40, 0x40 };
	//	memcpy(buf + 10, rumble_base, 9);
	//}

	buf[9] = subcommand;
	if (data && len != 0) {
		memcpy(buf + 10, data, len);
	}

	send_command(command, buf, 10 + len);

	if (data) {
		memcpy(data, buf, 0x40); //TODO
	}
}