Compiler = clang
CompilerFlags = -Wall -Wextra -std=c99
LibraryFlags = -lpthread
all: q1 q2 q3 q4 q5

q1:
	$(Compiler) $(CompilerFlags) $(LibraryFlags) A-Question1.c -o q1.exe

q2:
	$(Compiler) $(CompilerFlags) $(LibraryFlags) A-Question2.c -o q2.exe

q3:
	$(Compiler) $(CompilerFlags) $(LibraryFlags) A-Question3.c -o q3.exe

q4:
	$(Compiler) $(CompilerFlags) $(LibraryFlags) A-Question4.c -o q4.exe

q5:
	$(Compiler) $(CompilerFlags) $(LibraryFlags) A-Question5.c -o q5.exe

clean:
	rm -f *.exe
