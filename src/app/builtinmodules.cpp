#include "builtinmodules.h"

class ModuleManager;

// Each module defines its own registration function next to its
// implementation; they are listed here once, explicitly.
void registerAsciiCharsRef(ModuleManager&);
void registerKeyboardScancodesRef(ModuleManager&);
void registerBinaryTab(ModuleManager&);
void registerCodeEditorTab(ModuleManager&);
void registerDisassemblerTab(ModuleManager&);
void registerSTM32PinoutTab(ModuleManager&);
void registerDataConverterDialog(ModuleManager&);
void registerReverseCalculatorDialog(ModuleManager&);
void registerShellcodeGeneratorDialog(ModuleManager&);

void registerBuiltinModules(ModuleManager& manager)
{
    registerAsciiCharsRef(manager);
    registerKeyboardScancodesRef(manager);
    registerBinaryTab(manager);
    registerCodeEditorTab(manager);
    registerDisassemblerTab(manager);
    registerSTM32PinoutTab(manager);
    registerDataConverterDialog(manager);
    registerReverseCalculatorDialog(manager);
    registerShellcodeGeneratorDialog(manager);
}
