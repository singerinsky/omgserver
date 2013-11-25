#ifndef _FLEXSECURITYBOX_H
#define _FLEXSECURITYBOX_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include "../common/head.h"

#define SOCKET int
class FlexSecurityBox
{
private:
    const char * ListenAddress;
    const short Port;
    bool IsOpened;
    SOCKET m_socket;
    SOCKET aSocket;
    struct sockaddr_in m_address;
    struct sockaddr_in m_tempAddress;
public:
    FlexSecurityBox(const char * listenAddress, const short port) :
            ListenAddress(listenAddress), Port(port), IsOpened(false)
    {
    }
    bool Open()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        m_address.sin_addr.s_addr = htonl(INADDR_ANY);
        m_address.sin_family = AF_INET;
	m_address.sin_port = htons(Port);
        IsOpened = false;
        if (strcmp(ListenAddress, "0.0.0.0"))
        {
            struct hostent * hostname = gethostbyname(ListenAddress);
            if (hostname != 0)
                memcpy(&m_address.sin_addr.s_addr,
                        hostname->h_addr_list[0], hostname->h_length);
        }
        int ret = bind(m_socket, (const sockaddr*) &m_address, sizeof(m_address));
        if (ret != 0)
        {
            LOG(INFO)<<"Bind unsuccessful on port "<<Port;
            return IsOpened;
        }
        ret = listen(m_socket, 100);
        if (ret != 0)
        {
            printf("Unable to listen on port %u.", (unsigned int)Port);
            return IsOpened;
        }
        printf("Server %s: %u is listening ....../n", ListenAddress, Port);
        return IsOpened = true;
    }
    void DoWork()
    {
        char buf[23];
        char rbuf[110] = "<cross-domain-policy><allow-access-from domain=\"*\" to-ports=\"*\" /></cross-domain-policy>";
        int Len = sizeof(sockaddr_in);
        while (IsOpened)
        {
            //接受连接
            aSocket = accept(m_socket, (sockaddr*) &m_tempAddress, (socklen_t*) &Len);
            LOG(INFO)<<"Accept connection from "<<inet_ntoa(m_tempAddress.sin_addr);
            int bytes;
            if ((bytes = recv(aSocket, buf, sizeof(buf), 0)) == -1)
            {
		LOG(ERROR)<<"error of receive data";	
		close(aSocket);
            	continue;
	    }
	    
	    if(bytes != 23){//非策略文件
		LOG(ERROR)<<"error of policy";
		close(aSocket);
	   	continue; 
	   }
		
            buf[bytes] = '\0';
            if (strcmp(buf, "<policy-file-request/>") == 0)
            {
                //发送数据
                if (send(aSocket, rbuf, strlen(rbuf) + 1, 0) == -1)
                {
                    printf("发送数据失败！/n");
                }
                else
                {
                    LOG(INFO)<<"Message to "<<inet_ntoa(m_tempAddress.sin_addr);
                }
            }
            //清理套接字占用的资源
            // closesocket(sockConn);
            close(aSocket);
        }
    }
    ~FlexSecurityBox()
    {
    }
};
#endif

