# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\maksi\CLionProjects\YearProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\maksi\CLionProjects\YearProject\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/NomProjet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NomProjet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NomProjet.dir/flags.make

CMakeFiles/NomProjet.dir/main.cpp.obj: CMakeFiles/NomProjet.dir/flags.make
CMakeFiles/NomProjet.dir/main.cpp.obj: CMakeFiles/NomProjet.dir/includes_CXX.rsp
CMakeFiles/NomProjet.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\maksi\CLionProjects\YearProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NomProjet.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\NomProjet.dir\main.cpp.obj -c C:\Users\maksi\CLionProjects\YearProject\main.cpp

CMakeFiles/NomProjet.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NomProjet.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\maksi\CLionProjects\YearProject\main.cpp > CMakeFiles\NomProjet.dir\main.cpp.i

CMakeFiles/NomProjet.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NomProjet.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\maksi\CLionProjects\YearProject\main.cpp -o CMakeFiles\NomProjet.dir\main.cpp.s

# Object files for target NomProjet
NomProjet_OBJECTS = \
"CMakeFiles/NomProjet.dir/main.cpp.obj"

# External object files for target NomProjet
NomProjet_EXTERNAL_OBJECTS =

NomProjet.exe: CMakeFiles/NomProjet.dir/main.cpp.obj
NomProjet.exe: CMakeFiles/NomProjet.dir/build.make
NomProjet.exe: D:/Libraries/SFML/lib/libsfml-audio-s-d.a
NomProjet.exe: D:/Libraries/SFML/lib/libsfml-graphics-s-d.a
NomProjet.exe: D:/Libraries/SFML/lib/libsfml-window-s-d.a
NomProjet.exe: D:/Libraries/SFML/lib/libsfml-system-s-d.a
NomProjet.exe: D:/Libraries/SFML/lib/libfreetype.a
NomProjet.exe: D:/Libraries/SFML/lib/libjpeg.a
NomProjet.exe: D:/Libraries/SFML/lib/libopenal32.a
NomProjet.exe: D:/Libraries/SFML/lib/libFLAC.a
NomProjet.exe: D:/Libraries/SFML/lib/libvorbisenc.a
NomProjet.exe: D:/Libraries/SFML/lib/libvorbisfile.a
NomProjet.exe: D:/Libraries/SFML/lib/libvorbis.a
NomProjet.exe: D:/Libraries/SFML/lib/libogg.a
NomProjet.exe: D:/Libraries/SFML/lib/libopenal32.a
NomProjet.exe: D:/Libraries/SFML/lib/libFLAC.a
NomProjet.exe: D:/Libraries/SFML/lib/libvorbisenc.a
NomProjet.exe: D:/Libraries/SFML/lib/libvorbisfile.a
NomProjet.exe: D:/Libraries/SFML/lib/libvorbis.a
NomProjet.exe: D:/Libraries/SFML/lib/libogg.a
NomProjet.exe: CMakeFiles/NomProjet.dir/linklibs.rsp
NomProjet.exe: CMakeFiles/NomProjet.dir/objects1.rsp
NomProjet.exe: CMakeFiles/NomProjet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\maksi\CLionProjects\YearProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable NomProjet.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\NomProjet.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NomProjet.dir/build: NomProjet.exe

.PHONY : CMakeFiles/NomProjet.dir/build

CMakeFiles/NomProjet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\NomProjet.dir\cmake_clean.cmake
.PHONY : CMakeFiles/NomProjet.dir/clean

CMakeFiles/NomProjet.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\maksi\CLionProjects\YearProject C:\Users\maksi\CLionProjects\YearProject C:\Users\maksi\CLionProjects\YearProject\cmake-build-debug C:\Users\maksi\CLionProjects\YearProject\cmake-build-debug C:\Users\maksi\CLionProjects\YearProject\cmake-build-debug\CMakeFiles\NomProjet.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NomProjet.dir/depend

