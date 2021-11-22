// GBN_client.cpp : 定义控制台应用程序的入口点。
//
#include <stdlib.h>
#include <WinSock2.h>
#include <time.h>
#include <stdio.h>
#include <fstream>
#pragma comment(lib,"ws2_32.lib")
#define SERVER_PORT 12340 //接收数据的端口号
#define SERVER_IP "127.0.0.1" // 服务器的 IP 地址
const int BUFFER_LENGTH = 1026;
const int PACKET_NUM = 25;
const int SEQ_SIZE = 20;//接收端序列号个数，为 1~20
const int RECV_WIND_SIZE = 10;//接收窗口大小为 10，SR中应满足接收窗口和发送窗口的大小和小于等于总序列号个数

int curSeq;                 //当前数据包的 seq
int curAck;                 //当前等待确认的 ack
int totalPacket;            //需要发送的包总数
BOOL ack[SEQ_SIZE];//接收方窗口

int totalSeq;   //已发送的包的总数
int totalAck;   //确认收到（ack）的包的总数
/****************************************************************/
/* -time 从服务器端获取当前时间
-quit 退出客户端
-testgbn [X][Y] 测试 GBN 协议实现可靠数据传输
[X] [0,1] 模拟数据包丢失的概率
[Y] [0,1] 模拟 ACK 丢失的概率
*/
/****************************************************************/
void printTips() {
	printf("*****************************************\n");
	printf("| -time to get current time             |\n");
	printf("| -quit to exit client                  |\n");
	printf("| -testsr [X] [Y] to test the gbn       |\n");
	printf("*****************************************\n");
}
//************************************
// Method: lossInLossRatio
// FullName: lossInLossRatio
// Access: public
// Returns: BOOL
// Qualifier: 根据丢失率随机生成一个数字，判断是否丢失,丢失则返回TRUE，否则返回 FALSE
// Parameter: float lossRatio [0,1]
//************************************
BOOL lossInLossRatio(float lossRatio) {
	int lossBound = (int)(lossRatio * 100);
	int r = rand() % 100;
	if (r < lossBound) {
		return TRUE;
	}
	return FALSE;
}
//************************************
// Method: seqIsAvailable
// FullName: seqIsAvailable
// Access: public
// Returns: bool
// Qualifier: 当前序列号seq是否可接收
//************************************
bool seqRecvAvailable(int seq) {
	int step;
	step = seq - curAck;
	step = step >= 0 ? step : step + SEQ_SIZE;
	//序列号是否在当前接收窗口之内
	if (step >= RECV_WIND_SIZE) {
		return false;
	}
	return true;
}
int main(int argc, char* argv[])
{
	//加载套接字库（必须）
	WORD wVersionRequested;
	WSADATA wsaData;
	//套接字加载时错误提示
	int err;
	//版本 2.2
	wVersionRequested = MAKEWORD(2, 2);
	//加载 dll 文件 Scoket 库
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		//找不到 winsock.dll
		printf("WSAStartup failed with error: %d\n", err);
		return 1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();
	}
	else {
		printf("The Winsock 2.2 dll was found okay\n");
	}
	SOCKET socketClient = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrServer;
	addrServer.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(SERVER_PORT);
	//接收缓冲区
	char buffer[BUFFER_LENGTH];
	ZeroMemory(buffer, sizeof(buffer));
	int len = sizeof(SOCKADDR);
	//为了测试与服务器的连接，可以使用 -time 命令从服务器端获得当前时间
	//使用 -testgbn [X] [Y] 测试 GBN 其中[X]表示数据包丢失概率
	// [Y]表示 ACK 丢包概率
	printTips();
	int ret;
	int interval = 1;//收到数据包之后返回 ack 的间隔，默认为 1 表示每个都返回 ack，0 或者负数均表示所有的都不返回 ack
	char cmd[128];
	float packetLossRatio = 0; //默认包丢失率 0.2
	float ackLossRatio = 0; //默认 ACK 丢失率 0.2
	//用时间作为随机种子，放在循环的最外面
	srand((unsigned)time(NULL));

	//将测试数据读入内存
	std::ifstream icin;
	icin.open("../test.txt");
	char data[1024 * PACKET_NUM];
	ZeroMemory(data, sizeof(data));
	icin.read(data, 1024 * PACKET_NUM);
	icin.close();
	totalPacket = sizeof(data) / 1024;
	int recvSize;
	while (true) {
		gets_s(buffer);
		ret = sscanf(buffer, "%s%f%f", &cmd, &packetLossRatio, &ackLossRatio);
		//开始 SR 测试，使用 SR 协议实现 SR 可靠文件传输
		if (!strcmp(cmd, "-testsr")) {
			for (int i = 0; i < SEQ_SIZE; ++i) {
				ack[i] = FALSE;
			}
			FILE* fcli = fopen("clientfile.txt", "w+");
			printf("%s\n", "Begin to test GBN protocol, please don't abort the process");
			printf("The loss ratio of packet is %.2f,the loss ratio of ack is % .2f\n", packetLossRatio, ackLossRatio);
			int waitCount = 0;
			int stage = 0;
			curAck = 0;
			BOOL b;
			unsigned char u_code;//状态码
			unsigned short seq;//包的序列号
			unsigned short recvSeq;//接收窗口大小为 1，已确认的序列号
			unsigned short waitSeq;//等待的序列号
			sendto(socketClient, "-testsr", strlen("-testgbn") + 1, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
			while (true)
			{
				//等待 server 回复设置 UDP 为阻塞模式
				recvfrom(socketClient, buffer, BUFFER_LENGTH, 0, (SOCKADDR*)&addrServer, &len);
				if (strcmp(buffer, "All Finished!\n") == 0) {
					fclose(fcli);
					break;
				}
				switch (stage) {
				case 0://等待握手阶段
					u_code = (unsigned char)buffer[0];
					if ((unsigned char)buffer[0] == 205)
					{
						printf("Ready for file transmission\n");
						buffer[0] = 200;
						buffer[1] = '\0';
						sendto(socketClient, buffer, 2, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
						stage = 1;
						recvSeq = 0;
					}
					break;
				case 1://等待接收数据阶段
					seq = (unsigned short)buffer[0];
					//随机法模拟包是否丢失
					b = lossInLossRatio(packetLossRatio);
					if (b) {
						printf("The packet with a seq of %d loss\n", seq);
						continue;
					}
					printf("recv a packet with a seq of %d\n", seq);
					//在窗口内即接收
					if (seqRecvAvailable(seq)) {
						fwrite(&buffer[1], sizeof(char), strlen(buffer) - 1, fcli);
						//输出数据
						printf("%s\n",&buffer[1]);
						recvSeq = seq;
						ack[recvSeq - 1] = TRUE;
						buffer[0] = seq;
						buffer[1] = '\0';
						if (seq - 1 == curAck) {
							int nxt;
							for (int i = 0; i < RECV_WIND_SIZE; ++i) {
								nxt = (curAck + i) % SEQ_SIZE;
								if (!ack[nxt])break;
							}
							curAck = (nxt + 1) % SEQ_SIZE;
						}
					}
					else {
						//如果当前一个包都没有收到，则等待 Seq 为 1 的数据包，不是则不返回 ACK（因为并没有上一个正确的 ACK）
						recvSeq = seq;
						buffer[0] = recvSeq;
						buffer[1] = '\0';
					}
					b = lossInLossRatio(ackLossRatio);
					if (b) {
						printf("The ack of %d loss\n", (unsigned char)buffer[0]);
						continue;
					}
					sendto(socketClient, buffer, 2, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
					printf("send a ack of %d\n", (unsigned char)buffer[0]);
					break;
				}
				Sleep(500);
			}
		}
		//printf("%s\n", buffer);
		sendto(socketClient, buffer, strlen(buffer) + 1, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
		ret = recvfrom(socketClient, buffer, BUFFER_LENGTH, 0, (SOCKADDR*)&addrServer, &len);
		printf("%s\n", buffer);
		if (!strcmp(buffer, "Good bye!")) {
			break;
		}
		printTips();
	}
	//关闭套接字
	closesocket(socketClient);
	WSACleanup();
	return 0;
}