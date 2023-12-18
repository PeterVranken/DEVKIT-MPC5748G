# Makefile for GNU make 3.81
#   Type:
#   make 
#   make all
#   make clean
#   make run

appName := EmbeddedCoderAPIWithBusStruct
CONFIG ?= DEBUG

ifeq ($(OS),Windows_NT)
	executable := $(appName).exe
	CC := gcc.exe
	RM := rm.exe
else
	executable := $(appName)
	CC := gcc
	RM := rm
endif


# A blank separated list of defines for compiler run
defineList := $(CONFIG)

# List of C source files
#$(notdir $(wildcard ../slprj/ert/_sharedutils/*.c))
cFileList := cap_canApi.c pwr_computeEnginePower.c mai_main.c

# List of C source code folders
VPATH := ./ ../output/ ../pwr_computeEnginePower_ert_rtw/ ../slprj/ert/_sharedutils/

oFileList := $(patsubst %.c,%.o,$(cFileList))

# Link the application
$(executable): $(oFileList)
	$(CC) -o $@ $^

cFlags = -Wall -Wextra -Wstrict-overflow=4 -Wmissing-declarations -fno-exceptions			\
         -ffunction-sections -fdata-sections -MMD -Wa,-a=$(patsubst %.o,%.lst,$@) -std=c99	\
         $(foreach path,$(VPATH),-I$(path).)												\
         $(foreach def,$(defineList),-D$(def))
ifeq ($(CONFIG),DEBUG)
	cFlags += -ggdb3 -O0
else
	cFlags += -g -O2
endif

# Compile a file
%.o: %.c
	$(CC) $(cFlags) -o $@ -c $<

%.i: %.c
	$(info Preprocessing C file $< to text file $(patsubst %.c,%.i,$<))
	$(CC) -E $(filter-out -MMD,$(cFlags)) -o $(patsubst %.c,%.i,$<) $<

.PHONY: all
all: $(executable)

.PHONY: clean
clean:
	-$(RM) $(oFileList) $(patsubst %.o,%.d,$(oFileList)) $(patsubst %.o,%.lst,$(oFileList))	\
           $(executable)

.PHONY: run
run: $(executable)
	$(executable)

# Include the dependency files. Do this with a failure tolerant include operation - the
# files are not available after a clean.
-include $(patsubst %.o,%.d,$(oFileList))
