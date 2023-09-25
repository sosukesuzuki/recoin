#ifndef RECOIN_H
#define RECOIN_H

typedef char UChar;

enum TokenSyms {
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

enum RecoinNodeType { NODE_STRING, NODE_QTFR_STAR, NODE_CONS_ALT };

typedef struct RecoinNode RecoinNode;

typedef struct {
  RecoinNode *target;
} RecoinQtfrNode;

typedef struct {
  RecoinNode *car;
  RecoinNode *cdr;
} RecoinConsAltNode;

typedef struct {
  UChar *s;
} RecoinStringNode;

struct RecoinNode {
  enum RecoinNodeType type;
  union {
    RecoinQtfrNode qtfr;
    RecoinConsAltNode cons;
    RecoinStringNode string;
  } u;
};

typedef struct {
  int parse_depth;
} ScanEnv;

int fetch_token(RecoinToken *token, UChar **src, ScanEnv *env);
int parse_regexp(RecoinNode **node, UChar **src, ScanEnv *env);

#endif // RECOIN_H
