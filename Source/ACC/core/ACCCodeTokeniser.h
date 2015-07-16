#ifndef ACC_CODE_TOKENISER_H
#define ACC_CODE_TOKENISER_H

class ACCCodeTokeniser : public CodeTokeniser
{
public:
    ACCCodeTokeniser();

    //==============================================================================
    /** The token values returned by this tokeniser. */
    enum TokenType
    {
        errorTokenType = 0,
        commentTokenType,
        keywordTokenType,
        operatorTokenType,
        identifierTokenType,
        integerTokenType,
        floatTokenType,
        stringTokenType,
        bracketTokenType,
        punctuationTokenType,
        preprocessorTokenType
    };

    enum
    {
        shortestKeywordLength = 2,
        longestKeywordLength = 20
    };

    //==============================================================================
    /** This is a handy method for checking whether a string is an ACC reserved keyword. */
    static bool isReservedKeyword (const String& token) noexcept;

    static bool isIdentifierStart (juce_wchar c) noexcept;
    static bool isIdentifierBody (juce_wchar c) noexcept;
    static TokenType parseIdentifier (CodeDocument::Iterator& source);
    static TokenType parseNumber (CodeDocument::Iterator& source);

    //==============================================================================
    /** @internal */
    int readNextToken (CodeDocument::Iterator& source) override;
    /** @internal */
    CodeEditorComponent::ColourScheme getDefaultColourScheme() override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ACCCodeTokeniser)
};

#endif //ACC_CODE_TOKENISER_H