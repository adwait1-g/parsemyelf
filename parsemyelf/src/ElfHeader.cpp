//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// C++ SourceFile: ELFHeader.cpp
//
// Info: Contains definitions of all methods declared in ELFHeader.h
// 
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//


#include "pme.h"
#include "ElfHeader.h"

using namespace pme;

//---------------------------//
//
// class: Elf64Header
//
// All it's methods are defined here
//
//---------------------------//
	
	

Elf64Header::Elf64Header(unsigned char *PmeFilePtr) {


	// First, populate the Elf64_Ehdr C structure
	
	FilePtr = PmeFilePtr;

	Elf64_Ehdr *elf_hdr = (Elf64_Ehdr *)FilePtr;
        
	for(int i = 0; i < 16; i++)
                Elf64Hdr.e_ident[i] = elf_hdr->e_ident[i];

        Elf64Hdr.e_type = elf_hdr->e_type;
	Elf64Hdr.e_machine = elf_hdr->e_machine;
        Elf64Hdr.e_version = elf_hdr->e_version;
        Elf64Hdr.e_entry = elf_hdr->e_entry;
        Elf64Hdr.e_phoff = elf_hdr->e_phoff;
        Elf64Hdr.e_shoff = elf_hdr->e_shoff;
        Elf64Hdr.e_flags = elf_hdr->e_flags;
        Elf64Hdr.e_ehsize = elf_hdr->e_ehsize;
        Elf64Hdr.e_phentsize = elf_hdr->e_phentsize;
        Elf64Hdr.e_phnum = elf_hdr->e_phnum;
        Elf64Hdr.e_shentsize = elf_hdr->e_shentsize;
        Elf64Hdr.e_shnum = elf_hdr->e_shnum;
        Elf64Hdr.e_shstrndx = elf_hdr->e_shstrndx;


	// Then, start parsing it with the help of /usr/include/elf.h
		
		// Parsing e_ident[E_IDENT] array.


		//First 4 bytes: Magic number
		if(Elf64Hdr.e_ident[0] == 0x7f && Elf64Hdr.e_ident[1] == 'E' && Elf64Hdr.e_ident[2] == 'L' && Elf64Hdr.e_ident[3] == 'F') {
			Elf64HdrMap["e_magic"] = "7fELF";
		}
		else {
			PmeErrExit("Error: Magic Number doesn't match to that of en ELF");
		}
		
		
		// 5th byte: Architecture of the binary
		if(Elf64Hdr.e_ident[EI_CLASS] == ELFCLASSNONE)
			PmeErrExit("Error: Architecture for this binary is invalid");
		
		if(Elf64Hdr.e_ident[EI_CLASS] == ELFCLASS32)
			Elf64HdrMap["e_class"] = "32-bit";

		else if(Elf64Hdr.e_ident[EI_CLASS] == ELFCLASS64)
			Elf64HdrMap["e_class"] = "64-bit";
	
		
		
		// 6th byte: Endianess
		switch(Elf64Hdr.e_ident[EI_DATA]) {

			case ELFDATA2LSB:
				Elf64HdrMap["e_data"] = "2's Complement, Little-Endian";
				break;

			case ELFDATA2MSB:
				Elf64HdrMap["e_data"] = "2's Complement, Big-Endian";
				break;

			case ELFDATANONE:
				PmeErrExit("Error: Unknown Data Format(Endianess");
		}
		
		
		// 7th byte: Validity of ELF Version
		if(Elf64Hdr.e_ident[EI_VERSION] == EV_NONE)
			PmeErrExit("Error: Invalid ELF Version");

		else if(Elf64Hdr.e_ident[EI_VERSION] == EV_CURRENT)
			Elf64HdrMap["e_version"] = "Valid Version";


		// 8th byte: Operating System and ABI
		switch(Elf64Hdr.e_ident[EI_OSABI]) {

			case ELFOSABI_NONE:
				Elf64HdrMap["e_osabi"] = "UNIX System V";
				break;

			case ELFOSABI_HPUX:
				Elf64HdrMap["e_osabi"] = "HP_UX";
				break;

			case ELFOSABI_NETBSD:
				Elf64HdrMap["e_osabi"] = "NetBSD";
				break;

			case ELFOSABI_LINUX | ELFOSABI_GNU:
				Elf64HdrMap["e_osabi"] = "ELF using GNU Extensions";
				break;

			case ELFOSABI_SOLARIS:
				Elf64HdrMap["e_osabi"] = "Sun Solaris";
				break;

			case ELFOSABI_AIX:
				Elf64HdrMap["e_osabi"] = "IBM AIX";
				break;

			case ELFOSABI_IRIX:
				Elf64HdrMap["e_osabi"] = "SGI IRIX";
				break;

			case ELFOSABI_FREEBSD:
				Elf64HdrMap["e_osabi"] = "FreeBSD";
				break;

			case ELFOSABI_TRU64: 
				Elf64HdrMap["e_osabi"] = "Compaq TRU64 UNIX";
				break;

			case ELFOSABI_MODESTO:
				Elf64HdrMap["e_osabi"] = "Novell Modesto";
				break;

			case ELFOSABI_OPENBSD:
				Elf64HdrMap["e_osabi"] = "OpenBSD";
				break;

			case ELFOSABI_ARM_AEABI:
				Elf64HdrMap["e_osabi"] = "ARM EABI";
				break;

			case ELFOSABI_ARM:
				Elf64HdrMap["e_osabi"] = "ARM";
				break;

			case ELFOSABI_STANDALONE: 
				Elf64HdrMap["e_osabi"] = "Independent embedded application";
				break;

			default: 
				PmeErrExit("Error: Unable to recognize ABI");
		}
				

		// Rest of the 8 bytes in e_ident[EI_IDENT]: 
		// Assuming padding to be 00s
		Elf64HdrMap["e_padding"] = "00 00 00 00 00 00 00 00";
		
		// Parsing e_ident member done. 


		// ELF Type: e_type
		switch(Elf64Hdr.e_type) {

			case ET_REL:
				Elf64HdrMap["e_type"] = "Relocatable File";
				break;

			case ET_EXEC:
				Elf64HdrMap["e_type"] = "Executable File";
				break;

			case ET_DYN:
				Elf64HdrMap["e_type"] = "Shared Library / Dynamically Linked Object File";
				break;

			case ET_CORE:
				Elf64HdrMap["e_type"] = "Core File";
				break;

			default: 
				PmeErrExit("Error: Unknown ELF Type");
		}

		
		// Machine: e_machine
		switch(Elf64Hdr.e_machine) {

			case EM_M32: 
				Elf64HdrMap["e_machine"] = "AT&T WE 32100";
				break;

			case EM_SPARC:
				Elf64HdrMap["e_machine"] = "Sun Microsystems SPARC";
				break;

			case EM_386:
				Elf64HdrMap["e_machine"] = "Intel 80386";
				break;

			case EM_68K: 
				Elf64HdrMap["e_machine"] = "Motorola 68000";
				break;

			case EM_88K: 
				Elf64HdrMap["e_machine"] = "Motorola 88000";
				break;

			case EM_860: 
				Elf64HdrMap["e_machine"] = "Intel 80860";
				break;

			case EM_MIPS:
				Elf64HdrMap["e_machine"] = "MIPS RS3000";
				break;
			
			case EM_PARISC: 
				Elf64HdrMap["e_machine"] = "HP / PA";
				break;

			case EM_SPARC32PLUS: 
				Elf64HdrMap["e_machine"] = "SPARC with enhanced instruction set";
				break;

			case EM_PPC:
				Elf64HdrMap["e_machine"] = "PowerPC";
				break;

			case EM_PPC64: 
				Elf64HdrMap["e_machine"] = "PowerPC 64-bit";
				break;

			case EM_S390: 
				Elf64HdrMap["e_machine"] = "IBM S/390";
				break;

			case EM_ARM:
				Elf64HdrMap["e_machine"] = "Advanced RISC Machines";
				break;

			case EM_SH:
				Elf64HdrMap["e_machine"] = "Renesas SuperH";
				break;

			case EM_SPARCV9: 
				Elf64HdrMap["e_machine"] = "SPARC v9 64-bit";
				break;

			case EM_IA_64: 
				Elf64HdrMap["e_machine"] = "Intel Itanium";
				break;

			case EM_X86_64: 
				Elf64HdrMap["e_machine"] = "AMD x86-64";
				break;

			case EM_VAX:
				Elf64HdrMap["e_machine"] = "DEC Vax";
				break;
			
			// Error case
			case EM_NONE: 
				PmeErrExit("Error: Unknown Machine");
		}

		
		// ELF Entry Point Address: e_entry
		Elf64HdrMap["e_entry"] = std::to_string(Elf64Hdr.e_entry);
		
		// Program Header Table's Offset: e_phoff
		Elf64HdrMap["e_phoff"] = std::to_string(Elf64Hdr.e_phoff);

		// Section Header Table's Offset: e_shoff
		Elf64HdrMap["e_shoff"] = std::to_string(Elf64Hdr.e_shoff);

		// ELF Flags : e_flags
		Elf64HdrMap["e_flags"] = std::to_string(Elf64Hdr.e_flags);

		// ELF Header Size: e_ehsize
		Elf64HdrMap["e_ehsize"] = std::to_string(Elf64Hdr.e_ehsize);

		// Size of a Program Header: e_phentsize
		Elf64HdrMap["e_ehsize"] = std::to_string(Elf64Hdr.e_phentsize);

		// Number of Program Headers: e_phnum
		Elf64HdrMap["e_phnum"] = std::to_string(Elf64Hdr.e_phnum);

		// Size of a Section Header: e_shentsize
		Elf64HdrMap["e_shentsize"] = std::to_string(Elf64Hdr.e_shentsize);

		// Number of Section Headers: e_shnum
		Elf64HdrMap["e_shnum"] = std::to_string(Elf64Hdr.e_shnum);

		// Index of Section Header String Table
		Elf64HdrMap["e_shstrndx"] = std::to_string(Elf64Hdr.e_shstrndx);



	// From here, all code will handle the Section Header String Table
	

	// Temporary variable
	Elf64_Shdr *ShStrTabHdr;

	ShStrTabHdr = (Elf64_Shdr *)(PmeFilePtr + e_shoff() + e_shentsize() * e_shstrndx());
	
	// This pointer will be used every section header to know it's name
	ShStrTabPtr = (char *)(PmeFilePtr + ShStrTabHdr->sh_offset);


	// PmeShStrTabPtr is a global variable which can be anyone
	//PmeShStrTabPtr = ShStrTabPtr;

	return;
}


