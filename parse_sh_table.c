/*
 * Tool: parsemyelf
 *
 * C Sourcefile: parse_sh_table.c : It contains routines required to parse Section Header Table.
 *
 * Note: parsemyelf is a toy tool written in C language to understand the internal structure of an ELF File.
 * Aim is to parse the ELF File and display the contents in a human readable form.
 *
 * Author: Adwaith V Gautham
 *
 * BUG: For sections .shstrtab, .symtab, .strtab, .comment, Section Flags are wrong. 
 *
 */

#include"pme.h"

void pme_parse_sh_table(char *pme_elf_ptr) {

	system("clear");
	printf("#############################Section Header Table###############################\n\n\n");
	Elf64_Shdr *pme_sh_hdr;
	
	//Section Header Table variables
	Elf64_Off sh_off;
	Elf64_Half sh_entry_size;
	Elf64_Half sh_entry_count;

	//Populate Section Header table variables
	sh_off = pme_elf64_hdr->e_shoff;
	sh_entry_size = pme_elf64_hdr->e_shentsize;
	sh_entry_count = pme_elf64_hdr->e_shnum;


	//General details about Section Header Table
	printf("Offset at which Section Header Table is found: %lu bytes\n", sh_off);
	printf("Number of Section Header Entries: %d\n", sh_entry_count);
	printf("Size of each Section Header Entry: %d bytes\n", sh_entry_size);

	
	//Print details of every section(extract data from section header)
	for(int i = 0; i < sh_entry_count; i++) {
	
		printf("--------------------------------------------------------------------\n");
		pme_sh_hdr = (Elf64_Shdr *)(pme_elf_ptr + sh_off + sh_entry_size * i);
		printf("Section Number: %d\n", i);
		pme_display_sh_entry(pme_sh_hdr);
		printf("\n");
	}

	printf("\n");

	return;
}


