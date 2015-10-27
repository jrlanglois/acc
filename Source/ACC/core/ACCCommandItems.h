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

    String getCommandName() const { return TRANS (mainCommand); }

private:
    const String mainCommand; //Untranslated command string this item supports

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConsoleCommandItem)
};

//=============================================================================
class ExitCommandItem : public ConsoleCommandItem
{
public:
    ExitCommandItem() :
        ConsoleCommandItem (NEEDS_TRANS ("exit"))
    {
    }

    bool canProcess (const String& firstToken) override
    {
        return ConsoleCommandItem::canProcess (firstToken)
               || firstToken.compareIgnoreCase (TRANS ("quit")) == 0;
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ExitCommandItem)
};

//=============================================================================
class CopyrightCommandItem : public ConsoleCommandItem
{
public:
    CopyrightCommandItem() :
        ConsoleCommandItem (NEEDS_TRANS ("copyright"))
    {
    }

    bool process (String& message, const StringArray& tokens) override
    {
        if (tokens.size() > 1)
        {
            message = "Not sure what else to process!";
            return false;
        }

        message = CharPointer_UTF8 ("\xc2\xa9Jo\xc3\xabl R. Langlois") + ", " + String (Time::getCurrentTime().getYear());
        return true;
    }

    String processHelp() override
    {
        return String::empty;
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CopyrightCommandItem)
};

//=============================================================================
class VersionCommandItem : public ConsoleCommandItem
{
public:
    VersionCommandItem() :
        ConsoleCommandItem (NEEDS_TRANS ("version"))
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VersionCommandItem)
};

//=============================================================================
class ClearCommandItem : public ConsoleCommandItem
{
public:
    ClearCommandItem (TextEditor& i, TextEditor& o) :
        ConsoleCommandItem (NEEDS_TRANS ("clear")),
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
        return String ("use '-i'\t for just the input") + newLine
               + "use '-o'\t for just the output";
    }

private:
    TextEditor& input;
    TextEditor& output;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClearCommandItem)
};

//=============================================================================
class URLCommandItem : public ConsoleCommandItem
{
public:
    URLCommandItem() :
        ConsoleCommandItem (NEEDS_TRANS ("url"))
    {
    }

    bool canProcess (const String& firstToken) override
    {
        return URL::isProbablyAWebsiteURL (firstToken)
               || firstToken.startsWithIgnoreCase ("www.");
    }

    bool process (String& message, const StringArray& tokens) override
    {
        for (int i = 0; i < tokens.size(); ++i)
        {
            if (canProcess (tokens[i]))
            {
                if (URL (tokens[i]).launchInDefaultBrowser())
                {
                    message = "'" + tokens[i] + "' was apparently launched in your browser...";
                    return true;
                }
            }
        }

        message = "Not sure about that being a URL!";
        return false;
    }

    String processHelp() override
    {
        return "Simply type in a URL and I'll attempt opening it in your default browser.";
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (URLCommandItem)
};

#endif //ACC_COMMAND_ITEMS_H