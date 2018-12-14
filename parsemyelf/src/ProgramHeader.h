//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better.
//
// C++ HeaderFile: ProgramHeader.h
//
// Info: Contains classes and Data structures required to parse a Program Header.
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//

#ifndef _PROGRAM_HEADER_H
#define _PROGRAM_HEADER_H 1


namespace pme {

//---------------------------//
//
// class: Prgm64Header
//
// Underlying code C structure: Elf64_Phdr
//
//---------------------------//

class Prgm64Header {


private:
	// Program Header
	Elf64_Phdr Prgm64Hdr;
	unsigned char *FilePtr;
	Elf64_Off e_phoff;
	Elf64_Half e_phentsize;
	unsigned p_index;

	// An unordered-map to store details. 
	std::unordered_map<std::string, std::string> Prgm64HdrMap;

public:

	// Constructor
	// Does all the parsing and populates required data structures
	Prgm64Header(unsigned char *PmeFilePtr, 
			Elf64_Off phoff, 
			Elf64_Half phentsize, 
			unsigned index);


	// API to access the parsed information
	std::string p_type();
	std::string p_flags();
	
	Elf64_Off p_offset();
	Elf64_Addr p_vaddr();
	Elf64_Addr p_paddr();
	Elf64_Xword p_filesize();
	Elf64_Xword p_memsize();
	Elf64_Xword p_alignment();

	
	// Either the above API can be used to display the details the way you want or you can use this simple Display method: 
	void DisplayPrgmHeader();

};

}	// namespace end


#endif	//_PROGRAM_HEADER_H












