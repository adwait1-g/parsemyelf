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

	
	// Job0: Get the pointer which points to .shstrndx
	// This will help in building the Table based on section names
	
	char *ShStrBytes;

	ShStrBytes = (char *)(PmeFilePtr + Sctn64Header::GetShStrTabOffset(PmeFilePtr, e_shoff, e_shentsize, e_shnum, e_shstrndx));

	int index = 0;

	while(index < e_shnum) { 
		
		Sctn64Header section_header(PmeFilePtr, e_shoff, e_shentsize, index);
		char *ptr = ShStrBytes + section_header.sh_name();





























