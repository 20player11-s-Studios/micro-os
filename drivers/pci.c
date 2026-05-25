#include <drivers/pci.h>
#include <kernel/io.h>
#include <kernel/tty.h>

uint32_t pci_config_read(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

    outl(0xCF8, address);
    return inl(0xCFC);
}

void pci_init(void) {
    tty_printf("Scanning PCI bus...\n");
    for(int bus = 0; bus < 256; bus++) {
        for(int slot = 0; slot < 32; slot++) {
            uint32_t vendor = pci_config_read(bus, slot, 0, 0);
            if((vendor & 0xFFFF) != 0xFFFF) {
                uint32_t device = (vendor >> 16) & 0xFFFF;
                tty_printf("Found device: Vendor=0x%x, Device=0x%x at %d:%d\n", vendor & 0xFFFF, device, bus, slot);
            }
        }
    }
}
