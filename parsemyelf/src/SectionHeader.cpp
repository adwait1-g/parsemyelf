//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// C++ SourceFile: SectionHeader.cpp
//
// Info: Has definitions of all methods declared in SectionHeader.h . 
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//


#include "pme.h"
#include "SectionHeader.h"
//#include "ElfHeader.h"

using namespace pme;

// Constructor
Sctn64Header::Sctn64Header(unsigned char *PmeFilePtr, Elf64_Off shoff, Elf64_Half shentsize, unsigned index) {

	FilePtr = PmeFilePtr;
	e_shoff = shoff;
	e_shentsize = shentsize;
	s_index = index;

	Elf64_Shdr *sctn_hdr = (Elf64_Shdr *)(FilePtr + e_shoff + e_shentsize * s_index);
	
	// Update the Elf64_Shdr structure
	Sctn64Hdr.sh_name = sctn_hdr->sh_name;
	Sctn64Hdr.sh_type = sctn_hdr->sh_type;
	Sctn64Hdr.sh_flags = sctn_hdr->sh_flags;
	Sctn64Hdr.sh_addr = sctn_hdr->sh_addr;
	Sctn64Hdr.sh_offset = sctn_hdr->sh_offset;
	Sctn64Hdr.sh_size = sctn_hdr->sh_size;
	Sctn64Hdr.sh_link = sctn_hdr->sh_link;
	Sctn64Hdr.sh_info = sctn_hdr->sh_info;
	Sctn64Hdr.sh_addralign = sctn_hdr->sh_addralign;
	Sctn64Hdr.sh_entsize = sctn_hdr->sh_entsize;


	// Section Name
	SectionName = std::string(PmeGetShStrTabPtr(FilePtr) + Sctn64Hdr.sh_name);

	Sctn64HdrMap["sh_name"] = SectionName;
	
	// Section Type
	switch(Sctn64Hdr.sh_type) {

		case SHT_NULL:
			Sctn64HdrMap["sh_type"] = "NULL";
			break;

		case SHT_PROGBITS:
			Sctn64HdrMap["sh_type"] = "PROGBITS";
			break;

		case SHT_SYMTAB:
			Sctn64HdrMap["sh_type"] = "SYMTAB";
			break;

		case SHT_STRTAB:
			Sctn64HdrMap["sh_type"] = "STRTAB";
			break;

		case SHT_RELA:
			Sctn64HdrMap["sh_type"] = "RELA";
			break;

		case SHT_HASH:
			Sctn64HdrMap["sh_type"] = "HASH";
			break;

		case SHT_DYNAMIC:
			Sctn64HdrMap["sh_type"] = "DYNAMIC";
			break;

		case SHT_NOTE:
			Sctn64HdrMap["sh_type"] = "NOTE";
			break;

		case SHT_NOBITS:
			Sctn64HdrMap["sh_type"] = "NOBITS";
			break;

		case SHT_REL:
			Sctn64HdrMap["sh_type"] = "REL";
			break;

		case SHT_SHLIB:
			Sctn64HdrMap["sh_type"] = "SHLIB";
			break;

		case SHT_DYNSYM:
			Sctn64HdrMap["sh_type"] = "DYNSYM";
			break;

		case SHT_INIT_ARRAY:
			Sctn64HdrMap["sh_type"] = "INIT_ARRAY";
			break;

		case SHT_FINI_ARRAY:
			Sctn64HdrMap["sh_type"] = "FINI_ARRAY";
			break;

		case SHT_PREINIT_ARRAY:
			Sctn64HdrMap["sh_type"] = "PREINIT_ARRAY";
			break;

		case SHT_GROUP:
			Sctn64HdrMap["sh_type"] = "GROUP";
			break;

		case SHT_SYMTAB_SHNDX:
			Sctn64HdrMap["sh_type"] = "SYNTAB_SHNDX";
			break;

		case SHT_NUM:
			Sctn64HdrMap["sh_type"] = "NUM";
			break;

		case SHT_LOOS:
			Sctn64HdrMap["sh_type"] = "LOOS";
			break;

		case SHT_GNU_ATTRIBUTES:
			Sctn64HdrMap["sh_type"] = "GNU_ATTRIBUTES";
			break;

		case SHT_GNU_HASH:
			Sctn64HdrMap["sh_type"] = "GNU_HASH";
			break;

		case SHT_GNU_LIBLIST:
			Sctn64HdrMap["sh_type"] = "GNU_LIBLIST";
			break;

		case SHT_CHECKSUM:
			Sctn64HdrMap["sh_type"] = "CHECKSUM";
			break;

		case SHT_LOSUNW: 
			Sctn64HdrMap["sh_type"] = "LOSUNW";
			break;

//		case SHT_SUNW_move: 
//			Sctn64HdrMap["sh_type"] = "SUNW_move";
//			break;

		case SHT_SUNW_COMDAT:
			Sctn64HdrMap["sh_type"] = "SUNW_COMDAT";
			break;

		case SHT_SUNW_syminfo: 
			Sctn64HdrMap["sh_type"] = "SUNW_syminfo";
			break;

		case SHT_GNU_verdef: 
			Sctn64HdrMap["sh_type"] = "GNU_verdef";
			break;

		case SHT_GNU_verneed:
			Sctn64HdrMap["sh_type"] = "GNU_verneed";
			break;

		case SHT_GNU_versym: 
			Sctn64HdrMap["sh_type"] = "GNU_versym";
			break;

//		case SHT_HISUNW: 
//			Sctn64HdrMap["sh_type"] = "HISUNW";
//			break;
//
//		case SHT_HIOS: 
//			Sctn64HdrMap["sh_type"] = "HIOS";
//			break;
		
		case SHT_LOPROC: 
			Sctn64HdrMap["sh_type"] = "LOPROC";
			break;

		case SHT_HIPROC: 
			Sctn64HdrMap["sh_type"] = "HIPROC";
			break;

		case SHT_LOUSER: 
			Sctn64HdrMap["sh_type"] = "LOUSER";
			break;

		case SHT_HIUSER: 
			Sctn64HdrMap["sh_type"] = "HIUSER";
			break;
		
		
		default: 
			PmeErrExit("Error: Section type not found!");
	}
	

	// Section flags
	
	switch(Sctn64Hdr.sh_flags) {

		case SHF_WRITE: 
			Sctn64HdrMap["sh_flags"] = "WRITE";
			break;

		case SHF_ALLOC: 
			Sctn64HdrMap["sh_flags"] = "ALLOC";
			break;

		case SHF_EXECINSTR: 
			Sctn64HdrMap["sh_flags"] = "EXECINSTR";
			break;

		case SHF_MERGE: 
			Sctn64HdrMap["sh_flags"] = "MERGE";
			break;

		case SHF_STRINGS: 
			Sctn64HdrMap["sh_flags"] = "STRINGS";
			break;
		
		case SHF_INFO_LINK: 
			Sctn64HdrMap["sh_flags"] = "INFO_LINK";
			break;

		case SHF_LINK_ORDER: 
			Sctn64HdrMap["sh_flags"] = "LINK_ORDER";
			break;

		case SHF_OS_NONCONFORMING: 
			Sctn64HdrMap["sh_flags"] = "OS_NONCONFORMING";
			break;

		case SHF_GROUP: 
			Sctn64HdrMap["sh_flags"] = "GROUP";
			break;

		case SHF_TLS: 
			Sctn64HdrMap["sh_flags"] = "TLS";
			break;

		case SHF_COMPRESSED: 
			Sctn64HdrMap["sh_flags"] = "COMPRESSED";
			break;

		case SHF_MASKOS: 
			Sctn64HdrMap["sh_flags"] = "MASKOS";
			break;

		case SHF_MASKPROC: 
			Sctn64HdrMap["sh_flags"] = "MASKPROC";
			break;

		case SHF_ORDERED:
			Sctn64HdrMap["sh_flags"] = "ORDERED";
			break;

		case SHF_EXCLUDE: 
			Sctn64HdrMap["sh_flags"] = "EXCLUDE";
			break;

		// common combination 1: 
		case SHF_WRITE | SHF_ALLOC: 
			Sctn64HdrMap["sh_flags"] = "WRITE | ALLOC";
			break;

		// common combination 2: 
		case SHF_EXECINSTR | SHF_ALLOC: 
			Sctn64HdrMap["sh_flags"] = "EXEC | ALLOC";
			break;

		default: 
			Sctn64HdrMap["sh_flags"] = "Section flags not found or I have not added them";
	}
}


