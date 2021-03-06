// This file was generated by qlalr - DO NOT EDIT!
#ifndef JSONPARSER_CPP
#define JSONPARSER_CPP

class JsonGrammar
{
public:
  enum VariousConstants {
    EOF_SYMBOL = 0,
    ERROR = 12,
    T_COLON = 7,
    T_COMMA = 8,
    T_FALSE = 9,
    T_LCURLYBRACKET = 3,
    T_LSQUAREBRACKET = 5,
    T_NULL = 11,
    T_NUMBER = 2,
    T_RCURLYBRACKET = 4,
    T_RSQUAREBRACKET = 6,
    T_STRING = 1,
    T_TRUE = 10,

    ACCEPT_STATE = 12,
    RULE_COUNT = 17,
    STATE_COUNT = 27,
    TERMINAL_COUNT = 13,
    NON_TERMINAL_COUNT = 7,

    GOTO_INDEX_OFFSET = 27,
    GOTO_INFO_OFFSET = 37,
    GOTO_CHECK_OFFSET = 37
  };

  static const char  *const    spell [];
  static const short             lhs [];
  static const short             rhs [];

#ifndef QLALR_NO_JSONGRAMMAR_DEBUG_INFO
  static const int     rule_index [];
  static const int      rule_info [];
#endif // QLALR_NO_JSONGRAMMAR_DEBUG_INFO

  static const short    goto_default [];
  static const short  action_default [];
  static const short    action_index [];
  static const short     action_info [];
  static const short    action_check [];

  static inline int nt_action (int state, int nt)
  {
    const int yyn = action_index [GOTO_INDEX_OFFSET + state] + nt;
    if (yyn < 0 || action_check [GOTO_CHECK_OFFSET + yyn] != nt)
      return goto_default [nt];

    return action_info [GOTO_INFO_OFFSET + yyn];
  }

  static inline int t_action (int state, int token)
  {
    const int yyn = action_index [state] + token;

    if (yyn < 0 || action_check [yyn] != token)
      return - action_default [state];

    return action_info [yyn];
  }
};


const char *const JsonGrammar::spell [] = {
  "end of file", "string", "number", "{", "}", "[", "]", ":", ",", "false", 
  "true", "null", "error", 
#ifndef QLALR_NO_JSONGRAMMAR_DEBUG_INFO
"Root", "Value", "Object", "Members", "Array", "Values", "$accept"
#endif // QLALR_NO_JSONGRAMMAR_DEBUG_INFO
};

const short JsonGrammar::lhs [] = {
  13, 15, 16, 16, 16, 14, 14, 14, 14, 14, 
  14, 14, 17, 18, 18, 18, 19};

const short JsonGrammar::rhs [] = {
  1, 3, 3, 5, 0, 1, 1, 1, 1, 1, 
  1, 1, 3, 1, 3, 0, 2};


#ifndef QLALR_NO_JSONGRAMMAR_DEBUG_INFO
const int JsonGrammar::rule_info [] = {
    13, 14
  , 15, 3, 16, 4
  , 16, 1, 7, 14
  , 16, 16, 8, 1, 7, 14
  , 16
  , 14, 9
  , 14, 10
  , 14, 11
  , 14, 15
  , 14, 17
  , 14, 2
  , 14, 1
  , 17, 5, 18, 6
  , 18, 14
  , 18, 18, 8, 14
  , 18
  , 19, 13, 0};

const int JsonGrammar::rule_index [] = {
  0, 2, 6, 10, 16, 17, 19, 21, 23, 25, 
  27, 29, 31, 35, 37, 41, 42};
#endif // QLALR_NO_JSONGRAMMAR_DEBUG_INFO

const short JsonGrammar::action_default [] = {
  0, 10, 9, 0, 6, 5, 16, 8, 11, 12, 
  7, 1, 17, 0, 0, 0, 2, 0, 0, 4, 
  0, 3, 14, 0, 0, 13, 15};

const short JsonGrammar::goto_default [] = {
  3, 11, 2, 13, 1, 23, 0};

const short JsonGrammar::action_index [] = {
  24, -13, -13, 12, -13, -1, 24, -13, -13, -13, 
  -13, -13, -13, 1, -5, 2, -13, -6, 24, -13, 
  24, -13, -13, -2, 24, -13, -13, 

  -7, -7, -7, -7, -7, -7, 1, -7, -7, -7, 
  -7, -7, -7, -7, -7, -7, -7, -7, 0, -7, 
  -1, -7, -7, -7, 5, -7, -7};

