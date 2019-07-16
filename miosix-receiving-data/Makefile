##
## Makefile for Miosix embedded OS
##
MAKEFILE_VERSION := 1.07
## Path to kernel directory (edited by init_project_out_of_git_repo.pl)
KPATH := miosix
## Path to config directory (edited by init_project_out_of_git_repo.pl)
CONFPATH := $(KPATH)
include $(CONFPATH)/config/Makefile.inc

##
## List here subdirectories which contains makefiles
##
SUBDIRS := $(KPATH)
NN_LIB ?= ./Middlewares/ST/AI
STM32_HAL_DIR ?= ./Drivers
##
## List here your source files (both .s, .c and .cpp)
##
#C_SOURCES +=Middlewares/ST/AI/AI/data/estimator_data.c 
#C_SOURCES +=Middlewares/ST/AI/AI/src/estimator.c  
#C_SOURCES += $(STM32_HAL_DIR)/CMSIS/DSP_Lib/Source/BasicMathFunctions/arm_dot_prod_f32.c

SRC = main.cpp	
SRC += LSM6DSLSensor.cpp 
SRC += LSM6DSL_acc_gyro_driver.c 



##
## List here additional static libraries with relative path
##
LIBS := 
#LDFLAGS += -L$(NN_LIB)/AI/lib -l:network_runtime.a
#C_SOURCE += $(NN_LIB)/Application/SystemPerformance/Src/aiSystemPerformance.c

##
## List here additional include directories (in the form -Iinclude_dir)
##
INCLUDE_DIRS = \
#-IInc \
#-IMiddlewares/ST/AI/AI/include \
#-IMiddlewares/ST/AI/AI/data \
#-IDrivers/CMSIS/DSP/Include \
#-IDrivers/STM32F4xx_HAL_Driver/Inc \
#-IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy \
#-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
#-IDrivers/CMSIS/Include \
#-IDrivers/CMSIS/Include \
#-I$(NN_LIB)/Application/SystemPerformance/Inc
#-I$(STM32_HAL_DIR)/CMSIS/Include








#$(MCU) -Wall -fdata-sections -ffunction-sections

##############################################################################
## You should not need to modify anything below                             ##
##############################################################################

ifeq ("$(VERBOSE)","1")
Q := 
ECHO := @true
else
Q := @
ECHO := @echo
endif

## Replaces both "foo.cpp"-->"foo.o" and "foo.c"-->"foo.o"
OBJ := $(addsuffix .o, $(basename $(SRC)))

## Includes the miosix base directory for C/C++
## Always include CONFPATH first, as it overrides the config file location
CXXFLAGS := $(CXXFLAGS_BASE) -I$(CONFPATH) -I$(CONFPATH)/config/$(BOARD_INC)  \
            -I. -I$(KPATH) -I$(KPATH)/arch/common -I$(KPATH)/$(ARCH_INC)      \
            -I$(KPATH)/$(BOARD_INC) $(INCLUDE_DIRS)
CFLAGS   := $(CFLAGS_BASE)   -I$(CONFPATH) -I$(CONFPATH)/config/$(BOARD_INC)  \
            -I. -I$(KPATH) -I$(KPATH)/arch/common -I$(KPATH)/$(ARCH_INC)      \
            -I$(KPATH)/$(BOARD_INC) $(INCLUDE_DIRS)
AFLAGS   := $(AFLAGS_BASE)
LFLAGS   := $(LFLAGS_BASE)
DFLAGS   := -MMD -MP

LINK_LIBS := $(LIBS) -L$(KPATH) -Wl,--start-group -lmiosix -lstdc++ -lc \
             -lm -lgcc -Wl,--end-group

all: all-recursive main

clean: clean-recursive clean-topdir

program:
	$(PROGRAM_CMDLINE)

all-recursive:
	$(foreach i,$(SUBDIRS),$(MAKE) -C $(i)                               \
	  KPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(KPATH))       \
	  CONFPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(CONFPATH)) \
	  || exit 1;)

clean-recursive:
	$(foreach i,$(SUBDIRS),$(MAKE) -C $(i)                               \
	  KPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(KPATH))       \
	  CONFPATH=$(shell perl $(KPATH)/_tools/relpath.pl $(i) $(CONFPATH)) \
	  clean || exit 1;)

clean-topdir:
	-rm -f $(OBJ) main.elf main.hex main.bin main.map $(OBJ:.o=.d)

main: main.elf
	$(ECHO) "[CP  ] main.hex"
	$(Q)$(CP) -O ihex   main.elf main.hex
	$(ECHO) "[CP  ] main.bin"
	$(Q)$(CP) -O binary main.elf main.bin
	$(Q)$(SZ) main.elf

main.elf: $(OBJ) all-recursive
	$(ECHO) "[LD  ] main.elf"
	$(Q)$(CXX) $(LFLAGS) -o main.elf $(OBJ) $(KPATH)/$(BOOT_FILE) $(LINK_LIBS)

%.o: %.s
	$(ECHO) "[AS  ] $<"
	$(Q)$(AS)  $(AFLAGS) $< -o $@

%.o : %.c
	$(ECHO) "[CC  ] $<"
	$(Q)$(CC)  $(DFLAGS) $(CFLAGS) $< -o $@

%.o : %.cpp
	$(ECHO) "[CXX ] $<"
	$(Q)$(CXX) $(DFLAGS) $(CXXFLAGS) $< -o $@

#pull in dependecy info for existing .o files
-include $(OBJ:.o=.d)
