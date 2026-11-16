#ifndef BASEMENU_H
#define BASEMENU_H

#include <QMenu>

class IDEWindow;

class BaseMenu : public QMenu
{
    Q_OBJECT
public:
    BaseMenu(QString MenuName) { this->setTitle(MenuName); } ;
    virtual void setupConnections(IDEWindow* /*ideWind*/) {}
};

#endif // BASEMENU_H
