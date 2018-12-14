//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// C++ HeaderFile: ELFHeader.h
//
// Info: Contains required classes and methods to parse Elf Headers. 
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//

#ifndef _ELF_HEADER_H
#define _ELF_HEADER_H 1


namespace pme {


//---------------------------//
//
// class: Elf64Header
//
// Underlying core C structure: Elf64_Ehdr
//
//---------------------------//


class Elf64Header {

private: 
	//ELF Header
	Elf64_Ehdr Elf64Hdr;
	unsigned char *FilePtr;

	// A Hash-Table to store details of the header
	std::unordered_map<std::string, std::string> Elf64HdrMap;

public: 

	// Constructor
	// Does all the parsing and populates required data structures
	Elf64Header(unsigned char *PmeFilePtr);

	
	// API to access Elf Header details
	std::string e_magic();
	std::string e_class();
	std::string e_data();
	std::string e_version();
	std::string e_osabi();
	std::string e_padding();
	std::string e_type();
	std::string e_machine();

	Elf64_Addr e_entry();
	Elf64_Off e_phoff();
	Elf64_Off e_shoff();
	Elf64_Half e_ehsize();
	Elf64_Half e_phentsize();
	Elf64_Half e_shentsize();
	Elf64_Half e_phnum();
	Elf64_Half e_shnum();
	Elf64_Half e_shstrndx();

	// You can either use the above API to write your own display method or use this method: 
	void DisplayElfHeader();
};


}	// namespace end



#endif	// _ELF_HEADER_H


