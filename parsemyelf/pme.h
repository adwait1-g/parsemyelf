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
#include<capstone/capstone.h>

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

// .text Section details
Elf64_Shdr *pme_text_hdr;
char *text_ptr;
int text_index;


// .rodata Section details
Elf64_Shdr *pme_rodata_hdr;
char *rodata_ptr;
int rodata_index;


// .strtab Section details
Elf64_Shdr *pme_strtab_hdr;
char *strtab_ptr;
int strtab_index;

// .data Section details.
Elf64_Shdr *pme_data_hdr;
char *data_ptr;
int data_index;

// .bss Section details. 
Elf64_Shdr *pme_bss_hdr;
char *bss_ptr;
int bss_index;

// .comment Section details
Elf64_Shdr *pme_comment_hdr;
char *comment_ptr;
int comment_index;

// .interp Section details
Elf64_Shdr *pme_interp_hdr;
char *interp_ptr;
int interp_index;

// .note.ABI-tag Section details
Elf64_Shdr *pme_noteabi_hdr;
char *noteabi_ptr;
int noteabi_index;

// .note.gnu.build-id Section details
Elf64_Shdr *pme_buildid_hdr;
char *buildid_ptr;
int buildid_index;

// .gnu.hash Section details
Elf64_Shdr *pme_gnuhash_hdr;
char *gnuhash_ptr;
int gnuhash_index;


//pme_err_exit(): Routine which will be called if an error has occured.
void pme_err_exit(const char *errmsg);

//Init routine
void pme_init();


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

void pme_parse_symbol_table();
void pme_display_symbol(Elf64_Sym *symtab_entry_ptr);

void pme_parse_text_section();
void pme_parse_rodata_section();
void pme_parse_strtab_section();
void pme_parse_data_section();
void pme_parse_bss_section();
void pme_parse_comment_section();
void pme_parse_interp_section();
void pme_parse_noteabi_section();
void pme_parse_buildid_section();
void pme_parse_gnuhash_section();


#endif



