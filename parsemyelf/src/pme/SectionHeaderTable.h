//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// C++ HeaderFile: SectionHeaderTable.h 
//
// Info: Has classes and method declarations required to parse ALL section headers. 
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//


#ifndef _SECTION_HEADER_TABLE_H
#define _SECTION_HEADER_TABLE_H 1

namespace pme {
	
//---------------------------//
//
// class: Sctn64HeaderTable
//
// This class is the Table of all Section Headers
//
//---------------------------//

class Sctn64HeaderTable {

private: 

	// Map which retrival using name
	std::unordered_map<std::string, Sctn64Header> Sctn64HdrTblName;

	// Map with retrival using index
	std::unordered_map<unsigned int, Sctn64Header> Sctn64HdrTblIndex;

	// General details about the table
	unsigned char *FilePtr;
	Elf64_Off e_shoff;
	Elf64_Half e_shentsize;
	Elf64_Half e_shnum;

	Elf64_Half e_shstrndx;
	
public: 
	
	// Constructor
	Sctn64HeaderTable(unsigned char *PmeFilePtr, Elf64_Off shoff, Elf64_Half shentsize, Elf64_Half shnum, Elf64_Half shstrndx); 

	// Destructor
	~Sctn64HeaderTable();

	// Give the complete SHT with name as Index
	std::unordered_map<std::string, Sctn64Header> GetTableByName();

	std::unordered_map<unsigned int, Sctn64Header> GetTableByIndex();

	// Use the above table to write your own display method or use the following simple display method: 
	void DisplayTable();

};

}	// namespace end

#endif 	// _SECTION_HEADER_TABLE_H






























