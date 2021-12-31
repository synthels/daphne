#include <stdint.h>
#include <stddef.h>
#include <lib/readline.h>
#include <lib/libc.h>
#include <lib/blib.h>
#include <lib/term.h>
#if defined (bios)
#  include <lib/real.h>
#elif defined (uefi)
#  include <efi.h>
#endif

int getchar_internal(uint8_t scancode, uint8_t ascii) {
    switch (scancode) {
#if defined (bios)
        case 0x44:
            return GETCHAR_F10;
        case 0x4b:
            return GETCHAR_CURSOR_LEFT;
        case 0x4d:
            return GETCHAR_CURSOR_RIGHT;
        case 0x48:
            return GETCHAR_CURSOR_UP;
        case 0x50:
            return GETCHAR_CURSOR_DOWN;
        case 0x53:
            return GETCHAR_DELETE;
        case 0x4f:
            return GETCHAR_END;
        case 0x47:
            return GETCHAR_HOME;
        case 0x49:
            return GETCHAR_PGUP;
        case 0x51:
            return GETCHAR_PGDOWN;
        case 0x01:
            return GETCHAR_ESCAPE;
#elif defined (uefi)
        case SCAN_F10:
            return GETCHAR_F10;
        case SCAN_LEFT:
            return GETCHAR_CURSOR_LEFT;
        case SCAN_RIGHT:
            return GETCHAR_CURSOR_RIGHT;
        case SCAN_UP:
            return GETCHAR_CURSOR_UP;
        case SCAN_DOWN:
            return GETCHAR_CURSOR_DOWN;
        case SCAN_DELETE:
            return GETCHAR_DELETE;
        case SCAN_END:
            return GETCHAR_END;
        case SCAN_HOME:
            return GETCHAR_HOME;
        case SCAN_PAGE_UP:
            return GETCHAR_PGUP;
        case SCAN_PAGE_DOWN:
            return GETCHAR_PGDOWN;
        case SCAN_ESC:
            return GETCHAR_ESCAPE;
#endif
    }
    switch (ascii) {
        case '\r':
            return '\n';
        case '\b':
            return '\b';
    }
    // Guard against non-printable values
    if (ascii < 0x20 || ascii > 0x7e) {
        return -1;
    }
    return ascii;
}

#if defined (bios)
int getchar(void) {
again:;
    struct rm_regs r = {0};
    rm_int(0x16, &r, &r);
    int ret = getchar_internal((r.eax >> 8) & 0xff, r.eax);
    if (ret == -1)
        goto again;
    return ret;
}

int _pit_sleep_and_quit_on_keypress(uint32_t ticks);

int pit_sleep_and_quit_on_keypress(int seconds) {
    return _pit_sleep_and_quit_on_keypress(seconds * 18);
}
#endif

#if defined (uefi)
int getchar(void) {
again:;
    EFI_INPUT_KEY key = {0};

    UINTN which;

    uefi_call_wrapper(
        gBS->WaitForEvent, 3, 1, (EFI_EVENT[]){ gST->ConIn->WaitForKey }, &which);

    uefi_call_wrapper(gST->ConIn->ReadKeyStroke, 2, gST->ConIn, &key);

    int ret = getchar_internal(key.ScanCode, key.UnicodeChar);

    if (ret == -1)
        goto again;

    return ret;
}

int pit_sleep_and_quit_on_keypress(int seconds) {
    EFI_INPUT_KEY key = {0};

    UINTN which;

    EFI_EVENT events[2];

    events[0] = gST->ConIn->WaitForKey;

    uefi_call_wrapper(
        gBS->CreateEvent, 5, EVT_TIMER, TPL_CALLBACK, NULL, NULL, &events[1]);

    uefi_call_wrapper(
        gBS->SetTimer, 3, events[1], TimerRelative, 10000000 * seconds);

again:
    uefi_call_wrapper(gBS->WaitForEvent, 3, 2, events, &which);

    if (which == 1) {
        return 0;
    }

    uefi_call_wrapper(gST->ConIn->ReadKeyStroke, 2, gST->ConIn, &key);

    int ret = getchar_internal(key.ScanCode, key.UnicodeChar);

    if (ret == -1)
        goto again;

    return ret;
}
#endif

static void reprint_string(int x, int y, const char *s) {
    int orig_x, orig_y;
    disable_cursor();
    get_cursor_pos(&orig_x, &orig_y);
    set_cursor_pos(x, y);
    term_write(s, strlen(s));
    set_cursor_pos(orig_x, orig_y);
    enable_cursor();
}

static void cursor_back(void) {
    int x, y;
    get_cursor_pos(&x, &y);
    if (x) {
        x--;
    } else if (y) {
        y--;
        x = term_cols - 1;
    }
    set_cursor_pos(x, y);
}

static void cursor_fwd(void) {
    int x, y;
    get_cursor_pos(&x, &y);
    if (x < term_cols - 1) {
        x++;
    } else if (y < term_rows - 1) {
        y++;
        x = 0;
    }
    set_cursor_pos(x, y);
}

void readline(const char *orig_str, char *buf, size_t limit) {
    size_t orig_str_len = strlen(orig_str);
    memmove(buf, orig_str, orig_str_len);
    buf[orig_str_len] = 0;

    int orig_x, orig_y;
    get_cursor_pos(&orig_x, &orig_y);

    term_write(orig_str, orig_str_len);

    for (size_t i = orig_str_len; ; ) {
        int c = getchar();
        switch (c) {
            case GETCHAR_CURSOR_LEFT:
                if (i) {
                    i--;
                    cursor_back();
                }
                continue;
            case GETCHAR_CURSOR_RIGHT:
                if (i < strlen(buf)) {
                    i++;
                    cursor_fwd();
                }
                continue;
            case '\b':
                if (i) {
                    i--;
                    cursor_back();
            case GETCHAR_DELETE:;
                    size_t j;
                    for (j = i; ; j++) {
                        buf[j] = buf[j+1];
                        if (!buf[j]) {
                            buf[j] = ' ';
                            break;
                        }
                    }
                    reprint_string(orig_x, orig_y, buf);
                    buf[j] = 0;
                }
                continue;
            case '\n':
                term_write("\n", 1);
                return;
            default:
                if (strlen(buf) < limit - 1) {
                    for (size_t j = strlen(buf); ; j--) {
                        buf[j+1] = buf[j];
                        if (j == i)
                            break;
                    }
                    buf[i] = c;
                    i++;
                    cursor_fwd();
                    reprint_string(orig_x, orig_y, buf);
                }
        }
    }
}
