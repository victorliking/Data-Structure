COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -Wall -Werror
LINKER = g++

all: testimage testscene

testscene : testscene.o scene.o image.o png.o rgbapixel.o 
	$(LINKER) testscene.o scene.o image.o png.o rgbapixel.o -lpng -o testscene

testimage : testimage.o image.o png.o rgbapixel.o 
	$(LINKER) testimage.o image.o png.o rgbapixel.o -lpng -o testimage



scene.o :scene.cpp scene.h image.h png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) scene.cpp

image.o :image.cpp image.h png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) image.cpp

png.o :png.cpp png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) png.cpp

rgbapixel.o :rgbapixel.cpp rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) rgbapixel.cpp

testscene.o : testscene.cpp scene.h image.h png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) testscene.cpp

testimage.o : testimage.cpp image.h png.h rgbapixel.h
	$(COMPILER) $(COMPILER_FLAGS) testimage.cpp

clean:
	-rm -f *.o testscene testimage
