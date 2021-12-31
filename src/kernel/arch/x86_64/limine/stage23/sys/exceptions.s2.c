#include <stdint.h>
#include <lib/blib.h>
#include <lib/trace.h>
#include <lib/print.h>

#if defined (bios)

static const char *exception_names[] = {
    "Division by 0",
    "Debug",
    "NMI",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Device not available",
    "Double fault",
    "???",
    "Invalid TSS",
    "Segment not present",
    "Stack-segment fault",
    "General protection fault",
    "Page fault",
    "???",
    "x87 exception",
    "Alignment check",
    "Machine check",
    "SIMD exception",
    "Virtualisation",
    "???",
    "???",
    "???",
    "???",
    "???",
    "???",
    "???",
    "???",
    "???",
    "Security"
};

void except(uint32_t exception, uint32_t error_code, uint32_t ebp, uint32_t eip) {
    (void)ebp;
    panic("%s at %x. Error code: %x", exception_names[exception], eip, error_code);
}

#endif
