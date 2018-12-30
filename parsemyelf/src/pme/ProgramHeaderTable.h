//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better.
//
// C++ HeaderFile: ProgramHeaderTable.h 
//
// Info: Has all classes and method declarations required to parse the Program Header Table(ALL Program Headers)
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//

#ifndef _PROGRAM_HEADER_TABLE_H
#define _PROGRAM_HEADER_TABLE_H 1

namespace pme {

//---------------------------//
//
// class: Prgm64HeaderTable
//
// This class is the Table of all Program Headers
//
//---------------------------//
class Prgm64HeaderTable {

private: 
	
	// This vector is essentially the program header table
	std::vector<Prgm64Header> Prgm64HdrTblVector;
	unsigned char *FilePtr;
	Elf64_Off e_phoff;
	Elf64_Half e_phentsize;
	Elf64_Half e_phnum;

public: 
	// Constructor	
	Prgm64HeaderTable(unsigned char *PmeFilePtr, Elf64_Off phoff, Elf64_Half phentsize, Elf64_Half phnum);

	// Gives the complete PHT which you can use. 
	std::vector<Prgm64Header> GetCompleteTable();
	
	// Use the above Table to write your own display method or use the following simple display method: 
	void DisplayPrgmHeaderTable();

};

}	// namespace end


#endif	// _PROGRAM_HEADER_TABLE_H


