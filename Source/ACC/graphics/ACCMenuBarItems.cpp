//==============================================================================
class DefaultMenuBarItemHandler : public DeletedAtShutdown
{
public:
    DefaultMenuBarItemHandler()
    {
    }

    void setupDefaultItemsIfNecessary();

    OwnedArray<MenuBarItem> menuBarItems;

    juce_DeclareSingleton_SingleThreaded_Minimal (DefaultMenuBarItemHandler, true)

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DefaultMenuBarItemHandler)
};

juce_ImplementSingleton_SingleThreaded (DefaultMenuBarItemHandler)

//==============================================================================
MenuBarItem::MenuBarItem (const String& untranslatedName) :
    name (untranslatedName)
{
}

MenuBarItem::~MenuBarItem()
{
}

const OwnedArray<MenuBarItem>& MenuBarItem::getMenuBarItems()
{
    DefaultMenuBarItemHandler* handler = DefaultMenuBarItemHandler::getInstance();

    handler->setupDefaultItemsIfNecessary();

    return handler->menuBarItems;
}

PopupMenu MenuBarItem::createPopupMenuWithItems (const StringArray& items)
{
    PopupMenu popupMenu;

    for (int i = 0; i < items.size(); ++i)
    {
        const int nextId = i + 1;

        const String& s = items.strings.getReference (i);

        if (s == "-")
            popupMenu.addSeparator();
        else
            popupMenu.addItem (nextId, TRANS (s));
    }

    return popupMenu;
}

//==============================================================================
FileMenuBarItem::FileMenuBarItem() :
    MenuBarItem (NEEDS_TRANS ("File"))
{
}

int FileMenuBarItem::getId() const noexcept
{
    return 1;
}

PopupMenu FileMenuBarItem::createPopupMenu()
{
    static const char* const items[] =
    {
        NEEDS_TRANS("New"),
        NEEDS_TRANS("Open"),
        "-",
        NEEDS_TRANS("Save"),
        "-",
        NEEDS_TRANS("Exit"),
        nullptr
    };

    return createPopupMenuWithItems (StringArray (items));
}

void FileMenuBarItem::handleMenuResult (const int id)
{

}

//==============================================================================
EditMenuBarItem::EditMenuBarItem() :
    MenuBarItem (NEEDS_TRANS ("Edit"))
{
}

int EditMenuBarItem::getId() const noexcept
{
    return 100;
}

PopupMenu EditMenuBarItem::createPopupMenu()
{
    static const char* const items[] =
    {
        NEEDS_TRANS("Undo"),
        NEEDS_TRANS("Redo"),
        "-",
        NEEDS_TRANS("Cut"),
        NEEDS_TRANS("Copy"),
        NEEDS_TRANS("Paste"),
        NEEDS_TRANS("Delete"),
        "-",
        NEEDS_TRANS("Select All"),
        nullptr
    };

    return createPopupMenuWithItems (StringArray (items));
}

void EditMenuBarItem::handleMenuResult (const int id)
{

}

//==============================================================================
ViewMenuBarItem::ViewMenuBarItem() :
    MenuBarItem (NEEDS_TRANS ("View"))
{
}

int ViewMenuBarItem::getId() const noexcept
{
    return 200;
}

PopupMenu ViewMenuBarItem::createPopupMenu()
{
    static const char* const items[] =
    {
        NEEDS_TRANS("Error List"),
        NEEDS_TRANS("Output"),
        nullptr
    };

    return createPopupMenuWithItems (StringArray (items));
}

void ViewMenuBarItem::handleMenuResult (const int id)
{

}

//==============================================================================
BuildMenuBarItem::BuildMenuBarItem() :
    MenuBarItem (NEEDS_TRANS ("Build"))
{
}

int BuildMenuBarItem::getId() const noexcept
{
    return 300;
}

PopupMenu BuildMenuBarItem::createPopupMenu()
{
    static const char* const items[] =
    {
        NEEDS_TRANS("Build Project"),
        nullptr
    };

    return createPopupMenuWithItems (StringArray (items));
}

void BuildMenuBarItem::handleMenuResult (const int id)
{

}

//==============================================================================
ToolsMenuBarItem::ToolsMenuBarItem() :
    MenuBarItem (NEEDS_TRANS ("Tools"))
{
}

int ToolsMenuBarItem::getId() const noexcept
{
    return 400;
}

PopupMenu ToolsMenuBarItem::createPopupMenu()
{
    static const char* const items[] =
    {
        NEEDS_TRANS("Convert Tabs to Spaces"),
        NEEDS_TRANS("Trim Whitespace"),
        "-",
        NEEDS_TRANS("Change Theme"),
        NEEDS_TRANS("Edit Current Theme"),
        "-",
        NEEDS_TRANS("Options"),
        nullptr
    };

    return createPopupMenuWithItems (StringArray (items));
}

void ToolsMenuBarItem::handleMenuResult (const int id)
{

}

//==============================================================================
HelpMenuBarItem::HelpMenuBarItem() :
    MenuBarItem (NEEDS_TRANS ("Help"))
{
}

int HelpMenuBarItem::getId() const noexcept
{
    return 500;
}

PopupMenu HelpMenuBarItem::createPopupMenu()
{
    static const char* const items[] =
    {
        NEEDS_TRANS("Undo"),
        NEEDS_TRANS("Redo"),
        "-",
        NEEDS_TRANS("Cut"),
        NEEDS_TRANS("Copy"),
        NEEDS_TRANS("Paste"),
        NEEDS_TRANS("Delete"),
        "-",
        NEEDS_TRANS("Select All"),
        nullptr
    };

    return createPopupMenuWithItems (StringArray (items));
}

void HelpMenuBarItem::handleMenuResult (const int id)
{

}

//==============================================================================
void DefaultMenuBarItemHandler::setupDefaultItemsIfNecessary()
{
    if (menuBarItems.size() <= 0)
    {
        menuBarItems.add (new FileMenuBarItem());
        menuBarItems.add (new EditMenuBarItem());
        menuBarItems.add (new ViewMenuBarItem());
        menuBarItems.add (new BuildMenuBarItem());
        menuBarItems.add (new ToolsMenuBarItem());
        menuBarItems.add (new HelpMenuBarItem());
    }
}