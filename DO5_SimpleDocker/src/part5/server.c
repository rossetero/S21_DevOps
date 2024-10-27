#include <stdlib.h>

#include "fcgi_stdio.h"

int main(void) {
  while (FCGI_Accept() >= 0) {
    printf(
        "Content-Type: text/html\r\n\r\n<html><body><h1>Salam "
        "Aleykum!</h1></body></html>\n");
    fflush(stdout);
  }
  return 0;
}
