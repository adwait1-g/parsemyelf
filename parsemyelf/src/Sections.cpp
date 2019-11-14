//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// C++ SourceFile: Sections.cpp
//
// Info: Has definitions of all methods declared in Sections.h
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//


#include "pme/pme.h"
#include "pme/Sections.h"

using namespace pme;

// Routines required for base class

Section64::Section64() {
}


Section64::~Section64() {
}



ShstrtabSection64::ShstrtabSection64(unsigned char *PmeFilePtr, std::string name, Elf64_Off offset, Elf64_Half size) {

	std::cout<<"Inside shstrtab constructor"<<std::endl;
	// Populate the variables
	FilePtr = PmeFilePtr;
	SectionName = name;
	SectionOffset = offset;
	SectionSize = size;

	// Get the SectionPtr. 
	SectionPtr = (unsigned char* )(FilePtr + SectionOffset);
	
	// Get all section names and store it in SectionsNames. 
	unsigned x = 0;
	char* TempPtr = (char* )SectionPtr;
	while(x < SectionSize) {
	
		if(*(TempPtr - 1) == 0x00) {
			std::string tempname(TempPtr);
			SectionsNames.push_back(tempname);
		}
		TempPtr++;
		x++;
	}

	return;
}

ShstrtabSection64::~ShstrtabSection64() {
}


std::vector<std::string> ShstrtabSection64::GetAllSectionsNames() {
	return SectionsNames;
}














