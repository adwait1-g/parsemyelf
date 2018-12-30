//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// C++ SourceFile: ProgramHeaderTable.cpp
//
// Info: Has definitions of all methods declared in ProgramHeaderTable.h .
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//


#include "pme.h"
#include "ProgramHeader.h"
#include "ProgramHeaderTable.h"

using namespace pme;


// Constructor
Prgm64HeaderTable::Prgm64HeaderTable(unsigned char *PmeFilePtr, Elf64_Off phoff, Elf64_Half phentsize, Elf64_Half phnum) {

	FilePtr = PmeFilePtr;
	e_phoff = phoff;
	e_phentsize = phentsize;
	e_phnum = phnum;
	//Prgm64HdrTblVector.reserve(e_phnum);

	int index = 0;

        // Populate the vector
        while(index < e_phnum) {
                Prgm64HdrTblVector.push_back(Prgm64Header(FilePtr, e_phoff, e_phentsize, index));
                index++;
        }

	return;
}

// Give complete table
std::vector<Prgm64Header> Prgm64HeaderTable::GetCompleteTable() {
	return Prgm64HdrTblVector;
}

// Display method
void Prgm64HeaderTable::DisplayPrgmHeaderTable() {

	int index = 0;
	
	std::cout<<"Program Segment Header Table:	"<<std::endl;

	while(index < e_phnum) {
		std::cout<<"|------------------------------------------------------------------------|"<<std::endl;
		Prgm64HdrTblVector[index].DisplayPrgmHeader();
		index++;
	}
}


// Done defining methods for Prgm64HeaderTable
