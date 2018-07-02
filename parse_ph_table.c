/*
 * Tool: parsemyelf
 * 
 * C Sourcefile: parse_ph_table.c : It contains routines required to parse Program Header table.
 *
 * Note: A toy tool written in C language to understand the internal structure of an ELF File.
 * Aim is to parse the ELF File and display the contents in a human readable form.
 * 
 * Author: Adwaith V Gautham
 *
 * TODO: The tool at present is not printing Program Header flags. Should do it.
 */

#include"pme.h"

void pme_parse_ph_table(char *pme_elf_ptr) {

	system("clear");
	printf("##############################Program Header Table##############################\n\n\n");
	Elf64_Phdr *pme_ph_hdr;
	
	Elf64_Off ph_offset;
	Elf64_Half ph_entry_size;
	Elf64_Half ph_entry_count;

	ph_offset = pme_elf64_hdr->e_phoff;
	ph_entry_size = pme_elf64_hdr->e_phentsize;
	ph_entry_count = pme_elf64_hdr->e_phnum;

	printf("Offset at which Program Header table is found: %lu bytes\n", ph_offset);
	printf("Number of Program Header Entries: %d\n", ph_entry_count);
	printf("Size of each Program Header Entry: %d bytes\n", ph_entry_size);
	
	printf("\nVA: Virtual Address, PA: Physical Address\n\n");


	printf("Entry_no.|   Type   | Flags |    File_offset     |         VA         |         PA         |     Size(File)     |     size(Memory)    |     Alignment      \n");
	for(int i = 0; i < ph_entry_count; i++) {

		pme_ph_hdr = (Elf64_Phdr *)(pme_elf_ptr + ph_offset + ph_entry_size * i);
		pme_display_ph_entry(pme_ph_hdr, i);
	}

	printf("\n");

	return;
}

void pme_display_ph_entry(Elf64_Phdr *pme_ph_hdr, int ph_ent_no) {

	//Entry no.	
	printf("    %d    |", ph_ent_no);
		
	//Program Header Table Entry Type.
	switch(pme_ph_hdr->p_type) {

		case PT_LOAD:
			printf("   LOAD   |");
			break;
		case PT_DYNAMIC:
			printf("  DYNAMIC |");
			break;
		case PT_INTERP:
			printf("  INTERP  |");
			break;
		case PT_NOTE:
			printf("   NOTE   |");
			break;
		case PT_SHLIB:
			printf("  SHLIB   |");
			break;
		case PT_PHDR:
			printf("   PHDR   |");
			break;
		case PT_TLS:
			printf("   TLS    |");
			break;
		case PT_LOOS:
			printf("   LOOS   |");
			break;
		case PT_GNU_EH_FRAME:
			printf("GNUEHFRAME|");
			break;
		case PT_GNU_STACK:
			printf(" GNU_STACK|");
			break;
		case PT_GNU_RELRO:
			printf(" GNU_RELRO|");
			break;
		case PT_SUNWBSS:
			printf(" SUNWBSS  |");
			break;
		case PT_SUNWSTACK:
			printf("SUNWSTACK |");
			break;
		case PT_HIOS:
			printf("   HIOS   |");
			break;
		case PT_LOPROC:
			printf("  LOPROC  |");
			break;
		case PT_HIPROC:
			printf("  HIPROC  |");
			break;
		case PT_NULL:
			printf("  Unused  |");
			break;
		default:
			pme_err_exit("Error: Unknown Program Header Table Entry");
	}


	//Segment flags, Assuming W^X is always enabled.
	switch(pme_ph_hdr->p_flags) {

		case PF_X:
			printf("  X    |");
			break;
		case PF_W:
			printf("  W    |");
			break;
		case PF_R:
			printf("  R    |");
			break;
		case PF_X | PF_R:
			printf("  RX   |");
			break;
		case PF_W | PF_R:
			printf("  RW   |");
			break;
		default:
			pme_err_exit("Error: Unknown Flag");
	}

	//Segment File Offset.
	printf(" 0x%016lx |", pme_ph_hdr->p_offset);

	//Segment Virtual Address
	printf(" 0x%016lx |", pme_ph_hdr->p_vaddr);

	//Segment Physical Address
	printf(" 0x%016lx |", pme_ph_hdr->p_paddr);

	//Segment size in file
	printf(" 0x%016lx |", pme_ph_hdr->p_filesz);

	//Segment size on memory
	printf(" 0x%016lx |", pme_ph_hdr->p_memsz);

	//Segment Alignment
	printf(" 0x%016lx |", pme_ph_hdr->p_align);


	printf("\n");
		
	return;
}

	
