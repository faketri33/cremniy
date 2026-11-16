#ifndef MENUBARBUILDER_H
#define MENUBARBUILDER_H

#include <qmenubar.h>

class IDEWindow;

class MenuBarBuilder
{

private:
    QMenuBar* m_menuBar;

public:
    MenuBarBuilder(QMenuBar* mBar, IDEWindow* ideWind);
};

#endif // MENUBARBUILDER_H
