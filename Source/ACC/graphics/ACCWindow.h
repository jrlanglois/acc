#ifndef ACC_WINDOW_H
#define ACC_WINDOW_H

class ACCWindow : public DocumentWindow
{
public:
    ACCWindow();

    //==============================================================================
    /** @internal */
    void closeButtonPressed() override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ACCWindow)
};

#endif //ACC_WINDOW_H