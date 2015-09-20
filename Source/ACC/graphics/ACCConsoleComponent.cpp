

//=============================================================================
ConsoleComponent::ConsoleComponent()
{
    commandItems.add (new ExitItem());
    commandItems.add (new CopyrightItem());
    commandItems.add (new VersionItem());
    commandItems.add (new ClearCommandItem (input, output));

    input.setMultiLine (false, false);
    input.addListener (this);

    output.setReadOnly (true);
    output.setMultiLine (true, false);
    output.setPopupMenuEnabled (false);

    addAndMakeVisible (&input);
    addAndMakeVisible (&output);
}

ConsoleComponent::~ConsoleComponent()
{
    commandItems.clear(); //N.B.: Just in case the commands rely on anything else that may be out of scope at this point
}

//=============================================================================
void ConsoleComponent::addLine (const String& line, const bool prefixed)
{
    const String potentialNewLine = output.getTotalNumChars() > 0
                                        ? newLine
                                        : String::empty;

    output.moveCaretToEnd();
    output.insertTextAtCaret (potentialNewLine + (prefixed ? "> " : String::empty) + line);
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
bool ConsoleComponent::parseCommand (String& message, const String& command)
{
    StringArray tokens (StringArray::fromTokens (command, true));
    tokens.removeEmptyStrings();
    tokens.removeDuplicates (true);
    tokens.trim();

    if (tokens.size() <= 0)
    {
        message = "No commands to process!";
        return false;
    }

    const String& firstToken = tokens.strings.getReference (0);

    ConsoleCommandItem* item = nullptr;
    for (int i = commandItems.size(); --i >= 0;)
    {
        if (commandItems.getUnchecked (i)->canProcess (firstToken))
        {
            item = commandItems.getUnchecked (i);
            break;
        }
    }

    if (item == nullptr)
    {
        message = command.quoted() + " is an unknown command!";
        return false;
    }

    //Try processing 'help':
    if (tokens.size() == 2
        && tokens.getReference (1).compareIgnoreCase ("help") == 0)
    {
        addLine (item->processHelp(), false);
        return Result::ok();
    }

    return item->process (message, tokens);
}

//=============================================================================
void ConsoleComponent::textEditorReturnKeyPressed (TextEditor& textEditor)
{
    String message;
    parseCommand (message, textEditor.getText().trim());

    if (message.isNotEmpty())
        addLine (message, true);

    input.clear();
}

//=============================================================================
void ConsoleComponent::resized()
{
    const int inputHeight = (int) input.getFont().getHeight() + 6;

    input.setBounds (0, getHeight() - inputHeight, getWidth(), inputHeight);
    output.setBounds (0, 0, getWidth(), getHeight() - inputHeight);
}