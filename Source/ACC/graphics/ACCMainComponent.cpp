class ACCToolbarItemFactory : public ToolbarItemFactory
{
public:
    ACCToolbarItemFactory()
    {
    }

    void getAllToolbarItemIds (Array<int>& ids) override
    {
        getDefaultItemSet (ids);
    }

    void getDefaultItemSet (Array<int>& ids) override
    {
        ids.add (createNewFile);
        ids.add (saveFile);
        ids.add (openFile);
        ids.add (separatorBarId);
        ids.add (undo);
        ids.add (redo);
        ids.add (compile);
    }

    ToolbarItemComponent* createItem (int itemId) override
    {
        return nullptr;
    }

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ACCToolbarItemFactory)
};

//==============================================================================
ACCMainComponent::ACCMainComponent() :
    menuBarComponent (nullptr)
{
    codeEditorComponent = new ACCCodeEditorComponent (codeDocument);

    addAndMakeVisible (&menuBarComponent);
    addAndMakeVisible (&toolbar);
    addAndMakeVisible (codeEditorComponent);

    String path = File::getSpecialLocation (File::currentApplicationFile)
                        .getFullPathName()
                        .upToFirstOccurrenceOf ("jrl_acc", true, true)
                  + "/Source/UnitTests/AllTests.acs";

    setFile (File (path));

    setSize (800, 600);
}

Result ACCMainComponent::setFile (const File& file)
{
    Result result = acc::ScriptParser::isACCSourceFile (file);

    if (result.failed())
        return result;

    codeEditorComponent->loadContent (file.loadFileAsString());

    return Result::ok();
}

void ACCMainComponent::resized()
{
    enum
    {
        barHeight = 32,
        codeEditorOffset = barHeight * 2
    };

    const int w = getWidth();

    menuBarComponent.setBounds (0, 0, w, barHeight);
    toolbar.setBounds (0, barHeight, w, barHeight);

    if (codeEditorComponent != nullptr)
        codeEditorComponent->setBounds (0, codeEditorOffset, w, getHeight() - codeEditorOffset);
}

//==============================================================================
StringArray ACCMainComponent::getMenuBarNames()
{
    StringArray names;

    names.add (TRANS ("File"));
    names.add (TRANS ("Edit"));
    names.add (TRANS ("View"));
    names.add (TRANS ("Build"));
    names.add (TRANS ("Tools"));
    names.add (TRANS ("Help"));

    return names;
}

PopupMenu ACCMainComponent::getMenuForIndex (const int topLevelMenuIndex,
                                             const String& menuName)
{
    PopupMenu popupMenu;

    if (menuName == TRANS ("File"))
    {

    }
    else if (menuName == TRANS ("Edit"))
    {

    }
    else if (menuName == TRANS ("View"))
    {

    }
    else if (menuName == TRANS ("Build"))
    {

    }
    else if (menuName == TRANS ("Tools"))
    {

    }
    else if (menuName == TRANS ("Help"))
    {

    }

    return popupMenu;
}

void ACCMainComponent::menuItemSelected (const int menuItemID,
                                         const int topLevelMenuIndex)
{

}

void ACCMainComponent::menuBarItemsChanged (MenuBarModel* const menuBarModel)
{

}

void ACCMainComponent::menuCommandInvoked (MenuBarModel* const menuBarModel,
                                           const ApplicationCommandTarget::InvocationInfo& info)
{

}