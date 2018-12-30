//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// C++ HeaderFile: Sections.h
//
// Info: Has all classes and methods required to parse all sections(Not section headers).
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//


#include "pme.h"


namespace pme {

//---------------------------//
//
// class: Section64
//
// This is an abstract class. 
//
// Every Section is an inheritance of this class
//
//---------------------------//

class Section64 {

protected: 

	// Actual File pointer
	unsigned char *FilePtr;

	// General information about the section
	std::string SectionName;
	Elf64_Off SectionOffset;
	Elf64_Half SectionSize;

	// Pointer pointing to the section
	unsigned char *SectionPtr;

public: 

	// Every inherited class has it's own constructor. So. this is not required. 
	Section64();
	~Section64();


	// This is a pure virtual function. 
	// Will be defined for all children classes
	void virtual DisplayDetails() = 0;

};



//---------------------------//
//
// class: ShstrndxSection64
//
// Section: .shstrndx 
//
//---------------------------//

class ShstrndxSection64 : public Section64 {

private: 
	

public: 

	ShstrndxSection64(unsigned char* PmeFilePtr, std::string name, Elf64_Off offset, Elf64_Half size);

	~ShstrndxSection64();


};


} // namespace end
