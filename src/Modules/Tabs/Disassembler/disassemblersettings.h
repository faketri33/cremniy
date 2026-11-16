#ifndef DISASSEMBLERSETTINGS_H
#define DISASSEMBLERSETTINGS_H

#include <QString>

class AppSettings;

// Настройки модуля Disassembler.
//
// ВСЁ, что касается настроек этого модуля (ключи, умолчания, типы и
// уведомления об изменении), живёт в САМОМ модуле. Ядро (AppSettings)
// хранит только пары "ключ -> значение" и не знает ни одного из этих
// ключей. Поэтому разработчик может добавить/изменить настройку модуля,
// не трогая core/settings.
//
// Ключи модуля также объявляются фабрике настроек
// (SettingsRegistry::moduleOptions) в disassemblersettingspage.cpp — они
// автоматически попадают в экспорт/импорт INI.
namespace DisassemblerSettings {

enum class Backend {
    Objdump = 0,
    Radare2 = 1,
};

enum class AnalysisLevel {
    None = 0,   // r2 без анализа (быстро)
    Aa   = 1,   // aa (базовый)
    Aaa  = 2,   // aaa (полный)
};

enum class Syntax {
    Intel = 0,
    Att   = 1,
};

QString keyBackend();
QString keyObjdumpPath();
QString keyRadare2Path();
QString keyInsnLimitPerSection();
QString keyRadare2AnalysisLevel();
QString keyAsmSyntax();
QString keyRadare2PreCommands();

Backend backend(const AppSettings &settings);
void setBackend(AppSettings &settings, Backend backend);

QString objdumpPath(const AppSettings &settings);
void setObjdumpPath(AppSettings &settings, const QString &path);

QString radare2Path(const AppSettings &settings);
void setRadare2Path(AppSettings &settings, const QString &path);

int insnLimitPerSection(const AppSettings &settings);
void setInsnLimitPerSection(AppSettings &settings, int limit);

AnalysisLevel radare2AnalysisLevel(const AppSettings &settings);
void setRadare2AnalysisLevel(AppSettings &settings, AnalysisLevel level);

Syntax asmSyntax(const AppSettings &settings);
void setAsmSyntax(AppSettings &settings, Syntax syntax);

QString radare2PreCommands(const AppSettings &settings);
void setRadare2PreCommands(AppSettings &settings, const QString &cmds);

// Plain-value copy of all settings, safe to hand to another thread.
struct Snapshot {
    Backend backend = Backend::Objdump;
    QString objdumpPath;
    QString radare2Path;
    int insnLimitPerSection = 4000;
    AnalysisLevel radare2AnalysisLevel = AnalysisLevel::None;
    Syntax asmSyntax = Syntax::Intel;
    QString radare2PreCommands;
};

Snapshot snapshot(const AppSettings &settings);

} // namespace DisassemblerSettings

#endif // DISASSEMBLERSETTINGS_H