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
CMAKE_SOURCE_DIR = /home/miro/cs480/cs480Georgiev/PA5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/miro/cs480/cs480Georgiev/PA5/build

# Include any dependencies generated for this target.
include CMakeFiles/PA5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PA5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PA5.dir/flags.make

CMakeFiles/PA5.dir/src/camera.cpp.o: CMakeFiles/PA5.dir/flags.make
CMakeFiles/PA5.dir/src/camera.cpp.o: ../src/camera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miro/cs480/cs480Georgiev/PA5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PA5.dir/src/camera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA5.dir/src/camera.cpp.o -c /home/miro/cs480/cs480Georgiev/PA5/src/camera.cpp

CMakeFiles/PA5.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA5.dir/src/camera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miro/cs480/cs480Georgiev/PA5/src/camera.cpp > CMakeFiles/PA5.dir/src/camera.cpp.i

CMakeFiles/PA5.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA5.dir/src/camera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miro/cs480/cs480Georgiev/PA5/src/camera.cpp -o CMakeFiles/PA5.dir/src/camera.cpp.s

CMakeFiles/PA5.dir/src/engine.cpp.o: CMakeFiles/PA5.dir/flags.make
CMakeFiles/PA5.dir/src/engine.cpp.o: ../src/engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miro/cs480/cs480Georgiev/PA5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PA5.dir/src/engine.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA5.dir/src/engine.cpp.o -c /home/miro/cs480/cs480Georgiev/PA5/src/engine.cpp

CMakeFiles/PA5.dir/src/engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA5.dir/src/engine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miro/cs480/cs480Georgiev/PA5/src/engine.cpp > CMakeFiles/PA5.dir/src/engine.cpp.i

CMakeFiles/PA5.dir/src/engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA5.dir/src/engine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miro/cs480/cs480Georgiev/PA5/src/engine.cpp -o CMakeFiles/PA5.dir/src/engine.cpp.s

CMakeFiles/PA5.dir/src/graphics.cpp.o: CMakeFiles/PA5.dir/flags.make
CMakeFiles/PA5.dir/src/graphics.cpp.o: ../src/graphics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miro/cs480/cs480Georgiev/PA5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PA5.dir/src/graphics.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA5.dir/src/graphics.cpp.o -c /home/miro/cs480/cs480Georgiev/PA5/src/graphics.cpp

CMakeFiles/PA5.dir/src/graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA5.dir/src/graphics.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miro/cs480/cs480Georgiev/PA5/src/graphics.cpp > CMakeFiles/PA5.dir/src/graphics.cpp.i

CMakeFiles/PA5.dir/src/graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA5.dir/src/graphics.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miro/cs480/cs480Georgiev/PA5/src/graphics.cpp -o CMakeFiles/PA5.dir/src/graphics.cpp.s

CMakeFiles/PA5.dir/src/main.cpp.o: CMakeFiles/PA5.dir/flags.make
CMakeFiles/PA5.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miro/cs480/cs480Georgiev/PA5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PA5.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA5.dir/src/main.cpp.o -c /home/miro/cs480/cs480Georgiev/PA5/src/main.cpp

CMakeFiles/PA5.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA5.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miro/cs480/cs480Georgiev/PA5/src/main.cpp > CMakeFiles/PA5.dir/src/main.cpp.i

CMakeFiles/PA5.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA5.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miro/cs480/cs480Georgiev/PA5/src/main.cpp -o CMakeFiles/PA5.dir/src/main.cpp.s

CMakeFiles/PA5.dir/src/object.cpp.o: CMakeFiles/PA5.dir/flags.make
CMakeFiles/PA5.dir/src/object.cpp.o: ../src/object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miro/cs480/cs480Georgiev/PA5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PA5.dir/src/object.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA5.dir/src/object.cpp.o -c /home/miro/cs480/cs480Georgiev/PA5/src/object.cpp

CMakeFiles/PA5.dir/src/object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA5.dir/src/object.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miro/cs480/cs480Georgiev/PA5/src/object.cpp > CMakeFiles/PA5.dir/src/object.cpp.i

