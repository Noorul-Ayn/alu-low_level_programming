# QUESTION 1- C Program Lifecycle

a. An operating system is a real-world example of C programming. For example, the Linux operating system is built mostly with C, and C is fast and efficient while giving access to the hardware making it really good for system programming and embedded systems like the traffic lights system.

b. A syntax error is what happens when the code breaks the rule of the langauge, e.g, when a semicolon is omitted at the end of a code line and it doesn't run, while a Semantic error is what happens when the code is written well but without a proper logic, e.g, diving by the wrong number.

c. There are 4 stages that happens when a C program is compiled:
   1. Preprocessing: This is where all preprocessor directives like #include are handled, the comments get removed and the header files are expanded.
   2. Compilation: This stage checks the C code for syntax errors, then translate it into assembly langauge.
   3. Assembly: The assembly code translates it into machine langauge, and the output is an object file.
   4. Linking: In this stage, the linker combines the object file with necessary libraries and produce the final executable file that can be run.
