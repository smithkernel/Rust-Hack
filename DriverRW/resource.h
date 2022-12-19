#include <assert.h>
#include <stddef.h>

// NTSTATUS is a data type used by the Windows operating system
// to represent the status of a function call
typedef int NTSTATUS;

#define STATUS_SUCCESS 0
#define STATUS_INVALID_PARAMETER 0xC000000DL
#define STATUS_NOT_FOUND 0xC0000225L

// SystemModuleInformation is a data structure used by the
// Windows operating system to store information about a module
// in the system.
typedef struct _SystemModuleInformation {
  // Other fields omitted for brevity
} SystemModuleInformation;

NTSTATUS KernelmodeWindowsruntime(
  const SystemModuleInformation *system_module_info,
  const void *pattern, size_t len,
  void *wildcard,
  void **pp_found) {
  assert(pp_found != NULL && pattern != NULL && system_module_info != NULL);
  if (pp_found == NULL || pattern == NULL || system_module_info == NULL) {
    return STATUS_INVALID_PARAMETER;
  }

  // Calculate the size of the memory region to search
  size_t size = system_module_info->Size;

  // Get a pointer to the start of the memory region
  const void *base = system_module_info->Base;

  for (size_t i = 0; i < size - len; i++) {
    bool found = true;
    for (size_t j = 0; j < len; j++) {
      if (wildcard != NULL && *(const char*)wildcard == pattern[j]) {
        continue;
      }
      if (pattern[j] != *((const char*)base + i + j)) {
        found = false;
        break;
      }
    }
    if (found) {
      *pp_found = (char*)base + i;
      return STATUS_SUCCESS;
    }
  }
  return STATUS_NOT_FOUND;
}
