static ACCCodeTokeniser accCodeTokeniser;

ACCCodeEditorComponent::ACCCodeEditorComponent (CodeDocument& codeDocument) :
    CodeEditorComponent (codeDocument, &accCodeTokeniser)
{
}