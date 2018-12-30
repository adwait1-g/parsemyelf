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

	// Allocate memory to store the section
	Bytes = (unsigned char *)malloc(SectionSize);

	// Copy the section from memory mapping into Bytes
	memcpy(Bytes, PmeFilePtr + SectionOffset, SectionSize);
	
	// Now, every function will use Bytes and not PmeFilePtr
	
}

ShstrndxSection64::~ShstrndxSection64() {

	free(Bytes);
}



// This method does not really return a string. 
// Take a look at this StackOverflow Answer: https://stackoverflow.com/questions/3282608/another-c-learning-moment-returning-strings-from-functions. 


std::string ShstrndxSection64::GetSectionName(Elf64_Word sh_name) {

	char *ptr = (char *)(Bytes + sh_name);

	std::string name(ptr);

	return name;
}

