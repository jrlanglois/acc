#ifndef ACC_COMMAND_ITEMS_H
#define ACC_COMMAND_ITEMS_H

//=============================================================================
class ConsoleCommandItem
{
public:
    ConsoleCommandItem (const String& mainCommandName) :
        mainCommand (mainCommandName)
    {
    }

    virtual ~ConsoleCommandItem() { }

    virtual bool canProcess (const String& firstToken)
    {
        return mainCommand.compareIgnoreCase (firstToken) == 0;
    }

    virtual bool process (String& message, const StringArray& tokens) = 0;
    virtual String processHelp() = 0;

private:
    const String mainCommand;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConsoleCommandItem)
};

//=============================================================================
class ExitItem : public ConsoleCommandItem
{
public:
    ExitItem() :
        ConsoleCommandItem ("exit")
    {
    }

    bool canProcess (const String& firstToken) override
    {
        return ConsoleCommandItem::canProcess (firstToken)
               || firstToken.compareIgnoreCase ("quit") == 0;
    }

    bool process (String& message, const StringArray& tokens) override
    {
        if (tokens.size() > 1)
        {
            message = "Not sure what else to process!";
            return false;
        }

        JUCEApplication::getInstance()->systemRequestedQuit();
        return true;
    }

    String processHelp() override
    {
        return String::empty;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExitItem)
};

//=============================================================================
class CopyrightItem : public ConsoleCommandItem
{
public:
    CopyrightItem() :
        ConsoleCommandItem ("copyright")
    {
    }

    bool process (String& message, const StringArray& tokens) override
    {
        if (tokens.size() > 1)
        {
            message = "Not sure what else to process!";
            return false;
        }

        return true;
    }

    String processHelp() override
    {
        return String::empty;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CopyrightItem)
};

//=============================================================================
class VersionItem : public ConsoleCommandItem
{
public:
    VersionItem() :
        ConsoleCommandItem ("version")
    {
    }

    bool process (String& message, const StringArray& tokens) override
    {
        if (tokens.size() > 1)
        {
            message = "Not sure what else to process!";
            return false;
        }

        return true;
    }

    String processHelp() override
    {
        return String::empty;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VersionItem)
};

//=============================================================================
class ClearCommandItem : public ConsoleCommandItem
{
public:
    ClearCommandItem (TextEditor& i, TextEditor& o) :
        ConsoleCommandItem ("clear"),
        input (i),
        output (o)
    {
    }

    bool process (String&, const StringArray& tokens) override
    {
        if (tokens.contains ("-i", true))
        {
            input.clear();
        }
        else if (tokens.contains ("-o", true))
        {
            output.clear();
        }
        else
        {
            input.clear();
            output.clear();
        }

        return true;
    }

    String processHelp() override
    {
        return "'clear'" + newLine
               + "use '-i'\t for just the input" + newLine
               + "use '-o'\t for just the output";
    }

private:
    TextEditor& input;
    TextEditor& output;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClearCommandItem)
};

#endif //ACC_COMMAND_ITEMS_H