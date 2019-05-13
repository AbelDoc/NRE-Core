OBJ = $(OBJDIR)main.o 
OBJDIR = ../obj/

all : $(OBJ)

$(OBJDIR)%.o :  %.cpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)