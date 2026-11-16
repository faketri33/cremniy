#include "menubarbuilder.h"
#include "app/AppContext.h"
#include "menufactory.h"

MenuBarBuilder::MenuBarBuilder(QMenuBar* mBar, IDEWindow *ideWind) :
    m_menuBar(mBar)
{
    const MenuFactory& menuFactory = ideWind->appContext().menuFactory();
    qDebug() << menuFactory.availableMenus();
    for (const QString& menuID : menuFactory.availableMenus()){
        BaseMenu* menu = menuFactory.create(menuID, ideWind->appContext());

        menu->setupConnections(ideWind);
        m_menuBar->addMenu(menu);
    }
}
