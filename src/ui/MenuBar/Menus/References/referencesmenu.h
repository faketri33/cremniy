#ifndef REFERENCESMENU_H
#define REFERENCESMENU_H

#include "ui/MenuBar/basemenu.h"

class AppContext;

class ReferencesMenu : public BaseMenu
{
    Q_OBJECT

public:
    explicit ReferencesMenu(AppContext& context);

};

#endif // REFERENCESMENU_H
