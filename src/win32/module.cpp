#include "win32/module.h"
#include <utility>

namespace meh {

Module Module::FromOwnedModule(HMODULE handle) {
  return Module(UniqueModuleHandle(handle, &::FreeLibrary));
}

Module Module::FromUnownedModule(HMODULE handle) {
  return Module(UniqueModuleHandle(handle, &Module::NopFreeLibrary));
}

Module::Module(UniqueModuleHandle handle) : m_handle(std::move(handle)) {}

BOOL __stdcall Module::NopFreeLibrary(HMODULE handle) { return TRUE; }

} // namespace meh