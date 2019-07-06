export CXX = g++.exe
export LD = g++.exe

export CFLAGS = -pedantic -Wno-virtual-move-assign -Wall -Wextra -Wfloat-equal -Wstrict-overflow -Wshadow -Wconversion -Wunreachable-code -Wuninitialized -Winit-self -Werror -fstrict-overflow -std=c++17
export LDFLAGS = 

export INC = -I"C:/lib/MinGW64_7.3/include" -I"C:/Users/abell/Documents/GitHub/NRE-Tester/src" 
export LIB = "-lmingw32" "-lNRE-Tester" 
export LIBDIR = -L"C:/lib/MinGW64_7.3/x86_64-w64-mingw32/lib" -L"C:/lib/NRE" 

OBJDIR = obj/
BIN = bin/
SRC = test
OBJ = $(OBJDIR)NRE_Main.o 
OUT = Test-NRE-Utility

all : childs out

childs :
	@(cd $(SRC) && $(MAKE))

out : $(OBJ)
	@$(LD) $(LIBDIR) -o $(BIN)$(OUT) $^ $(LDFLAGS) $(LIB)
	@echo "Jobs done."

clean : 
	@echo "Clear of obj/"
	@rm -r obj
	@mkdir obj
	@echo "obj-Tree creation done."
	@echo "Clean done."
