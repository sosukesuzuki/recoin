#include "recoin.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int parse_depth;
} ScanEnv;

int fetch_token(RecoinToken *token, UChar **src, ScanEnv *env) {
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
    return 0;
  } else if (*p == '|') {
    token->type = TK_VERTICAL_LINE;
    *src = p + 1;
    return 0;
  } else if (*p == '*') {
    token->type = TK_ASTERISK;
    *src = p + 1;
    return 0;
  } else if (*p == '\0') {
    token->type = TK_EOT;
    *src = p;
    return 0;
  }

  return 1;
}

int parse_subexp(RecoinNode **node, RecoinToken *token, UChar **src,
                 ScanEnv *env) {
  return 0;
}

int parse_regexp(RecoinNode **node, UChar **src, ScanEnv *env) {
  int r;
  RecoinToken token;

  // initialize ScanEnv
  env->parse_depth = 0;

  r = fetch_token(&token, src, env);
  if (r > 0)
    return r;

  r = parse_subexp(node, &token, src, env);
  if (r > 0)
    return r;

  return 0;
}
