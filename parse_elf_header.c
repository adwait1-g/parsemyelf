/*
 * Tool: parsemyelf
 * 
 * C sourcefile: parse_elf_header.c
 *
 * This C file contains a function will completely processes the ELF Header of any 64-bit Binary and displays it's contents in human-readable form. It also updates the ELF Header data structure whose entries will be used later.
 * 
 * Author: Adwaith V Gautham
 */


#include"pme.h"

void pme_display_elf_header(char *pme_file_ptr) {
	
	system("clear");
	printf("##############################ELF Header##############################\n\n");
	Elf64_Ehdr *pme_elf_hdr = (Elf64_Ehdr *)pme_file_ptr;
	char ch, magic_no[5];
	int int_ch, index = 0, pme_arch_bit;
	
	/*
	 * Dissection of e_ident[E_IDENT] array. 
	 */

	//First 4 bytes: Magic numbers.	
	magic_no[0] = pme_elf_hdr->e_ident[0];
	magic_no[1] = pme_elf_hdr->e_ident[1];
	magic_no[2] = pme_elf_hdr->e_ident[2];
	magic_no[3] = pme_elf_hdr->e_ident[3];
	magic_no[4] = '\0';

	if(strcmp(magic_no, ELFMAG) != 0)
		pme_err_exit("Error: Magic numbers not matching. Probably not an ELF file");

	printf("\n\n%d. Magic number:\t\t\t%x%c%c%c", index, pme_elf_hdr->e_ident[0], pme_elf_hdr->e_ident[1], pme_elf_hdr->e_ident[2], pme_elf_hdr->e_ident[3]);

	index++;


	//5th Byte: Architecture of the binary.
	ch = pme_elf_hdr->e_ident[EI_CLASS];
	int_ch = (int)ch;
	if(int_ch == ELFCLASSNONE)
		pme_err_exit("Error: Architecture for this binary is invalid.");

	printf("\n%d. Architecture:\t\t\t", index);

	if(int_ch == ELFCLASS32) {
		pme_arch_bit = 32;
		printf("32-bit");
	}
	else if(int_ch == ELFCLASS64) {
		pme_arch_bit = 64;
		printf("64-bit");
	}

	index++;

	

	//6th Byte: Endianess.
	ch = pme_elf_hdr->e_ident[EI_DATA];
	int_ch = (int)ch;
	if(int_ch == ELFDATANONE)
		pme_err_exit("Error: Unknown data format");

	printf("\n%d. Endianess:\t\t\t\t", index);
	
	if(int_ch == ELFDATA2LSB)
		printf("2's Complement, Little-Endian");

	else if(int_ch == ELFDATA2MSB)
		printf("2's Complement, Big-Endian");

	index++;


	//7th Byte: Validity of ELF version.
	ch = pme_elf_hdr->e_ident[EI_VERSION];
	int_ch = (int)ch;
	if(int_ch == EV_NONE)
		pme_err_exit("Error: Invalid ELF Version");

	else if(int_ch == EV_CURRENT)
		printf("\n%d. ELF Version:\t\t\t\tValid Version. Version %d", index, EV_CURRENT);

	index++;


	//8th Byte: Operating System and ABI(Application Binary Interface)
	ch = pme_elf_hdr->e_ident[EI_OSABI];
	int_ch = (int)ch;

	printf("\n%d. Application Binary Interface:\t", index);
	
	switch(int_ch) {

		case ELFOSABI_NONE:
			printf("UNIX System V");
			break;
		case ELFOSABI_HPUX:
			printf("HP_UX");
			break;
		case ELFOSABI_NETBSD:
			printf("NetBSD");
			break;
		case ELFOSABI_LINUX | ELFOSABI_GNU:
			printf("ELF using GNU Extensions");
			break;
		case ELFOSABI_SOLARIS:
			printf("Sun Solaris");
			break;
		case ELFOSABI_AIX:
			printf("IBM AIX");
			break;
		case ELFOSABI_IRIX:
			printf("SGI Irix");
			break;
		case ELFOSABI_FREEBSD:
			printf("FreeBSD");
			break;
		case ELFOSABI_TRU64:
			printf("Compaq TRU64 UNIX");
			break;
		case ELFOSABI_MODESTO:
			printf("Novell Modesto");
			break;
		case ELFOSABI_OPENBSD:
			printf("OpenBSD");
			break;
		case ELFOSABI_ARM_AEABI:
			printf("ARM EABI");
			break;
		case ELFOSABI_ARM:
			printf("ARM");
			break;
		case ELFOSABI_STANDALONE:
			printf("Independent embedded application");
			break;
		default:
			pme_err_exit("Error: Unable to recognize ABI");

	}

	index++;


	//Rest of the 8 bytes:
	printf("\n%d. Rest of 8 bytes:\t\t\t", index);
	for(int i = 8; i <= 15; i++)
		printf("%d ", (int)pme_elf_hdr->e_ident[i]);

	index++;

	/*
	 * Done with e_ident[E_IDENT]. 
	 */
	

	//ELF Type: e_type
	ch = pme_elf_hdr->e_type;
	int_ch = (int)ch;

	if(int_ch == ET_NONE)
		pme_err_exit("Error: Unknown ELF File Type");
	

	printf("\n%d. ELF Type:\t\t\t\t", index);

	switch(int_ch) {

		case ET_REL:
			printf("Relocatable File / Object File");
			break;
		case ET_EXEC:
			printf("Executable File");
			break;
		case ET_DYN:
			printf("Shared Library / Dynamically Linked Object file");
			break;
		case ET_CORE:
			printf("Core File");
			break;
	}

	index++;


	//Machine: e_machine
	ch = pme_elf_hdr->e_machine;
	int_ch = (int)ch;

	if(int_ch == EM_NONE)
		pme_err_exit("Error: Unknown machine");

	printf("\n%d. Machine:\t\t\t\t", index);
	
	/*
	 * I have included cases only for popular machines. The exhaustive list is present in elf.h
	 */

	switch(int_ch) {
		case EM_M32:
			printf("AT&T WE 32100");
			break;
		case EM_SPARC:
			printf("Sun Microsystems SPARC");
			break;
		case EM_386:
			printf("Intel 80836");
			break;
		case EM_68K:
			printf("Motorola 68000");
			break;
		case EM_88K:
			printf("Motorola 88000");
			break;
		case EM_860:
			printf("Intel 80860");
			break;
		case EM_MIPS:
			printf("MIPS RS3000");
			break;
		case EM_PARISC:
			printf("HP / PA");
			break;
		case EM_SPARC32PLUS:
			printf("SPARC with enhanced instruction set");
			break;
		case EM_PPC:
			printf("PowerPC");
			break;
		case EM_PPC64:
			printf("PowerPC 64-bit");
			break;
		case EM_S390:
			printf("IBM S/390");
			break;
		case EM_ARM:
			printf("Advanced RISC Machines");
			break;
		case EM_SH:
			printf("Renesas SuperH");
			break;
		case EM_SPARCV9:
			printf("SPARC v9 64-bit");
			break;
		case EM_IA_64:
			printf("Intel Itanium");
			break;
		case EM_X86_64:
			printf("AMD x86-64");
			break;
		case EM_VAX:
			printf("DEC Vax");
			break;
	}

	index++;

	
	/*
	 * Skipping ELF Version because it was taken care above.
	 */


	//ELF Entry point Address: e_entry
	printf("\n%d. Entry Point Address:\t\t\t0x%lx", index++, (unsigned long int)pme_elf_hdr->e_entry);


	//Program Header table's offset 
	printf("\n%d. Offset of Program Header Table:\t%d bytes (From beginning of file)", index++, (int)pme_elf_hdr->e_phoff);


	//Section Header table's offset.
	printf("\n%d. Offset of Section Header Table:\t%d bytes (From beginning of file)", index++, (int)pme_elf_hdr->e_shoff);


	//ELF Flags.
	printf("\n%d. Flags:\t\t\t\t0x%lx", index++, (unsigned long int)pme_elf_hdr->e_flags);


	//ELF Header Size
	printf("\n%d. ELF Header Size:\t\t\t%lu bytes", index++, (unsigned long int)pme_elf_hdr->e_ehsize);


	//Size of Single Entry in Program Header Table.
	printf("\n%d. Sizeof PH Table's single entry:\t%lu bytes", index++, (unsigned long int)pme_elf_hdr->e_phentsize);


	//Number of Program Header Table Entries.
	printf("\n%d. Number of PH Table entries:\t\t%lu", index++, (unsigned long int)pme_elf_hdr->e_phnum);


	//Size of single entry in Section Header Table
	printf("\n%d. Sizeof SH Table's single entry:\t%lu bytes", index++, (unsigned long int)pme_elf_hdr->e_shentsize);


	//Number of Section Header Table entries.
	printf("\n%d. Number of SH Table entries:\t\t%lu", index++, (unsigned long int)pme_elf_hdr->e_shnum);


	//Section name string table index.
	printf("\n%d. Section header string table index:\t%lu", index++, (unsigned long int)pme_elf_hdr->e_shstrndx);

	printf("\n\nPH = Program Header, SH = Section Header");


	//Updating the appropriate ELF Header. Very Important to store this because it has the Offset and Size of each Program Header and Section Header Table's entries.
	
	return;
}


