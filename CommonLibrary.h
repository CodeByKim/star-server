#pragma once

#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>
#include <memory>
#include <functional>
#include <chrono>
#include <queue>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <conio.h>

#define SERVER_PORT 3000
#define PACKET_SIZE 16

#define BUFFER_SIZE 1024
#define MAX_CCU 10