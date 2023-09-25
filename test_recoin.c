#include "recoin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_ASSERT(expr)                                                      \
  do {                                                                         \
    if (!(expr)) {                                                             \
      fprintf(stderr, "Assertion failed: %s (%s:%d)\n", #expr, __FILE__,       \
              __LINE__);                                                       \
      exit(1);                                                                 \
    }                                                                          \
  } while (0)

#define RUN_TEST(test_func)                                                    \
  do {                                                                         \
    printf("Running test: %s\n", #test_func);                                  \
    test_func();                                                               \
    printf("Test passed.\n\n");                                                \
  } while (0)

void fetch_token_str_1() {
  UChar *src = "abc";
  RecoinToken token;
  fetch_token(&token, &src);
  TEST_ASSERT(token.type == TK_STRING);
  TEST_ASSERT(strcmp(token.u.s, "abc") == 0);
}
void fetch_token_cons_alt_1() {
  UChar *src = "|";
  RecoinToken token;
  fetch_token(&token, &src);
  TEST_ASSERT(token.type == TK_VERTICAL_LINE);
}
void fetch_token_qtfr_asterrisk_1() {
  UChar *src = "*";
  RecoinToken token;
  fetch_token(&token, &src);
  TEST_ASSERT(token.type == TK_ASTERISK);
}
void fetch_token_basic_regexp_1() {
  UChar *src = "abc|def*";
  RecoinToken token;
  fetch_token(&token, &src);
  TEST_ASSERT(token.type == TK_STRING);
  TEST_ASSERT(strcmp(token.u.s, "abc") == 0);
  fetch_token(&token, &src);
  TEST_ASSERT(token.type == TK_VERTICAL_LINE);
  fetch_token(&token, &src);
  TEST_ASSERT(token.type == TK_STRING);
  TEST_ASSERT(strcmp(token.u.s, "def") == 0);
  fetch_token(&token, &src);
  TEST_ASSERT(token.type == TK_ASTERISK);
}

int main() {
  RUN_TEST(fetch_token_str_1);
  RUN_TEST(fetch_token_cons_alt_1);
  RUN_TEST(fetch_token_qtfr_asterrisk_1);
  RUN_TEST(fetch_token_basic_regexp_1);

  return 0;
}
