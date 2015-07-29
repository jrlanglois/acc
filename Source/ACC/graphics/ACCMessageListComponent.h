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
    void addMessageItem (const String& description, const String& file, int line);

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
    enum HeaderColumnIds
    {
        itemTypeId,
        itemDescriptionId,
        itemFileId,
        itemLineNumberId
    };

    //==============================================================================
    enum ItemType
    {
        errorItem,
        warningItem,
        messageItem
    };

    struct ListItem
    {
        ListItem (ItemType itemType, const String& desc, const String& f, int lineNumber) :
            type (itemType),
            description (desc),
            file (f),
            line (lineNumber)
        {
        }

        ListItem (const ListItem& other) :
            type (other.type),
            description (other.description),
            file (other.file),
            line (other.line)
        {
        }

        ListItem& operator= (const ListItem& other)
        {
            if (this != &other)
            {
                type = other.type;
                description = other.description;
                file = other.file;
                line = other.line;
            }

            return *this;
        }

        ItemType type;
        String description, file;
        int line;
    };

    Array<ListItem> items;

    //==============================================================================
    void addItem (ItemType type, const String& description, const String& file, int line);

    static void paintTextCell (const String& text, Graphics& g, int w, int h);
    static void paintErrorCell (Graphics& g, const Rectangle<float>& iconRect);
    static void paintWarningCell (Graphics& g, const Rectangle<float>& iconRect);
    static void paintMessageCell (Graphics& g, const Rectangle<float>& iconRect);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MessageListComponent)
};

#endif //ACC_MESSAGE_LIST_COMPONENT_H