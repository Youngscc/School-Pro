#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <string.h>
#include <tchar.h> 

#pragma comment(lib, "Ws2_32.lib")

#define MAXSIZE 65507 //发送数据报文的最大长度
#define HTTP_PORT 80  // http 服务器端口

#define CACHE_MAXSIZE 100  //最大缓存数
#define DATELENGTH 50      //时间字节数

const bool RestricitiveTurnOn = false;  // 限制用户访问开关
const bool DisabledHostTurnOn = false;  // 网址过滤开关
// Http 重要头部数据
struct HttpHeader {
    char method[4]; // POST 或者 GET，注意有些为 CONNECT，本实验暂不考虑
    char url[1024];         // 请求的 url
    char host[1024];        // 目标主机
    char cookie[1024 * 10]; // cookie
    HttpHeader() {
        ZeroMemory(this, sizeof(HttpHeader));
    }
};

struct cache_HttpHeader {
    char method[4]; // POST 或者 GET，注意有些为 CONNECT，本实验暂不考虑
    char url[1024];  //  请求的 url 
    char host[1024]; //  目标主机 
    cache_HttpHeader() {
        ZeroMemory(this, sizeof(cache_HttpHeader)); //内存置零
    }
};

struct __CACHE {
    cache_HttpHeader httphed;
    char buffer[MAXSIZE];
    char date[DATELENGTH];//存储的更新时间
    __CACHE() {
        ZeroMemory(this->buffer, MAXSIZE);
        ZeroMemory(this->date, DATELENGTH);
    }

};
int Cache_index = 0;//标记下一个应该放缓存的位置
__CACHE cache[CACHE_MAXSIZE];

const char* ife = "If-Modified-Since: ";
const char* blank = " ";
const char* Modd = "304";


BOOL InitSocket();
void ParseHttpHead(char* buffer, HttpHeader* httpHeader);
BOOL ConnectToServer(SOCKET* serverSocket, char* host);
unsigned int __stdcall ProxyThread(LPVOID lpParameter);
int Cache_Search(__CACHE* cache, HttpHeader htp);
void Change(char* res, char* a, const char* b);

//代理相关参数
SOCKET ProxyServer;
sockaddr_in ProxyServerAddr;
const int ProxyPort = 10240;
//禁用网站
const char* disabledHost[10] = { "jwts.hit.edu.cn" };
int disabledHost_number = 1;


// 限制用户
const char* restrictiveClient[10] = { "127.0.0.1" };
int restrictiveClient_number = 1;

