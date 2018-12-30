/*
 * Tool: parsemyelf
 * 
 * C Sourcefile: parse_all_sections.c : It contains routines which help in parsing all Sections (NOT Section Headers) 
 *
 * Note: A toy tool written in C language to understand the internal structure of an ELF File.
 * Aim is to parse the ELF File and display the contents in a human readable form.
 * 
 * Author: Adwaith V Gautham
 */


#include"pme.h"

/*********************************************************************/
// Parse text section
void pme_parse_text_section() {

	printf("\n\n");
        printf("############################.text Section###############################");

        // Using capstone to disassemble the complete .text section
        csh handle;
        cs_insn *insn;
        size_t insn_count;

        if(cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
                return;

        int count = cs_disasm(handle, text_ptr, pme_text_hdr->sh_size, pme_elf64_hdr->e_entry, 0, &insn);

        if(count > 0) {
                size_t j;

                for(j = 0; j < count; j++) {
                        printf("0x%lx:  %s      %s", insn[j].address, insn[j].mnemonic, insn[j].op_str);
			printf("\n");
                }

                cs_free(insn, count);
        }

        else
                pme_err_exit("Error: Unable to disassemble .text section\n Quitting...");

        return;
}


/**************************************************************************/

// Parse symbol table
void pme_parse_symbol_table() {
	
	printf("\n\n");
        printf("##########################.symtab Section#############################");

	printf("\n\n");
        printf("Section Number: %d", symtab_index);

        Elf64_Sym *symtab_entry_ptr;

        int number_of_entries = (pme_symtab_hdr->sh_size) / (pme_symtab_hdr->sh_entsize);

        printf("\nSymbol Table .symtab has %d entries.", number_of_entries);

        printf("\n\nNumber, Value, Size, Binding, Type, Visibility, Index, Name\n");


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


/**************************************************************************/
// Parse .rodata Section

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


/***************************************************************************/
// Parse .strtab Section

void pme_parse_strtab_section() {

        printf("\n\n##############################.strtab Section###############################");

        printf("\n\nSection number: %d", strtab_index);

        char *ptr = strtab_ptr;
        int str_count = 0;

        printf("\n\nThese are the strings present in .strtab section: ");

	printf("\n\n");
        // Ignore the first NULL Character present in the section.
        ptr++;
        for(int i = 0; i < pme_strtab_hdr->sh_size; i++) {
                printf("%d:     %s\n", str_count, ptr);
                ptr = ptr + strlen(ptr) + 1;
                str_count++;
        }

        return;
}


/**************************************************************************/
// Parse .data section
//TODO: Link it with symbols so that the values in .data section look meaningful
void pme_parse_data_section() {

	printf("\n\n#############################.data Section####################################");

	printf("\n\nSection number: %d", data_index);


	printf("\n");
	char *ptr = data_ptr;

	for(int i = 0; i < pme_data_hdr->sh_size; i++) {
		printf("%x ", *ptr);
		ptr++;
	}

	return;
}



/**************************************************************************/
//Parse .bss section
// TODO: Link it with symbols so that the values in .bss section look meaningful

void pme_parse_bss_section() {

	printf("\n\n##############################.bss Section##################################");

	printf("\n\nSection number: %d", bss_index);

	char *ptr = bss_ptr;

	printf("\n\nThe following is present in this section: ");
	printf("\n\n");
	for(int i = 0; i < pme_bss_hdr->sh_size; i++) {
		printf("%x ", *ptr);
		ptr++;
	}

	return;
}


/**************************************************************************/
// Parse .comment section

void pme_parse_comment_section() {

	printf("\n\n##############################.comment Section##############################");

	printf("\n\nSection number: %d", comment_index);

	printf("\n\nThere is only 1 string in this section: ");
	printf("\n\n%s\n", comment_ptr);

	return;
}


/**************************************************************************/
// Parse .interp section

void pme_parse_interp_section() {

	printf("\n\n###############################.interp Section##############################");

	printf("\n\nSection number: %d", interp_index);
	printf("\n\nPath to the interpreter to be used: %s\n", interp_ptr);

	return;
}


/*************************************************************************/
// Parse .note.ABI-tag section
// TODO: To understand this section completely and get meaning from it. 

void pme_parse_noteabi_section() {

	printf("\n\n##############################.note.ABI-tag Section#########################");

	printf("\n\nSection number: %d", noteabi_index);


	// Populate the Elf64_Nhdr. 
	Elf64_Nhdr *note_hdr;
	note_hdr = (Elf64_Nhdr *)(noteabi_ptr);
	printf("\n\nLength of note's name: %u", note_hdr->n_namesz);
	printf("\nLength of note's descriptor: %u", note_hdr->n_descsz);

	printf("\nType of note: ");
	if(note_hdr->n_type == NT_GNU_ABI_TAG)
		printf("NT_GNU_ABI_TAG");

	char *ptr = noteabi_ptr + sizeof(Elf64_Nhdr);
	
	printf("\nNote Owner: %s", ptr);
	ptr = ptr + note_hdr->n_namesz;
	int *int_ptr = (int *)ptr;

	printf("\nOS: ");
	if(int_ptr[0] == ELF_NOTE_OS_LINUX)
		printf("ELF_NOTE_OS_LINUX");

	else if(int_ptr[0] == ELF_NOTE_OS_GNU)
		printf("ELF_NOTE_OS_GNU");

	else if(int_ptr[0] == ELF_NOTE_OS_SOLARIS2)
		printf("ELF_NOTE_OS_SOLARIS2");

	else if(int_ptr[0] == ELF_NOTE_OS_FREEBSD)
		printf("ELF_NOTE_OS_FREEBSD");

	printf("\nABI Version: %d.%d.%d\n", int_ptr[1], int_ptr[2], int_ptr[3]);

	return;
}

/*************************************************************************/
// Parse: .note.gnu.build-id section

void pme_parse_buildid_section() {

	printf("##############################.note.gnu.build-id Section###############################");

	printf("\n\nSection number: %d", buildid_index);

	Elf64_Nhdr *note_hdr;
	
	note_hdr = (Elf64_Nhdr *)buildid_ptr;
	printf("\n\nLength of note's name: %d", note_hdr->n_namesz);
	printf("\nLength of note's descriptor: %d", note_hdr->n_descsz);
	printf("\nType of note: ");
	if(note_hdr->n_type == NT_GNU_BUILD_ID)
		printf("NT_GNU_BUILD_ID");

	char *ptr = buildid_ptr + sizeof(Elf64_Nhdr);

	printf("\nNote owner: %s", ptr);

	ptr = ptr + note_hdr->n_namesz;

	unsigned char *uptr = (unsigned char *)ptr;
	printf("\nBuild-ID: ");
	for(int i = 0; i < note_hdr->n_descsz; i++) {
		printf("%02x", *uptr);
		uptr++;
	}
	
	return;
}


/***********************************************************************/
// Parse .gnu.hash section
/*

void pme_parse_gnuhash_section() {

	printf("\n\n#############################.gnu.hash Section###############################");
	printf("\n\nSection number: %d", gnuhash_index);

	unsigned  char *ptr = (unsigned char *)gnuhash_ptr;

	for(int i = 0; i < pme_gnuhash_hdr->sh_size; i++) {
		printf("%02x ", *ptr);
		ptr++;
	}

	return;
}
*/














