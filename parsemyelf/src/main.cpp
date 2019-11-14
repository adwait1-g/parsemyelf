//----------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// C++ SourceFile: main.cpp
//
// Info: This sourcefile has the main function which is the driver function of this tool. 
//
// Note: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better.
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//----------------------------------------------------------------------//

#include "pme/pme.h"
#include "pme/ElfHeader.h"
#include "pme/ProgramHeader.h"
#include "pme/ProgramHeaderTable.h"
#include "pme/SectionHeader.h"
#include "pme/SectionHeaderTable.h"
#include "pme/Sections.h"

using namespace pme; 


int main(int argc, char **argv) {

	if(argc != 3) {

		std::cout<<"Usage: "<<argv[0]<<" ELF_FILE_NAME ELF_FILE_SIZE"<<std::endl;
		return -1;
	}

	PmeLogo();

	// Required variables
	int PmeFd, PmeFileSize, option;
	char *PmeFileName;
	unsigned char *PmeFilePtr;

	// 2 parameters
	PmeFileName = argv[1];
	PmeFileSize = atoi(argv[2]);

	// Open file
	PmeFd = open(PmeFileName, O_RDONLY);
	if(PmeFd == -1) 
		PmeErrExit("Error: Unable to open the ELF File");

	// Copy ELF File onto main memory
	PmeFilePtr = (unsigned char *)mmap(NULL, PmeFileSize, PROT_READ, MAP_PRIVATE, PmeFd, 0);
	if(PmeFilePtr == NULL) 
		PmeErrExit("Error: Unable to copy ELF File onto main memory");

	//system("clear");

	// Create the required objects
	std::cout<<"Pme: Creating 64-bit Elf Header object"<<std::endl;
	Elf64Header Elf64Hdr(PmeFilePtr);
	std::cout<<"Pme: Successfully created and populated 64-bit Elf Header object"<<std::endl;

	std::cout<<"Pme: Creating 64-bit Program Header Table object"<<std::endl;
	Prgm64HeaderTable Prgm64HdrTbl(PmeFilePtr, Elf64Hdr.e_phoff(), Elf64Hdr.e_phentsize(), Elf64Hdr.e_phnum());
	std::cout<<"Pme: Successfully created and populated 64-bit Program Header Table object"<<std::endl;

	std::cout<<"Pme: Creating 64-bit Section Header Table object"<<std::endl;
	Sctn64HeaderTable Sctn64HdrTbl(PmeFilePtr, Elf64Hdr.e_shoff(), Elf64Hdr.e_shentsize(), Elf64Hdr.e_shnum(), Elf64Hdr.e_shstrndx());
	std::cout<<"Pme: Successfully created and populated 64-bit Section Header Table object"<<std::endl;


	std::unordered_map<std::string, Sctn64Header> Table = Sctn64HdrTbl.GetTableByName();
	
	Table[".shstrtab"].DisplayHeader();



	
	while(1) {

		std::cout<<"\n\nOptions: "<<std::endl;
		std::cout<<"0.	ELF Header "<<std::endl;
		std::cout<<"1.	Program Headers"<<std::endl;
		std::cout<<"2.	Section Headers"<<std::endl;
		std::cout<<"3.	Sections"<<std::endl;
		
		std::cin>>option;

		switch(option) {

			case 0: 
				Elf64Hdr.DisplayElfHeader();
				break;

			case 1: 
				Prgm64HdrTbl.DisplayPrgmHeaderTable();
				break;
			
			case 2:
				Sctn64HdrTbl.DisplayTable();
				break;

			case 3: 
			//	DisplaySections(PmeFilePtr);
				break;

			default: 
				std::cout<<"Help me implement other stuff :P"<<std::endl;
		}

	}

	return 0;
}
