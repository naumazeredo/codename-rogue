# @Incomplete configure better / Cross-compilation
EXECUTABLE=rogue.exe

CC=cl.exe
LINK=link.exe
TARGET=x64

FLAGS=-std:c++17 -Zi -FC -MD

# @FixIt remove ..\ from sources (build dir)
SOURCES=\
				..\main.cpp


SDL2_LIB=C:\libs\SDL2-2.0.10

SDL2_LIBDIR=$(SDL2_LIB)\lib\$(TARGET)
SDL2_LIBINC=$(SDL2_LIB)\include


LIBS=\
		 $(SDL2_LIBDIR)\SDL2.lib \
		 $(SDL2_LIBDIR)\SDL2main.lib

INCLUDES=\
				 -I$(SDL2_LIBINC)

all: windows

# @Incomplete copy dlls
windows:
	mkdir -p build
	cd build
	$(CC) $(FLAGS) $(SOURCES) $(INCLUDES) $(LIBS) -link /machine:$(TARGET) -entry:WinMainCRTStartup -subsystem:WINDOWS

clean:
	rm build
