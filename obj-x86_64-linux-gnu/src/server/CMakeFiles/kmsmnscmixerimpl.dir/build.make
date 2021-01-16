# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/andrey/mnscmodule/2/desktop--KurentoGstreamer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu

# Include any dependencies generated for this target.
include src/server/CMakeFiles/kmsmnscmixerimpl.dir/depend.make

# Include the progress variables for this target.
include src/server/CMakeFiles/kmsmnscmixerimpl.dir/progress.make

# Include the compile flags for this target's objects.
include src/server/CMakeFiles/kmsmnscmixerimpl.dir/flags.make

src/server/cpp_server_internal.generated: ../src/server/interface/mnscmixer.kmd.json
src/server/cpp_server_internal.generated: ../src/server/interface/mnscmixer.mnscmixer.kmd.json
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating cpp_server_internal.generated, implementation/generated-cpp/SerializerExpanderMnscmixer.cpp, implementation/generated-cpp/mnscmixerImplInternal.cpp, implementation/generated-cpp/mnscmixerImplFactory.hpp"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/cmake -E touch cpp_server_internal.generated
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/kurento-module-creator -c /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/implementation/generated-cpp -r /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/src/server/interface -dr /usr/share/kurento/modules -dr /usr/share/kurento/modules -it cpp_server_internal

src/server/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp: src/server/cpp_server_internal.generated
	@$(CMAKE_COMMAND) -E touch_nocreate src/server/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp

src/server/implementation/generated-cpp/mnscmixerImplInternal.cpp: src/server/cpp_server_internal.generated
	@$(CMAKE_COMMAND) -E touch_nocreate src/server/implementation/generated-cpp/mnscmixerImplInternal.cpp

src/server/implementation/generated-cpp/mnscmixerImplFactory.hpp: src/server/cpp_server_internal.generated
	@$(CMAKE_COMMAND) -E touch_nocreate src/server/implementation/generated-cpp/mnscmixerImplFactory.hpp

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o: src/server/CMakeFiles/kmsmnscmixerimpl.dir/flags.make
src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o: ../src/server/implementation/objects/mnscmixerImpl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o -c /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/src/server/implementation/objects/mnscmixerImpl.cpp

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.i"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/src/server/implementation/objects/mnscmixerImpl.cpp > CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.i

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.s"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/src/server/implementation/objects/mnscmixerImpl.cpp -o CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.s

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o.requires:

.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o.requires

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o.provides: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o.requires
	$(MAKE) -f src/server/CMakeFiles/kmsmnscmixerimpl.dir/build.make src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o.provides.build
.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o.provides

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o.provides.build: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o


src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o: src/server/CMakeFiles/kmsmnscmixerimpl.dir/flags.make
src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o: src/server/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o -c /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.i"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp > CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.i

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.s"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp -o CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.s

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o.requires:

.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o.requires

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o.provides: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o.requires
	$(MAKE) -f src/server/CMakeFiles/kmsmnscmixerimpl.dir/build.make src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o.provides.build
.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o.provides

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o.provides.build: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o


src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o: src/server/CMakeFiles/kmsmnscmixerimpl.dir/flags.make
src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o: src/server/implementation/generated-cpp/mnscmixerImplInternal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o -c /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/implementation/generated-cpp/mnscmixerImplInternal.cpp

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.i"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/implementation/generated-cpp/mnscmixerImplInternal.cpp > CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.i

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.s"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/implementation/generated-cpp/mnscmixerImplInternal.cpp -o CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.s

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o.requires:

.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o.requires

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o.provides: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o.requires
	$(MAKE) -f src/server/CMakeFiles/kmsmnscmixerimpl.dir/build.make src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o.provides.build
.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o.provides

src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o.provides.build: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o


# Object files for target kmsmnscmixerimpl
kmsmnscmixerimpl_OBJECTS = \
"CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o" \
"CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o" \
"CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o"

# External object files for target kmsmnscmixerimpl
kmsmnscmixerimpl_EXTERNAL_OBJECTS =

src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: src/server/CMakeFiles/kmsmnscmixerimpl.dir/build.make
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: /usr/lib/x86_64-linux-gnu/libkmselementsimpl.so
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: /usr/lib/x86_64-linux-gnu/libkmsfiltersimpl.so
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: /usr/lib/x86_64-linux-gnu/libkmselementsimpl.so
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: src/server/libkmsmnscmixerinterface.a
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: /usr/lib/x86_64-linux-gnu/libkmselementsimpl.so
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: /usr/lib/x86_64-linux-gnu/libkmsfiltersimpl.so
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: /usr/lib/x86_64-linux-gnu/libkmselementsimpl.so
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: /usr/lib/x86_64-linux-gnu/libkmsfiltersimpl.so
src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68: src/server/CMakeFiles/kmsmnscmixerimpl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libkmsmnscmixerimpl.so"
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kmsmnscmixerimpl.dir/link.txt --verbose=$(VERBOSE)
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && $(CMAKE_COMMAND) -E cmake_symlink_library "libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68" libkmsmnscmixerimpl.so.0 libkmsmnscmixerimpl.so

src/server/libkmsmnscmixerimpl.so.0: src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68
	@$(CMAKE_COMMAND) -E touch_nocreate src/server/libkmsmnscmixerimpl.so.0

src/server/libkmsmnscmixerimpl.so: src/server/libkmsmnscmixerimpl.so.0.0.1~7.ga0e3f68
	@$(CMAKE_COMMAND) -E touch_nocreate src/server/libkmsmnscmixerimpl.so

# Rule to build all files generated by this target.
src/server/CMakeFiles/kmsmnscmixerimpl.dir/build: src/server/libkmsmnscmixerimpl.so

.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/build

src/server/CMakeFiles/kmsmnscmixerimpl.dir/requires: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/objects/mnscmixerImpl.cpp.o.requires
src/server/CMakeFiles/kmsmnscmixerimpl.dir/requires: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp.o.requires
src/server/CMakeFiles/kmsmnscmixerimpl.dir/requires: src/server/CMakeFiles/kmsmnscmixerimpl.dir/implementation/generated-cpp/mnscmixerImplInternal.cpp.o.requires

.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/requires

src/server/CMakeFiles/kmsmnscmixerimpl.dir/clean:
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server && $(CMAKE_COMMAND) -P CMakeFiles/kmsmnscmixerimpl.dir/cmake_clean.cmake
.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/clean

src/server/CMakeFiles/kmsmnscmixerimpl.dir/depend: src/server/cpp_server_internal.generated
src/server/CMakeFiles/kmsmnscmixerimpl.dir/depend: src/server/implementation/generated-cpp/SerializerExpanderMnscmixer.cpp
src/server/CMakeFiles/kmsmnscmixerimpl.dir/depend: src/server/implementation/generated-cpp/mnscmixerImplInternal.cpp
src/server/CMakeFiles/kmsmnscmixerimpl.dir/depend: src/server/implementation/generated-cpp/mnscmixerImplFactory.hpp
	cd /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrey/mnscmodule/2/desktop--KurentoGstreamer /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/src/server /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server /home/andrey/mnscmodule/2/desktop--KurentoGstreamer/obj-x86_64-linux-gnu/src/server/CMakeFiles/kmsmnscmixerimpl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/server/CMakeFiles/kmsmnscmixerimpl.dir/depend

