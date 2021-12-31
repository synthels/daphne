#include <stdint.h>
#include <stddef.h>
#include <drivers/edid.h>
#include <mm/pmm.h>
#include <lib/blib.h>
#include <lib/libc.h>
#include <lib/print.h>

#if defined (bios)

#include <lib/real.h>

struct edid_info_struct *get_edid_info(void) {
    static struct edid_info_struct *buf = NULL;

    if (buf == NULL)
        buf = conv_mem_alloc(sizeof(struct edid_info_struct));

    struct rm_regs r = {0};

    r.eax = 0x4f15;
    r.ebx = 0x0001;
    r.edi = (uint32_t)rm_off(buf);
    r.ds  = (uint32_t)rm_seg(buf);
    r.es  = r.ds;
    rm_int(0x10, &r, &r);

    if ((r.eax & 0x00ff) != 0x4f)
        goto fail;
    if ((r.eax & 0xff00) != 0)
        goto fail;

    for (size_t i = 0; i < sizeof(struct edid_info_struct); i++)
        if (((uint8_t *)buf)[i] != 0)
            goto success;

fail:
    printv("edid: Could not fetch EDID data.\n");
    return NULL;

success:
    printv("edid: Success.\n");
    return buf;
}

#endif

#if defined (uefi)

#include <efi.h>

struct edid_info_struct *get_edid_info(void) {
    struct edid_info_struct *buf = ext_mem_alloc(sizeof(struct edid_info_struct));

    EFI_STATUS status;

    EFI_HANDLE *handles = NULL;
    UINTN handles_size = 0;
    EFI_GUID gop_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

    status = uefi_call_wrapper(gBS->LocateHandle, 5,
        ByProtocol, &gop_guid, NULL, &handles_size, handles);

    if (status && status != EFI_BUFFER_TOO_SMALL)
        goto fail;

    handles = ext_mem_alloc(handles_size);

    status = uefi_call_wrapper(gBS->LocateHandle, 5,
        ByProtocol, &gop_guid, NULL, &handles_size, handles);

    if (status)
        goto fail;

    EFI_EDID_ACTIVE_PROTOCOL *edid = NULL;
    EFI_GUID edid_guid = EFI_EDID_ACTIVE_PROTOCOL_GUID;

    status = uefi_call_wrapper(gBS->HandleProtocol, 3,
        handles[0], &edid_guid, &edid);

    if (status)
        goto fail;

    if (edid->SizeOfEdid < sizeof(struct edid_info_struct))
        goto fail;

    memcpy(buf, edid->Edid, sizeof(struct edid_info_struct));

    for (size_t i = 0; i < sizeof(struct edid_info_struct); i++)
        if (((uint8_t *)buf)[i] != 0)
            goto success;

fail:
    printv("edid: Could not fetch EDID data.\n");
    return NULL;

success:
    printv("edid: Success.\n");
    return buf;
}

#endif
