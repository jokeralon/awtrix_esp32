# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alon/github/awtrix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alon/github/awtrix/build

# Include any dependencies generated for this target.
include esp-idf/riscv/CMakeFiles/__idf_riscv.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include esp-idf/riscv/CMakeFiles/__idf_riscv.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/riscv/CMakeFiles/__idf_riscv.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/riscv/CMakeFiles/__idf_riscv.dir/flags.make

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/instruction_decode.c.obj: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/flags.make
esp-idf/riscv/CMakeFiles/__idf_riscv.dir/instruction_decode.c.obj: ../esp-idf/components/riscv/instruction_decode.c
esp-idf/riscv/CMakeFiles/__idf_riscv.dir/instruction_decode.c.obj: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/riscv/CMakeFiles/__idf_riscv.dir/instruction_decode.c.obj"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/riscv/CMakeFiles/__idf_riscv.dir/instruction_decode.c.obj -MF CMakeFiles/__idf_riscv.dir/instruction_decode.c.obj.d -o CMakeFiles/__idf_riscv.dir/instruction_decode.c.obj -c /home/alon/github/awtrix/esp-idf/components/riscv/instruction_decode.c

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/instruction_decode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_riscv.dir/instruction_decode.c.i"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alon/github/awtrix/esp-idf/components/riscv/instruction_decode.c > CMakeFiles/__idf_riscv.dir/instruction_decode.c.i

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/instruction_decode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_riscv.dir/instruction_decode.c.s"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alon/github/awtrix/esp-idf/components/riscv/instruction_decode.c -o CMakeFiles/__idf_riscv.dir/instruction_decode.c.s

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/interrupt.c.obj: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/flags.make
esp-idf/riscv/CMakeFiles/__idf_riscv.dir/interrupt.c.obj: ../esp-idf/components/riscv/interrupt.c
esp-idf/riscv/CMakeFiles/__idf_riscv.dir/interrupt.c.obj: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/riscv/CMakeFiles/__idf_riscv.dir/interrupt.c.obj"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/riscv/CMakeFiles/__idf_riscv.dir/interrupt.c.obj -MF CMakeFiles/__idf_riscv.dir/interrupt.c.obj.d -o CMakeFiles/__idf_riscv.dir/interrupt.c.obj -c /home/alon/github/awtrix/esp-idf/components/riscv/interrupt.c

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/interrupt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_riscv.dir/interrupt.c.i"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alon/github/awtrix/esp-idf/components/riscv/interrupt.c > CMakeFiles/__idf_riscv.dir/interrupt.c.i

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/interrupt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_riscv.dir/interrupt.c.s"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alon/github/awtrix/esp-idf/components/riscv/interrupt.c -o CMakeFiles/__idf_riscv.dir/interrupt.c.s

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/vectors.S.obj: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/flags.make
esp-idf/riscv/CMakeFiles/__idf_riscv.dir/vectors.S.obj: ../esp-idf/components/riscv/vectors.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building ASM object esp-idf/riscv/CMakeFiles/__idf_riscv.dir/vectors.S.obj"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/__idf_riscv.dir/vectors.S.obj -c /home/alon/github/awtrix/esp-idf/components/riscv/vectors.S

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/vectors.S.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing ASM source to CMakeFiles/__idf_riscv.dir/vectors.S.i"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -E /home/alon/github/awtrix/esp-idf/components/riscv/vectors.S > CMakeFiles/__idf_riscv.dir/vectors.S.i

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/vectors.S.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling ASM source to assembly CMakeFiles/__idf_riscv.dir/vectors.S.s"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -S /home/alon/github/awtrix/esp-idf/components/riscv/vectors.S -o CMakeFiles/__idf_riscv.dir/vectors.S.s

# Object files for target __idf_riscv
__idf_riscv_OBJECTS = \
"CMakeFiles/__idf_riscv.dir/instruction_decode.c.obj" \
"CMakeFiles/__idf_riscv.dir/interrupt.c.obj" \
"CMakeFiles/__idf_riscv.dir/vectors.S.obj"

# External object files for target __idf_riscv
__idf_riscv_EXTERNAL_OBJECTS =

esp-idf/riscv/libriscv.a: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/instruction_decode.c.obj
esp-idf/riscv/libriscv.a: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/interrupt.c.obj
esp-idf/riscv/libriscv.a: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/vectors.S.obj
esp-idf/riscv/libriscv.a: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/build.make
esp-idf/riscv/libriscv.a: esp-idf/riscv/CMakeFiles/__idf_riscv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libriscv.a"
	cd /home/alon/github/awtrix/build/esp-idf/riscv && $(CMAKE_COMMAND) -P CMakeFiles/__idf_riscv.dir/cmake_clean_target.cmake
	cd /home/alon/github/awtrix/build/esp-idf/riscv && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_riscv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/riscv/CMakeFiles/__idf_riscv.dir/build: esp-idf/riscv/libriscv.a
.PHONY : esp-idf/riscv/CMakeFiles/__idf_riscv.dir/build

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/clean:
	cd /home/alon/github/awtrix/build/esp-idf/riscv && $(CMAKE_COMMAND) -P CMakeFiles/__idf_riscv.dir/cmake_clean.cmake
.PHONY : esp-idf/riscv/CMakeFiles/__idf_riscv.dir/clean

esp-idf/riscv/CMakeFiles/__idf_riscv.dir/depend:
	cd /home/alon/github/awtrix/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alon/github/awtrix /home/alon/github/awtrix/esp-idf/components/riscv /home/alon/github/awtrix/build /home/alon/github/awtrix/build/esp-idf/riscv /home/alon/github/awtrix/build/esp-idf/riscv/CMakeFiles/__idf_riscv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/riscv/CMakeFiles/__idf_riscv.dir/depend

