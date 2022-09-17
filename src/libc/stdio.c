#include "libc/stdio.h"

static volatile struct limine_terminal_request terminal_request = {
  .id = LIMINE_TERMINAL_REQUEST,
  .revision = 0
};

void puts(char* str){
  struct limine_terminal *terminal = terminal_request.response->terminals[0];
  terminal_request.response->write(terminal, str, strlen(str));
}


// TODO: implement character printing.
void printf(char* fmt, ...){
  va_list ap;
  va_start(ap, fmt);

  for(char* ptr = fmt; *ptr != '\0'; ++ptr){
    if(*ptr == '%'){
      ++ptr;
      switch(*ptr){
        case 's':
          puts(va_arg(ap, char*));
          break;

        case 'd': // integer
          puts(itoa(va_arg(ap, int), 10));
          break;

        case 'x': // hexadecimal
          puts(itoa(va_arg(ap, uint32_t), 16));
          break;
      }
    } else {
      // not a format keyword
      char _tmp[2] = { *ptr, 0 };
      puts(_tmp);
    }
  }
}