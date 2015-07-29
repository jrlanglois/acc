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

//==============================================================================
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
    const Result result = isACCSourceFile (accFile);

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