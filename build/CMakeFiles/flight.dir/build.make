# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/build-cyh/flight-control

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/build-cyh/flight-control/build

# Include any dependencies generated for this target.
include CMakeFiles/flight.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/flight.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/flight.dir/flags.make

CMakeFiles/flight.dir/main.cpp.o: CMakeFiles/flight.dir/flags.make
CMakeFiles/flight.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/build-cyh/flight-control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/flight.dir/main.cpp.o"
	/home/user/build/openwrt-sdk-rockchip-armv8_gcc-11.2.0_musl.Linux-x86_64/staging_dir/toolchain-aarch64_generic_gcc-11.2.0_musl/bin/aarch64-openwrt-linux-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/flight.dir/main.cpp.o -c /home/user/build-cyh/flight-control/main.cpp

CMakeFiles/flight.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/flight.dir/main.cpp.i"
	/home/user/build/openwrt-sdk-rockchip-armv8_gcc-11.2.0_musl.Linux-x86_64/staging_dir/toolchain-aarch64_generic_gcc-11.2.0_musl/bin/aarch64-openwrt-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/build-cyh/flight-control/main.cpp > CMakeFiles/flight.dir/main.cpp.i

CMakeFiles/flight.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/flight.dir/main.cpp.s"
	/home/user/build/openwrt-sdk-rockchip-armv8_gcc-11.2.0_musl.Linux-x86_64/staging_dir/toolchain-aarch64_generic_gcc-11.2.0_musl/bin/aarch64-openwrt-linux-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/build-cyh/flight-control/main.cpp -o CMakeFiles/flight.dir/main.cpp.s

# Object files for target flight
flight_OBJECTS = \
"CMakeFiles/flight.dir/main.cpp.o"

# External object files for target flight
flight_EXTERNAL_OBJECTS =

flight: CMakeFiles/flight.dir/main.cpp.o
flight: CMakeFiles/flight.dir/build.make
flight: CMakeFiles/flight.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/build-cyh/flight-control/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable flight"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flight.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/flight.dir/build: flight

.PHONY : CMakeFiles/flight.dir/build

CMakeFiles/flight.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/flight.dir/cmake_clean.cmake
.PHONY : CMakeFiles/flight.dir/clean

CMakeFiles/flight.dir/depend:
	cd /home/user/build-cyh/flight-control/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/build-cyh/flight-control /home/user/build-cyh/flight-control /home/user/build-cyh/flight-control/build /home/user/build-cyh/flight-control/build /home/user/build-cyh/flight-control/build/CMakeFiles/flight.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/flight.dir/depend

