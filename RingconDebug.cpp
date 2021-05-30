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

	printf("\n* Enabling MCU data 21 21 1 1...\n");

	static int output_buffer_length = 49; //CTCAER
	int res = 0;

	memset(buf, 0, sizeof(buf));
	//auto hdr = (brcm_hdr*)buf;
	//hdr->cmd = 0x01;
	//hdr->rumble[0] = timing_byte & 0xF;
	//timing_byte++;
	buf[10] = 0x21;
	buf[11] = 0x21;
	buf[12] = 0x01;
	buf[13] = 0x01;

	buf[48] = mcu_crc8_calc(buf + 12, 36);

	/*for (int i = 0; i <= 48; i++) {
		printf("%i: %02x ", i, buf[i]);
	}
	printf("\n");
	printf("\n");*/

	hid_write(buf, output_buffer_length);
	//int retries = 0;

	//while (1) {
	//	res = hid_read_timeout(handle, buf, sizeof(buf), 64);
	//	/*for (int i = 0; i <= 100; i++) {
	//		printf("%i: %02x ", i, buf[i]);
	//	}
	//	printf("\n");
	//	printf("\n");*/
	//	if (buf[0] == 0x21) {
	//		if (buf[15] == 0x09 && buf[17] == 0x01) // Mcu mode is external ready
	//			goto step6;
	//	}
	//	retries++;
	//	if (retries > 8 || res == 0)
	//		break;
	//}
}

void step6() {
	//retries2 = 0;
	printf("\n* Get ext data 59.\n");

	//while (1) {
	{
		static int output_buffer_length = 49; //CTCAER
		int res = 0;

		memset(buf, 0, sizeof(buf));
		//auto hdr = (brcm_hdr*)buf;
		//hdr->cmd = 0x01;
		//hdr->rumble[0] = timing_byte & 0xF;
		//timing_byte++;
		buf[10] = 0x59;

		/*for (int i = 0; i <= 48; i++) {
			printf("%i: %02x ", i, buf[i]);
		}
		printf("\n");
		printf("\n");*/

		hid_write(buf, output_buffer_length);
		//int retries = 0;

		//while (1) {
		//	res = hid_read_timeout(handle, buf, sizeof(buf), 64);
		//	/*for (int i = 0; i <= 100; i++) {
		//		printf("%i: %02x ", i, buf[i]);
		//	}
		//	printf("\n");
		//	printf("\n");*/
		//	if (buf[0] == 0x21) {
		//		if (buf[14] == 0x59 && buf[16] == 0x20) { // Mcu mode is ringcon ready (Note:0x20 is the Ringcon ext device id - it may also be the fm_main_ver) No ringcon is buf[15]=fe. With ringcon buf[15]=0
		//			goto step7;
		//		}
		//	}
		//	retries++;
		//	if (retries > 8 || res == 0)
		//		break;
		//}
		//retries2++;
		//if (retries2 > 28 || res == 0) {
		//	printf("Enabling IMU data...\n");
		//	buf[0] = 0x01; // Enabled
		//	send_subcommand(0x01, 0x40, buf, 1);
		//	//GetCalibrationData();

		//	printf("Successfully initialized but no Ringcon detected %s!\n", this->name.c_str());
		//	return 0;
		//}
	}
}

