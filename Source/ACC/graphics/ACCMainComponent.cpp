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

    bar = new StretchableLayoutResizerBar (&layoutManager, 1, false);

    layoutManager.setItemLayout (0, -0.1, -0.8, -0.6);
    layoutManager.setItemLayout (1, 5.0, 5.0, 5.0);
    layoutManager.setItemLayout (2, -0.1, -0.8, -0.3);

    menuBarComponent.setModel (this);

    addAndMakeVisible (&menuBarComponent);
    addAndMakeVisible (&toolbar);
    addAndMakeVisible (codeEditorComponent);
    addAndMakeVisible (bar);
    addAndMakeVisible (&messageListComponent);

    String path = File::getSpecialLocation (File::currentApplicationFile)
                        .getFullPathName()
                        .upToFirstOccurrenceOf ("jrl_acc", true, true)
                  + "/Source/UnitTests/AllTests.acs";

    setFile (File (path));

    setSize (1024, 768);
}

Result ACCMainComponent::setFile (const File& file)
{
    const Result result = acc::ScriptParser::isACCSourceFile (file);

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
        leftoverOffset = menuBarHeight + toolBarHeight
    };

    Rectangle<int> r (getLocalBounds().withPosition (1, 1).withWidth (getWidth() - 2));

    menuBarComponent.setBounds (r.withHeight (menuBarHeight));
    toolbar.setBounds (r.withHeight (toolBarHeight).withY (menuBarComponent.getBottom() + 1));

    Array<Component*> comps;
    comps.add (codeEditorComponent);
    comps.add (bar);
    comps.add (&messageListComponent);

    const int b = toolbar.getBottom() + 1;
    r = r.withHeight (r.getHeight() - b)
         .withY (b);

    layoutManager.layOutComponents (comps.getRawDataPointer(), comps.size(),
                                    r.getX(), r.getY(), r.getWidth(), r.getHeight(),
                                    true, true);
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