// API to use the parsed information

std::string Elf64Header::e_magic() {
	return Elf64HdrMap["e_magic"];
}

std::string Elf64Header::e_class() {
	return Elf64HdrMap["e_class"];
}

std::string Elf64Header::e_data() {
	return Elf64HdrMap["e_data"];
}

std::string Elf64Header::e_version() {
	return Elf64HdrMap["e_version"];
}

std::string Elf64Header::e_osabi() {
	return Elf64HdrMap["e_osabi"];
}

std::string Elf64Header::e_padding() {
	return Elf64HdrMap["e_padding"];
}

std::string Elf64Header::e_type() {
	return Elf64HdrMap["e_type"];
}

std::string Elf64Header::e_machine() {
	return Elf64HdrMap["e_machine"];
}



// Returns Entry Address
Elf64_Addr Elf64Header::e_entry() {
	return Elf64Hdr.e_entry;
}
	
// Program Header Offset
Elf64_Off Elf64Header::e_phoff() {
	return Elf64Hdr.e_phoff;
}

	// Section Header Offset
Elf64_Off Elf64Header::e_shoff() {
	return Elf64Hdr.e_shoff;
}

// ELF Header Size
Elf64_Half Elf64Header::e_ehsize() {
	return Elf64Hdr.e_ehsize;
}
	
