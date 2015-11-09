Compiler = clang
CompilerFlags = -Wall -Wextra
LanguageStandard1-2 = -std=c99
LanguageStandard3-4-5 = -std=gnu99
LibraryFlags = -lpthread

all: q1 q2 q3 q4 q5

q1:
	$(Compiler) $(CompilerFlags) $(LanguageStandard1-2) $(LibraryFlags) A-Question1.c -o q1.exe

q2:
	$(Compiler) $(CompilerFlags) $(LanguageStandard1-2) $(LibraryFlags) A-Question2.c -o q2.exe

q3:
	$(Compiler) $(CompilerFlags) $(LanguageStandard3-4-5) $(LibraryFlags) A-Question3.c -o q3.exe

q4:
	$(Compiler) $(CompilerFlags) $(LanguageStandard3-4-5) $(LibraryFlags) A-Question4.c -o q4.exe

q5:
	$(Compiler) $(CompilerFlags) $(LanguageStandard3-4-5) $(LibraryFlags) A-Question5.c -o q5.exe

clean:
	rm -f *.exe
	rm *~
