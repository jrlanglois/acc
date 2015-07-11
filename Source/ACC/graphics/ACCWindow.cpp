ACCWindow::ACCWindow() :
    DocumentWindow (ProjectInfo::projectName, Colours::lightgrey, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);

    setContentOwned (new ACCMainComponent(), true);
    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}

void ACCWindow::closeButtonPressed()
{
    JUCEApplication::quit();
}