#ifndef ACC_MESSAGE_LIST_COMPONENT_H
#define ACC_MESSAGE_LIST_COMPONENT_H

class MessageListComponent : public TableListBox,
                             private TableListBoxModel
{
public:
    MessageListComponent();

    //==============================================================================
    void addErrorItem (const String& description, const String& file, int line);
    void addWarningItem (const String& description, const String& file, int line);
    void addMessageItem (const String& description);

    void clear();

    //==============================================================================
    /** @internal */
    int getNumRows() override;
    /** @internal */
    void paintRowBackground (Graphics& g, int rowNumber,
                             int width, int height, bool rowIsSelected) override;
    /** @internal */
    void paintCell (Graphics& g, int rowNumber, int columnId,
                    int width, int height, bool rowIsSelected) override;

private:
    //==============================================================================
    class HeaderComponent;

    //==============================================================================
    enum ItemType
    {
        errorItem,
        warningItem,
        messageItem
    };

    struct ListItem
    {
        ListItem (const String& desc, const String& f,
                  int lineNumber, bool isError) :
            itemType (isError ? errorItem : warningItem),
            description (desc),
            file (f),
            line (lineNumber)
        {
        }

        ListItem (const String& desc) :
            itemType (messageItem),
            description (desc),
            line (0)
        {
        }

        ListItem (const ListItem& other) :
            itemType (other.itemType),
            description (other.description),
            file (other.file),
            line (other.line)
        {
        }

        ListItem& operator= (const ListItem& other)
        {
            if (this != &other)
            {
                itemType = other.itemType;
                description = other.description;
                file = other.file;
                line = other.line;
            }

            return *this;
        }

        ItemType itemType;
        String description, file;
        int line;
    };

    Array<ListItem> items;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MessageListComponent)
};

#endif //ACC_MESSAGE_LIST_COMPONENT_H