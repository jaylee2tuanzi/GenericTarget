#########################################################################
#
# Generic Makefile (g++)
#
# Version 20200513
# Copyright (c) Robert Damerius
#
#########################################################################

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Project settings
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PRODUCT_NAME      := GenericTarget
DEBUG_MODE        := 0


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Directory settings
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
DIRECTORY_SOURCE  := source/
DIRECTORY_BUILD   := build/
DIRECTORY_PRODUCT := bin/
DIRECTORY_PCH     := source/pch/


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Libraries and symbols
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
LIBS_WIN          := -lstdc++ -lstdc++fs -lpthread -lwinmm -lgdi32 -lws2_32 -lwsock32
LIBS_UNIX         := -lstdc++ -lstdc++fs -lpthread -latomic
CC_SYMBOLS         = -DGENERIC_TARGET_IMPLEMENTATION


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Flags
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Build Flags
CC_FLAGS        = -Wall -Wextra -Wno-format-security -Ofast -mtune=native
CPP_FLAGS       = -std=c++17 -Wall -Wextra -Wno-format-security -Ofast -mtune=native
LD_FLAGS        = -Wall -Wextra -Wno-format-security -Ofast -mtune=native
DEP_FLAGS       = -MT $@ -MMD -MP -MF $(DIRECTORY_BUILD)$*.Td
POSTCOMPILE     = mv -f $(DIRECTORY_BUILD)$*.Td $(DIRECTORY_BUILD)$*.d

# Additional build flags depending on debug mode
ifeq ($(DEBUG_MODE), 1)
	CC_FLAGS   += -ggdb
	CPP_FLAGS  += -ggdb
	CC_SYMBOLS += -DDEBUG
else
	LD_FLAGS   += -s
endif

# Libs and shared objects
ifeq ($(OS), Windows_NT)
    LD_LIBS    := -static-libgcc -static-libstdc++ -Wl,-Bstatic $(LIBS_WIN) -Wl,-Bdynamic
else
    LD_LIBS    := $(LIBS_UNIX)
endif


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Toolset settings
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CC      := g++
CPP     := g++
LD      := ld
RM      := rm -f -r
MKDIR   := mkdir -p
WINDRES := windres


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Scan recursively for all source files in source directory
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Recursive wildcard function
rwildcard = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Source files
SOURCES_BIN := $(call rwildcard,$(DIRECTORY_SOURCE),*.bin)
SOURCES_C   := $(call rwildcard,$(DIRECTORY_SOURCE),*.c)
SOURCES_CPP := $(call rwildcard,$(DIRECTORY_SOURCE),*.cpp)
SOURCES_RC  := $(call rwildcard,$(DIRECTORY_SOURCE),*.rc)

# Precompiled headers
PCH_H       := $(call rwildcard,$(DIRECTORY_PCH),*.h)
PCH_HPP     := $(call rwildcard,$(DIRECTORY_PCH),*.hpp)
GCH_H       := $(PCH_H:.h=.gch)
GCH_HPP     := $(PCH_HPP:.hpp=.gch)
GCH_ALL     := $(addprefix $(DIRECTORY_PCH), $(GCH_H) $(GCH_HPP))

# Object files
OBJECTS_BIN := $(SOURCES_BIN:.bin=.o)
OBJECTS_C   := $(SOURCES_C:.c=.o)
OBJECTS_CPP := $(SOURCES_CPP:.cpp=.o)
OBJECTS_RC  := $(SOURCES_RC:.rc=.o)
OBJECTS_ALL  = $(addprefix $(DIRECTORY_BUILD), $(OBJECTS_BIN) $(OBJECTS_C) $(OBJECTS_CPP))
ifeq ($(OS), Windows_NT)
    OBJECTS_ALL += $(addprefix $(DIRECTORY_BUILD), $(OBJECTS_RC))
endif

# Additional shared objects from source directory
SHARED_OBJECTS = $(call rwildcard,$(DIRECTORY_SOURCE),*.so)

# All subdirectories of source directory
DIRECTORY_ALL := $(dir $(call rwildcard,$(DIRECTORY_SOURCE),.))

