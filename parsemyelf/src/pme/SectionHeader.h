//---------------------------------------------------------------------//
//
// Tool: parsemyelf
// 
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better.
//
// C++ HeaderFile: SectionHeader.h
//
// Info: has classes and methods' declaration required to parse a Section Header.
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//


#include "Sections.h"

namespace pme {


//---------------------------//
//
// class: Sctn64Header
//
// Underlying C structure: Elf64_Shdr
//
//---------------------------//


class Sctn64Header {

private: 

	// All the stuff required to parse the SectionHeader in the file
	Elf64_Shdr Sctn64Hdr;
	unsigned char *FilePtr;
	Elf64_Off e_shoff;
	Elf64_Half e_shentsize;
	unsigned s_index;

	std::string SectionName;

	// Pointer to it's respective Section class
	Section64 *SectionPointer;
	
	// Unordered-Map to store details.
	std::unordered_map<std::string, std::string> Sctn64HdrMap;

public: 

	// Constructor
	Sctn64Header(unsigned char *PmeFilePtr,
			Elf64_Off shoff,
			Elf64_Half shentsize,
			unsigned index);
	// Destructor
	~Sctn64Header();

	std::string sh_name();
	std::string sh_type();
	std::string sh_flags();

	Elf64_Addr sh_addr();
	Elf64_Off sh_offset();
	Elf64_Xword sh_size();
	Elf64_Word sh_link();
	Elf64_Xword sh_info();
	Elf64_Xword sh_addralign();
	Elf64_Xword sh_entsize();

	// A simple display method
	void DisplayHeader();
};

}	// namespace end