const short JsonGrammar::action_info [] = {
  14, 18, 20, 17, 25, 16, 24, 0, 0, 15, 
  0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 9, 8, 5, 0, 6, 
  0, 0, 0, 4, 10, 7, 0, 

  21, 19, 22, 0, 0, 0, 26, 0, 0, 0, 
  0, 0};

const short JsonGrammar::action_check [] = {
  1, 7, 7, 1, 6, 4, 8, -1, -1, 8, 
  -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, 
  -1, -1, -1, -1, -1, 1, 2, 3, -1, 5, 
  -1, -1, -1, 9, 10, 11, -1, 

  1, 1, 1, -1, -1, -1, 1, -1, -1, -1, 
  -1, -1};


#line 29 "json.g"

/****************************************************************************
**
** Copyright (c) 2010 Girish Ramakrishnan <girish@forwardbias.in>
** Copyright (c) 2011 Denis Dzyubenko <shadone@gmail.com>
**
** Use, modification and distribution is allowed without limitation,
** warranty, liability or support of any kind.
**
****************************************************************************/

#ifndef JSONPARSER_P_H
#define JSONPARSER_P_H

#include <QString>
#include <QVariant>
#include <QVector>

class JsonLexer
{
public:
    JsonLexer(const QString &string);
    ~JsonLexer();

    int lex();
    QVariant symbol() const { return m_symbol; }
    int lineNumber() const { return m_lineNumber; }
    int pos() const { return m_pos; }

private:
    int parseNumber();
    int parseString();
    int parseKeyword();

    QString m_strdata;
    int m_lineNumber;
    int m_pos;
    QVariant m_symbol;
};

class JsonParser : protected JsonGrammar
{
public:
    JsonParser();
    ~JsonParser();

    bool parse(JsonLexer *lex);
    QVariant result() const { return m_result; }
    QString errorMessage() const { return QString::fromLatin1("%1 at line %2 pos %3").arg(m_errorMessage).arg(m_errorLineNumber).arg(m_errorPos); }

private:
    void reallocateStack();

    inline QVariant &sym(int index)
    { return m_symStack[m_tos + index - 1]; }
    inline QVariantMap &map(int index)
    { return m_mapStack[m_tos + index - 1]; }
    inline QVariantList &list(int index)
    { return m_listStack[m_tos + index - 1]; }

    int m_tos;
    QVector<int> m_stateStack;
    QVector<QVariant> m_symStack;
    QVector<QVariantMap> m_mapStack;
    QVector<QVariantList> m_listStack;
    QString m_errorMessage;
    int m_errorLineNumber;
    int m_errorPos;
    QVariant m_result;
};

#endif // JSONPARSER_P_H

#line 103 "json.g"

/****************************************************************************
**
** Copyright (c) 2010 Girish Ramakrishnan <girish@forwardbias.in>
** Copyright (c) 2011 Denis Dzyubenko <shadone@gmail.com>
**
** Use, modification and distribution is allowed without limitation,
** warranty, liability or support of any kind.
**
****************************************************************************/

#include <QtDebug>

#define L1C(c) ushort(uchar(c))

JsonLexer::JsonLexer(const QString &str)
    : m_strdata(str), m_lineNumber(1), m_pos(0)
{
}



JsonLexer::~JsonLexer()
{
}