// Single Program Header Size
Elf64_Half Elf64Header::e_phentsize() {
	return Elf64Hdr.e_phentsize;
}

// Single Section Header Size
Elf64_Half Elf64Header::e_shentsize() {
	return Elf64Hdr.e_shentsize;
}

//Number of Program Headers
Elf64_Half Elf64Header::e_phnum() {
	return Elf64Hdr.e_phnum;
}

// Number of Section Headers
Elf64_Half Elf64Header::e_shnum() {
	return Elf64Hdr.e_shnum;
}

// Section header string table Index
Elf64_Half Elf64Header::e_shstrndx() {
	return Elf64Hdr.e_shstrndx;
}


// This method returns ShStrTabPtr
char* Elf64Header::GetShStrTabPtr() {
	return ShStrTabPtr;
}





// Display the ELF Header
void Elf64Header::DisplayElfHeader() {

	system("clear");

	unsigned index = 0;

	std::cout<<"ELF Header: "<<std::endl;

	// Magic Number
	std::cout<<index<<".	Magic Number:		"<<e_magic()<<std::endl;
	index++;

	// Architecture of the binary
	std::cout<<index<<".	Architecture:		"<<e_class()<<std::endl;
	index++;

	// Endianess
	std::cout<<index<<".	Endianess:		"<<e_data()<<std::endl;
	index++;

	// ELF Version
	std::cout<<index<<".	ELF Version:		"<<e_version()<<std::endl;
	index++;

	// OS and ABI
	std::cout<<index<<".	OS & ABI:		"<<e_osabi()<<std::endl;
	index++;

	// Padding
	std::cout<<index<<".	Padding:		"<<e_padding()<<std::endl;
	index++;

	// ELF Type
	std::cout<<index<<".	ELF Type:		"<<e_type()<<std::endl;
	index++;

	// Machine
	std::cout<<index<<".	Machine:		"<<e_machine()<<std::endl;
	index++;

	// Entry Address
	std::cout<<index<<".	Entry Address:		0x"<<std::hex<<e_entry()<<std::endl;
	index++;

	// Program Header Offset
	std::cout<<std::dec<<index<<".	PHT Offset:		"<<e_phoff()<<" bytes"<<std::endl;
	index++;

	// Section Header Offset
	std::cout<<index<<".	SHT Offset:		"<<e_shoff()<<" bytes"<<std::endl;
	index++;

	// ELF Header Size
	std::cout<<index<<".	ELFHeader Size:		"<<e_ehsize()<<" bytes"<<std::endl;
	index++;

	// Program Header Size
	std::cout<<index<<".	PH Size:		"<<e_phentsize()<<" bytes"<<std::endl;
	index++;

	// Section Header Size
	std::cout<<index<<".	SH Size:		"<<e_shentsize()<<" bytes"<<std::endl;
	index++;
	
	// Number of Program Headers
	std::cout<<index<<".	PHs' Count:		"<<e_phnum()<<std::endl;
	index++;

	// Number of Section Headers
	std::cout<<index<<".	SHs' Count:		"<<e_shnum()<<std::endl;
	index++;


	// Section Header String Table Index
	std::cout<<index<<".	SHST Index:		"<<e_shstrndx()<<std::endl;


	std::cout<<std::endl;
	std::cout<<"PH:	Program Header"<<std::endl;
	std::cout<<"SH:	Section Header"<<std::endl;
	std::cout<<"SHT:	Section Header Table"<<std::endl;
	std::cout<<"PHT:	Program Header Table"<<std::endl;
	std::cout<<"SHST:	Section Header String Table"<<std::endl;


	std::cout<<std::endl;
}


// Done defining all Elf64Header class's methods
