#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char UChar;

enum TokenSyms {
  TK_START,
  TK_EOT,
  TK_CHAR,
  TK_STRING,
  TK_VERTICAL_LINE,        // U+007C |
  TK_REVERSE_SOLIDUS,      // U+005C (\)
  TK_LEFT_PARENTHESIS,     // U+0028 (
  TK_RIGHT_PARENTHESIS,    // U+0029 )
  TK_LEFT_SQUARE_BRACKET,  // U+005B [
  TK_RIGHT_SQUARE_BRACKET, // U+005D ]
  TK_QUESTION_MARK,        // U+003F ?
  TK_PLUS_SIGN,            // U+002B +
  TK_ASTERISK,             // U+002A *
  TK_DOLLAR_SIGN,          // U+0024 $
  TK_CIRCUMFLEX_ACCENT,    // U+005E ^
  TK_HYPHEN_MINUS          // U+002D -
};

typedef struct {
  enum TokenSyms type;
  union {
    // TK_CHAR
    UChar c;
    // TK_STRING
    UChar *s;
  } u;
} RecoinToken;

int fetch_token(RecoinToken *token, UChar **src) {
  UChar *p = *src;

  if (isalpha(*p)) {
    UChar *start = p;
    while (isalpha(*p)) {
      p++;
    }
    UChar *end = p;
    int length = end - start;
    token->type = TK_STRING;
    token->u.s = malloc(sizeof(UChar) * (length + 1));
    memcpy(token->u.s, start, length);
    token->u.s[end - start] = '\0';
    *src = p;
    return 1;
  } else if (*p == '|') {
    token->type = TK_VERTICAL_LINE;
    *src = p + 1;
    return 1;
  } else if (*p == '*') {
    token->type = TK_ASTERISK;
    *src = p + 1;
    return 1;
  } else if (*p == '\0') {
    token->type = TK_EOT;
    *src = p;
    return 1;
  }

  return 0;
}

int main() {
  UChar *src = "abc|*";
  RecoinToken token;
  token.type = TK_START;

  fetch_token(&token, &src);
  printf("%u\n", token.type);
  fetch_token(&token, &src);
  printf("%u\n", token.type);
  fetch_token(&token, &src);
  printf("%u\n", token.type);

  return 0;
}