int JsonLexer::parseString()
{
    bool esc = false;
    ++m_pos; // skip initial "
    int start = m_pos;

    const ushort *uc = m_strdata.utf16();
    const int remaining = m_strdata.length() - m_pos;
    int i;
    for (i = 0; i < remaining; ++i) {
        const ushort c = uc[m_pos + i];
        if (c == L1C('\"')) {
            m_symbol = QString((QChar *)uc + m_pos, i);
            m_pos += i;
            ++m_pos; // eat quote
            return JsonGrammar::T_STRING;
        } else if (c == L1C('\\')) {
            ++m_pos; // eat backslash
            esc = true;
            break;
        }
    }

    QString str;
    if (i) {
        str.resize(i);
        memcpy((char *)str.utf16(), uc + start, i * 2);
        m_pos += i;
    }

    for (; m_pos < m_strdata.length(); ++m_pos) {
        const ushort c = uc[m_pos];
        if (esc) {
            if (c == L1C('b')) str += QLatin1Char('\b');
            else if (c == L1C('f')) str += QLatin1Char('\f');
            else if (c == L1C('n')) str += QLatin1Char('\n');
            else if (c == L1C('r')) str += QLatin1Char('\r');
            else if (c == L1C('t')) str += QLatin1Char('\t');
            else if (c == L1C('\\')) str += QLatin1Char('\\');
            else if (c == L1C('\"')) str += QLatin1Char('\"');
            else if (c == L1C('u') && m_pos+4<m_strdata.length()-1) {
                QString u = m_strdata.mid(m_pos+1, 4);
                str += QChar(u.toUShort(0, 16));
                m_pos += 4;
            } else {
                str += QChar(c);
            }
            esc = false;
        } else if (c == L1C('\\')) {
            esc = true;
        } else if (c == L1C('\"')) {
            m_symbol = str;
            ++m_pos;
            return JsonGrammar::T_STRING;
        } else {
            str += QChar(c);
        }
    }
    return JsonGrammar::ERROR;
}

int JsonLexer::parseNumber()
{
    int start = m_pos;
    bool isDouble = false;
    const ushort *uc = m_strdata.utf16();
    const int l = m_strdata.length();
    const int negative = (uc[m_pos] == L1C('-') ? ++m_pos, -1 : (uc[m_pos] == L1C('+') ? ++m_pos, 1 : 1));
    qlonglong value = 0;
    for (; m_pos < l; ++m_pos) {
        const ushort &c = uc[m_pos];
        if (c == L1C('+') || c == L1C('-'))
            continue;
        if (c == L1C('.') || c == L1C('e') || c == L1C('E')) {
            isDouble = true;
            continue;
        }
        if (c >= L1C('0') && c <= L1C('9')) {
            if (!isDouble) {
                value *= 10;
                value += c - L1C('0');
            }
            continue;
        }
        break;
    }
    if (!isDouble) {
        m_symbol = value * negative;
    } else {
        QString number = QString::fromRawData((QChar *)uc+start, m_pos-start);
        m_symbol = number.toDouble();
    }
    return JsonGrammar::T_NUMBER;
}

int JsonLexer::parseKeyword()
{
    int start = m_pos;
    for (; m_pos < m_strdata.length(); ++m_pos) {
        const ushort c = m_strdata.at(m_pos).unicode();
        if (c >= L1C('a') && c <= L1C('z'))
            continue;
        break;
    }
    const ushort *k = (const ushort *)m_strdata.constData() + start;
    const int l = m_pos-start;
    if (l == 4) {
        static const ushort true_data[] = { 't', 'r', 'u', 'e' };
        static const ushort null_data[] = { 'n', 'u', 'l', 'l' };
        if (!memcmp(k, true_data, 4 * sizeof(ushort)))
            return JsonGrammar::T_TRUE;
        if (!memcmp(k, null_data, 4 * sizeof(ushort)))
            return JsonGrammar::T_NULL;
    } else if (l == 5) {
        static const ushort false_data[] = { 'f', 'a', 'l', 's', 'e' };
        if (!memcmp(k, false_data, 5 * sizeof(ushort)))
            return JsonGrammar::T_FALSE;
    }
    return JsonGrammar::ERROR;
}

int JsonLexer::lex()
{
    m_symbol.clear();

    const ushort *uc = m_strdata.utf16();
    const int len = m_strdata.length();
    while (m_pos < len) {
        const ushort c = uc[m_pos];
        switch (c) {
        case L1C('['): ++m_pos; return JsonGrammar::T_LSQUAREBRACKET;
        case L1C(']'): ++m_pos; return JsonGrammar::T_RSQUAREBRACKET;
        case L1C('{'): ++m_pos; return JsonGrammar::T_LCURLYBRACKET;
        case L1C('}'): ++m_pos; return JsonGrammar::T_RCURLYBRACKET;
        case L1C(':'): ++m_pos; return JsonGrammar::T_COLON;
        case L1C(','): ++m_pos; return JsonGrammar::T_COMMA;
        case L1C(' '): case L1C('\r'): case L1C('\t'): ++m_pos; break;
        case L1C('\n'): ++m_pos; ++m_lineNumber; break;
        case L1C('"'): return parseString();
        default:
            if (c == L1C('+') || c == L1C('-') || (c >= L1C('0') && c <= L1C('9'))) {
                return parseNumber();
            }
            if (c >= L1C('a') && c <= L1C('z')) {
                return parseKeyword();
            }
            return JsonGrammar::ERROR;
        }
    }
    return JsonGrammar::EOF_SYMBOL;
}
#undef L1C

