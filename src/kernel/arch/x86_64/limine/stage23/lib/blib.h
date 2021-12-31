#ifndef __LIB__BLIB_H__
#define __LIB__BLIB_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <fs/file.h>
#include <lib/part.h>
#if defined (uefi)
#  include <efi.h>
#endif

#if defined (uefi)
extern EFI_SYSTEM_TABLE *gST;
extern EFI_BOOT_SERVICES *gBS;
extern EFI_RUNTIME_SERVICES *gRT;
extern EFI_HANDLE efi_image_handle;
extern EFI_MEMORY_DESCRIPTOR *efi_mmap;
extern UINTN efi_mmap_size, efi_desc_size, efi_desc_ver;

extern bool efi_boot_services_exited;
bool efi_exit_boot_services(void);
#endif

extern struct volume *boot_volume;

#if defined (bios)
extern bool stage3_loaded;
#endif

extern bool verbose;

bool parse_resolution(int *width, int *height, int *bpp, const char *buf);

uint64_t sqrt(uint64_t a_nInput);

int digit_to_int(char c);
uint8_t bcd_to_int(uint8_t val);

__attribute__((noreturn)) void panic(const char *fmt, ...);

int pit_sleep_and_quit_on_keypress(int seconds);

uint64_t strtoui(const char *s, const char **end, int base);

#define DIV_ROUNDUP(a, b) (((a) + ((b) - 1)) / (b))

#define ALIGN_UP(x, a) ({ \
    typeof(x) value = x; \
    typeof(a) align = a; \
    value = DIV_ROUNDUP(value, align) * align; \
    value; \
})

#define ALIGN_DOWN(x, a) ({ \
    typeof(x) value = x; \
    typeof(a) align = a; \
    value = (value / align) * align; \
    value; \
})

#define SIZEOF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

typedef char symbol[];

#if defined (uefi)
__attribute__((noreturn)) void do_32(void *fnptr, int args, ...);
#endif

#endif
