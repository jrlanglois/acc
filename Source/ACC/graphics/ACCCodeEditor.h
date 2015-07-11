#ifndef ACC_CODE_EDITOR_H
#define ACC_CODE_EDITOR_H

class ACCCodeEditorComponent : public CodeEditorComponent
{
public:
    ACCCodeEditorComponent (CodeDocument& codeDocument);

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ACCCodeEditorComponent)
};

#endif //ACC_CODE_EDITOR_H