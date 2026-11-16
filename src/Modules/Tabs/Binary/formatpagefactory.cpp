#include "formatpagefactory.h"

// Defined next to each page implementation.
void registerRawPage(FormatPageFactory& factory);
void registerElfPage(FormatPageFactory& factory);
void registerPePage(FormatPageFactory& factory);
void registerMbrPage(FormatPageFactory& factory);

void FormatPageFactory::registerPage(const QString& id, Creator creator) {
    m_creators[id] = std::move(creator);
}

FormatPage* FormatPageFactory::create(const QString& id) const {
    const auto it = m_creators.constFind(id);
    return it != m_creators.cend() ? it.value()() : nullptr;
}

QStringList FormatPageFactory::availablePages() const {
    return m_creators.keys();
}

void registerBuiltinFormatPages(FormatPageFactory& factory) {
    registerRawPage(factory);
    registerElfPage(factory);
    registerPePage(factory);
    registerMbrPage(factory);
}