//网站诱导
const char* induceSite = "jwes.hit.edu.cn";
const char* targetSite = "www.csszengarden.com";
//由于新的连接都使用新线程进行处理，对线程的频繁的创建和销毁特别浪费资源
//可以使用线程池技术提高服务器效率
// const int ProxyThreadMaxNum = 20;
// HANDLE ProxyThreadHandle[ProxyThreadMaxNum] = {0};
// DWORD ProxyThreadDW[ProxyThreadMaxNum] = {0};
struct ProxyParam {
    SOCKET clientSocket;
    SOCKET serverSocket;
};
int _tmain(int argc, _TCHAR* argv[]) {
    printf("代理服务器正在启动\n");
    printf("初始化...\n");
    if (!InitSocket()) {
        printf("socket 初始化失败\n");
        return -1;
    }
    printf("代理服务器正在运行，监听端口 %d\n", ProxyPort);
    SOCKET acceptSocket = INVALID_SOCKET;
    ProxyParam* lpProxyParam;
    HANDLE hThread;
    DWORD dwThreadID;
    //代理服务器不断监听
    sockaddr_in verAddr;
    int dds = sizeof(SOCKADDR);
    while (true) {
        acceptSocket = accept(ProxyServer, (SOCKADDR*)&verAddr, &(dds));
        lpProxyParam = new ProxyParam;
        if (lpProxyParam == NULL) {
            continue;
        }
        if (RestricitiveTurnOn) {
            bool flag = 0;
            // printf("%s----------------------------------\n",inet_ntoa(verAddr.sin_addr));
            for (int i = 0; i < restrictiveClient_number; ++i) {
                if (!strcmp(restrictiveClient[i], inet_ntoa(verAddr.sin_addr))) {
                    printf("用户访问受限\n");
                    flag = 1;
                    break;
                }
            }
            if (flag) continue;
        }

        lpProxyParam->clientSocket = acceptSocket;
        hThread = (HANDLE)_beginthreadex(NULL, 0, &ProxyThread, (LPVOID)lpProxyParam, 0, 0);
        CloseHandle(hThread);
        Sleep(200);
    }
    closesocket(ProxyServer);
    WSACleanup();
    return 0;
}
//************************************
// Method: InitSocket
// FullName: InitSocket
// Access: public
// Returns: BOOL
// Qualifier: 初始化套接字
//************************************
BOOL InitSocket() {
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
        printf("加载 winsock 失败，错误代码为: %d\n", WSAGetLastError());
        return FALSE;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        printf("不能找到正确的 winsock 版本\n");
        WSACleanup();
        return FALSE;
    }
    ProxyServer = socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == ProxyServer) {
        printf("创建套接字失败，错误代码为：%d\n", WSAGetLastError());
        return FALSE;
    }
    ProxyServerAddr.sin_family = AF_INET;
    ProxyServerAddr.sin_port = htons(ProxyPort);
    ProxyServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
    // ProxyServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//设置IP地址
    if (bind(ProxyServer, (SOCKADDR*)&ProxyServerAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        printf("绑定套接字失败\n");
        return FALSE;
    }
    if (listen(ProxyServer, SOMAXCONN) == SOCKET_ERROR) {
        printf("监听端口%d 失败", ProxyPort);
        return FALSE;
    }
    return TRUE;
}
//************************************
// Method: ProxyThread
// FullName: ProxyThread
// Access: public
// Returns: unsigned int __stdcall
// Qualifier: 线程执行函数
// Parameter: LPVOID lpParameter
//************************************
unsigned int __stdcall ProxyThread(LPVOID lpParameter) {
    const char* delim = "\r\n";
    char Buffer[MAXSIZE];
    char* CacheBuffer;
    char* cacheBuff;
    char* ptr;
    char ThisDate[DATELENGTH];
    char* p;
    ZeroMemory(Buffer, MAXSIZE);
    SOCKADDR_IN clientAddr;
    int recvSize;
    int ret;
    int index;
    bool isUpdate;
    recvSize = recv(((ProxyParam*)lpParameter)->clientSocket, Buffer, MAXSIZE, 0);
    HttpHeader* httpHeader = new HttpHeader();
    if (recvSize <= 0) {
        printf("本地客户端等待中\n");
        goto error;
    }
    CacheBuffer = new char[recvSize + 1];
    ZeroMemory(CacheBuffer, recvSize + 1);
    memcpy(CacheBuffer, Buffer, recvSize);
    ParseHttpHead(CacheBuffer, httpHeader);
    delete CacheBuffer;

    if (!strcmp(induceSite, httpHeader->host)) {
        printf("正在跳转网站……\n");
        Change(Buffer, httpHeader->host, targetSite); // 将报文中所有的原网址替换为新网址
        ZeroMemory(httpHeader->host, strlen(httpHeader->host));
        memcpy(httpHeader->host, targetSite, strlen(targetSite));
        sprintf_s(httpHeader->url, "http://%s/", targetSite);// 将新报文的url修改
    }

    // printf("%s--------\n%s------------------\n", httpHeader->host, httpHeader->url);

    if (!ConnectToServer(&((ProxyParam*)lpParameter)->serverSocket, httpHeader->host)) {
        printf("连接目的服务器失败\n");
        // printf("%s\n",httpHeader->host);
        goto error;
    }
    printf("代理连接主机 %s 成功\n", httpHeader->host);

    index = Cache_Search(cache, *httpHeader); // 在CACHE中寻找是否缓存过该报文
    // printf("-------------------------\n%s\n%s\n%s\n--------------------------------\n",httpHeader->host,httpHeader->url,httpHeader->method);
    // printf("%d ----- \n",index);
    ZeroMemory(ThisDate, DATELENGTH);

    if (index >= 0) {
        memcpy(ThisDate, cache[index].date, strlen(cache[index].date));
        char ThisBuffer[MAXSIZE];
        ZeroMemory(ThisBuffer, MAXSIZE);
        // printf("-------------------Get报文------------------------\n%s\n", Buffer);
        p = strtok_s(Buffer, delim, &ptr);
        bool flag = false; // 判断是否已经有 If-Modified 请求
        while (p) {
            // printf("------------%s\n",p);
            int length = strlen(ThisBuffer);
            memcpy(ThisBuffer + length, p, strlen(p));
            memcpy(ThisBuffer + length + strlen(p), delim, strlen(delim));
            if (p[0] == 'I') {
                char now[100];
                ZeroMemory(now, 100);
                memcpy(now, p, 11);
                if (!memcmp(now, "If-Modified", 11)) {
                    flag = true;
                }
            }
            p = strtok_s(NULL, delim, &ptr);
        }
        if (!flag) { // 添加 If-Modified请求
            int length = strlen(ThisBuffer);
            memcpy(ThisBuffer + length, ife, strlen(ife));
            length += strlen(ife);
            memcpy(ThisBuffer + length, cache[index].date, strlen(cache[index].date));
            length = strlen(ThisBuffer);
            memcpy(ThisBuffer + length, delim, strlen(delim));
        }
        int length = strlen(ThisBuffer);
        memcpy(ThisBuffer + length, delim, strlen(delim));
        //将客户端发送的 HTTP 数据报文处理后转发给目标服务器 
        // printf("-------------------条件性Get报文------------------------\n%s\n", ThisBuffer);
        ret = send(((ProxyParam*)lpParameter)->serverSocket, ThisBuffer, strlen(ThisBuffer) + 1, 0);
        // printf("-------------------------------------------\n%s\n", ThisBuffer);
        // printf("------------------------------------------------\n");
        //等待目标服务器返回数据 
        recvSize = recv(((ProxyParam*)lpParameter)->serverSocket, ThisBuffer, MAXSIZE, 0);
        // printf("------------------Server返回报文-------------------\n%s\n", ThisBuffer);
        // printf("-------------------------------------------\n");

        if (recvSize <= 0) {
            goto error;
        }

        if (!memcmp(&ThisBuffer[9], Modd, strlen(Modd))) {
            ret = send(((ProxyParam*)lpParameter)->clientSocket, cache[index].buffer, strlen(cache[index].buffer) + 1, 0);
            printf("------------------------------------\n");
            printf("\n将cache中的数据返回给客户端\n\n");
            printf("------------------------------------\n");
            goto error;
        }
        printf("-----------------------------------------------------------\n");

    }

    //将客户端发送的 HTTP 数据报文直接转发给目标服务器
    ret = send(((ProxyParam*)lpParameter)->serverSocket, Buffer, strlen(Buffer) + 1, 0);
    //等待目标服务器返回数据
    recvSize = recv(((ProxyParam*)lpParameter)->serverSocket, Buffer, MAXSIZE, 0);
    if (recvSize <= 0) {
        printf("目标服务器未响应\n");
        goto error;
    }

    cacheBuff = new char[MAXSIZE];
    ZeroMemory(cacheBuff, MAXSIZE);
    memcpy(cacheBuff, Buffer, MAXSIZE);

    ZeroMemory(ThisDate, sizeof(ThisDate));
    p = strtok_s(cacheBuff, delim, &ptr);
    isUpdate = false;
    while (p) { // 提取该报文的Last-Modified的时间
        if (strlen(p) > 15) {
            char header[15];
            ZeroMemory(header, sizeof(header));
            memcpy(header, p, 14);
            if (!(strcmp(header, "Last-Modified:"))) {
                memcpy(ThisDate, &p[15], strlen(p) - 15);
                isUpdate = true;
                break;
            }
        }
        p = strtok_s(NULL, delim, &ptr);
    }
    delete(cacheBuff);

    //如果有更新，将新的报文放到缓存里
    if (isUpdate) {
        if (index >= 0) {
            memcpy(&(cache[index].buffer), Buffer, strlen(Buffer));
            memcpy(&(cache[index].date), ThisDate, strlen(ThisDate));
        }
        else {
            //循环使用
            memcpy(&(cache[Cache_index % CACHE_MAXSIZE].httphed.host), httpHeader->host, strlen(httpHeader->host));
            memcpy(&(cache[Cache_index % CACHE_MAXSIZE].httphed.method), httpHeader->method, strlen(httpHeader->method));
            memcpy(&(cache[Cache_index % CACHE_MAXSIZE].httphed.url), httpHeader->url, strlen(httpHeader->url));
            memcpy(&(cache[Cache_index % CACHE_MAXSIZE].buffer), Buffer, strlen(Buffer));
            memcpy(&(cache[Cache_index % CACHE_MAXSIZE].date), ThisDate, strlen(ThisDate));
            Cache_index++;
        }
    }

    // printf("------------------------------%d\n",Cache_index++);

    //将目标服务器返回的数据直接转发给客户端
    ret = send(((ProxyParam*)lpParameter)->clientSocket, Buffer, sizeof(Buffer), 0);
    //错误处理
error:
    printf("关闭套接字\n");
    Sleep(200);
    closesocket(((ProxyParam*)lpParameter)->clientSocket);
    closesocket(((ProxyParam*)lpParameter)->serverSocket);
    delete lpParameter;
    _endthreadex(0);
    return 0;
}
//************************************
// Method: ParseHttpHead
// FullName: ParseHttpHead
// Access: public
// Returns: void
// Qualifier: 解析 TCP 报文中的 HTTP 头部
// Parameter: char * buffer
// Parameter: HttpHeader * httpHeader
//************************************
void ParseHttpHead(char* buffer, HttpHeader* httpHeader)
{
    char* p;
    char* ptr;
    const char* delim = "\r\n";
    p = strtok_s(buffer, delim, &ptr); //提取第一行
    printf("%s\n", p);
    if (p[0] == 'G') { // GET 方式
        memcpy(httpHeader->method, "GET", 3);
        memcpy(httpHeader->url, &p[4], strlen(p) - 13);
    }
    else if (p[0] == 'P') { // POST 方式
        memcpy(httpHeader->method, "POST", 4);
        memcpy(httpHeader->url, &p[5], strlen(p) - 14);
    }
    printf("%s\n", httpHeader->url);
    p = strtok_s(NULL, delim, &ptr);
    while (p) {
        switch (p[0]) {
        case 'H': // Host
            memcpy(httpHeader->host, &p[6], strlen(p) - 6);
            break;
        case 'C': // Cookie
            if (strlen(p) > 8) {
                char header[8];
                ZeroMemory(header, sizeof(header));
                memcpy(header, p, 6);
                if (!strcmp(header, "Cookie")) {
                    memcpy(httpHeader->cookie, &p[8], strlen(p) - 8);
                }
            }
            break;
        default:
            break;
        }
        p = strtok_s(NULL, delim, &ptr);
    }
}
//************************************
// Method: ConnectToServer
// FullName: ConnectToServer
// Access: public
// Returns: BOOL
// Qualifier: 根据主机创建目标服务器套接字，并连接
// Parameter: SOCKET * serverSocket
// Parameter: char * host
//************************************
BOOL ConnectToServer(SOCKET* serverSocket, char* host)
{
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(HTTP_PORT);

    if (DisabledHostTurnOn) {
        for (int i = 0; i < disabledHost_number; ++i) {
            if (!strcmp(disabledHost[i], host)) { // 与过滤列表中的网址进行一一比对
                printf("该网站已被过滤\n");
                return false;
            }
        }
    }

    HOSTENT* hostent = gethostbyname(host);
    if (!hostent) {
        return FALSE;
    }
    in_addr Inaddr = *((in_addr*)*hostent->h_addr_list);
    serverAddr.sin_addr.s_addr = inet_addr(inet_ntoa(Inaddr));
    *serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (*serverSocket == INVALID_SOCKET) {
        return FALSE;
    }
    if (connect(*serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(*serverSocket);
        return FALSE;
    }
    return TRUE;
}

//判断两个报文是否相同
BOOL Isequal(cache_HttpHeader htp1, HttpHeader htp2) {
    if (strcmp(htp1.method, htp2.method)) return false;
    if (strcmp(htp1.url, htp2.url)) return false;
    if (strcmp(htp1.host, htp2.host)) return false;
    return true;
}

//在缓存中找到对应的对象
int Cache_Search(__CACHE* cache, HttpHeader htp) {
    for (int i = 0; i < CACHE_MAXSIZE; ++i)
        if (Isequal(cache[i].httphed, htp)) return i;
    return -1;
}

// 将res中的所有a字符串修改为b字符串

void Change(char* res, char* a, const char* b) {
    char ret[MAXSIZE];
    ZeroMemory(ret, sizeof(ret));
    int p = 0;
    int length = 0;
    while (p < (int)strlen(res)) {
        if (!memcmp(res + p, a, strlen(a))) {
            memcpy(ret + length, b, strlen(b));
            ret[length += strlen(b)] = '\0';
            p += strlen(a);
            continue;
        }
        ret[length++] = res[p++];
        ret[length] = '\0';
    }
    ret[strlen(ret)] = '\0';
    memcpy(res, ret, strlen(ret));
}