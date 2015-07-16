ACCWindow::ACCWindow() :
    DocumentWindow (ProjectInfo::projectName, Colours::lightgrey, DocumentWindow::allButtons)
{
    setUsingNativeTitleBar (true);
    setResizable (true, false);

    ComponentBoundsConstrainer* constrainer = new ComponentBoundsConstrainer();
    constrainer->setMinimumSize (500, 500); //Limit minimum window size to something sensible
    setConstrainer (constrainer);

    setContentOwned (new ACCMainComponent(), true);
    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}

void ACCWindow::closeButtonPressed()
{
    JUCEApplication::quit();
}