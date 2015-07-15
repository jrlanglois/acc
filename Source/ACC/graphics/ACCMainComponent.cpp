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

    menuBarComponent.setModel (this);

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
        menuBarHeight = 24,
        toolBarHeight = 32,
        codeEditorOffset = menuBarHeight + toolBarHeight
    };

    const int w = getWidth();

    menuBarComponent.setBounds (0, 0, w, menuBarHeight);
    toolbar.setBounds (0, menuBarHeight, w, toolBarHeight);

    if (codeEditorComponent != nullptr)
        codeEditorComponent->setBounds (0, codeEditorOffset, w, getHeight() - codeEditorOffset);
}

//==============================================================================
StringArray ACCMainComponent::getMenuBarNames()
{
    StringArray names;

    const OwnedArray<MenuBarItem>& items = MenuBarItem::getMenuBarItems();

    for (int i = 0; i < items.size(); ++i)
        names.add (items.getUnchecked (i)->getName());

    return names;
}

PopupMenu ACCMainComponent::getMenuForIndex (const int topLevelMenuIndex,
                                             const String& menuName)
{
    const OwnedArray<MenuBarItem>& items = MenuBarItem::getMenuBarItems();

    for (int i = 0; i < items.size(); ++i)
        if (i == topLevelMenuIndex)
            return items.getUnchecked (i)->createPopupMenu();

    jassertfalse; //Messed up index or missing item!
    return PopupMenu();
}

void ACCMainComponent::menuItemSelected (const int menuItemID,
                                         const int topLevelMenuIndex)
{
    const OwnedArray<MenuBarItem>& items = MenuBarItem::getMenuBarItems();

    for (int i = 0; i < items.size(); ++i)
    {
        if (i == topLevelMenuIndex)
        {
            items.getUnchecked (i)->handleMenuResult (menuItemID);
            break;
        }
    }
}

void ACCMainComponent::menuBarItemsChanged (MenuBarModel* const)
{

}

void ACCMainComponent::menuCommandInvoked (MenuBarModel* const, const ApplicationCommandTarget::InvocationInfo& info)
{

}