MessageListComponent::MessageListComponent()
{
    setModel (this);

    addErrorItem ("desc", "file", 0);
    addWarningItem ("desc", "file", 0);
    addMessageItem ("desc");
}

//==============================================================================
void MessageListComponent::addErrorItem (const String& desc, const String& file, int line)
{
    if (desc.isNotEmpty() && file.isNotEmpty())
    {
        items.add (ListItem (desc, file, line, true));
        repaint();
    }
}

void MessageListComponent::addWarningItem (const String& desc, const String& file, int line)
{
    if (desc.isNotEmpty() && file.isNotEmpty())
    {
        items.add (ListItem (desc, file, line, false));
        repaint();
    }
}

void MessageListComponent::addMessageItem (const String& desc)
{
    if (desc.isNotEmpty())
    {
        items.add (ListItem (desc));
        repaint();
    }
}

void MessageListComponent::clear()
{
    if (items.size() > 0)
    {
        items.clear();
        repaint();
    }
}

//==============================================================================
int MessageListComponent::getNumRows()
{
    return items.size();
}

void MessageListComponent::paintRowBackground (Graphics& g, const int rowNumber,
                                               const int width, const int height,
                                               const bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll (Colour (51, 153, 255));
    else
        g.fillAll (Colour (246, 246, 246));
}

void MessageListComponent::paintCell (Graphics& g, const int rowNumber, const int columnId,
                                      const int width, const int height, const bool)
{
    if (! isPositiveAndBelow (rowNumber, getNumRows()))
        return;

    g.setColour (Colours::black);
    g.setFont (Font (12.0f, Font::plain));

    const ListItem& item = items.getReference (rowNumber);

    String text;

    if (columnId == 0)
        jassertfalse;

    g.drawText (item.description, 2, 0, width - 4, height, Justification::centredLeft, false);
    g.setColour (Colours::black.withAlpha (0.2f));
    g.fillRect (width - 1, 0, 1, height);
}