# Add header directories and library directories to related paths
INCLUDE_PATHS += -I/usr/local/include $(addprefix -I,$(DIRECTORY_ALL)) $(addprefix -I,$(DIRECTORY_PCH)) $(addprefix -include ,$(notdir $(PCH_H))) $(addprefix -include ,$(notdir $(PCH_HPP)))
LIBRARY_PATHS += -L/usr/local/lib $(addprefix -L,$(DIRECTORY_ALL))


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Final product
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ifeq ($(OS), Windows_NT)
    PRODUCT = $(DIRECTORY_PRODUCT)$(PRODUCT_NAME).exe
else
    PRODUCT = $(DIRECTORY_PRODUCT)$(PRODUCT_NAME)
endif

# Create build folders
$(shell $(MKDIR) $(DIRECTORY_BUILD) $(addprefix $(DIRECTORY_BUILD), $(DIRECTORY_ALL)) $(DIRECTORY_BUILD) $(addprefix $(DIRECTORY_BUILD), $(DIRECTORY_ALL)))


# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Make targets
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.PHONY: all pch info clean

all: $(PRODUCT)

pch: $(GCH_ALL) 

info:
	@echo ""
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "AppName: $(PRODUCT_NAME)"
	@echo "OS:      $(OS)"
	@echo ""
	@echo "~~~~~~~ COMMAND LIST ~~~~~~~~~~~~~~~~~~~~~~~~"
	@echo "all:     Makes complete software (no precompiled headers)."
	@echo "pch:     Makes precompiled headers in directory \"$(DIRECTORY_PCH)\"".
	@echo "clean:   Removes out built project files (.o, .d), precompiled headers (.gch) and build directory \"$(DIRECTORY_BUILD)\"".
	@echo "info:    Shows this info."
	@echo ""
	@echo "~~~~~~~ DIRECTORY SETTINGS ~~~~~~~~~~~~~~~~~~"
	@echo "Source:  [$(DIRECTORY_SOURCE)]"
	@echo "Build:   [$(DIRECTORY_BUILD)]"
	@echo "Product: [$(DIRECTORY_PRODUCT)]"
	@echo ""
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

clean:
	@$(RM) $(call rwildcard,$(DIRECTORY_BUILD),*.o) $(call rwildcard,$(DIRECTORY_BUILD),*.d) $(call rwildcard,$(DIRECTORY_PCH),*.gch) $(PRODUCT)
	@$(RM) $(DIRECTORY_BUILD)
	@echo "Clean: Done."

$(PRODUCT): $(OBJECTS_ALL)
	@printf "[APP]  > $@\n"
	@$(CC) $(LD_FLAGS) $(LIBRARY_PATHS) -o $@ $^ $(SHARED_OBJECTS) $(LD_LIBS)

$(DIRECTORY_BUILD)%.o: %.c
$(DIRECTORY_BUILD)%.o: %.c $(DIRECTORY_BUILD)%.d
	@printf "[C]    > $<\n"
	@$(CC) $(INCLUDE_PATHS) $(CC_FLAGS) $(DEP_FLAGS) -o $@ -c $< $(CC_SYMBOLS)
	@$(POSTCOMPILE)

$(DIRECTORY_BUILD)%.o: %.cpp
$(DIRECTORY_BUILD)%.o: %.cpp $(DIRECTORY_BUILD)%.d
	@printf "[CPP]  > $<\n"
	@$(CPP) $(INCLUDE_PATHS) $(CPP_FLAGS) $(DEP_FLAGS) -o $@ -c $< $(CC_SYMBOLS)
	@$(POSTCOMPILE)

$(DIRECTORY_BUILD)%.o: %.rc
	@printf "[.RC]  > $<\n"
	@$(WINDRES) $< -O coff -o $@

$(DIRECTORY_BUILD)%.o: %.bin
	@printf "[BIN]  > $<\n"
	@$(LD) -r -b binary -o $@ $<

$(DIRECTORY_PCH)%.gch: %.h
	@printf "[PCH]  > $<\n"
	@$(CPP) $(CPP_FLAGS) $<

$(DIRECTORY_PCH)%.gch: %.hpp
	@printf "[PCH]  > $<\n"
	@$(CPP) $(CPP_FLAGS) $<

$(DIRECTORY_BUILD)%.d: ;
.PRECIOUS: $(DIRECTORY_BUILD)%.d

-include $(patsubst %,$(DIRECTORY_BUILD)%.d,$(basename $(SOURCES_C) $(SOURCES_CPP)))