void pme_parse_elf_header(char *pme_file_ptr) {

	pme_elf64_hdr = (Elf64_Ehdr *)malloc(sizeof(Elf64_Ehdr));
	if(pme_elf64_hdr == NULL)
		pme_err_exit("Error: Unable to allocate memory to store the ELF Header");

	Elf64_Ehdr *pme_elf_hdr = (Elf64_Ehdr *)pme_file_ptr;
	strncpy(pme_elf64_hdr->e_ident, pme_elf_hdr->e_ident, 16);
	pme_elf64_hdr->e_type = pme_elf_hdr->e_type;
	pme_elf64_hdr->e_machine = pme_elf_hdr->e_machine;
	pme_elf64_hdr->e_version = pme_elf_hdr->e_version;
	pme_elf64_hdr->e_entry = pme_elf_hdr->e_entry;
	pme_elf64_hdr->e_phoff = pme_elf_hdr->e_phoff;
	pme_elf64_hdr->e_shoff = pme_elf_hdr->e_shoff;
	pme_elf64_hdr->e_flags = pme_elf_hdr->e_flags;
	pme_elf64_hdr->e_ehsize = pme_elf_hdr->e_ehsize;
	pme_elf64_hdr->e_phentsize = pme_elf_hdr->e_phentsize;
	pme_elf64_hdr->e_phnum = pme_elf_hdr->e_phnum;
	pme_elf64_hdr->e_shentsize = pme_elf_hdr->e_shentsize;
	pme_elf64_hdr->e_shnum = pme_elf_hdr->e_shnum;
	pme_elf64_hdr->e_shstrndx = pme_elf_hdr->e_shstrndx;


	printf("\n\n");

	return ;
}
