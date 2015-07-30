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
namespace LayoutHelpers
{
    static const double barSize = 5.0;

    static void layoutResizerBar (StretchableLayoutManager& layoutManager, int index)
    {
        layoutManager.setItemLayout (index, barSize, barSize, barSize);
    }
}

//==============================================================================
class ACCMainComponent::VerticalLayout : public Component
{
public:
    VerticalLayout() :
        hasBeenLayedOut (false)
    {
    }

    void addComponent (Component& component)
    {
        if (! hasBeenLayedOut)
        {
            jassert (! comps.contains (&component));

            comps.add (&component);
            addAndMakeVisible (&component);
        }
    }

    void addBar()
    {
        if (! hasBeenLayedOut)
        {
            const int index = comps.size() + 1;

            StretchableLayoutResizerBar* bar = new StretchableLayoutResizerBar (&layoutManager, index, true);

            comps.add (bars.add (bar));
            addAndMakeVisible (bar);
        }
    }

    void clear()
    {
        comps.clear();
        bars.clear();
        hasBeenLayedOut = false;
    }

    void resized() override
    {
        layout();

        const Rectangle<int> r (getLocalBounds());

        layoutManager.layOutComponents (comps.getRawDataPointer(), comps.size(),
                                        r.getX(), r.getY(), r.getWidth(), r.getHeight(),
                                        false, true);
    }

private:
    Array<Component*> comps;
    OwnedArray<StretchableLayoutResizerBar> bars;
    StretchableLayoutManager layoutManager;

    bool hasBeenLayedOut;

    void layout()
    {
        if (! hasBeenLayedOut)
        {
            const int numComps = comps.size();
            const int numBars = bars.size();

            double maxSize = (double) getWidth() - (double) (numBars * LayoutHelpers::barSize);
            maxSize = maxSize / (numComps - numBars);
            maxSize = maxSize / getWidth();

            for (int i = 0; i < numComps; ++i)
            {
                if (StretchableLayoutResizerBar* b = dynamic_cast<StretchableLayoutResizerBar*>(comps.getUnchecked (i)))
                    LayoutHelpers::layoutResizerBar (layoutManager, i);
                else
                    layoutManager.setItemLayout (i, -0.1, -maxSize, -0.25);
            }

            hasBeenLayedOut = true;
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VerticalLayout)
};

//==============================================================================
ACCMainComponent::ACCMainComponent() :
    verticalLayout (new VerticalLayout())
{
    codeEditorComponent = new ACCCodeEditorComponent (codeDocument);

    bar = new StretchableLayoutResizerBar (&layoutManager, 1, false);

    verticalLayout->addComponent (messageListComponent);
    verticalLayout->addBar();
    verticalLayout->addComponent (consoleComponent);

    layoutManager.setItemLayout (0, -0.1, -0.8, -0.6);
    LayoutHelpers::layoutResizerBar (layoutManager, 1);
    layoutManager.setItemLayout (2, -0.1, -0.8, -0.3);

    menuBarComponent.setModel (this);

    addAndMakeVisible (&menuBarComponent);
    addAndMakeVisible (&toolbar);
    addAndMakeVisible (codeEditorComponent);
    addAndMakeVisible (bar);
    addAndMakeVisible (verticalLayout);

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
    comps.add (verticalLayout);

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