void pme_display_sh_entry(Elf64_Shdr *pme_sh_hdr) {
	
	//Section name
	printf("Section Name: %s\n", shstrtab_ptr + pme_sh_hdr->sh_name);

	//Section type - sh_type
	printf("\nSection Type: ");
	Elf64_Word sht = pme_sh_hdr->sh_type;
	
	if(sht == SHT_NULL)
		printf("SHT_NULL");

	else if(sht == SHT_PROGBITS)
		printf("SHT_PROGBITS");

	else if(sht == SHT_SYMTAB)
		printf("SHT_SYMTAB");

	else if(sht == SHT_STRTAB)
		printf("SHT_STRTAB");

	else if(sht == SHT_RELA)
		printf("SHT_RELA");

	else if(sht == SHT_HASH)
		printf("SHT_HASH");

	else if(sht == SHT_DYNAMIC)
		printf("SHT_DYNAMIC");

	else if(sht == SHT_NOTE)
		printf("SHT_NOTE");

	else if(sht == SHT_NOBITS)
		printf("SHT_NOBITS");
	
	else if(sht == SHT_REL)
		printf("SHT_REL");

	else if(sht == SHT_SHLIB)
		printf("SHT_SHLIB");

	else if(sht == SHT_DYNSYM)
		printf("SHT_DYNSYM");

	else if(sht == SHT_INIT_ARRAY)
		printf("SHT_INIT_ARRAY");

	else if(sht == SHT_FINI_ARRAY)
		printf("SHT_FINI_ARRAY");

	else if(sht == SHT_PREINIT_ARRAY)
		printf("SHT_PREINIT_ARRAY");

	else if(sht == SHT_GROUP)
		printf("SHT_GROUP");

	else if(sht == SHT_SYMTAB_SHNDX)
		printf("SHT_SYMTAB_SHNDX");

	else if(sht == SHT_NUM)
		printf("SHT_NUM");

	else if(sht == SHT_LOOS)
		printf("SHT_LOOS");

	else if(sht == SHT_GNU_ATTRIBUTES)
		printf("SHT_GNU_ATTRIBUTES");

	else if(sht == SHT_GNU_HASH)
		printf("SHT_GNU_HASH");

	else if(sht == SHT_GNU_LIBLIST)
		printf("SHT_GNU_LIBLIST");

	else if(sht == SHT_CHECKSUM)
		printf("SHT_CHECKSUM");

	else if(sht == SHT_LOSUNW)
		printf("SHT_LOSUNW");

	else if(sht == SHT_SUNW_move)
		printf("SHT_SUNW_move");

	else if(sht == SHT_SUNW_COMDAT)
		printf("SHT_SUNW_COMDAT");

	else if(sht == SHT_SUNW_syminfo)
		printf("SHT_SUNW_syminfo");

	else if(sht == SHT_GNU_verdef)
		printf("SHT_GNU_verdef");

	else if(sht == SHT_GNU_verneed)
		printf("SHT_GNU_verneed");

	else if(sht == SHT_GNU_versym)
		printf("SHT_GNU_versym");

	else if(sht == SHT_HISUNW)
		printf("SHT_GNU_HISUNW");

	else if(sht == SHT_HIOS)
		printf("SHT_HIOS");

	else if(sht == SHT_LOPROC)
		printf("SHT_LOPROC");

	else if(sht == SHT_HIPROC)
		printf("SHT_HIPROC");

	else if(sht == SHT_LOUSER)
		printf("SHT_LOUSER");

	else if(sht == SHT_HIUSER)
		printf("SHT_HIUSER");
	
	else
		printf("Something is wrong with this executable\n");

	//Section flags
	// Assuming W^X is always enabled.
	
	int flags = pme_sh_hdr->sh_flags;
	printf("\nSection flags: ");

	if(flags == SHF_WRITE)
		printf("SHF_WRITE");

	else if(flags == SHF_ALLOC)
		printf("SHF_ALLOC");

	else if(flags == SHF_EXECINSTR)
		printf("SHF_EXECINSTR");

	else if(flags == SHF_MERGE)
		printf("SHF_MERGE");

	else if(flags == SHF_STRINGS)
		printf("SHF_STRINGS");

	else if(flags == SHF_INFO_LINK)
		printf("SHF_INFO_LINK");

	else if(flags == SHF_LINK_ORDER)
		printf("SHF_LINK_ORDER");

	else if(flags == SHF_OS_NONCONFORMING)
		printf("SHF_OS_NONCONFORMING");

	else if(flags == SHF_GROUP)
		printf("SHF_GROUP");

	else if(flags == SHF_TLS)
		printf("SHF_TLS");

	else if(flags == SHF_COMPRESSED)
		printf("SHF_COMPRESSED");

	else if(flags == SHF_MASKOS)
		printf("SHF_MASKOS");

	else if(flags == SHF_MASKPROC)
		printf("SHF_MASKPROC");

	else if(flags == SHF_ORDERED)
		printf("SHF_ORDERED");

	else if(flags == SHF_EXCLUDE)
		printf("SHF_EXCLUDE");

	else if(flags == SHF_WRITE | SHF_ALLOC)
		printf("SHF_WRITE | SHF_ALLOC");

	else if(flags == SHF_EXECINSTR | SHF_ALLOC)
		printf("SHF_EXECINSTR | SHF_ALLOC");

	else if(flags == SHF_MERGE | SHF_STRINGS)
		printf("SHF_MERGE | SHF_STRINGS");

	else
		printf("Something wrong or I have not parsed");


	// Section address - sh_addr
	printf("\nSection Virtual Address: 0x%lx", pme_sh_hdr->sh_addr);

	
	// Section file offset
	printf("\nSection File Offset: %lu", pme_sh_hdr->sh_offset);

	
	// Section size in bytes
	printf("\nSection Size: %lu bytes", pme_sh_hdr->sh_size);

	// Link to another section
	printf("\nLink to another Section: %u", pme_sh_hdr->sh_link);

	
	// Section Information
	printf("\nSection Information: %u", pme_sh_hdr->sh_info);

	// Section Alignment
	printf("\nSection Alignment: %lu", pme_sh_hdr->sh_addralign);


	// Section Entry size - if section holds a table
	printf("\nSection Entry Size: %lu\n", pme_sh_hdr->sh_entsize);
}
