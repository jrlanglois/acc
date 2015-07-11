#ifndef ACC_CODE_TOKENISER_H
#define ACC_CODE_TOKENISER_H

class ACCCodeTokeniser : public CodeTokeniser
{
public:
    ACCCodeTokeniser();

    //==============================================================================
    /** This is a handy method for checking whether a string is an ACC reserved keyword. */
    static bool isReservedKeyword (const String& token) noexcept;

    /** The token values returned by this tokeniser. */
    enum TokenType
    {
        tokenType_error = 0,
        tokenType_comment,
        tokenType_keyword,
        tokenType_operator,
        tokenType_identifier,
        tokenType_integer,
        tokenType_float,
        tokenType_string,
        tokenType_bracket,
        tokenType_punctuation,
        tokenType_preprocessor
    };

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