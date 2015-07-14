//==============================================================================
#define ACC_OPERATORS(X) \
    X(plus, "+")            X(minus, "-")           X(times, "*")               X(divide, "/") \
    X(modulo, "%")          X(not, "~")             X(bitwiseAnd, "&")          X(bitwiseOr, "|") \
    X(bitwiseXor, "^")      X(assign, "=")          X(plusplus, "++")           X(minusminus, "--") \
    X(plusEquals, "+=")     X(minusEquals, "-=")    X(timesEquals, "*=")        X(divideEquals, "/=") \
    X(moduloEquals, "%=")   X(xorEquals, "^=")      X(andEquals, "&=")          X(orEquals, "|=") \
    X(equals, "==")         X(notEquals, "!=")      X(logicalAnd, "&&")         X(logicalOr, "||") \
    X(lessThan, "<")        X(greaterThan, ">")     X(lessThanOrEqual, "<=")    X(greaterThanOrEqual, ">=") \
    X(leftShift, "<<")      X(rightShift, ">>")     X(leftShiftEquals, "<<=")   X(rightShiftEquals, ">>=") \
    X(semicolon, ";")       X(dot, ".")             X(comma, ",") \
    X(openParen, "(")       X(closeParen, ")")      X(openBrace, "{")           X(closeBrace, "}") \
    X(openBracket, "[")     X(closeBracket, "]")    X(colon, ":")               X(question,   "?") \

/*
    X(semicolon,     ";")        X(dot,          ".")       X(comma,        ",") \
    X(openParen,     "(")        X(closeParen,   ")")       X(openBrace,    "{")    X(closeBrace, "}") \
    X(openBracket,   "[")        X(closeBracket, "]")       X(colon,        ":")    X(question,   "?") \
    X(typeEquals,    "===")      X(equals,       "==")      X(assign,       "=") \
    X(typeNotEquals, "!==")      X(notEquals,    "!=")      X(logicalNot,   "!") \
    X(plusEquals,    "+=")       
    X(minusEquals,   "-=") \
    X(timesEquals,   "*=")       X(times,        "*")       X(divideEquals, "/=")   X(divide,     "/") \
    X(moduloEquals,  "%=")       X(modulo,       "%")       X(xorEquals,    "^=")   X(bitwiseXor, "^") \
    X(andEquals,     "&=")       X(logicalAnd,   "&&")      X(bitwiseAnd,   "&") \
    X(orEquals,      "|=")       X(logicalOr,    "||")      X(bitwiseOr,    "|") \
    X(leftShiftEquals,    "<<=") X(lessThanOrEqual,  "<=")  X(leftShift,    "<<")   X(lessThan,   "<") \
    X(rightShiftUnsigned, ">>>") X(rightShiftEquals, ">>=") X(rightShift,   ">>")   X(greaterThanOrEqual, ">=")  X(greaterThan,  ">")
*/

#define ACC_KEYWORDS(X) \
    X(acs_executewait) \
	X(acs_namedexecutewait) \
	X(bluereturn) \
	X(clientside) \
	X(createtranslation) \
	X(death) \
	X(define) \
	X(disconnect) \
	X(encryptstrings) \
	X(enter) \
	X(function) \
	X(global) \
	X(hudmessage) \
	X(hudmessagebold) \
	X(import) \
	X(include) \
	X(libdefine) \
	X(library) \
	X(lightning) \
	X(log) \
	X(net) \
	X(nocompact) \
	X(nowadauthor) \
	X(open) \
	X(pickup) \
	X(print) \
	X(printbold) \
	X(redreturn) \
	X(respawn) \
	X(restart) \
	X(script) \
	X(special) \
	X(str) \
	X(strparam) \
	X(suspend) \
	X(terminate) \
	X(unloading) \
	X(until) \
	X(wadauthor) \
	X(whitereturn) \
	X(world)

#define ACC_OVERRIDDEN_CPP_KEYWORDS(X) \
	X(bool) \
    X(break) \
	X(case) \
	X(const) \
	X(continue) \
	X(default) \
	X(do) \
	X(else) \
	X(event) \
	X(for) \
	X(goto) \
	X(if) \
	X(int) \
	X(return) \
	X(static) \
	X(strcpy) \
	X(switch) \
	X(void) \
	X(while)

namespace TokenTypes
{
    #define ACC_DECLARE_TOKEN(name, str) \
        static const char* const name = str;

    #define ACC_DECLARE_UNNAMED_TOKEN(name) \
        static const char* const name = JUCE_STRINGIFY (name);

    #define ACC_DECLARE_OVERRIDDEN_TOKEN(name) \
        static const char* const JUCE_JOIN_MACRO (name, _) = JUCE_STRINGIFY (name);

    ACC_OPERATORS (ACC_DECLARE_TOKEN)
    ACC_KEYWORDS (ACC_DECLARE_UNNAMED_TOKEN)
    ACC_OVERRIDDEN_CPP_KEYWORDS (ACC_DECLARE_OVERRIDDEN_TOKEN)

    ACC_DECLARE_TOKEN (eof,         "$eof")
    ACC_DECLARE_TOKEN (literal,     "$literal")
    ACC_DECLARE_TOKEN (identifier,  "$identifier")

    #undef ACC_DECLARE_TOKEN
    #undef ACC_DECLARE_UNNAMED_TOKEN
    #undef ACC_DECLARE_OVERRIDDEN_TOKEN
}

#undef ACC_KEYWORDS
#undef ACC_OPERATORS

//==============================================================================
class IncludePathHandler
{
public:
    IncludePathHandler()
    {
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (IncludePathHandler)
};

Result openObject (const String& name, int size, int flags);
Result closeObject();

//==============================================================================
ScriptParser::ScriptParser()
{
}

Result ScriptParser::isACCSourceFile (const File& potentialACCSourceFile)
{
    if (! potentialACCSourceFile.hasFileExtension (".acs"))
        return Result::fail (TRANS ("The file given is not an ACC script!"));

    return Result::ok();
}

Result ScriptParser::evaluate (const File& accFile, const Parameters& parameters)
{
    Result result = isACCSourceFile (accFile);

    if (result.failed())
        return result;

    return evaluate (accFile.loadFileAsString(), parameters);
}

Result ScriptParser::evaluate (const String& accScriptCode, const Parameters& parameters)
{
    if (accScriptCode.isEmpty())
        return Result::fail (TRANS ("Either failed loading the file, or the file is empty!"));

    jassertfalse;

    return Result::ok();
}