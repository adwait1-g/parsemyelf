#include<stdio.h>
#include<stdlib.h>
#include<sys/ptrace.h>
#include<unistd.h>
#include<sys/user.h>
#include<capstone/capstone.h>
#include<signal.h>
#include<string.h>


void display_registers(struct user process_state);


void get_siginfo(int pid);


int main(int argc, char **argv) {

	if(argc != 2) {
		fprintf(stdout, "Usage: $ %s <TraceeName> \n", argv[0]);
		return -1;
	}

	char *TraceeName[2];
	TraceeName[1] = argv[1];
	TraceeName[2] = '\0';
	unsigned char buffer[16];
	struct user process_state;



	int fork_value;
	
	fork_value = fork();

	// Parent process
	if(fork_value != 0) {
		printf("parent process! \n");
		long ptrace_ret = ptrace(PTRACE_ATTACH, fork_value, 0, 0);
	
		// ptrace_ret = 0 => Successfully hooked.
		printf("ptrace_ret = %ld\n", ptrace_ret);


		ptrace(PTRACE_CONT, fork_value, 0, SIGSTOP);
		ptrace(PTRACE_GETREGS, fork_value, NULL, &process_state);
		
		csh handle;
		cs_insn *insn;

		size_t insn_count;

		if(cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK)
			exit(1);



		
	}

	// Child process
	else if(fork_value == 0){
		printf("Child process! \n");
		if(execve(TraceeName[1], TraceeName, 0) != 0)
			printf("execve fail!\n");
	}

	return 0;
}

	

void display_registers(struct user process_state) {


	printf("\nGeneral Purpose Registers: ");
	printf("\n\nRAX:	0x%llx", process_state.regs.rax);
	printf("\nRBX:	0x%llx", process_state.regs.rbx);
	printf("\nRCX:	0x%llx", process_state.regs.rcx);
	printf("\nRDX:	0x%llx", process_state.regs.rdx);
	printf("\nRDI:	0x%llx", process_state.regs.rdi);
	printf("\nRSI:	0x%llx", process_state.regs.rsi);
	printf("\nRBP:	0x%llx", process_state.regs.rbp);
	printf("\nRSP: 	0x%llx", process_state.regs.rsp);
	printf("\nR8:	0x%llx", process_state.regs.r8);
	printf("\nR9:	0x%llx", process_state.regs.r9);
	printf("\nR10:	0x%llx", process_state.regs.r10);
	printf("\nR11:	0x%llx", process_state.regs.r11);
	printf("\nR12:	0x%llx", process_state.regs.r12);
	printf("\nR13:	0x%llx", process_state.regs.r13);
	printf("\nR14:	0x%llx", process_state.regs.r14);
	printf("\nR15:	0x%llx", process_state.regs.r15);
	

	printf("\n\nSpecial Purpose Registers: ");
	printf("\n\nRIP:	0x%llx", process_state.regs.rip);
	printf("\nEFLAGS:	0x%llx", process_state.regs.eflags);
	printf("\nCS:	0x%llx", process_state.regs.cs);
	printf("\nDS:	0x%llx", process_state.regs.ds);
	printf("\nSS:	0x%llx", process_state.regs.ss);
	printf("\nES:	0x%llx", process_state.regs.es);
	printf("\nFS:	0x%llx", process_state.regs.fs);
	printf("\nGS:	0x%llx", process_state.regs.gs);

	printf("\n\n");

	return;
}
	
void get_siginfo(int pid) {

	siginfo_t siginfo;

	ptrace(PTRACE_GETSIGINFO, pid, NULL, &siginfo);

	printf("\n\nInformation of Signal which paused the execution");
	printf("\n\nSignal: ");
	
	switch(siginfo.si_signo) {

		case SIGHUP:
			printf("SIGHUP");
			break;
		
		case SIGINT:
			printf("SIGINT");
			break;

		case SIGQUIT:
			printf("SIGQUIT");
			break;

		case SIGILL:
			printf("SIGILL");
			break;

		case SIGABRT:
			printf("SIGABRT");
			break;
	
		case SIGFPE:
			printf("SIGFPE");
			break;

		case SIGKILL:
			printf("SIGKILL");
			break;
	
		case SIGSEGV:
			printf("SIGSEGV");
			break;
		
		case SIGPIPE:
			printf("SIGPIPE");
			break;
	
		case SIGALRM:
			printf("SIGALRM");
			break;

		case SIGTERM:
			printf("SIGTERM");
			break;
	
		case SIGUSR1:
			printf("SIGUSR1");
			break;

		case SIGUSR2:
			printf("SIGUSR2");
			break;

		case SIGCHLD:
			printf("SIGCHLD");
			break;

		case SIGCONT:
			printf("SIGCONT");
			break;

		case SIGSTOP:
			printf("SIGSTOP");
			break;

		case SIGTSTP:
			printf("SIGTSTP");
			break;

		case SIGTTIN:
			printf("SIGTTIN");
			break;

		case SIGTTOU:
			printf("SIGTTOU");
			break;
		
		case SIGBUS:
			printf("SIGBUS");
			break;
	
		case SIGPOLL:
			printf("SIGPOLL");
			break;

		case SIGPROF:
			printf("SIGPROF");
			break;

		case SIGSYS:
			printf("SIGSYS");
			break;
		
		case SIGTRAP:
			printf("SIGTRAP");
			break;

		case SIGURG:
			printf("SIGURG");
			break;

		case SIGVTALRM:
			printf("SIGVTALRM");
			break;

		case SIGXCPU:
			printf("SIGXCPU");
			break;

		case SIGXFSZ:
			printf("SIGXFSZ");
			break;

	}

	printf("\nSignal sending PID:	%d", siginfo.si_pid);
	printf("\nSignal sending Process's UID:	%d", siginfo.si_uid);
	
	// For a programmer, only these might help. Other details like clocktime, usertime, system time might be of no use. 
	
	printf("\n");

	return ;
}
































































		











