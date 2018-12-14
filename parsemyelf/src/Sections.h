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

	unsigned char *FilePtr;

	// Points to the array of bytes. 
	// Will be using malloc here - should find a way of bypassing malloc
	unsigned char *Bytes;
	std::string SectionName;
	Elf64_Off SectionOffset;
	Elf64_Half SectionSize;

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


public: 
	ShstrndxSection64(unsigned char *PmeFilePtr, std::string name, Elf64_Off offset, Elf64_Half size);

	~ShstrndxSection64();

	std::string GetSectionName(Elf64_Word sh_name);

};


//---------------------------//
//
// class: NoNameSection64
//
// Section: No name for this section.
//
//---------------------------//

/*
class NoNameSection64 : public Section64 {

public: 
	NoNameSection64(unsigned char *PmeFilePtr, std::string name, Elf64_Off offset, Elf64_Half size);

	~NoNameSection64();

};


//---------------------------//
//
// class: InterpSection64
//
// Section: .interp
//
//---------------------------//


class InterpSection64 : public Section64 {

public: 
	InterpSection64(unsigned char *PmeFilePtr, std::string name, Elf64_Off offset, Elf64_Half size);

	~InterpSection64();

	std::string GetInterpName();
};


//---------------------------//
//
// class: NoteAbiTagSection64
//
// Section: .note.ABI-tag
//
// Methods: 
//
// 1. DisplayDetails: Will display the whole note in human readable form
//
// 2. n_namesz: Returns the NameSize
//
// 3. n_descsz: Returns the DescriptionSize
//
// 4. n_type: Returns the note type
//
// 4. 


class NoteAbiTagSection64 : public Section64 {

private: 
	
	Elf64_Nhdr NoteHdr;
	
public: 
	NoteAbiTagSection64(unsigned char *PmeFilePtr, std::string name, Elf64_Off offset, Elf64_Half size);

	~NoteAbiTagSection64();


};


*/











} // namespace end
