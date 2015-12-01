Compiler = mpicc
CompilerFlags = -Wall -Wextra
LanguageStandard1-2 = -std=c99
LanguageStandard3-4-5 = -std=c99
LibraryFlags =

all: q1 q2 q3 q4 q5

demos: demo1 demo2

q1:
	$(Compiler) $(CompilerFlags) $(LanguageStandard1-2) $(LibraryFlags) A-Question1.c -o q1.exe -lm

q2:
	$(Compiler) $(CompilerFlags) $(LanguageStandard1-2) $(LibraryFlags) A-Question2.c -o q2.exe -lm

q3:
	$(Compiler) $(CompilerFlags) $(LanguageStandard3-4-5) $(LibraryFlags) A-Question3.c -o q3.exe -lm

q4:
	$(Compiler) $(CompilerFlags) $(LanguageStandard3-4-5) $(LibraryFlags) A-Question4.c -o q4.exe -lm

demo1:
	$(Compiler) $(CompilerFlags) $(LanguageStandard3-4-5) $(LibraryFlags) demo_1.c -o demo_1.exe -lm

demo2:
	$(Compiler) $(CompilerFlags) $(LanguageStandard3-4-5) $(LibraryFlags) demo_2.c -o demo_2.exe -lm

clean:
	rm -f *.exe
	rm *~
