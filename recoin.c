enum TokenSyms {
  TK_CHAR,
  TK_STRING,
  TK_VERTICAL_LINE,        // U+007C
  TK_REVERSE_SOLIDUS,      // U+005C
  TK_LEFT_PARENTHESIS,     // U+0028
  TK_RIGHT_PARENTHESIS,    // U+0029
  TK_LEFT_SQUARE_BRACKET,  // U+005B
  TK_RIGHT_SQUARE_BRACKET, // U+005D
  TK_QUESTION_MARK,        // U+003F
  TK_PLUS_SIGN,            // U+002B
  TK_ASTERISK,             // U+002A
  TK_DOLLAR_SIGN,          // U+0024
  TK_CIRCUMFLEX_ACCENT,    // U+005E
  TK_HYPHEN_MINUS          // U+002D
};

typedef struct {
  enum TokenSyms type;
  union {
    char c;
    char *s;
  } u;
} RecoinToken;

int fetch_token(RecoinToken *token, char **src) { return 0; }