void step7() {
	//ringconattached = true;
	// Enable IMU data
	printf("\n* Enabling IMU data 3...\n");
	buf[0] = 0x03; // Ringcon IMU enabled 
	send_subcommand(0x01, 0x40, buf, 1);

	int res = 0;
	int retries = 0;
	//while (1) {
		//res = hid_read_timeout(handle, buf, sizeof(buf), 64);
		/*for (int i = 0; i <= 60; i++) {
			printf("%i: %02x ", i, buf[i]);
		}
		printf("\n");
		printf("\n");*/
		//if (buf[0] == 0x21) {
		//	if (buf[14] == 0x40) {
				//break;
				printf("\n* Enabling IMU data 1...\n");
				buf[0] = 0x02;
				send_subcommand(0x01, 0x40, buf, 1);
				buf[0] = 0x01;
				send_subcommand(0x01, 0x40, buf, 1);
	//			Ringconretries++; //Was having issues with the Gyro being screwy sometimes.
	//			if (Ringconretries <= 1) {
	//				GetCalibrationData();
	//				goto step1;
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//	}
	//	retries++;
	//	if (retries > 20 || res == 0)
	//		break;
	//}

	//unsigned long long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	//IntToByteArray(timestamp);

	//while (1) {
	{
		printf("\n* Get ext dev in format config 5C...\n");

		static int output_buffer_length = 49; //CTCAER 
		//int res = 0;

		memset(buf, 0, sizeof(buf));
		//auto hdr = (brcm_hdr*)buf;
		//hdr->cmd = 0x01;
		//hdr->rumble[0] = timing_byte & 0xF;
		//timing_byte++;
		buf[10] = 0x5C;
		buf[11] = 0x06;
		buf[12] = 0x03;
		buf[13] = 0x25;
		buf[14] = 0x06;
		buf[19] = 0x1C;
		buf[20] = 0x16;
		buf[21] = 237;// 0xCD;//+
		buf[22] = 52;// 0xA6;//+
		buf[23] = 54;// 0x2B;//+ These change but appear to be connected with the last values
		buf[27] = 10;//timestampbuffer[0];// 27-32 = timestamp
		buf[28] = 100;//timestampbuffer[1];
		buf[29] = 11;//timestampbuffer[2];
		buf[30] = 230;//timestampbuffer[3];
		buf[31] = 169;//timestampbuffer[4];
		buf[32] = 34;//timestampbuffer[5];
		buf[33] = 0x00;//timestampbuffer[6];
		buf[34] = 0x00;//timestampbuffer[7]; 
		buf[35] = 0x04;
		buf[43] = 0x90;
		buf[44] = 0xA8;
		buf[45] = 225;// 0xC1;//+
		buf[46] = 52;// 0x34;// 0xA6;//+
		buf[47] = 54;// 0x36;// 0x2B;//+ These numbers have something to do with the input report from 40 3 */

		//21/10/20  92 6 3 37 6 0 0 0 0 28 22 205 166 43 0 0 0 197 20 147 187 160 13 0 0 4 0 0 0 0 0 0 0 144 168 193 166 43 0
		//08/10/20  92 6 3 37 6 0 0 0 0 28 22 237 52  54 0 0 0 10 100  11 230 169 34 0 0 4 0 0 0 0 0 0 0 144 168 225 52  54 0

		/*for (int i = 0; i <= 48; i++) {
			printf("%i: %02x ", i, buf[i]);
		}
		printf("\n");
		printf("\n");*/

		hid_write(buf, output_buffer_length);
		//int retries = 0;
		//while (1) {
		{
			//res = hid_read_timeout(handle, buf, sizeof(buf), 64);
			/*for (int i = 0; i <= 60; i++) {
				printf("%i: %02x ", i, buf[i]);
			}
			printf("\n");
			printf("\n");*/
			//if (buf[0] == 0x21) {
			//	if (buf[14] == 0x5C) { // Ringcon config set
			//		goto step8;
			//	}
			//	/*if (buf[14] == 0x40) { // Sensor put to sleep for some reason. Try again.
			//		printf("Enabling IMU data 1...\n");
			//		buf[0] = 0x01; // Ringcon IMU enabled
			//		send_subcommand(0x01, 0x40, buf, 1);
			//		goto step1;
			//	}*/
			//}
			//retries++;
			//if (retries > 8 || res == 0)
			//	break;
		}
	}

} 

void step8() {
	//while (1) {
	{
		printf("\n* Start external polling 5A...\n"); //This may only be for the config stuff. The app turns it off after config then calls the MCU again. If you call the 5c command when the polling is enbled, it will fail.

		static int output_buffer_length = 49; //CTCAER
		//int res = 0;

		memset(buf, 0, sizeof(buf));
		//auto hdr = (brcm_hdr*)buf;
		//hdr->cmd = 0x01;
		//hdr->rumble[0] = timing_byte & 0xF;
		//timing_byte++;
		buf[10] = 0x5A;
		buf[11] = 0x04;
		buf[12] = 0x01;
		buf[13] = 0x01;
		buf[14] = 0x02;

		/*for (int i = 0; i <= 48; i++) {
			printf("%i: %02x ", i, buf[i]);
		}
		printf("\n");
		printf("\n");*/

		hid_write(buf, output_buffer_length);
		//int retries = 0;

		//while (1) {
		//	res = hid_read_timeout(handle, buf, sizeof(buf), 64);
		//	/*for (int i = 0; i <= 63; i++) {
		//		printf("%i: %02x ", i, buf[i]);
		//	}
		//	printf("\n");
		//	printf("\n");*/
		//	if (buf[0] == 0x21) {
		//		if (buf[14] == 0x5A) {// Mcu mode is ringcon polling
		//			goto step13;
		//		}
		//	}
		//	retries++;
		//	if (retries > 8 || res == 0)
		//		break;
		//}
	}
}