JsonParser::JsonParser()
    : m_tos(0)
    , m_errorLineNumber(-1)
    , m_errorPos(-1)
{
}

JsonParser::~JsonParser()
{
}

void JsonParser::reallocateStack()
{
    int size = m_stateStack.size();
    if (size == 0)
        size = 128;
    else
        size <<= 1;

    m_symStack.resize(size);
    m_mapStack.resize(size);
    m_listStack.resize(size);
    m_stateStack.resize(size);
}

bool JsonParser::parse(JsonLexer *lexer)
{
    const int INITIAL_STATE = 0;
    int yytoken = -1;
    reallocateStack();
    m_tos = 0;
    m_stateStack[++m_tos] = INITIAL_STATE;

    while (true) {
        const int state = m_stateStack[m_tos];
        if (yytoken == -1 && -TERMINAL_COUNT != action_index[state]) {
            yytoken = lexer->lex();
        }
        int act = t_action(state, yytoken);
        if (act == ACCEPT_STATE)
            return true;
        else if (act > 0) {
            if (++m_tos == m_stateStack.size())
                reallocateStack();
            m_stateStack[m_tos] = act;
            m_symStack[m_tos] = lexer->symbol();
            yytoken = -1;
        } else if (act < 0) {
            int r = -act-1;
            m_tos -= rhs[r];
            act = m_stateStack.at(m_tos++);
            switch (r) {

#line 334 "json.g"
          case 0: { m_result = sym(1); break; } 
#line 337 "json.g"
          case 1: { sym(1) = map(2); break; } 
#line 340 "json.g"
          case 2: { QVariantMap m; m.insert(sym(1).toString(), sym(3)); map(1) = m; break; } 
#line 343 "json.g"
          case 3: { map(1).insert(sym(3).toString(), sym(5)); break; } 
#line 346 "json.g"
          case 4: { map(1) = QVariantMap(); break; } 
#line 349 "json.g"
          case 5: { sym(1) = QVariant(false); break; } 
#line 352 "json.g"
          case 6: { sym(1) = QVariant(true); break; } 
#line 361 "json.g"
          case 12: { sym(1) = list(2); break; } 
#line 364 "json.g"
          case 13: { QVariantList l; l.append(sym(1)); list(1) = l; break; } 
#line 367 "json.g"
          case 14: { list(1).append(sym(3)); break; } 
#line 370 "json.g"
          case 15: { list(1) = QVariantList(); break; } 
#line 372 "json.g"

            } // switch
            m_stateStack[m_tos] = nt_action(act, lhs[r] - TERMINAL_COUNT);
        } else {
            int ers = state;
            int shifts = 0;
            int reduces = 0;
            int expected_tokens[3];
            for (int tk = 0; tk < TERMINAL_COUNT; ++tk) {
                int k = t_action(ers, tk);

                if (! k)
                  continue;
                else if (k < 0)
                  ++reduces;
                else if (spell[tk]) {
                    if (shifts < 3)
                      expected_tokens[shifts] = tk;
                    ++shifts;
                }
            }

            m_errorLineNumber = lexer->lineNumber();
            m_errorPos = lexer->pos();
            m_errorMessage.clear();
            if (shifts && shifts < 3) {
                bool first = true;

                for (int s = 0; s < shifts; ++s) {
                    if (first)
                      m_errorMessage += QLatin1String("Expected ");
                    else
                      m_errorMessage += QLatin1String(", ");

                    first = false;
                    m_errorMessage += QLatin1String("'");
                    m_errorMessage += QLatin1String(spell[expected_tokens[s]]);
                    m_errorMessage += QLatin1String("'");
                }
            }
            return false;
        }
    }

    return false;
}


#endif // JSONPARSER_CPP

