ConsoleComponent::ConsoleComponent()
{
    input.setMultiLine (false, false);
    input.addListener (this);

    output.setReadOnly (true);
    output.setMultiLine (true, false);
    output.setPopupMenuEnabled (false);

    addAndMakeVisible (&input);
    addAndMakeVisible (&output);
}

//=============================================================================
void ConsoleComponent::addLine (const String& line, const bool prefixed)
{
    output.moveCaretToEnd();
    output.insertTextAtCaret (newLine + (prefixed ? "> " : String::empty) + line);
}

void ConsoleComponent::addLines (const StringArray& lines, const bool prefixed)
{

}

void ConsoleComponent::clear()
{
    input.clear();
    output.clear();
}

//=============================================================================
static bool isCommand (const String& source, const String& commandToCheck)
{
    return source.compareIgnoreCase (commandToCheck) == 0
           || source.startsWithIgnoreCase (commandToCheck);
}

void ConsoleComponent::parseCommand (const String& command)
{
    if (isCommand (command, "clear"))
    {
        input.clear();
        output.clear();
    }
    else if (isCommand (command, "help"))
    {
        addLine ("Some important list of commands will eventually show up...", true);
    }
    else if (isCommand (command, "version"))
    {
        addLine (String ("V") + ProjectInfo::versionString, true);
    }
    else if (isCommand (command, "copyright"))
    {
        addLine ("Jo\u00ebl R. Langlois, 2015(C) to present", true);
    }
    else if (isCommand (command, "compile"))
    {
    }
    else if (isCommand (command, "recompile"))
    {
    }
    else
    {
        addLine (command.quoted() + " is an unknown command!", true);
    }
}

//=============================================================================
void ConsoleComponent::textEditorReturnKeyPressed (TextEditor& textEditor)
{
    parseCommand (textEditor.getText().trim());

    input.clear();
}

//=============================================================================
void ConsoleComponent::resized()
{
    const int inputHeight = (int) input.getFont().getHeight() + 6;
    input.setBounds (0, getHeight() - inputHeight, getWidth(), inputHeight);

    output.setBounds (0, 0, getWidth(), getHeight() - inputHeight);
}