void set_ext_config(int a, int b, int c, int d) {
	unsigned char buf[0x400];
	memset(buf, 0, 0x40);

	//while (1) {
	{
		printf("\n* Set Ext Config 58\n");

		static int output_buffer_length = 49; //CTCAER - USE THIS - for some reason the pkt sub command was positioned right but all the subcommand 21 21 stuff was offset plus one byte
		//int res = 0;

		memset(buf, 0, sizeof(buf));
		//auto hdr = (brcm_hdr*)buf;
		//hdr->cmd = 0x01;
		//hdr->rumble[0] = timing_byte & 0xF;
		//timing_byte++;
		buf[10] = 0x58;
		buf[11] = a;
		buf[12] = b;
		buf[13] = c;
		buf[14] = d;

		/*for (int i = 0; i <= 48; i++) {
			printf("%i: %02x ", i, buf[i]);
		}
		printf("\n");
		printf("\n");*/

		hid_write(buf, output_buffer_length);
		//int retries = 0;

		/*for (int i = 0; i < 50; i++) {
			res = hid_read_timeout(handle, buf, sizeof(buf), 64);
			for (int i = 0; i <= 100; i++) {
				printf("%i: %02x ", i, buf[i]);
			}
			printf("\n");
			printf("\n");*/


			//while (1) {
			//	buf[0] != 21;
			//}

			//while (1) {}

		//while (1) {
		//	res = hid_read_timeout(handle, buf, sizeof(buf), 64);
		//	//for (int i = 0; i <= 60; i++) {
		//	//	printf("%i: %02x ", i, buf[i]);
		//	//}
		//	//printf("\n");
		//	//printf("\n");
		//	if (buf[0] == 0x21) {
		//		if (buf[14] == 0x58) {
		//			return;
		//		}
		//	}
		//	retries++;
		//	if (retries > 8 || res == 0) {
		//		break;
		//	}
		//}
	}
}

void step13() {
	//Set ext config
	/*printf("Set Ext Config 58 - 4 5 1 2...\n");
	set_ext_config(0x04, 0x05, 0x01, 0x02);
	printf("Set Ext Config 58 - 4 0 0 2...\n");
	set_ext_config(0x04, 0x00, 0x00, 0x02);
	printf("Set Ext Config 58 - 4 4 5 2...\n");
	set_ext_config(0x04, 0x04, 0x05, 0x02);
	printf("Set Ext Config 58 - 4 0 0 2...\n");
	set_ext_config(0x04, 0x00, 0x00, 0x02);
	printf("Set Ext Config 58 - 4 4 1 2...\n");
	set_ext_config(0x04, 0x04, 0x01, 0x02);
	printf("Set Ext Config 58 - 4 4 2 2...\n");
	set_ext_config(0x04, 0x04, 0x02, 0x02);
	printf("Set Ext Config 58 - 4 4 4 2...\n");
	set_ext_config(0x04, 0x04, 0x04, 0x02);
	printf("Set Ext Config 58 - 4 4 3 2...\n");
	set_ext_config(0x04, 0x04, 0x03, 0x02);
	printf("Set Ext Config 58 - 4 4 32 2...\n");
	set_ext_config(0x04, 0x04, 0x32, 0x02);
	printf("Set Ext Config 58 - 4 0 1 2...\n");
	set_ext_config(0x04, 0x00, 0x01, 0x02);
	printf("Set Ext Config 58 - 4 0 0 2...\n");
	set_ext_config(0x04, 0x00, 0x00, 0x02);
	printf("Set Ext Config 58 - 4 4 1 2...\n");
	set_ext_config(0x04, 0x04, 0x01, 0x02);
	printf("Set Ext Config 58 - 4 4 2 2...\n");
	set_ext_config(0x04, 0x04, 0x02, 0x02);
	printf("Set Ext Config 58 - 4 4 4 2...\n");
	set_ext_config(0x04, 0x04, 0x04, 0x02);
	printf("Set Ext Config 58 - 4 4 3 2...\n");
	set_ext_config(0x04, 0x04, 0x03, 0x02);
	printf("Set Ext Config 58 - 4 0 0 2...\n");
	set_ext_config(0x04, 0x00, 0x00, 0x02);
	printf("Set Ext Config 58 - 4 4 11 2...\n");
	set_ext_config(0x04, 0x04, 0x11, 0x02);*/
	printf("\n* Set Ext Config 58 - 4 4 12 2...\n");
	set_ext_config(0x04, 0x04, 0x12, 0x02);
	/*printf("Set Ext Config 58 - 4 4 13 2...\n");
	set_ext_config(0x04, 0x04, 0x13, 0x02);*/
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

	printf("\n");
	printf("###############################\n");
	printf("# Step[6]                     #\n");
	printf("###############################\n");
	step6();

	printf("\n");
	printf("###############################\n");
	printf("# Step[7]                     #\n");
	printf("###############################\n");
	step7();

	printf("\n");
	printf("###############################\n");
	printf("# Step[8]                     #\n");
	printf("###############################\n");
	step8();

	printf("\n");
	printf("###############################\n");
	printf("# Step[13]                    #\n");
	printf("###############################\n");
	step13();


	printf("\n* Successfully initialized !\n");
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
