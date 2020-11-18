compile:
	rm -f jshell
	gcc -g -Wall -o jshell main.c \
		Shell/Shell.c Shell/Command.c \
		DataStructures/LinkedList.c \
		FileManager/FileManager.c FileManager/File.c FileManager/MyFiles.c \
		ErrorHandler/ErrorTable.c \
		IOManager/PrintHandler.c IOManager/MacroLookupTable.c
main:
	make compile
	jshell