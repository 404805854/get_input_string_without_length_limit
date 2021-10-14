#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

#if defined(__linux__)
#include <termios.h>
#include <unistd.h>
#elif defined(_WIN32)
#include <conio.h>
#include <windows.h>
#endif

bool clear_icanon();
std::string get_input_str_without_len_limit();