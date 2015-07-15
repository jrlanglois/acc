#ifndef ACC_MENU_BAR_ITEMS_H
#define ACC_MENU_BAR_ITEMS_H

//==============================================================================
class MenuBarItem
{
public:
    MenuBarItem (const String& untranslatedName);
    virtual ~MenuBarItem();

    String getName() const noexcept { return TRANS (name); }

    static const OwnedArray<MenuBarItem>& getMenuBarItems();

    virtual int getId() const noexcept = 0;
    virtual PopupMenu createPopupMenu() = 0;
    virtual void handleMenuResult (int id) = 0;

protected:
    /** Creates a flat list PopupMenu from a StringArray,
        where the ids start at offset 1.

        @note Items must be untranslated!
              An item who is a '-' (dash) represents a separator.
    */
    static PopupMenu createPopupMenuWithItems (const StringArray& items);

private:
    const String name; //Note: this string is to be untranslated!

    static void createDefaultMenuBarItems();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MenuBarItem)
};

//==============================================================================
class FileMenuBarItem : public MenuBarItem
{
public:
    FileMenuBarItem();

    int getId() const noexcept override;
    PopupMenu createPopupMenu() override;
    void handleMenuResult (int id) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileMenuBarItem)
};

//==============================================================================
class EditMenuBarItem : public MenuBarItem
{
public:
    EditMenuBarItem();

    int getId() const noexcept override;
    PopupMenu createPopupMenu() override;
    void handleMenuResult (int id) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditMenuBarItem)
};

//==============================================================================
class ViewMenuBarItem : public MenuBarItem
{
public:
    ViewMenuBarItem();

    int getId() const noexcept override;
    PopupMenu createPopupMenu() override;
    void handleMenuResult (int id) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViewMenuBarItem)
};

//==============================================================================
class BuildMenuBarItem : public MenuBarItem
{
public:
    BuildMenuBarItem();

    int getId() const noexcept override;
    PopupMenu createPopupMenu() override;
    void handleMenuResult (int id) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BuildMenuBarItem)
};

//==============================================================================
class ToolsMenuBarItem : public MenuBarItem
{
public:
    ToolsMenuBarItem();

    int getId() const noexcept override;
    PopupMenu createPopupMenu() override;
    void handleMenuResult (int id) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToolsMenuBarItem)
};

//==============================================================================
class HelpMenuBarItem : public MenuBarItem
{
public:
    HelpMenuBarItem();

    int getId() const noexcept override;
    PopupMenu createPopupMenu() override;
    void handleMenuResult (int id) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelpMenuBarItem)
};

#endif //ACC_MENU_BAR_ITEMS_H