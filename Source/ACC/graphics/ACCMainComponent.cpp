ACCMainComponent::ACCMainComponent()
{
    setSize (800, 600);
}

Result ACCMainComponent::setFile (const File& file)
{
    Result result = acc::ScriptParser::isACCSourceFile (file);

    if (result.failed())
        return result;

    codeDocument.replaceAllContent (file.loadFileAsString());
    component = new ACCCodeEditorComponent (codeDocument);
    addAndMakeVisible (component);

    return Result::ok();
}

void ACCMainComponent::resized()
{
    if (component != nullptr)
        component->setBounds (getLocalBounds());
}