// Destructor
Sctn64Header::~Sctn64Header() {

}


// API to access section header details. 

std::string Sctn64Header::sh_name() {
	return Sctn64HdrMap["sh_name"];
}


// Section type
std::string Sctn64Header::sh_type() {
	return Sctn64HdrMap["sh_type"];
}

// Section flags
std::string Sctn64Header::sh_flags() {
	return Sctn64HdrMap["sh_flags"];
}

// Section Virtual Address
Elf64_Addr Sctn64Header::sh_addr() {
	return Sctn64Hdr.sh_addr;
}

// Section File offset
Elf64_Off Sctn64Header::sh_offset() {
	return Sctn64Hdr.sh_offset;
}

// Section size (in bytes)
Elf64_Xword Sctn64Header::sh_size() {
	return Sctn64Hdr.sh_size;
}

// Section number of section linked!
Elf64_Word Sctn64Header::sh_link() {
	return Sctn64Hdr.sh_link;
}

// Section info
Elf64_Xword Sctn64Header::sh_info() {
	return Sctn64Hdr.sh_info;
}

// Section Address Alignment
Elf64_Xword Sctn64Header::sh_addralign() {
	return Sctn64Hdr.sh_addralign;
}

// Section entry size if section is a table
Elf64_Xword Sctn64Header::sh_entsize() {
	return Sctn64Hdr.sh_entsize;
}


void Sctn64Header::DisplayHeader() {
	
	std::cout<<"Name:	"<<sh_name()<<std::endl;
	std::cout<<"Type:	"<<sh_type()<<std::endl;
	std::cout<<"Flags:	"<<sh_flags()<<std::endl;
	std::cout<<"Address:	0x"<<std::hex<<sh_addr()<<std::dec<<std::endl;
	std::cout<<"File Offset:"<<sh_offset()<<" bytes(from beginning)"<<std::endl;
	std::cout<<"SectionSize:"<<sh_size()<<" bytes"<<std::endl;
	std::cout<<"Link:	"<<sh_link()<<std::endl;
	std::cout<<"Info:	"<<sh_info()<<std::endl;
	std::cout<<"Alignment:	"<<sh_addralign()<<std::endl;
	std::cout<<"Table Entry Size:	"<<sh_entsize()<<std::endl;

}













