#pragma once
#include "definitions.h"
#define ioctl_allocate_virtual_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x221, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ioctl_copy_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x224, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ioctl_get_module_base CTL_CODE(FILE_DEVICE_UNKNOWN, 0x222, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) 
#define ioctl_protect_virutal_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x223, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;


typedef struct _k_alloc_mem_request {
  ULONG pid;           // The process ID of the process making the request
  ULONG allocation_type; // The type of memory allocation
  ULONG protect;        // The protection type for the allocated memory
  ULONGLONG addr;       // The starting address of the allocated memory
  SIZE_T size;          // The size of the memory allocation
} k_alloc_mem_request, *pk_alloc_mem_request;

typedef struct _k_get_base_module_request {
  ULONG pid;           // The process ID of the process making the request
  ULONGLONG handle;     // The handle of the base module
  WCHAR name[260];      // The name of the base module
} k_get_base_module_request, *pk_get_base_module_request;

typedef struct _k_protect_mem_request {
  ULONG pid;           // The process ID of the process making the request
  ULONG protect;        // The protection type for the memory
  ULONGLONG addr;       // The starting address of the memory
  SIZE_T size;          // The size of the memory
} k_protect_mem_request, *pk_protect_mem_request;

typedef struct _k_rw_request {
  uint32_t src_pid;     // The process ID of the source process
  uint32_t dst_pid;     // The process ID of the destination process
  uint64_t src_addr;    // The starting address of the source memory
  uint64_t dst_addr;    // The starting address of the destination memory
  SIZE_T size;          // The size of the memory being read/written
} k_rw_request, *pk_rw_request;
