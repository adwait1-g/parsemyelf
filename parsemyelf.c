/*
 * Tool: parsemyelf
 * 
 * C Sourcefile: parsemyelf.c : It contains the main function , which is the driver function of the tool. 
 *
 * Note: A toy tool written in C language to understand the internal structure of an ELF File.
 * Aim is to parse the ELF File and display the contents in a human readable form.
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

		// Populate details about .symtab
		if(section_hdr->sh_type == SHT_SYMTAB) {
			symtab_index = i;
			pme_symtab_hdr = section_hdr;
			symtab_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}
		
		// Populate details about .dynsym
		else if(section_hdr->sh_type == SHT_DYNSYM) {
			dynsym_index = i;
			pme_dynsym_hdr = section_hdr;
			dynsym_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}

		// Populate details about .strtab
		else if(section_hdr->sh_type == SHT_STRTAB && i != shstrtab_index) {
			strtab_index = i;
			pme_strtab_hdr = section_hdr;
			strtab_ptr = (char *)(pme_file_ptr + section_hdr->sh_offset);
		}
	}

	return;
}


int main(int argc, char **argv) {

	if(argc != 3) {
		fprintf(stderr, "Usage: $ %s ELF_FILE_NAME ELF_FILE_SIZE\n", argv[0]);
		exit(1);
	}

	int pme_fd, pme_file_size, choice;
	char *pme_file_name = argv[1], *pme_file_ptr;
	pme_file_size = atoi(argv[2]);

	
	//Open the specified ELF file and get the file descriptor.
	pme_fd = open(pme_file_name, O_RDONLY);
	if(pme_fd == -1)
		pme_err_exit("Error: Unable to open the specified ELF file");

	
	//Copy the whole ELF file from disk to main memory.
	pme_file_ptr = (char *)mmap(NULL, pme_file_size, PROT_READ, MAP_PRIVATE, pme_fd, 0);
	if(pme_file_ptr == NULL)
		pme_err_exit("Error: Unable to copy ELF file on disk onto main memory");


	pme_init(pme_file_ptr);

	while(1) {

		printf("\n\nOptions: \n");
		printf("0. ELF Header details \n");
		printf("1. Program Header Table entries \n");
		printf("2. Section Header Table entries \n");
		printf("3. Symbol Table entries \n");
			
		scanf("%d", &choice);

		switch(choice) {

			case 0:
				pme_display_elf_header(pme_file_ptr);
				break;
			case 1:
				pme_parse_ph_table(pme_file_ptr);
				break;
			case 2:
				pme_parse_sh_table(pme_file_ptr);
				break;

			case 3:
				pme_parse_symbol_table();
				break;

			
			default:
				printf("\nAll other stuff are yet to be implemented\n");
				system("clear");
		}
	}


	return 0;
}
