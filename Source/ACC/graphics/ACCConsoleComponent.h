#ifndef ACC_CONSOLE_COMPONENT_H
#define ACC_CONSOLE_COMPONENT_H

class ConsoleComponent : public Component,
                         private TextEditor::Listener
{
public:
    ConsoleComponent();

    //=============================================================================
    void addLine (const String& line, bool prefixed = false);
    void addLines (const StringArray& lines, bool prefixed = false);
    void clear();

    //=============================================================================
    void parseCommand (const String& command);

    //=============================================================================
    /** @internal */
    void resized() override;
    /** @internal */
    void textEditorReturnKeyPressed (TextEditor& textEditor) override;

private:
    //=============================================================================
    TextEditor input, output;

    //=============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConsoleComponent)
};

#endif //ACC_CONSOLE_COMPONENT_H