MessageListComponent::MessageListComponent()
{
    TableHeaderComponent& header = getHeader();

    header.addColumn (TRANS("Type"), itemTypeId, 50);
    header.addColumn (TRANS("Description"), itemDescriptionId, 200);
    header.addColumn (TRANS("File"), itemFileId, 100);
    header.addColumn (TRANS("Line"), itemLineNumberId, 40);

    addErrorItem ("Some really lengthy error message.", "C:/", 1);
    addWarningItem ("Some important warning.", "C:/", 50);
    addMessageItem ("An extremely interesting message, not brought to you by our sponsors.", "C:/", 100);

    setModel (this);
}

//==============================================================================
void MessageListComponent::addItem (const ItemType type, const String& desc, const String& file, const int line)
{
    if (desc.isNotEmpty() && file.isNotEmpty())
    {
        items.add (ListItem (type, desc, file, line));
        repaint();
    }
}

void MessageListComponent::addErrorItem (const String& desc, const String& file, const int line)
{
    addItem (errorItem, desc, file, line);
}

void MessageListComponent::addWarningItem (const String& desc, const String& file, const int line)
{
    addItem (warningItem, desc, file, line);
}

void MessageListComponent::addMessageItem (const String& desc, const String& file, const int line)
{
    addItem (messageItem, desc, file, line);
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

//==============================================================================
void MessageListComponent::paintErrorCell (const ListItem& item, Graphics& g,
                                           const int w, const int h)
{
    const float iconSize = jmin ((float) w * 0.9f, (float) h * 0.9f);
    const Rectangle<float> iconRect (iconSize, iconSize);

    Path icon;
    icon.addEllipse (iconRect);

    g.setColour (Colours::darkred);
    g.fillPath (icon);

    const char character = 'X';

    GlyphArrangement ga;
    ga.addFittedText (Font (iconRect.getHeight() * 0.9f, Font::bold),
                      String::charToString ((juce_wchar) (uint8) character),
                      iconRect.getX(), iconRect.getY(),
                      iconRect.getWidth(), iconRect.getHeight(),
                      Justification::centred, false);
    Path glyph;
    ga.createPath (glyph);
    g.setColour (Colours::white);
    g.fillPath (glyph);
}

void MessageListComponent::paintWarningCell (const ListItem& item, Graphics& g,
                                             const int w, const int h)
{
    const float iconSize = jmin ((float) w * 0.9f, (float) h * 0.9f);
    const Rectangle<float> iconRect (iconSize, iconSize);

    Path icon;
    icon.addTriangle (iconRect.getX() + iconRect.getWidth() * 0.5f, iconRect.getY(),
                      iconRect.getRight(), iconRect.getBottom(),
                      iconRect.getX(), iconRect.getBottom());

    g.setColour (Colours::yellow);
    g.fillPath (icon);

    const char character = '!';

    GlyphArrangement ga;
    ga.addFittedText (Font (iconRect.getHeight() * 0.9f, Font::bold),
                      String::charToString ((juce_wchar) (uint8) character),
                      iconRect.getX(), iconRect.getY(),
                      iconRect.getWidth(), iconRect.getHeight(),
                      Justification::centred, false);
    Path glyph;
    ga.createPath (glyph);
    g.setColour (Colours::black);
    g.fillPath (glyph);
}

void MessageListComponent::paintMessageCell (const ListItem& item, Graphics& g,
                                             const int w, const int h)
{
    const float iconSize = jmin ((float) w * 0.9f, (float) h * 0.9f);
    const Rectangle<float> iconRect (iconSize, iconSize);

    Path icon;
    icon.addEllipse (iconRect);

    const char character = 'i';

    GlyphArrangement ga;
    ga.addFittedText (Font (iconRect.getHeight() * 0.9f, Font::bold),
                      String::charToString ((juce_wchar) (uint8) character),
                      iconRect.getX(), iconRect.getY(),
                      iconRect.getWidth(), iconRect.getHeight(),
                      Justification::centred, false);
    ga.createPath (icon);

    icon.setUsingNonZeroWinding (false);
    g.setColour (Colours::blue);
    g.fillPath (icon);
}

void MessageListComponent::paintTextCell (const String& text, Graphics& g,
                                          const int w, const int h)
{
    g.setColour (Colours::black);
    g.setFont (Font (12.0f, Font::plain));
    g.drawText (text, 2, 0, w - 4, h, Justification::centredLeft, false);
    g.setColour (Colours::black.withAlpha (0.2f));
    g.fillRect (w - 1, 0, 1, h);
}

void MessageListComponent::paintCell (Graphics& g, const int rowNumber, const int columnId,
                                      const int width, const int height, const bool)
{
    if (! isPositiveAndBelow (rowNumber, getNumRows()))
        return;

    const ListItem& item = items.getReference (rowNumber);

    switch (columnId)
    {
        case itemTypeId:
        {
            switch (item.type)
            {
                case errorItem:     paintErrorCell (item, g, width, height); break;
                case warningItem:   paintWarningCell (item, g, width, height); break;
                case messageItem:   paintMessageCell (item, g, width, height); break;

                default:
                    jassertfalse; //???
                break;
            }
        }
        break;

        case itemDescriptionId: paintTextCell (item.description, g, width, height); break;
        case itemFileId:        paintTextCell (item.file, g, width, height); break;
        case itemLineNumberId:  paintTextCell (String (item.line), g, width, height); break;

        default:
            jassertfalse; //???
        break;
    }
}