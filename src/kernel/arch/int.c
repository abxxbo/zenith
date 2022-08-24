#include "arch/int.h"

void enable_IRQ(void){
  int tmp;
  __asm__("MRS %0, CPSR" : "=r"(tmp));
  __asm__("BIC %0, %0, #0x80" : "=r"(tmp));
  __asm__("MSR CPSR_c, %0" : "=r"(tmp));

  printf("%sIRQs enabled%s\r\n",
          COLOR_Green, COLOR_None);
}

void enable_FIQ(void){
  int tmp;
  __asm__("MRS %0, CPSR" : "=r"(tmp));
  __asm__("BIC %0, %0, #0x40" : "=r"(tmp));
  __asm__("MSR CPSR_c, %0" : "=r"(tmp));

    printf("%sFIQs enabled%s\r\n",
          COLOR_Green, COLOR_None);
}




void disable_IRQ(void){
  int tmp;
  __asm__("MRS %0, CPSR" : "=r"(tmp));
  __asm__("ORR %0, %0, #0x80" : "=r"(tmp));
  __asm__("MSR CPSR_c, %0" : "=r"(tmp));

  printf("%sIRQs disabled%s\r\n",
          COLOR_Red, COLOR_None);
}

void disable_FIQ(void){
  int tmp;
  __asm__("MRS %0, CPSR" : "=r"(tmp));
  __asm__("ORR %0, %0, #0x40" : "=r"(tmp));
  __asm__("MSR CPSR_c, %0" : "=r"(tmp));

    printf("%sFIQs disabled%s\r\n",
          COLOR_Red, COLOR_None);
}