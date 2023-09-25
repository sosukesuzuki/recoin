#include "recoin.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int parse_qtfr(RecoinNode *node, RecoinToken *token, UChar **src) { return 0; }

int parse_atom(RecoinNode *node, RecoinToken *token, UChar **src) {
  if (token->type == TK_STRING) {
    node->type = NODE_STRING;
    // copy string from token
    node->u.string.s = malloc(sizeof(UChar) * (strlen(token->u.s) + 1));
    strcpy(node->u.string.s, token->u.s);
    return fetch_token(token, src);
  }
  return 1;
}

int parse_cons_alt(RecoinNode *node, RecoinToken *token, UChar **src) {
  int r;
  RecoinNode *car = malloc(sizeof(RecoinNode));
  r = parse_atom(car, token, src);
  if (r > 0) {
    return r;
  }
  for (;;) {
    if (token->type == TK_VERTICAL_LINE) {
      r = fetch_token(token, src);
      if (r > 0) {
        return r;
      }
      RecoinNode *cdr = malloc(sizeof(RecoinNode));
      r = parse_atom(cdr, token, src);
      if (r > 0) {
        return r;
      }
      node->type = NODE_CONS_ALT;
      node->u.cons.car = car;
      node->u.cons.cdr = cdr;
    } else {
      *node = *car;
      return 0;
    }
  }
  return 0;
}

int parse_subexp(RecoinNode **node, RecoinToken *token, UChar **src) {
  return parse_cons_alt(*node, token, src);
}

int parse_regexp(RecoinNode **node, UChar **src) {
  int r;
  RecoinToken token;

  r = fetch_token(&token, src);
  if (r > 0)
    return r;

  r = parse_subexp(node, &token, src);
  if (r > 0)
    return r;

  return 0;
}
