#include "libc/stdint.h"

// GDT entry structure
struct gdt_entry {
    uint16_t limit_low;  // Lower 16 bits of the limit
    uint16_t base_low;   // Lower 16 bits of the base
    uint8_t base_middle; // Next 8 bits of the base
    uint8_t access;      // Access flags
    uint8_t granularity; // Granularity and limit
    uint8_t base_high;   // Last 8 bits of the base
} __attribute__((packed));

// GDT pointer structure
struct gdt_ptr {
    uint16_t limit; // Size of the GDT
    uint32_t base;  // Address of the first GDT entry
} __attribute__((packed));

// Declare GDT and GDT pointer
struct gdt_entry gdt[3];
struct gdt_ptr gdtp;

// Function to set a GDT entry
void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[index].base_low = base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = limit & 0xFFFF;
    gdt[index].granularity = (limit >> 16) & 0x0F;

    gdt[index].granularity |= granularity & 0xF0;
    gdt[index].access = access;
}

// Assembly function to load the GDT
extern void gdt_flush(uint32_t);

// Initialize the GDT
void gdt_init() {
    gdtp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdtp.base = (uint32_t)&gdt;

    // NULL descriptor
    gdt_set_entry(0, 0, 0, 0, 0);

    // Code segment descriptor
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Data segment descriptor
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Load the GDT
    gdt_flush((uint32_t)&gdtp);
}