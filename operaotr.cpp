#include "operator.h"

bool clear_icanon() {
#if defined(__linux__)
  struct termios settings;
  int result;
  result = tcgetattr(STDIN_FILENO, &settings);
  if (result < 0) {
    perror("error in tcgetattr");
    return false;
  }

  settings.c_lflag &= ~ICANON;

  result = tcsetattr(STDIN_FILENO, TCSANOW, &settings);
  if (result < 0) {
    perror("error in tcsetattr");
    return false;
  }
  return true;
#elif defined(_WIN32)
  DWORD mode;
  HANDLE console = GetStdHandle(STD_INPUT_HANDLE);

  GetConsoleMode(console, &mode);
  SetConsoleMode(console, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
  return true;
#endif
}

std::string get_input_str_without_len_limit() {
  std::string str = "";
  if (clear_icanon()) {
    char c;
    while (true) {
#if defined(__linux__)
      c = getchar();
#elif defined(_WIN32)
      c = _getch();
      if (c < 31 && c != '\n' && c != '\r') {
        exit(-1);
      }
      printf("%c", c);
#endif
      if ('\n' == c || '\r' == c) {
        printf("\n");
        break;
      }
      str += c;
    }
  }
  return str;
}
