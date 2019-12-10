
#include <efi/efi.h>
#include <efi/efilib.h>

EFI_STATUS
		EFIAPI
efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
InitializeLib(ImageHandle, SystemTable);
UINTN Index;
EFI_INPUT_KEY Key;
BOOLEAN exit;
EFI_STATUS err;
exit = FALSE;
uefi_call_wrapper(ST->ConOut->OutputString, 2, ST->ConOut, L"Hello From the Kernel!");

while(!exit) {
uefi_call_wrapper(BS->WaitForEvent, 3, 1, &ST->ConIn->WaitForKey, &Index);
err = uefi_call_wrapper(ST->ConIn->ReadKeyStroke, 2, ST->ConIn, &Key);
if(EFI_ERROR(err)) {
continue;
}
switch(Key.ScanCode) {
case SCAN_ESC:
exit = TRUE;
break;
}
}

return EFI_SUCCESS;
}
