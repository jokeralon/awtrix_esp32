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
include esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/flags.make

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/flags.make
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.obj: ../esp-idf/components/esp_rom/patches/esp_rom_crc.c
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.obj"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.obj -MF CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.obj.d -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.obj -c /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_crc.c

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.i"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_crc.c > CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.i

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.s"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_crc.c -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.s

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/flags.make
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.obj: ../esp-idf/components/esp_rom/patches/esp_rom_sys.c
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.obj"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.obj -MF CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.obj.d -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.obj -c /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_sys.c

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.i"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_sys.c > CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.i

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.s"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_sys.c -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.s

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/flags.make
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.obj: ../esp-idf/components/esp_rom/patches/esp_rom_uart.c
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.obj"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.obj -MF CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.obj.d -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.obj -c /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_uart.c

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.i"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_uart.c > CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.i

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.s"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_uart.c -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.s

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/flags.make
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.obj: ../esp-idf/components/esp_rom/patches/esp_rom_tjpgd.c
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.obj"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.obj -MF CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.obj.d -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.obj -c /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_tjpgd.c

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.i"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_tjpgd.c > CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.i

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.s"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_tjpgd.c -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.s

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/flags.make
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.obj: ../esp-idf/components/esp_rom/patches/esp_rom_efuse.c
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.obj: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.obj"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.obj -MF CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.obj.d -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.obj -c /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_efuse.c

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.i"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_efuse.c > CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.i

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.s"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && /home/alon/.espressif/tools/riscv32-esp-elf/esp-2021r2-patch4-8.4.0/riscv32-esp-elf/bin/riscv32-esp-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alon/github/awtrix/esp-idf/components/esp_rom/patches/esp_rom_efuse.c -o CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.s

# Object files for target __idf_esp_rom
__idf_esp_rom_OBJECTS = \
"CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.obj" \
"CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.obj" \
"CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.obj" \
"CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.obj" \
"CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.obj"

# External object files for target __idf_esp_rom
__idf_esp_rom_EXTERNAL_OBJECTS =

esp-idf/esp_rom/libesp_rom.a: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_crc.c.obj
esp-idf/esp_rom/libesp_rom.a: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_sys.c.obj
esp-idf/esp_rom/libesp_rom.a: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_uart.c.obj
esp-idf/esp_rom/libesp_rom.a: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_tjpgd.c.obj
esp-idf/esp_rom/libesp_rom.a: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/patches/esp_rom_efuse.c.obj
esp-idf/esp_rom/libesp_rom.a: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/build.make
esp-idf/esp_rom/libesp_rom.a: esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alon/github/awtrix/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C static library libesp_rom.a"
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_rom.dir/cmake_clean_target.cmake
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_esp_rom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/build: esp-idf/esp_rom/libesp_rom.a
.PHONY : esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/build

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/clean:
	cd /home/alon/github/awtrix/build/esp-idf/esp_rom && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_rom.dir/cmake_clean.cmake
.PHONY : esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/clean

esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/depend:
	cd /home/alon/github/awtrix/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alon/github/awtrix /home/alon/github/awtrix/esp-idf/components/esp_rom /home/alon/github/awtrix/build /home/alon/github/awtrix/build/esp-idf/esp_rom /home/alon/github/awtrix/build/esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/esp_rom/CMakeFiles/__idf_esp_rom.dir/depend

