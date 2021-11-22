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
const int SEND_WIND_SIZE = 10;//发送窗口大小为 10，GBN 中应满足 W + 1 <=N（W 为发送窗口大小，N 为序列号个数）

BOOL ack[SEQ_SIZE];         //收到 ack 情况，对应 0~19 的 ack
int curSeq;                 //当前数据包的 seq
int curAck;                 //当前等待确认的 ack
int totalPacket;            //需要发送的包总数

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
	printf("| -testgbn [X] [Y] to test the gbn      |\n");
	printf("| -testgbn_send [X] [Y] to test the gbn |\n");
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
// Qualifier: 当前序列号 curSeq 是否可用
//************************************
bool seqIsAvailable() {
	int step;
	step = curSeq - curAck;
	step = step >= 0 ? step : step + SEQ_SIZE;
	//序列号是否在当前发送窗口之内
	if (step >= SEND_WIND_SIZE) {
		return false;
	}
	if (ack[curSeq]) {
		return true;
	}
	return false;
}
//************************************
// Method: timeoutHandler
// FullName: timeoutHandler
// Access: public 
// Returns: void
// Qualifier: 超时重传处理函数，滑动窗口内的数据帧都要重传
//************************************
void timeoutHandler() {
	printf("Timer out error.\n");
	int index;
	int res = 0;
	for (int i = 0; i < SEND_WIND_SIZE; ++i) {//将已经发出去的，还没收到ack的，重新置为还没发
		index = (i + curAck) % SEQ_SIZE;
		if (ack[index] == FALSE)res++;
		ack[index] = TRUE;
	}
	totalSeq -= res; // 重置数量
	curSeq = curAck;
}
//************************************
// Method: ackHandler
// FullName: ackHandler
// Access: public
// Returns: void
// Qualifier: 收到 ack，累积确认，取数据帧的第一个字节
//由于发送数据时，第一个字节（序列号）为 0（ASCII）时发送失败，因此加一了，此处需要减一还原
// Parameter: char c
//************************************
void ackHandler(char c) {
	unsigned char index = (unsigned char)c - 1; //序列号减一
	printf("Recv a ack of %d\n", index);
	if (curAck <= index) {
		for (int i = curAck; i <= index; ++i) { //对当前的ack进行标记
			ack[i] = TRUE;
			totalAck++;
		}
		curAck = (index + 1) % SEQ_SIZE;
	}
	else {
		//这种情况可能有两种原因导致，一种是发生丢包，另一种是用于序列号循环使用
		//但考虑到发生连续好几个ack都丢了的概率较低，根据两者差值判断是哪种情况
		//ack 超过了最大值，回到了 curAck 的左边
		if (curAck - index > SEND_WIND_SIZE) {
			for (int i = curAck; i < SEQ_SIZE; ++i) {
				ack[i] = TRUE;
				totalAck++;
			}
			for (int i = 0; i <= index; ++i) {
				ack[i] = TRUE;
				totalAck++;
			}
		}
		curAck = index + 1;
	}
}
int main(int argc, char* argv[]) {
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
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
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
	for (int i = 0; i < SEQ_SIZE; ++i) ack[i] = TRUE;
	while (true) {
		gets_s(buffer);
		ret = sscanf(buffer, "%s%f%f", &cmd, &packetLossRatio, &ackLossRatio);
		//开始 GBN 测试，使用 GBN 协议实现 UDP 可靠文件传输
		if (!strcmp(cmd, "-testgbn")) {
			FILE* fcli = fopen("clientfile.txt", "w+");
			printf("%s\n", "Begin to test GBN protocol, please don't abort the process");
			printf("The loss ratio of packet is %.2f,the loss ratio of ack is % .2f\n",packetLossRatio,ackLossRatio);
			int waitCount = 0;
			int stage = 0;
			BOOL b;
			unsigned char u_code;//状态码
			unsigned short seq;//包的序列号
			unsigned short recvSeq;//接收窗口大小为 1，已确认的序列号
			unsigned short waitSeq;//等待的序列号
			sendto(socketClient, "-testgbn", strlen("-testgbn") + 1, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
			while (true) {
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
						waitSeq = 1;
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
					//如果是期待的包，正确接收，正常确认即可
					if (!(waitSeq - seq)) {
						++waitSeq;
						// 将接收的文件写入输出文件中
						fwrite(&buffer[1], sizeof(char), strlen(buffer) - 1, fcli);
						if (waitSeq == 21) {
								waitSeq = 1;
						}
						//输出数据
						printf("%s\n",&buffer[1]);
						buffer[0] = seq;
						recvSeq = seq;
						buffer[1] = '\0';
					}
					else {
						//如果当前一个包都没有收到，则等待 Seq 为 1 的数据包，不是则不返回 ACK（因为并没有上一个正确的 ACK）
						if (!recvSeq) {
							continue;
						}
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
		else if (strcmp(cmd, "-testgbn_send") == 0) {
			//进入 gbn 测试阶段
			//首先 server（server 处于 0 状态）向 client 发送 205 状态码（server进入 1 状态）
			//server 等待 client 回复 200 状态码，如果收到（server 进入 2 状态），则开始传输文件，否则延时等待直至超时
			//在文件传输阶段，server 发送窗口大小设为 20
			for (int i = 0; i < SEQ_SIZE; ++i) {
				ack[i] = TRUE;
			}
			ZeroMemory(buffer, sizeof(buffer));
			int recvSize;
			int waitCount = 0;
			printf("Begin to test GBN protocol,please don't abort the process\n");
			//加入了一个握手阶段
			//首先服务器向客户端发送一个 205 的状态码（我自己定义的）表示服务器准备好了，可以发送数据
			//客户端收到 205 之后回复一个 200 的状态码，表示客户端准备好了，可以接收数据了
			//服务器收到 200 状态码之后，就开始使用 GBN 发送数据了
			printf("Shake hands stage\n");
			int stage = 0;
			bool runningFlag = true;
			int flag = 0;
			sendto(socketClient, "-testgbn_send", strlen("-testgbn_send") + 1, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
			int iMode = 1; //1：非阻塞，0：阻塞
			ioctlsocket(socketClient, FIONBIO, (u_long FAR*)& iMode);//非阻塞设置
			while (runningFlag) {
				if (flag) {
					break;
				}
				switch (stage) {
				case 0://发送 205 阶段
					buffer[0] = 205;
					sendto(socketClient, buffer, strlen(buffer) + 1, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
					Sleep(100);
					stage = 1;
					break;
				case 1://等待接收 200 阶段，没有收到则计数器+1，超时则放弃此次“连接”，等待从第一步开始
					recvSize = recvfrom(socketClient, buffer, BUFFER_LENGTH, 0, ((SOCKADDR*)&addrServer), &len);
					if (recvSize < 0) {
						++waitCount;
						if (waitCount > 20) {
							runningFlag = false;
							printf("Timeout error\n");
							break;
						}
						Sleep(500);
						continue;
					}
					else {
						if ((unsigned char)buffer[0] == 200) {
							printf("Begin a file transfer\n");
							printf("File size is %dB, each packet is 1024B and packet total num is %d\n", sizeof(data), totalPacket);
							curSeq = 0;
							curAck = 0;
							totalSeq = 0;
							totalAck = 0;
							waitCount = 0;
							stage = 2;
						}
					}
					break;
				case 2://数据传输阶段
					if (seqIsAvailable() && totalSeq < totalPacket) {//第二个判断是处理已经发出但因为部分ack丢失，还未确认的情况。这时是暂时不需要传的
						//发送给客户端的序列号从 1 开始
						buffer[0] = curSeq + 1;
						ack[curSeq] = FALSE;
						//数据发送的过程中应该判断是否传输完成
						//为简化过程此处并未实现
						memcpy(&buffer[1], data + 1024 * totalSeq, 1024);
						printf("send a packet with a seq of %d\n", curSeq);
						sendto(socketClient, buffer, BUFFER_LENGTH, 0, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));						
						++curSeq;
						curSeq %= SEQ_SIZE;
						++totalSeq;
						Sleep(500);
					}
					//等待 Ack，若没有收到，则返回值为-1，计数器+1
					recvSize = recvfrom(socketClient, buffer, BUFFER_LENGTH, 0, ((SOCKADDR*)&addrServer), &len);
					if (recvSize < 0) {
						waitCount++;
						//20 次等待 ack 则超时重传
						if (waitCount > 20)
						{
							timeoutHandler();
							waitCount = 0;
						}
					}
					else {
						//收到 ack
						ackHandler(buffer[0]);
						waitCount = 0;
						// printf("%d\n", totalAck);
						if (totalAck == totalPacket) {
							flag = 1;
							strcpy(buffer, "All Finished!\n");
						}
					}
					Sleep(500);
					break;
				}
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