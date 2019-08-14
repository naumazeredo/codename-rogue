# @Incomplete add Linux, emscripten (Web) and mobile
EXECUTABLE=rogue.exe

CC=cl.exe
LINK=link.exe
TARGET=x64

FLAGS=-std:c++17 -Zi -FC -MD -EHsc

DEFINES=\
				-DIMGUI_IMPL_OPENGL_LOADER_GLEW

# @FixIt remove ..\ from sources (build dir)
SOURCES=\
				..\*.cpp \
				..\imgui\*.cpp \


# SDL2
SDL2=C:\libs\SDL2-2.0.10
SDL2_LIBDIR=$(SDL2)\lib\$(TARGET)
SDL2_INC=$(SDL2)\include

# GLEW
GLEW=C:\libs\glew-2.1.0
GLEW_LIBDIR=$(GLEW)\lib\$(TARGET)
GLEW_INC=$(GLEW)\include

LIBS=\
		 $(SDL2_LIBDIR)\SDL2.lib \
		 $(SDL2_LIBDIR)\SDL2main.lib \
		 $(GLEW_LIBDIR)\glew32.lib \
		 $(GLEW_LIBDIR)\glew32s.lib \
		 opengl32.lib \

INCLUDES=\
				 -I..\imgui \
				 -I$(SDL2_INC) \
				 -I$(GLEW_INC) \

DLLS=\
		 $(SDL2)\lib\$(TARGET)\SDl2.dll \
		 $(GLEW)\bin\$(TARGET)\glew32.dll \


all: run

#$(CC) $(FLAGS) $(DEFINES) $(INCLUDES) $(SOURCES) $(LIBS) -link /machine:$(TARGET) -entry:WinMainCRTStartup -subsystem:WINDOWS -out:$(EXECUTABLE)
windows:
	mkdir -p build
	cd build
	$(CC) $(FLAGS) $(DEFINES) $(INCLUDES) $(SOURCES) $(LIBS) -link /machine:$(TARGET) -subsystem:console -out:$(EXECUTABLE)
	cp $(DLLS) .
	cd ..

run: windows
	.\build\$(EXECUTABLE)

clean:
	rm -rf build
	rm -f imgui.ini

linux:
	mkdir -p build
	cd build
	g++ -I imgui/ *.cpp imgui/*.cpp -lm -lGLEW -lGL -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -DIMGUI_IMPL_OPENGL_LOADER_GLEW
