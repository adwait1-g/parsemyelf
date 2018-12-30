//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// C++ SourceFile: SectionHeaderTable.cpp
//
// Info: Has definitions of all methods declared in SectionHeaderTable.h . 
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
#include "SectionHeaderTable.h"

using namespace pme;

// Constructor

Sctn64HeaderTable::Sctn64HeaderTable(unsigned char *PmeFilePtr, Elf64_Off shoff, Elf64_Half shentsize, Elf64_Half shnum, Elf64_Half shstrndx) {
	
	FilePtr = PmeFilePtr;
	e_shoff = shoff;
	e_shentsize = shentsize;
	e_shnum = shnum;
	e_shstrndx = shstrndx;

	int index = 0;
	std::string name;

	// Populate the vector
	while(index < e_shnum) {
		Sctn64HdrTbl.push_back(Sctn64Header(FilePtr, e_shoff, e_shentsize, index));
		index++;
	}

	return;
}

Sctn64HeaderTable::~Sctn64HeaderTable() {

}


// A simple display routine which you can use!
void Sctn64HeaderTable::DisplayTable() {
	
	std::cout<<"Section Header Table: \n"<<std::endl;
	for(unsigned count = 0; count < e_shnum; count++) {
		std::cout<<"|----------------------------------------------------------------------------|"<<std::endl;
		std::cout<<"Section Header "<<count<<"\n"<<std::endl;
		Sctn64HdrTbl[count].DisplayHeader();
	}

	return;
}











