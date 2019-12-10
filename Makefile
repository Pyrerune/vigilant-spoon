all:
	gcc main.c -c -fno-stack-protector -fpic -fshort-wchar -mno-red-zone -DEFI_FUNCTION_WRAPPER -I /usr/include/efi -I /usr/include/efi/x86_64 -o main.o
	ld main.o /usr/lib/crt0-efi-x86_64.o -nostdlib -znocombreloc -T /usr/lib/elf_x86_64_efi.lds -shared -Bsymbolic -L /usr/lib -l:libgnuefi.a -l:libefi.a -o main.so
	objcopy -j .text                          -j .sdata -j .data                          -j .dynamic                       -j .dynsym -j .rel                           -j .rela -j .reloc                         --target=efi-app-x86_64           main.so main.efi


run:
	uefi-run -b /usr/share/ovmf/x64/OVMF_CODE.fd -q /usr/bin/qemu-system-x86_64 main.efi	