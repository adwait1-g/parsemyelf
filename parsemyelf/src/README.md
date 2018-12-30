# PME - ParseMyElf

PME is a simple 64-bit ELF Parser written in C++. The goal was to learn C++ and to do something useful. So, this project. 

This is how you get the tool: 

    parsemyelf/parsemyelf/src$ g++ main.cpp pme.cpp ElfHeader.cpp ProgramHeader.cpp ProgramHeaderTable.cpp  SectionHeader.cpp  SectionHeaderTable.cpp -std=c++11 -o pme

You will get an executable with name **pme**, that is the tool. 

At this point, this can parse Elf Header, Section Headers and Program Headers. There is a lot left to implement. 

### History

The ELF File Format has been a black box for me. It does a lot of stuff. So, I wanted to write a parser. That way, I dissect it and know what it is made up of. I started writing the parser in C but later realized that I was not happy with it because it felt limited. 

So, this is a complete rewrite in C++. This was a well-thought off thing. In the C version, people had to use the tool I wrote. 

But here, I have written classes which will do all the hardwork by parsing everything you want. You can write a tool of your own, present the parsed data the way you want. 


### Inspiration

There are 2 tools which I specifically loved to play around with. Scapy and ns3. 

**ns3** : Hands down, one of the best open source tools to play around with Computer Networks, understand it better. All the required classes were present. I just had to use them and simulate something. This idea had a mark. 

***scapy**: Man, this tool is awesome! . It is so easy to use. It is a simple interpreter. To create an IP Packet, just ip = IP() is enough. It will encourage everyone to use it and learn and understand stuff better. 

### End Goal

One definite goal is to write an interpreter like Scapy for ELF parsing. That will help people to play around with ELFs, it seems like a lot of fun!

### Bug alert!

If you find any bugs, please create an issue. 