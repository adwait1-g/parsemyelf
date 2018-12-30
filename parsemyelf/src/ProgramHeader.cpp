//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// C++ SourceFile: ProgramHeaders.cpp
//
// Info: All routines declared in the headerfile ProgramHeaders.h are defined in this sourcefile. 
//
// Note: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//

#include "pme/pme.h"
#include "pme/ProgramHeader.h"

using namespace pme;


// Constructor
Prgm64Header::Prgm64Header(unsigned char *PmeFilePtr, Elf64_Off phoff, Elf64_Half phentsize, unsigned index) {

	FilePtr = PmeFilePtr;
	e_phoff = phoff;
	e_phentsize = phentsize;
	p_index = index;


	// Populate the Elf64_Phdr C structure
	Elf64_Phdr *prgm_hdr = (Elf64_Phdr *)(FilePtr + e_phoff + e_phentsize * p_index);


        Prgm64Hdr.p_type = prgm_hdr->p_type;
        Prgm64Hdr.p_offset = prgm_hdr->p_offset;
        Prgm64Hdr.p_vaddr = prgm_hdr->p_vaddr;
        Prgm64Hdr.p_paddr = prgm_hdr->p_paddr;
        Prgm64Hdr.p_filesz = prgm_hdr->p_filesz;
        Prgm64Hdr.p_memsz = prgm_hdr->p_memsz;
        Prgm64Hdr.p_flags = prgm_hdr->p_flags;
        Prgm64Hdr.p_align = prgm_hdr->p_align;
	
	
	// Then start parsing!

	// Segment Type
	switch(Prgm64Hdr.p_type) {
		
		case PT_NULL:
			Prgm64HdrMap["e_type"] = "NULL";
			break;

		case PT_LOAD: 
			Prgm64HdrMap["p_type"] = "LOAD";
			break;

		case PT_DYNAMIC: 
			Prgm64HdrMap["p_type"] = "DYNAMIC";
			break;
	
		case PT_INTERP:
			Prgm64HdrMap["p_type"] = "INTERP";
			break;
		
		case PT_NOTE:
			Prgm64HdrMap["p_type"] = "NOTE";
			break;

		case PT_SHLIB:
			Prgm64HdrMap["p_type"] = "SHLIB";
			break;

		case PT_PHDR:
			Prgm64HdrMap["p_type"] = "PHDR";
			break;

		case PT_TLS:
			Prgm64HdrMap["p_type"] = "TLS";
			break;
		
		case PT_NUM:
			Prgm64HdrMap["p_type"] = "NUM";
			break;

		case PT_LOOS:
			Prgm64HdrMap["p_type"] = "LOOS";
			break;

		case PT_GNU_EH_FRAME:
			Prgm64HdrMap["p_type"] = "GNU_EH_FRAME";
			break;

		case PT_GNU_STACK:
			Prgm64HdrMap["p_type"] = "GNU_STACK";
			break;

		case PT_GNU_RELRO:
			Prgm64HdrMap["p_type"] = "GNU_RELRO";
			break;

		case PT_LOSUNW:
			Prgm64HdrMap["p_type"] = "LOSUNW";
			break;

//		case PT_SUNWBSS:
//			Prgm64HdrMap["p_type"] = "SUNWBSS";
//			break;
//
//		case PT_SUNWSTACK:
//			Prgm64HdrMap["p_type"] = "SUNWSTACK";
//			break;
//
//		case PT_HISUNW:
//			Prgm64HdrMap["p_type"] = "HISUNW";
//			break;

		case PT_HIOS:
			Prgm64HdrMap["p_type"] = "HIOS";
			break;

		case PT_LOPROC:
			Prgm64HdrMap["p_type"] = "LOPROC";
			break;

		case PT_HIPROC:
			Prgm64HdrMap["p_type"] = "HIPROC";
			break;
	}
			
	

	// Segment Flags - p_flags
	
	switch(Prgm64Hdr.p_flags) {

		case PF_X:
			Prgm64HdrMap["p_flags"] = "X";
			break;

		case PF_W:
			Prgm64HdrMap["p_flags"] = "W";
			break;

		case PF_R:
			Prgm64HdrMap["p_flags"] = "R";
			break;

		case PF_R | PF_X:
			Prgm64HdrMap["p_flags"] = "RX";
			break;

		case PF_R | PF_W:
			Prgm64HdrMap["p_flags"] = "RW";
			break;
		
		// Dangerous case
		case PF_R | PF_W | PF_X:
			Prgm64HdrMap["p_flags"] = "RWX - Are you sure about this?!";
			break;

		case PF_MASKOS:
			Prgm64HdrMap["p_flags"] = "MASKOS";
			break;

		case PF_MASKPROC:
			Prgm64HdrMap["p_flags"] = "MASKPROC";
			break;
	}

}


// API to access Program Header information

std::string Prgm64Header::p_type() {
	return Prgm64HdrMap["p_type"];
}

std::string Prgm64Header::p_flags() {
	return Prgm64HdrMap["p_flags"];
}


Elf64_Off Prgm64Header::p_offset() {
	return Prgm64Hdr.p_offset;
}


Elf64_Addr Prgm64Header::p_vaddr() {
	return Prgm64Hdr.p_vaddr;
}

Elf64_Addr Prgm64Header::p_paddr() {
	return Prgm64Hdr.p_paddr;
}

Elf64_Xword Prgm64Header::p_filesize() {
	return Prgm64Hdr.p_filesz;
}

Elf64_Xword Prgm64Header::p_memsize() {
	return Prgm64Hdr.p_memsz;
}

Elf64_Xword Prgm64Header::p_alignment() {
	return Prgm64Hdr.p_align;
}


// Display method which displays all details about the program header
void Prgm64Header::DisplayPrgmHeader() {
	
	unsigned index = 0;

	std::cout<<"Program Header "<<p_index<<std::endl;
	
	std::cout<<index<<".	Segment Type:	"<<p_type()<<std::endl;
	index++;


	std::cout<<index<<".	Segment Flags:	"<<p_flags()<<std::endl;
	index++;

	std::cout<<index<<".	Segment File Offset:	"<<p_offset()<<" bytes"<<std::endl;
	index++;

	std::cout<<index<<".	Segment Virtual Address:	0x"<<std::hex<<p_vaddr()<<std::dec<<std::endl;
	index++;

	std::cout<<index<<".	Segment Physical Address:	0x"<<std::hex<<p_paddr()<<std::dec<<std::endl;
	index++;

	std::cout<<index<<".	Segment size on file:	"<<p_filesize()<<" bytes"<<std::endl;
	index++;

	std::cout<<index<<".	Segment size on memory:	"<<p_memsize()<<" bytes"<<std::endl;
	index++;

	std::cout<<index<<".	Segment Alignment:	0x"<<std::hex<<p_alignment()<<" bytes"<<std::endl;

	return;
}
