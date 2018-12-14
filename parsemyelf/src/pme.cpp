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

	void PmeErrExit(const char *errmsg) {

		std::cout<<errmsg<<std::endl;
		exit(-1);
	}

}
