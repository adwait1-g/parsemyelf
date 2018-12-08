# parsemyelf
A toy tool written to understand Internal Structure of ELF . It is written purely in C.

This is how you compile it:

### gcc parsemyelf.c parse_elf_header.c parse_ph_table.c parse_sh_table.c parse_symbol_table.c -o pme

This will give you an executable **pme** and that is the tool. 
