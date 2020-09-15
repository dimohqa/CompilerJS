#include "TokenTypeSwitch.h"

string TokenOfEnum(int Tok) {
    switch (Tok) {
        case TokenType::KW_THIS:
            return "this";

        case TokenType::KW_NEW:
            return "new";

        case TokenType::KW_FUNCTION:
            return "function";

        case TokenType::KW_VAR:
            return "var";

        case TokenType::KW_FOR:
            return "for";

        case TokenType::KW_IF:
            return "if";

        case TokenType::KW_ELSE:
            return "else";

        case TokenType::KW_TRUE:
            return "true";

        case TokenType::KW_FALSE:
            return "false";

        case TokenType::KW_RETURN:
            return "return";

        case TokenType::KW_UNDEFINED:
            return "undefined";

        case TokenType::KW_NULL:
            return "null";

        case TokenType::KW_INSTANCEOF:
            return "instanceof";

        case TokenType::KW_IN:
            return "in";

        case TokenType::KW_DO:
            return "do";

        case TokenType::KW_DEFAULT:
            return "default";

        case TokenType::KW_VOID:
            return "void";

        case TokenType::KW_WHILE:
            return "while";

        case TokenType::KW_BREAK:
            return "break";

        case TokenType::KW_CASE:
            return "case";

        case TokenType::KW_TYPEOF:
            return "typeof";

        case TokenType::KW_CONTINUE:
            return "continue";

        case TokenType::KW_INFINITY:
            return "infinity";

        case TokenType::KW_NAN:
            return "nan";

        case TokenType::KW_DELETE:
            return "delete";

        case TokenType::KW_SWITCH:
            return "switch";

        case TokenType::KW_TRY:
            return "try";

        case TokenType::KW_CATCH:
            return "catch";

        case TokenType::KW_THROW:
            return "throw";

        case TokenType::KW_FINALLY:
            return "finally";

        case TokenType::KW_WITH:
            return "with";

        case TokenType::KW_DEBUGGER:
            return "debugger";

        case TokenType::KW_LET:
            return "let";

        case TokenType::KW_CONST:
            return "const";

        case TokenType::KW_CONSOLE:
            return "console";

        case TokenType::KW_LOG:
            return "log";

        case TokenType::LBRACKET:
            return "lbracket";

        case TokenType::RBRACKET:
            return "rbracket";

        case TokenType::DOT:
            return "dot";

        case TokenType::GEQT:
            return "geqt";

        case TokenType::PLUS:
            return "plus";

        case TokenType::LSHIFT:
            return "lshift";

        case TokenType::NEGATION:
            return "negation";

        case TokenType::GGEQT:
            return "ggeqt";

        case TokenType::SEMICOLON:
            return "semicolon";

        case TokenType::DIVISION:
            return "division";

        case TokenType::EEQUAL:
            return "eequal";

        case TokenType::MINUS:
            return "minus";

        case TokenType::RSHIFT:
            return "rshift";

        case TokenType::CEDILLA:
            return "cedilla";

        case TokenType::PLUSEQ:
            return "pluseq";

        case TokenType::DIVISIONEQ:
            return "divisioneq";

        case TokenType::GGGEQT:
            return "gggeqt";

        case TokenType::LPAREN:
            return "lparen";

        case TokenType::COMMA:
            return "comma";

        case TokenType::NOTEQUAL:
            return "notequal";

        case TokenType::STAR:
            return "star";

        case TokenType::GGGT:
            return "gggt";

        case TokenType::AND:
            return "and";

        case TokenType::MINUSEQ:
            return "minuseq";

        case TokenType::ANDEQ:
            return "andeq";

        case TokenType::RPAREN:
            return "rparen";

        case TokenType::LT:
            return "lt";

        case TokenType::EEEQUAL:
            return "eeequal";

        case TokenType::PERCENTAGE:
            return "percentage";

        case TokenType::BW_AND:
            return "bw_and";

        case TokenType::OR:
            return "or";

        case TokenType::TIMESEQ:
            return "timeseq";

        case TokenType::OREQ:
            return "oreq";

        case TokenType::LBRACE:
            return "lbrace";

        case TokenType::GT:
            return "gt";

        case TokenType::NOTEEQUAL:
            return "noteequal";

        case TokenType::INCREMENT:
            return "increment";

        case TokenType::BW_OR:
            return "bw_or";

        case TokenType::QUESTION:
            return "qustion";

        case TokenType::PERCENTAGEEQUAL:
            return "percentageequal";

        case TokenType::EXPEQUAL:
            return "expqual";

        case TokenType::ESCAPE:
            return "escape";

        case TokenType::DECREMENT:
            return "decrement";

        case TokenType::EXP:
            return "exp";

        case TokenType::COLON:
            return "colon";

        case TokenType::LLEQT:
            return "lleqt";

        case TokenType::RBRACE:
            return "rbrace";

        case TokenType::LEQT:
            return "leqt";

        case TokenType::EQUAL:
            return "equal";

        case TokenType::ID:
            return "id";

        case TokenType::OCT_NUMBER:
            return "oct_number";

        case TokenType::HEX_NUMBER:
            return "hex_number";

        case TokenType::NUMBER:
            return "number";

        case TokenType::REAL_NUMBER:
            return "real_number";

        case TokenType::STRING:
            return "string";

        case TokenType::E0F:
            return "eof";

        default:
            return "unknown";
    }
}
