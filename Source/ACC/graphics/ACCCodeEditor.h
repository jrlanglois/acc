#ifndef ACC_CODE_EDITOR_COMPONENT_H
#define ACC_CODE_EDITOR_COMPONENT_H

class ACCCodeEditorComponent : public CodeEditorComponent
{
public:
    ACCCodeEditorComponent (CodeDocument& codeDocument);

    //==============================================================================
    /** @internal */
    void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;

private:
    //==============================================================================
    float fontSize;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ACCCodeEditorComponent)
};

#endif //ACC_CODE_EDITOR_COMPONENT_H