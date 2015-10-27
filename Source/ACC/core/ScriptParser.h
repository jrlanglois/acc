#ifndef ACC_SCRIPT_PARSER_H
#define ACC_SCRIPT_PARSER_H

/** An ACC script parser
*/
class ScriptParser
{
public:
    ScriptParser();

    //==============================================================================
    struct Parameters
    {
        Parameters() :
            useHexenCase (false),
            enforceHexenCase (false),
            warnIfNotHexen (false),
            showWadAuthor (false),
            encryptStrings (false)
        {
        }

        bool useHexenCase, enforceHexenCase, warnIfNotHexen;
        bool showWadAuthor, encryptStrings;
    };

    static Result isACCSourceFile (const File& potentialACCSourceFile);

    Result evaluate (const File& accFile, const Parameters& parameters = Parameters());

private:
    //==============================================================================
    enum Configuration
    {
        maxIdentifierLength     = 32,
        maxFileNameLength       = 512,
        maxStatementLength      = 4096,
        maxQuotedLength         = 32768,
        maxNumStrings           = 32768,

        maxNumScripts           = 1000,
        maxNumMapVariables      = 128,
        maxNumWorldVariables    = 256,
        maxNumGlobalVariables   = 64,

        maxNumScriptArrays      = 255,
        maxNumFunctions         = 256,
        maxNumImports           = 256,
        maxNumIncludePaths      = 16,
        maxNumTranslations      = 32,

        defaultObjectSize = 65536
    };

    //==============================================================================
    struct ScopeVariable
    {
        ScopeVariable() :
            numVariables (0),
            numArrays (0)
        {
        }

        int numVariables, numArrays;
    };

    int numMaps;
    ScopeVariable worldVariables, globalVariables;

    ACCCodeTokeniser tokeniser;

    //==============================================================================
    Result evaluate (const String& accScriptCode, const Parameters& parameters);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScriptParser)
};

#endif //ACC_SCRIPT_PARSER_H