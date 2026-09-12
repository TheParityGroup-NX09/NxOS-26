
unsigned int ram_format = 1024;
struct multiboot_info
{
    unsigned int flags;
    unsigned int mem_lower;
    unsigned int mem_upper;
};

extern "C" void kmain(unsigned int magic, multiboot_info* mboot)
{
    if (magic != 0x2BADB002){return;} //something went wrong
    if (mboot->flags & 1)
    {
        unsigned int low_ram_kb = mboot->mem_lower;
        unsigned int high_ram_kb = mboot->mem_upper;
        unsigned int total_ram_mb = (low_ram_kb + high_ram_kb) / ram_format;//ram format can be chagned.
    }
    

    
}