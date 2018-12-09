/*
 * Tool: parsemyelf
 * 
 * C Sourcefile: parse_text_section.c : It has routines which will process the text section. 
 *
 * Uses the capstone framework to disassemble the text section.
 *
 * Note: A toy tool written in C language to understand the internal structure of
 an ELF File.
 * Aim is to parse the ELF File and display the contents in a human readable form
.
 * 
 * Author: Adwaith V Gautham
 */

#include"pme.h"

void pme_parse_text_section() {

	printf("###########################.text Section###############################\n");
	
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
			printf("0x%lx:	%s	%s\n", insn[j].address, insn[j].mnemonic, insn[j].op_str);
		}

		cs_free(insn, count);
	}

	else 
		pme_err_exit("Error: Unable to disassemble .text section\n Quitting...");
		
	return;
}
