/*
 * Tool: parsemyelf
 * 
 * C Sourcefile: pme.c :  It contains helper routines. 
 *
 * Note: A toy tool written in C language to understand the internal structure of
 an ELF File.
 * Aim is to parse the ELF File and display the contents in a human readable form
.
 * 
 * Author: Adwaith V Gautham
 */

#include"pme.h"

void pme_err_exit(const char *errmsg) {

        fprintf(stderr, "%s\n", errmsg);
        exit(1);
}


void pme_init(unsigned char *pme_file_ptr) {

        // Populate the pme_elf64_hdr structure. 
        pme_parse_elf_header(pme_file_ptr);


        // Section header String Table!
        pme_shstr_hdr = (Elf64_Shdr *)(pme_file_ptr + pme_elf64_hdr->e_shoff + pme_elf64_hdr->e_shentsize  * pme_elf64_hdr->e_shstrndx);
        shstrtab_ptr = pme_file_ptr + pme_shstr_hdr->sh_offset;
        shstrtab_index = pme_elf64_hdr->e_shstrndx;


        Elf64_Shdr *section_hdr;
        for(int i = 0; i < pme_elf64_hdr->e_shnum; i++) {
                section_hdr = (Elf64_Shdr *)(pme_file_ptr + pme_elf64_hdr->e_shoff + pme_elf64_hdr->e_shentsize * i);

                // Populate details of .symtab
                if(section_hdr->sh_type == SHT_SYMTAB) {
                        symtab_index = i;
                        pme_symtab_hdr = section_hdr;
                        symtab_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
                }

                // Populate details of .dynsym
                else if(section_hdr->sh_type == SHT_DYNSYM) {
                        dynsym_index = i;
                        pme_dynsym_hdr = section_hdr;
                        dynsym_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
                }

                // Populate details of .strtab
                else if(section_hdr->sh_type == SHT_STRTAB && i != shstrtab_index) {
                        strtab_index = i;
                        pme_strtab_hdr = section_hdr;
                        strtab_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
                }
		
		// Populate details of .text
                else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".text") == 0) {
                        text_index = i;
                        pme_text_hdr = section_hdr;
                        text_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
                }

		// Populate details of .rodata
		else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".rodata") == 0) {
			rodata_index = i;
			pme_rodata_hdr = section_hdr;
			rodata_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}

		// Populate details of .strtab
		else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".strtab") == 0) {
			strtab_index = i;
			pme_strtab_hdr = section_hdr;
			strtab_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}
		
		// Populate details of .data
		else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".data") == 0) {
			data_index = i;
			pme_data_hdr = section_hdr;
			data_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}
		
		// Populate details of .bss
		else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".bss") == 0) {
			bss_index = i;
			pme_bss_hdr = section_hdr;
			bss_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}
		
		// Populate details of .comment
		else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".comment") == 0) {
			comment_index = i;
			pme_comment_hdr = section_hdr;
			comment_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}

		// Populate details of .interp
		else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".interp") == 0) {
			interp_index = i;
			pme_interp_hdr = section_hdr;
			interp_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}

		// Populate details of.note.ABI-tag
		else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".note.ABI-tag") == 0) {
			noteabi_index = i;
			pme_noteabi_hdr = section_hdr;
			noteabi_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}
		
		// Populate details of .note.gnu.build-id
		else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".note.gnu.build-id") == 0) {
			buildid_index = i;
			pme_buildid_hdr = section_hdr;
			buildid_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}

		else if(strcmp(shstrtab_ptr + section_hdr->sh_name, ".gnu.hash") == 0) {
			gnuhash_index = i;
			pme_gnuhash_hdr = section_hdr;
			gnuhash_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}
        }

        return;
}

