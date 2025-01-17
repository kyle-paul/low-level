# Low Level Programming

C++ compile and link
```bash
g++ -o bin/main main.cpp # compile and link object file
g++ -S main.cpp # compile the assembly code
./bin/main
```

Assembly compilation and linking
```bash
nasm -f elf64 hello.asm -o bin/hello.o # generate object file
ld bin/hello.o -o bin/hello # gnu linking
gcc -nostartfiles bin/hello.o -o bin/hello # gcc linking
./bin/hello
```