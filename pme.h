/*
 * Tool: parsemyelf
 * 
 * C Headerfile: pme.h : Contains Data Structures, Function Declarations and header files required for the tool to function properly.
 *
 * Note: A toy tool written in C language to understand the internal structure of an ELF File.
 * Aim is to parse the ELF File and display the contents in a human readable form.
 * 
 * Author: Adwaith V Gautham
 */



#ifndef _PME_H

#define _PME_H 1

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<string.h>
#include<elf.h>


//Structures required.

//ELF Headers. Depending on the file, memory will be allocated for one of these pointers and their values will be updated. 

Elf64_Ehdr *pme_elf64_hdr;
Elf32_Ehdr *pme_elf32_hdr;


//Section Header String Table Details. 
Elf64_Shdr *pme_shstr_hdr;
char *shstrtab_ptr;
int shstrtab_index;


// Symbol Table - .symtab section details. 
Elf64_Shdr *pme_symtab_hdr;
char *symtab_ptr;
int symtab_index;


// Dynamic Symbol Table - .dynsym section details. 
Elf64_Shdr *pme_dynsym_hdr;
char *dynsym_ptr;
int dynsym_index;

// String Table - .strtab section details. 
Elf64_Shdr *pme_strtab_hdr;
char *strtab_ptr;
int strtab_index;








//pme_err_exit(): Routine which will be called if an error has occured.
void pme_err_exit(const char *errmsg);


//This routine updates the ELF Header data structure.  
void pme_parse_elf_header(char *pme_elf_ptr);


//This routine displays ELF Header details.
void pme_display_elf_header(char *pme_file_ptr);

//This routine parses Program Header Table and displayes it's contents.
void pme_parse_ph_table(char *pme_elf_ptr);

//This routine displays contents of a specified Program Header entry. 
void pme_display_ph_entry(Elf64_Phdr *pme_ph_hdr, int ph_ent_no);

//Routine parses Section Header Table and displays it's contents.
void pme_parse_sh_table(char *pme_elf_ptr);

//Routine displays contents of a specified Section Header Entry.
void pme_display_sh_entry(Elf64_Shdr *pme_sh_hdr);

// Name says it all!
void pme_parse_symbol_table();

void pme_display_symbol(Elf64_Sym *symtab_entry_ptr);

#endif



