#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include <Allocation.h>

void *
allocate_pages(UINTN n, EFI_MEMORY_TYPE type) {
    EFI_STATUS status;
    EFI_PHYSICAL_ADDRESS memory;

    if(n == 0) return NULL;

    status = gBS->AllocatePages(AllocateAnyPages, type, n, &memory);
    if(EFI_ERROR(status)) {
        AsciiPrint("AllocatePages: %r\n", status);
        return NULL;
    }

    return (void *)memory;
}

void *
allocate_pool(UINTN size, EFI_MEMORY_TYPE type) {
    EFI_STATUS status;
    void *memory;

    if(size == 0) return NULL;

    status = gBS->AllocatePool(type, size, &memory);
    if(EFI_ERROR(status)) {
        AsciiPrint("AllocatePages: %r\n", status);
        return NULL;
    }

    return memory;
}

void *
allocate_zero_pool(UINTN size, EFI_MEMORY_TYPE type) {
    void *memory= allocate_pool(size, type);

    if(memory) ZeroMem(memory, size);

    return memory;
}