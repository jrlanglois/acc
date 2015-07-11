ACCCodeTokeniser::ACCCodeTokeniser()
{
}

//==============================================================================
int ACCCodeTokeniser::readNextToken (CodeDocument::Iterator& source)
{
    return CppTokeniserFunctions::readNextToken (source);
}

CodeEditorComponent::ColourScheme ACCCodeTokeniser::getDefaultColourScheme()
{
    const CodeEditorComponent::ColourScheme::TokenType types[] =
    {
        { "Error",              Colour (0xffcc0000) },
        { "Comment",            Colour (0xff00aa00) },
        { "Keyword",            Colour (0xff0000cc) },
        { "Operator",           Colour (0xff225500) },
        { "Identifier",         Colour (0xff000000) },
        { "Integer",            Colour (0xff880000) },
        { "Float",              Colour (0xff885500) },
        { "String",             Colour (0xff990099) },
        { "Bracket",            Colour (0xff000055) },
        { "Punctuation",        Colour (0xff004400) },
        { "Preprocessor Text",  Colour (0xff660000) }
    };

    CodeEditorComponent::ColourScheme colourScheme;

    for (unsigned int i = 0; i < sizeof (types) / sizeof (types[0]); ++i)  // (NB: numElementsInArray doesn't work here in GCC4.2)
        colourScheme.set (types[i].name, Colour (types[i].colour));

    return colourScheme;
}

bool ACCCodeTokeniser::isReservedKeyword (const String& token) noexcept
{
    return CppTokeniserFunctions::isReservedKeyword (token.getCharPointer(), token.length());
}