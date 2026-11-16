#include "referencesmenu.h"
#include "app/AppContext.h"
#include "core/modules/ModuleManager.h"
#include "core/modules/ReferenceBase.h"

ReferencesMenu::ReferencesMenu(AppContext& context) : BaseMenu(tr("References")) {
    QList<QString> groups = context.moduleManager().getGroups<ReferenceBase>();
    for (QString group : groups){

        const QVector<ModuleDescription<ReferenceBase>>& descRefModules = context.moduleManager().getByGroup<ReferenceBase>(group);

        QMenu* groupMenu;
        if (group == "") groupMenu = this;
        else groupMenu = new QMenu(group);

        for (const ModuleDescription<ReferenceBase>& desc : descRefModules){
            QAction* newAction = new QAction(desc.name(), this);
            groupMenu->addAction(newAction);
            connect(newAction, &QAction::triggered, this, [desc, &context](){
                auto* module = desc.creator(context);
                if (!module)
                    return;
                module->setAttribute(Qt::WA_DeleteOnClose);
                module->showWindow();
            });
        }
        if (group != "") this->addMenu(groupMenu);

    }
}
