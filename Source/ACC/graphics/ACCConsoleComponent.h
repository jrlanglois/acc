#ifndef ACC_CONSOLE_COMPONENT_H
#define ACC_CONSOLE_COMPONENT_H

class ConsoleComponent : public Component,
                         private TextEditor::Listener
{
public:
    ConsoleComponent();
    ~ConsoleComponent();

    //=============================================================================
    void addLine (const String& line, bool prefixed = false);
    void addLines (const StringArray& lines, bool prefixed = false);
    void clear();

    //=============================================================================
    bool parseCommand (String& message, const String& command);

    //=============================================================================
    /** @internal */
    void resized() override;
    /** @internal */
    void textEditorReturnKeyPressed (TextEditor& textEditor) override;

private:
    //=============================================================================
    TextEditor input, output;

    OwnedArray<ConsoleCommandItem> commandItems;

    //=============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConsoleComponent)
};

#endif //ACC_CONSOLE_COMPONENT_H