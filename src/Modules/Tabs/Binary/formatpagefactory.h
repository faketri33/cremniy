#ifndef FORMATPAGEFACTORY_H
#define FORMATPAGEFACTORY_H

#include <functional>

#include <QMap>
#include <QStringList>

#include "formatpage.h"

/// Creates the format pages of the binary tab. Not global: BinaryTab builds
/// its own factory and fills it via registerBuiltinFormatPages(). Pages are
/// listed in the order of their ids.
class FormatPageFactory
{
public:
    using Creator = std::function<FormatPage*()>;

    void registerPage(const QString& id, Creator creator);
    FormatPage* create(const QString& id) const;
    QStringList availablePages() const;

private:
    QMap<QString, Creator> m_creators;
};

/// Registers RAW, ELF, PE and MBR pages.
void registerBuiltinFormatPages(FormatPageFactory& factory);

#endif // FORMATPAGEFACTORY_H
