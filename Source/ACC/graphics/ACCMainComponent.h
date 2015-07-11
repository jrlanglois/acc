#ifndef ACC_MAIN_COMPONENT_H
#define ACC_MAIN_COMPONENT_H

class ACCMainComponent : public Component
{
public:
    ACCMainComponent();

    //==============================================================================
    Result setFile (const File& file);

    //==============================================================================
    /** @internal */
    void resized() override;

private:
    //==============================================================================
    CodeDocument codeDocument;
    ScopedPointer<ACCCodeEditorComponent> component;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ACCMainComponent)
};

#endif //ACC_MAIN_COMPONENT_H