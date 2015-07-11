#include "../ACC/ACCModule.h"

//==============================================================================
class CommandLine
{
public:
    CommandLine (int numArguments, char* listOfArguments[])
    {
        for (int i = 0; i < numArguments; ++i)
            arguments.addTokens (String (listOfArguments[i]).trim(), true);

        arguments.trim();
    }

    void displayUsage()
    {
	    output ("\nUsage: ACC [options] source[.acs] [object[.o]]\n");
	    output ("-i [path]  Add include path to find include files");
	    output ("-d [file]  Output debugging information");
	    output ("-h         Create pcode compatible with Hexen and old ZDooms");
	    output ("-hh        Like -h, but use of new features is only a warning");
    }

private:
    StringArray arguments;

    void output (const String& text)
    {
        Logger::writeToLog (text);
    }

    JUCE_DECLARE_NON_COPYABLE (CommandLine)
};


//==============================================================================
class ACCApplication : public JUCEApplication
{
public:
    ACCApplication()
    {
    }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        window = new ACCWindow();
    }

    void shutdown() override
    {
    }

    //==============================================================================
    const String getApplicationName() override
    {
        return ProjectInfo::projectName;
    }

    const String getApplicationVersion() override
    {
        return ProjectInfo::versionString;
    }

    bool moreThanOneInstanceAllowed() override
    {
        return true;
    }

    void anotherInstanceStarted (const String& commandLine) override
    {
    }

private:
    ScopedPointer<ACCWindow> window;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ACCApplication)
};

//==============================================================================
START_JUCE_APPLICATION (ACCApplication)