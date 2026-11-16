#include "buildmenu.h"
#include "app/IDEWindow/idewindow.h"

BuildMenu::BuildMenu() : BaseMenu(tr("Build")) {
    m_build = new QAction(tr("Build"), this);
    m_openBuildConfigurator = new QAction(tr("Configurate"), this);

    this->addAction(m_build);
    this->addSeparator();
    this->addAction(m_openBuildConfigurator);
}

void BuildMenu::setupConnections(IDEWindow *ideWind) {
    connect(m_build, &QAction::triggered, ideWind, &IDEWindow::on_Build);
    connect(m_openBuildConfigurator, &QAction::triggered, ideWind, &IDEWindow::on_openBuildConfigurate);
}