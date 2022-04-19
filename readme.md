# ProcView

### Tool to analyze processes easily.

I work on this project to become better at C++ and learn more about processes and Linux in general.
Therefore, this program may not be reliable.
I'm always open for tips via GitHub issues.


#### Functionality:

- List processes
- List users with processes
- View process info
- Read/Write process memory
- Search process for strings
- Log system calls
- Dump process


#### TODO:

- Add logging library
- Scan for signature/byte sequence
- Inject shared object into target process that hooks functions and sends arguments via IPC to the analyzer process
- Communicate with kernel module that hooks system calls by overwriting the system call table
- Disassemble machine code at a given address with the help of a disassembler library
- Block system calls