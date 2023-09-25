#include "recoin.h"
#include <stdio.h>

int main() {
  UChar *src = "abc|*";
  RecoinToken token;

  fetch_token(&token, &src);
  printf("%u\n", token.type);
  fetch_token(&token, &src);
  printf("%u\n", token.type);
  fetch_token(&token, &src);
  printf("%u\n", token.type);

  return 0;
}
