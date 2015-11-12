Compiler = clang
CompilerFlags = -Wall -Wextra
LanguageStandard1-2 = -std=c99
LanguageStandard3-4-5 = -std=gnu99
LibraryFlags = -lpthread

all: q1 q2 

q1:
	$(Compiler) $(CompilerFlags) $(LanguageStandard1-2) $(LibraryFlags) A-Question1.c -o q1.exe

q2:
	$(Compiler) $(CompilerFlags) $(LanguageStandard1-2) $(LibraryFlags) A-Question2.c -o q2.exe

clean:
	rm -f *.exe
	rm numbers.txt
	rm sum.txt
	rm child1.txt
	rm child2.txt
	rm *~
