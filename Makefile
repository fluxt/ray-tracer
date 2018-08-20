
# Declaration of variables
CC = g++
CC_FLAGS = -w -DNDEBUG -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization \
	-Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept \
	-Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo \
	-Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused \
	-std=c++1y
# CC_FLAGS = -w -nodebug -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization \
# 	-Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept \
# 	-Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo \
# 	-Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused \
# 	-std=c++1y
# CC_LDFLAGS = -L/usr/lib

# File names
SOURCES = $(wildcard *.cpp) include/lodepng/lodepng.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXEC = main

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)