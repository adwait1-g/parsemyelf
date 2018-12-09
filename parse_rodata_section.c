/*
 * Tool: parsemyelf
 * 
 * C Sourcefile: parse_rodata_section.c :  Routines which parse rodata section.  
 *
 * Note: A toy tool written in C language to understand the internal structure of
 an ELF File.
 * Aim is to parse the ELF File and display the contents in a human readable form
.
 * 
 * Author: Adwaith V Gautham
 */


#include"pme.h"

void pme_parse_rodata_section() {

	printf("##############################.rodata Section############################\n");

	printf("Section number: %d\n", rodata_index);

	char *ptr = rodata_ptr;
	int str_count = 0;
	
	printf("These are the strings present in .rodata section: \n\n");

	for(int i = 0; i < pme_rodata_hdr->sh_size; i++) {

		// Case *ptr = '\0'
		if(*ptr == '\0') {
			ptr++;
			continue;
		}
		
		// Case i = 0;
		else if(*ptr != '\0') {
			printf("%d: %s\n", str_count, ptr);
			ptr = ptr + strlen(ptr) + 1;
			str_count++;
		}
		
		printf("\n");

	}

	return;
}
