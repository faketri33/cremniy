#ifndef TOOLSMENU_H
#define TOOLSMENU_H

#include "core/modules/ModuleManager.h"
#include "ui/MenuBar/basemenu.h"

#include <QList>

class AppContext;
class IDEWindow;
class TabBase;
class QAction;

class ToolsMenu : public BaseMenu
{
    Q_OBJECT
private:

public:
    explicit ToolsMenu(AppContext& context);
    void setupConnections(IDEWindow* ideWind) override;

signals:
    void openTabModule(ModuleDescription<TabBase> desc);
};

#endif // TOOLSMENU_H
