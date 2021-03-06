#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <sys/socket.h>
#include <iostream>
#include "mynet.h"
using namespace std;
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "net", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "net", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "net", __VA_ARGS__))
#define RCVBUFSIZE 1024
/*const char *servIP;
 unsigned short servPort;*/
net::net() {
	host = "api.taose69.com";
	port = 80;
}
void net::setPort(unsigned short port) {
	this->port = port;
}
;
const char*net::getIP(bool newget) {
	cout << "newget=" << newget << "ip=" << ip << strlen(this->ip) << endl;
	if (!newget && strlen(this->ip) > 5) {
		cout << "ip=" << ip << endl;
		return this->ip;
	}
	struct hostent* host = gethostbyname(this->host);
	char** current_addr = host->h_addr_list;
	if (*current_addr != NULL) {
		struct in_addr* addr = (struct in_addr*) (*current_addr);
		LOGI("address: %s\n", inet_ntoa(*addr));
		const char* ip = inet_ntoa(*addr);
		this->ip=ip;
		LOGI("######################ip=");
		LOGI(ip);
		return ip;
	}
	return NULL;
}
void net::setHost(const char*host) {
	this->host = host;
	this->ip = getIP(true);
}
const char*net::getUrlStr(const char*pathStr, bool isGet) {

	string request;
	request.append(isGet ? "GET " : "POST ");
	request.append(pathStr);
	request.append(" HTTP/1.1\r\nHost: ");
	request.append(this->host);
	request.append("\n");
	request.append(
			"Content-Type:application/x-www-form-urlencoded ;charset=UTF-8\n");
	request.append(
			"User-Agent:AndroidBrunjoy/1.0 Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.2 Safari/537.17\n");
	request.append("\r\n\r\n ");

	LOGI("LOGI(==========request.c_str()=\n)");
	LOGI(request.c_str() );
	return request.c_str();
}

const char* net::receviceByURL(const char*url) {
	LOGI(url );
	int sock; // Socket descriptor
	struct sockaddr_in servAddr; // server address
	char recvBuffer[RCVBUFSIZE]; // Buffer for response string
	unsigned int requestLen; // Length of string to send
	int bytesRcvd; // Bytes read in single recv()
	bool status = true;
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		status = false;
	}
	LOGE("=========ip====status========="+status);

	if (status) {
		// Convert dotted decimal into binary server address.
		memset(&servAddr, 0, sizeof(servAddr));
		servAddr.sin_family = AF_INET;
		servAddr.sin_addr.s_addr = inet_addr(this->getIP(false));

		LOGE(this->getIP(false));
		servAddr.sin_port = htons(this->port);

		// Connect to the server.
		if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr))
				< 0) {
			status = false;
		}
	}
	if (status) {
		requestLen = strlen(url);
		LOGI("=====send(sock, url, requestLen, 0)====333======" );
		if (send(sock, url, requestLen, 0) != requestLen) {
			status = false;
		}
	}
	LOGI("=========333======" );

	string msg;
	if (status) {
		int index = 0;
		while (status) {
			//读取接受到数据
			if ((bytesRcvd = recv(sock, recvBuffer, RCVBUFSIZE - 1, 0)) <= 0) {
				status = false;
			}
			if (status) {
				if (bytesRcvd < (RCVBUFSIZE - 1)) {
					recvBuffer[bytesRcvd] = '\0';
					status = false;
				} else {
				}
			}
			msg.append(recvBuffer);
			index++;
		}
	}
	close(sock);
	return msg.c_str();
}
/*int main() {
	net net;
	const char*content = net.receviceByURL(
			net.getUrlStr("/items/getAllParentsCategorys", true));
	cout<<content<<endl;
}*/

