static ACCCodeTokeniser accCodeTokeniser;

ACCCodeEditorComponent::ACCCodeEditorComponent (CodeDocument& codeDocument) :
    CodeEditorComponent (codeDocument, &accCodeTokeniser),
    fontSize (12.0f)
{
    setTabSize (4, true);

    setFont (getFont().withHeight (fontSize));

    LookAndFeel& laf = getLookAndFeel();
    laf.setColour (CodeEditorComponent::highlightColourId, Colour (234, 234, 242));
    laf.setColour (CodeEditorComponent::lineNumberBackgroundId, Colours::white);
    laf.setColour (CodeEditorComponent::lineNumberTextId, Colour (43, 145, 175));
}

//==============================================================================
void ACCCodeEditorComponent::mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& mwd)
{
    if (e.mods.isCommandDown())
    {
        const float lastSize = fontSize;
        const float scrollRatio = 1.2f;

        if (mwd.deltaY > 0.0f)
            fontSize += scrollRatio;
        else if (mwd.deltaY < 0.0f)
            fontSize -= scrollRatio;

        if (fontSize != lastSize)
            setFont (getFont().withHeight (fontSize));
    }
    else
    {
        CodeEditorComponent::mouseWheelMove (e, mwd);
    }
}