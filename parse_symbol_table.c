/*
 * Tool: parsemyelf
 *
 * C Sourcefile: parse_symbol_table.c : It contains routines required to parse Symbol Table - one of the sections in the ELF File. 
 *
 * Note: parsemyelf is a toy tool written in C language to understand the interna
l structure of an ELF File.
 * Aim is to parse the ELF File and display the contents in a human readable form
.
 *
 * Author: Adwaith V Gautham
 *
 * BUG: For sections .shstrtab, .symtab, .strtab, .comment, Section Flags are wro
ng. 
 *
 */

#include"pme.h"

void pme_parse_symbol_table() {
	
	printf("#########################Symbol Table#############################\n");

	printf("\nSection Number: %d\n", symtab_index);
	printf("\nSection Name: %s\n", shstrtab_ptr + pme_symtab_hdr->sh_name);

	Elf64_Sym *symtab_entry_ptr;

	int number_of_entries = (pme_symtab_hdr->sh_size) / (pme_symtab_hdr->sh_entsize);
	
	printf("\nSymbol Table .symtab has %d entries.\n", number_of_entries);

	printf("\nNumber, Value, Size, Binding, Type, Visibility, Index, Name\n");


	for(int i = 0; i < number_of_entries; i++) {
	
		symtab_entry_ptr = (Elf64_Sym *)(symtab_ptr + i * pme_symtab_hdr->sh_entsize);
		printf("%d. ", i);

		pme_display_symbol(symtab_entry_ptr);
		printf("\n\n");
	}

	return;
}


void pme_display_symbol(Elf64_Sym *symtab_entry_ptr) {

	// Symbol Value(Address)
	printf("0x%lx, ", symtab_entry_ptr->st_value);
	
	// Symbol Size
	printf("%lu bytes, ", symtab_entry_ptr->st_size);
	
	
	// Symbol Binding and Type
	unsigned char val = symtab_entry_ptr->st_info;
	unsigned bind = ELF64_ST_BIND(val);
	unsigned type = ELF64_ST_TYPE(val);


	// Symbol Binding
	if(bind == STB_LOCAL)
		printf("LOCAL, ");

	else if(bind == STB_GLOBAL)
		printf("GLOBAL, ");

	else if(bind == STB_WEAK)
		printf("WEAK, ");

	else  if(bind == STB_NUM)
		printf("NUM, ");

	else if(bind == STB_LOOS)
		printf("LOOS, ");

	else if(bind == STB_GNU_UNIQUE)
		printf("GNU_UNIQUE, ");

	else if(bind == STB_HIOS)
		printf("HIOS, ");

	else if(bind == STB_LOPROC)
		printf("LOPROC, ");

	else if(bind == STB_HIPROC)
		printf("HIPROC, ");

	
	//Symbol Type
	if(type == STT_NOTYPE)
		printf("NOTYPE, ");

	else if(type == STT_OBJECT)
		printf("OBJECT, ");

	else if(type == STT_FUNC)
		printf("FUNC, ");

	else  if(type == STT_SECTION)
		printf("SECTION, ");

	else if(type == STT_FILE)
		printf("FILE, ");

	else if(type == STT_COMMON)
		printf("COMMON, ");

	else if(type == STT_TLS)
		printf("TLS, ");

	else if(type == STT_NUM)
		printf("NUM, ");

	else if(type == STT_LOOS)
		printf("LOOS, ");

	else  if(type == STT_GNU_IFUNC)
		printf("GNU_IFUNC, ");

	else if(type == STT_HIOS)
		printf("HIOS, ");
		
	else if(type == STT_LOPROC)
		printf("LOPROC, ");

	else if(type == STT_HIPROC)
		printf("HIPROC, ");


	//Symbol Visibility
	int vis = ELF64_ST_VISIBILITY(symtab_entry_ptr->st_other);

	if(vis == STV_DEFAULT)
		printf("DEFAULT, ");
	
	else if(vis == STV_INTERNAL)
		printf("INTERNAL, ");

	else if(vis == STV_HIDDEN)
		printf("HIDDEN, ");

	else if(vis == STV_PROTECTED)
		printf("PROTECTED, ");


	printf("%s", strtab_ptr + symtab_entry_ptr->st_name);
}
