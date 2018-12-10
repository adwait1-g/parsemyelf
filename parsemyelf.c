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

	system("clear");

	while(1) {

		printf("\n\nOptions: \n");
		printf("0.	ELF Header details \n");
		printf("1.	Program Headers \n");
		printf("2.	Section Headers \n");
		printf("3.	.symtab Section \n");
		printf("4. 	.text Section (Gives the disassembly)\n");
		printf("5. 	.rodata Section \n");
		printf("6. 	.strtab Section \n");
		printf("7. 	.data Section \n");
		printf("8. 	.bss Section \n");
		printf("9. 	.comment Section \n");
		printf("10. 	.interp Section \n");
		printf("11.	.note.ABI-tag Section \n");
		printf("12.	.note.gnu.build-id Section \n");
		printf("13.	.gnu.hash Section \n");
			
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
			
			case 4: 
				pme_parse_text_section();
				break;

			case 5: 
				pme_parse_rodata_section();
				break;

			case 6:
				pme_parse_strtab_section();
				break;

			case 7: 
				pme_parse_data_section();
				break;

			case 8: 
				pme_parse_bss_section();
				break;

			case 9: 
				pme_parse_comment_section();
				break;

			case 10: 
				pme_parse_interp_section();
				break;

			case 11: 
				pme_parse_noteabi_section();
				break;

			case 12: 
				pme_parse_buildid_section();
				break;

			case 13: 
				pme_parse_gnuhash_section();
				break;

			default:
				printf("Other stuff yet to be implemented\n");
		}
	}


	return 0;
}