CMakeFiles/PA5.dir/src/object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA5.dir/src/object.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miro/cs480/cs480Georgiev/PA5/src/object.cpp -o CMakeFiles/PA5.dir/src/object.cpp.s

CMakeFiles/PA5.dir/src/shader.cpp.o: CMakeFiles/PA5.dir/flags.make
CMakeFiles/PA5.dir/src/shader.cpp.o: ../src/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miro/cs480/cs480Georgiev/PA5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PA5.dir/src/shader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA5.dir/src/shader.cpp.o -c /home/miro/cs480/cs480Georgiev/PA5/src/shader.cpp

CMakeFiles/PA5.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA5.dir/src/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miro/cs480/cs480Georgiev/PA5/src/shader.cpp > CMakeFiles/PA5.dir/src/shader.cpp.i

CMakeFiles/PA5.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA5.dir/src/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miro/cs480/cs480Georgiev/PA5/src/shader.cpp -o CMakeFiles/PA5.dir/src/shader.cpp.s

CMakeFiles/PA5.dir/src/window.cpp.o: CMakeFiles/PA5.dir/flags.make
CMakeFiles/PA5.dir/src/window.cpp.o: ../src/window.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miro/cs480/cs480Georgiev/PA5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/PA5.dir/src/window.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA5.dir/src/window.cpp.o -c /home/miro/cs480/cs480Georgiev/PA5/src/window.cpp

CMakeFiles/PA5.dir/src/window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA5.dir/src/window.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miro/cs480/cs480Georgiev/PA5/src/window.cpp > CMakeFiles/PA5.dir/src/window.cpp.i

CMakeFiles/PA5.dir/src/window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA5.dir/src/window.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miro/cs480/cs480Georgiev/PA5/src/window.cpp -o CMakeFiles/PA5.dir/src/window.cpp.s

# Object files for target PA5
PA5_OBJECTS = \
"CMakeFiles/PA5.dir/src/camera.cpp.o" \
"CMakeFiles/PA5.dir/src/engine.cpp.o" \
"CMakeFiles/PA5.dir/src/graphics.cpp.o" \
"CMakeFiles/PA5.dir/src/main.cpp.o" \
"CMakeFiles/PA5.dir/src/object.cpp.o" \
"CMakeFiles/PA5.dir/src/shader.cpp.o" \
"CMakeFiles/PA5.dir/src/window.cpp.o"

# External object files for target PA5
PA5_EXTERNAL_OBJECTS =

PA5: CMakeFiles/PA5.dir/src/camera.cpp.o
PA5: CMakeFiles/PA5.dir/src/engine.cpp.o
PA5: CMakeFiles/PA5.dir/src/graphics.cpp.o
PA5: CMakeFiles/PA5.dir/src/main.cpp.o
PA5: CMakeFiles/PA5.dir/src/object.cpp.o
PA5: CMakeFiles/PA5.dir/src/shader.cpp.o
PA5: CMakeFiles/PA5.dir/src/window.cpp.o
PA5: CMakeFiles/PA5.dir/build.make
PA5: /usr/lib/x86_64-linux-gnu/libGLEW.so
PA5: /usr/lib/x86_64-linux-gnu/libGL.so
PA5: /usr/lib/x86_64-linux-gnu/libGLU.so
PA5: /usr/lib/x86_64-linux-gnu/libSDL2main.a
PA5: /usr/lib/x86_64-linux-gnu/libSDL2.so
PA5: CMakeFiles/PA5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/miro/cs480/cs480Georgiev/PA5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable PA5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PA5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PA5.dir/build: PA5

.PHONY : CMakeFiles/PA5.dir/build

CMakeFiles/PA5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PA5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PA5.dir/clean

CMakeFiles/PA5.dir/depend:
	cd /home/miro/cs480/cs480Georgiev/PA5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/miro/cs480/cs480Georgiev/PA5 /home/miro/cs480/cs480Georgiev/PA5 /home/miro/cs480/cs480Georgiev/PA5/build /home/miro/cs480/cs480Georgiev/PA5/build /home/miro/cs480/cs480Georgiev/PA5/build/CMakeFiles/PA5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PA5.dir/depend

