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



ShstrndxSection64::ShstrndxSection64(unsigned char *PmeFilePtr, std::string name, Elf64_Off offset, Elf64_Half size) {

	// Populate the variables
	FilePtr = PmeFilePtr;
	SectionName = name;
	SectionOffset = offset;
	SectionSize = size;

	// Get the SectionPtr. 
	SectionPtr = (unsigned char* )(FilePtr + SectionOffset);
	

	
}

ShstrndxSection64::~ShstrndxSection64() {
}
