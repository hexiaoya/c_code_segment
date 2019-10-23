#include <stdio.h> 
#include <winsock2.h> //winsock库头文件
#include <windows.h> 
#include <string.h>
#pragma comment(lib,"WS2_32.lib") //连接winsock库文件

int main()
{ 

WSADATA stWsaData = {0};
SOCKET hSocket = 0;
LPHOSTENT   lphostent;
sockaddr_in stRemoteAddr = {0};
char cSendData[4096] = {0}; //发送数据缓冲区
char cRecvData[10240] = {0}; //接收数据缓冲区
int nRetBytes = 0;
const   char*   host_name="pt.hit.edu.cn";   
::WSAStartup(MAKEWORD(2,0),&stWsaData); //初始化winsock库
lphostent=gethostbyname(host_name);   
if(lphostent==NULL)   
    printf("lphostent   is   null");   
hSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); //创建TCP套接字
if(hSocket == INVALID_SOCKET)
return 0;
stRemoteAddr.sin_family = AF_INET; //填充sockaddr_in结构
stRemoteAddr.sin_addr=*((LPIN_ADDR)*lphostent->h_addr_list); 
stRemoteAddr.sin_port = htons(80);
if(connect(hSocket,(sockaddr *)&stRemoteAddr,sizeof stRemoteAddr) == -1) //连接到服务器
{
closesocket(hSocket); //关闭TCP套接字
WSACleanup(); //释放winsock库
return 0;
}

//构造HTTP请求数据包的请求头
sprintf(cSendData,"GET /take_signin_bonus.php HTTP/1.1\r\n"); 
strcat(cSendData,"Accept: */*\r\n"); 
//strcat(cSendData,"Referer: http://pt.hit.edu.cn/details.php?id=28542&hit=1\r\n"); 
strcat(cSendData,"Accept-Language: zh-cn\r\n"); 
strcat(cSendData,"Content-Type: application/x-www-form-urlencoded\r\n"); 
strcat(cSendData,"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko\r\n"); 
strcat(cSendData,"Host: pt.hit.edu.cn\r\n"); 
strcat(cSendData,"Content-Length:8\r\n");
strcat(cSendData,"Cookie: c_secure_uid=NTgwOQ%3D%3D; c_secure_pass=44aa08ab15d973a6c5acf790f12f1b18; c_secure_ssl=bm9wZQ%3D%3D; c_secure_tracker_ssl=bm9wZQ%3D%3D; c_secure_login=bm9wZQ%3D%3D\r\n");
strcat(cSendData,"Connection: Keep-Alive\r\n"); 
strcat(cSendData,"cache-Control: no-cache\r\n"); 
//请求头与用户数据段之间的分隔行
strcat(cSendData,"\r\n");
//构造HTTP请求数据包的用户数据段
/*
strcat(cSendData,"id=");
char sss[50];
sprintf(sss,"%d",cishu);
printf("%s",sss);
strcat(cSendData,sss);
*/
send(hSocket,cSendData,sizeof cSendData,0); //发送
/*
char   dest[10000];   
int nRet=1; 
while(nRet>0)   
{
    char * cbgn=NULL,* cend=NULL;
    nRet=recv(hSocket,(LPSTR)dest,sizeof(dest),0); 
//	printf("%d",nRet);
    if(nRet>0)   
       dest[nRet]=0;   
    else   
        dest[0]=0;   
//    printf("\nReceived   bytes:%d\n",nRet);   
//   printf("Result:\n%s",dest);
} 
*/
printf("PT签到成功\n");
closesocket(hSocket); //关闭TCP套接字
WSACleanup(); //释放winsock库


::WSAStartup(MAKEWORD(2,0),&stWsaData); //初始化winsock库
lphostent=gethostbyname(host_name);   
if(lphostent==NULL)   
    printf("lphostent   is   null");   
hSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); //创建TCP套接字
if(hSocket == INVALID_SOCKET)
return 0;
stRemoteAddr.sin_family = AF_INET; //填充sockaddr_in结构
stRemoteAddr.sin_addr=*((LPIN_ADDR)*lphostent->h_addr_list); 
stRemoteAddr.sin_port = htons(80);
if(connect(hSocket,(sockaddr *)&stRemoteAddr,sizeof stRemoteAddr) == -1) //连接到服务器
{
closesocket(hSocket); //关闭TCP套接字
WSACleanup(); //释放winsock库
return 0;
}

//构造HTTP请求数据包的请求头
sprintf(cSendData,"GET /take_signin_bonus.php?redate=1 HTTP/1.1\r\n"); 
strcat(cSendData,"Accept: */*\r\n"); 
//strcat(cSendData,"Referer: http://pt.hit.edu.cn/details.php?id=28542&hit=1\r\n"); 
strcat(cSendData,"Accept-Language: zh-cn\r\n"); 
strcat(cSendData,"Content-Type: application/x-www-form-urlencoded\r\n"); 
strcat(cSendData,"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko\r\n"); 
strcat(cSendData,"Host: pt.hit.edu.cn\r\n"); 
strcat(cSendData,"Content-Length:8\r\n");
strcat(cSendData,"Cookie: c_secure_uid=NTgwOQ%3D%3D; c_secure_pass=44aa08ab15d973a6c5acf790f12f1b18; c_secure_ssl=bm9wZQ%3D%3D; c_secure_tracker_ssl=bm9wZQ%3D%3D; c_secure_login=bm9wZQ%3D%3D\r\n");
strcat(cSendData,"Connection: Keep-Alive\r\n"); 
strcat(cSendData,"cache-Control: no-cache\r\n"); 
//请求头与用户数据段之间的分隔行
strcat(cSendData,"\r\n");
send(hSocket,cSendData,sizeof cSendData,0); //发送
printf("PT签到成功\n");
closesocket(hSocket); //关闭TCP套接字
WSACleanup(); //释放winsock库
getchar();
return 0; 
} 