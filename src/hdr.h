#pragma once
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>

#pragma comment (lib, "Ws2_32.lib")
using namespace std;

addrinfo* findHost(string ip, string port);
int findQSL(addrinfo* addr, string target);
string pad(string s, int l, char c);
void shell(addrinfo* addr, string target);
int findHlen(addrinfo* addr, string target, int qsl);
void sendchain(addrinfo* addr, string target, int qsl, int hlen, vector<string> chain);
string setsetting(addrinfo* addr, string target, string val, int qsl, int hlen);
