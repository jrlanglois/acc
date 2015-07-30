#ifndef ACC_MAIN_COMPONENT_H
#define ACC_MAIN_COMPONENT_H

#include "ACCMessageListComponent.h"

class ACCMainComponent : public Component,
                         private MenuBarModel,
                         private MenuBarModel::Listener
{
public:
    ACCMainComponent();

    //==============================================================================
    Result setFile (const File& file);

    //==============================================================================
    /** @internal */
    void resized() override;
    /** @internal */
    StringArray getMenuBarNames() override;
    /** @internal */
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    /** @internal */
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    /** @internal */
    void menuBarItemsChanged (MenuBarModel* menuBarModel) override;
    /** @internal */
    void menuCommandInvoked (MenuBarModel* menuBarModel, const ApplicationCommandTarget::InvocationInfo& info) override;

private:
    //==============================================================================
    MenuBarComponent menuBarComponent;
    Toolbar toolbar;

    CodeDocument codeDocument;

    StretchableLayoutManager layoutManager;

    ScopedPointer<ACCCodeEditorComponent> codeEditorComponent;
    ScopedPointer<StretchableLayoutResizerBar> bar;

    MessageListComponent messageListComponent;
    ConsoleComponent consoleComponent;

    class VerticalLayout;
    ScopedPointer<VerticalLayout> verticalLayout;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ACCMainComponent)
};

#endif //ACC_MAIN_COMPONENT_H