# Makefile Generique

EXT = c
CC = gcc
EXEC = Map_Editor
CXXFLAGS = -Wall -W 
LDFLAGS =`allegro-config --cflags --libs`


OBJDIR = obj
SRCDIR = srcs
SRC = $(wildcard $(SRCDIR)/*.$(EXT))
OBJ = $(notdir $(SRC:.$(EXT)=.o))
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

all: $(EXEC) clean

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o:  $(SRCDIR)/%.$(EXT)
	@mkdir -p $(OBJDIR)
	@$(CC) -o $@ -c $< $(CCFLAGS)

clean:
	@rm -rf $(OBJDIR)

install: $(EXEC)
	@cp $(EXEC) /usr/bin/
