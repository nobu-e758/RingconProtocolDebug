#include <iostream>
#include "io.hpp"

// 最初に64byte確保
unsigned char buf[0x40];


void step0() {
	memset(buf, 0, 0x40);
	// set blocking to ensure command is recieved:
	//hid_set_nonblocking(this->handle, 0);

	// Enable vibration
	printf("\n* Enabling vibration...\n");
	buf[0] = 0x01; // Enabled
	send_subcommand(0x1, 0x48, buf, 1);

	// Enable IMU data
	printf("\n* Enabling IMU data...\n");
	buf[0] = 0x01; // Enabled
	send_subcommand(0x01, 0x40, buf, 1);


	// Set input report mode (to push at 60hz)
	// x00	Active polling mode for IR camera data. Answers with more than 300 bytes ID 31 packet
	// x01	Active polling mode
	// x02	Active polling mode for IR camera data.Special IR mode or before configuring it ?
	// x21	Unknown.An input report with this ID has pairing or mcu data or serial flash data or device info
	// x23	MCU update input report ?
	// 30	NPad standard mode. Pushes current state @60Hz. Default in SDK if arg is not in the list
	// 31	NFC mode. Pushes large packets @60Hz
	printf("\n* Set input report mode to 0x30...\n");
	buf[0] = 0x30;
	send_subcommand(0x01, 0x03, buf, 1);

	//GetCalibrationData();

	//if (this->left_right == 1 || this->left_right == 3) {
	//	printf("Successfully initialized %s!\n", this->name.c_str());
	//	return 0;
	//}

	//int Ringconretries = 0;
}


void step1() {
	// Enable MCU data
	int retries2 = 0;
	//while (1) {
	{
		printf("\n* Enabling MCU data 22 1\n");
		buf[0] = 0x01; // Enabled - 00 = suspend, 01 = resume
		send_subcommand(0x01, 0x22, buf, 1);

		//int retries = 0;
		//while (1) {
		//	int res = hid_read_timeout(handle, buf, sizeof(buf), 64);
		//	/*for (int i = 0; i <= 100; i++) {
		//		printf("%i: %02x ", i, buf[i]);
		//	}
		//	printf("\n");
		//	printf("\n");*/
		//	if (*(u16*)&buf[0xD] == 0x2280)
		//		goto step3;

		//	retries++;
		//	if (retries > 8 || res == 0)
		//		break;
		//}
		//retries2++;
		/*if (retries2 > 8) {
			goto step20;
		}	*/
	}
}


void step3() {
	// Enable MCU polling
	//printf("Enabling MCU polling...\n");
	//buf[0] = 0x01; // Enabled empty 0, 5, 6 Not 1 49:1 56:1 2 49:2A 56:0
	//send_subcommand(0x01, 0x24, buf, 1);
	//retries2 = 0;
	//Set MCU Mode
	//while (1) {
	{
		printf("\n* Enabling MCU data 21 21 0 3...\n");
		static int output_buffer_length = 49; //CTCAER - USE THIS - for some reason the pkt sub command was positioned right but all the subcommand 21 21 stuff was offset plus one byte
		int res = 0;

		memset(buf, 0, sizeof(buf));
		//auto hdr = (brcm_hdr*)buf;
		//auto pkt = (brcm_cmd_01*)(hdr+1);
		//hdr->cmd = 0x01;
		//hdr->rumble[0] = timing_byte & 0xF;
		//timing_byte++;
		buf[10] = 0x21;
		buf[11] = 0x21;
		buf[12] = 0x00;
		buf[13] = 0x03;
		//pkt->subcmd_21_21.mcu_cmd = 0x21; // Set MCU mode cmd
		//pkt->subcmd_21_21.mcu_subcmd = 0x00; // Set MCU mode cmd
		//pkt->subcmd_21_21.mcu_mode = 0x03; // MCU mode - 1: Standby, 4: NFC, 5: IR, 6: Initializing/FW Update?

		buf[48] = mcu_crc8_calc(buf + 12, 36);
		/*for (int i = 0; i <= 48; i++) {
			printf("%i: %02x ", i, buf[i]);
		}
		printf("\n");*/

		hid_write(buf, output_buffer_length);
		//int retries = 0;

		//while (1) {
		//	res = hid_read_timeout(handle, buf, sizeof(buf), 64);
		//	/*for (int i = 0; i <= 100; i++) {
		//		printf("%i: %02x ", i, buf[i]);
		//	}
		//	printf("\n");*/
		//	if (buf[0] == 0x21) {
		//		// *(u16*)buf[18]LE x04 in lower than 3.89fw, x05 in 3.89
		//		// *(u16*)buf[20]LE x12 in lower than 3.89fw, x18 in 3.89
		//		if (buf[15] == 0x01 && buf[22] == 0x03) // Mcu mode is standby
		//			goto step5;
		//	}
		//	retries++;
		//	if (retries > 8 || res == 0) {
		//		break;
		//	}
		//}
		//retries2++;
		/*if (retries2 > 8) {
			goto step20;
		}*/
	}
}

void step5() {

}


int main()
{
	printf("\n");
	printf("###############################\n");
	printf("# Step[0]                     #\n");
	printf("###############################\n");
	step0();

	printf("\n");
	printf("###############################\n");
	printf("# Step[1]                     #\n");
	printf("###############################\n");
	step1();

	printf("\n");
	printf("###############################\n");
	printf("# Step[3]                     #\n");
	printf("###############################\n");
	step3();

	printf("\n");
	printf("###############################\n");
	printf("# Step[5]                     #\n");
	printf("###############################\n");
	step5();
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
