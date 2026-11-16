#include "disassemblersettings.h"

#include "core/settings/appsettings.h"

namespace DisassemblerSettings {

QString keyBackend() { return QStringLiteral("modules/disassembler/backend"); }
QString keyObjdumpPath() { return QStringLiteral("modules/disassembler/objdumpPath"); }
QString keyRadare2Path() { return QStringLiteral("modules/disassembler/radare2Path"); }
QString keyInsnLimitPerSection() { return QStringLiteral("modules/disassembler/insnLimitPerSection"); }
QString keyRadare2AnalysisLevel() { return QStringLiteral("modules/disassembler/radare2/analysisLevel"); }
QString keyAsmSyntax() { return QStringLiteral("modules/disassembler/asmSyntax"); }
QString keyRadare2PreCommands() { return QStringLiteral("modules/disassembler/radare2/preCommands"); }

static void notifyChanged(AppSettings &settings, const QString &key)
{
    emit settings.settingsChanged(key);
}

Backend backend(const AppSettings &settings)
{
    const int v = settings.value(keyBackend(), static_cast<int>(Backend::Objdump)).toInt();
    if (v == static_cast<int>(Backend::Radare2)) return Backend::Radare2;
    return Backend::Objdump;
}

void setBackend(AppSettings &settings, Backend b)
{
    settings.setValue(keyBackend(), static_cast<int>(b));
    notifyChanged(settings, keyBackend());
}

QString objdumpPath(const AppSettings &settings)
{
    return settings.value(keyObjdumpPath(), QString()).toString().trimmed();
}

void setObjdumpPath(AppSettings &settings, const QString &path)
{
    settings.setValue(keyObjdumpPath(), path.trimmed());
    notifyChanged(settings, keyObjdumpPath());
}

QString radare2Path(const AppSettings &settings)
{
    return settings.value(keyRadare2Path(), QString()).toString().trimmed();
}

void setRadare2Path(AppSettings &settings, const QString &path)
{
    settings.setValue(keyRadare2Path(), path.trimmed());
    notifyChanged(settings, keyRadare2Path());
}

int insnLimitPerSection(const AppSettings &settings)
{
    const int v = settings.value(keyInsnLimitPerSection(), 4000).toInt();
    if (v < 50) return 50;
    if (v > 200000) return 200000;
    return v;
}

void setInsnLimitPerSection(AppSettings &settings, int limit)
{
    settings.setValue(keyInsnLimitPerSection(), limit);
    notifyChanged(settings, keyInsnLimitPerSection());
}

AnalysisLevel radare2AnalysisLevel(const AppSettings &settings)
{
    const int v = settings.value(keyRadare2AnalysisLevel(),
                                static_cast<int>(AnalysisLevel::None)).toInt();
    if (v == static_cast<int>(AnalysisLevel::Aaa)) return AnalysisLevel::Aaa;
    if (v == static_cast<int>(AnalysisLevel::Aa)) return AnalysisLevel::Aa;
    return AnalysisLevel::None;
}

void setRadare2AnalysisLevel(AppSettings &settings, AnalysisLevel level)
{
    settings.setValue(keyRadare2AnalysisLevel(), static_cast<int>(level));
    notifyChanged(settings, keyRadare2AnalysisLevel());
}

Syntax asmSyntax(const AppSettings &settings)
{
    const int v = settings.value(keyAsmSyntax(), static_cast<int>(Syntax::Intel)).toInt();
    if (v == static_cast<int>(Syntax::Att)) return Syntax::Att;
    return Syntax::Intel;
}

void setAsmSyntax(AppSettings &settings, Syntax syntax)
{
    settings.setValue(keyAsmSyntax(), static_cast<int>(syntax));
    notifyChanged(settings, keyAsmSyntax());
}

QString radare2PreCommands(const AppSettings &settings)
{
    return settings.value(keyRadare2PreCommands(), QString()).toString().trimmed();
}

void setRadare2PreCommands(AppSettings &settings, const QString &cmds)
{
    settings.setValue(keyRadare2PreCommands(), cmds.trimmed());
    notifyChanged(settings, keyRadare2PreCommands());
}

Snapshot snapshot(const AppSettings &settings)
{
    Snapshot s;
    s.backend = backend(settings);
    s.objdumpPath = objdumpPath(settings);
    s.radare2Path = radare2Path(settings);
    s.insnLimitPerSection = insnLimitPerSection(settings);
    s.radare2AnalysisLevel = radare2AnalysisLevel(settings);
    s.asmSyntax = asmSyntax(settings);
    s.radare2PreCommands = radare2PreCommands(settings);
    return s;
}

} // namespace DisassemblerSettings