#include "menufactory.h"

void MenuFactory::registerMenu(const QString& id, Creator creator) {
    m_creators[id] = std::move(creator);
}

BaseMenu* MenuFactory::create(const QString& id, AppContext& context) const {
    const auto it = m_creators.constFind(id);
    return it != m_creators.cend() ? it.value()(context) : nullptr;
}

QStringList MenuFactory::availableMenus() const {
    return m_creators.keys();
}
