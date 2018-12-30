//---------------------------------------------------------------------//
//
// Tool: parsemyelf
//
// About the tool: parsemyelf is a simple ELF Parser written in C++ to understand ELF binaries better. 
//
// C++ SourceFile: pme.cpp
//
// Info: This sourcefile has helper functions like init, exit functions. 
//
// Author: Adwaith V Gautham
//
// License: NONE
//
// Use the tool the way you want to, enjoy the learning and improve :)
//
//---------------------------------------------------------------------//


#include"pme.h"

namespace pme {

	void PmeErrExit(const char* errmsg) {

		std::cout<<errmsg<<std::endl;
		exit(-1);
	}

	void PmeLogo() {

		std::cout<<"________ ____    ____ _________"<<std::endl;
		std::cout<<"| ____ | | _ \\  / _ | | ______|"<<std::endl;
		std::cout<<"| |  | | | |  \\/  | | | |  "<<std::endl;  
		std::cout<<"| |__| | | |      | | | |____  "<<std::endl;
		std::cout<<"| _____| | |      | | |  ____|"<<std::endl;
		std::cout<<"| |      | |      | | | |     "<<std::endl;
		std::cout<<"| |      | |      | | | |______"<<std::endl;
		std::cout<<"|_|      |_|      |_| |_______|\n\n"<<std::endl;

		std::cout<<"Hey y'all! I am PME - ParseMyElf"<<std::endl;
		std::cout<<"I parse 64-bit ELF Files you give!"<<std::endl;
		std::cout<<"If you want to know more about me, how I was written, go to <this link> "<<std::endl;
		std::cout<<"\n\nNow, let me do my job :P"<<std::endl;

		std::cout<<"\n\n"<<std::endl;
	}
	



	// Had to go full on pointers here just to maintain independence between Elf64Header and Sctn64Header classes
	// I don't like this :( 
	char* PmeGetShStrTabPtr(unsigned char* PmeFilePtr) {

		Elf64_Ehdr *EHdr;
		Elf64_Shdr *ShStrTabHdr;

		EHdr = (Elf64_Ehdr* )PmeFilePtr;
		
		ShStrTabHdr = (Elf64_Shdr* )(PmeFilePtr + EHdr->e_shoff + (EHdr->e_shentsize) * (EHdr->e_shstrndx));

		return (char *)(PmeFilePtr + ShStrTabHdr->sh_offset);
	}
}
