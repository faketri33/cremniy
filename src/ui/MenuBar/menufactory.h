#ifndef MENUFACTORY_H
#define MENUFACTORY_H

#include <functional>

#include <QMap>
#include <QStringList>

#include "ui/MenuBar/basemenu.h"

class AppContext;

/// Creates the menu-bar menus. Owned by AppContext; populated explicitly by
/// registerBuiltinMenus(). Menus appear in the order of their ids.
class MenuFactory
{
public:
    using Creator = std::function<BaseMenu*(AppContext&)>;

    void registerMenu(const QString& id, Creator creator);
    BaseMenu* create(const QString& id, AppContext& context) const;
    QStringList availableMenus() const;

private:
    QMap<QString, Creator> m_creators;
};

#endif // MENUFACTORY_H
