# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sjp/webserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sjp/webserver/build

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/FileInfo.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/FileInfo.cpp.o: ../FileInfo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sjp/webserver/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/FileInfo.cpp.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/FileInfo.cpp.o -c /home/sjp/webserver/FileInfo.cpp

CMakeFiles/test.dir/FileInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/FileInfo.cpp.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sjp/webserver/FileInfo.cpp > CMakeFiles/test.dir/FileInfo.cpp.i

CMakeFiles/test.dir/FileInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/FileInfo.cpp.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sjp/webserver/FileInfo.cpp -o CMakeFiles/test.dir/FileInfo.cpp.s

CMakeFiles/test.dir/FileInfo.cpp.o.requires:
.PHONY : CMakeFiles/test.dir/FileInfo.cpp.o.requires

CMakeFiles/test.dir/FileInfo.cpp.o.provides: CMakeFiles/test.dir/FileInfo.cpp.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/FileInfo.cpp.o.provides.build
.PHONY : CMakeFiles/test.dir/FileInfo.cpp.o.provides

CMakeFiles/test.dir/FileInfo.cpp.o.provides.build: CMakeFiles/test.dir/FileInfo.cpp.o

CMakeFiles/test.dir/test.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/test.cc.o: ../test.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sjp/webserver/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/test.cc.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/test.cc.o -c /home/sjp/webserver/test.cc

CMakeFiles/test.dir/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/test.cc.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sjp/webserver/test.cc > CMakeFiles/test.dir/test.cc.i

CMakeFiles/test.dir/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/test.cc.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sjp/webserver/test.cc -o CMakeFiles/test.dir/test.cc.s

CMakeFiles/test.dir/test.cc.o.requires:
.PHONY : CMakeFiles/test.dir/test.cc.o.requires

CMakeFiles/test.dir/test.cc.o.provides: CMakeFiles/test.dir/test.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/test.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/test.cc.o.provides

CMakeFiles/test.dir/test.cc.o.provides.build: CMakeFiles/test.dir/test.cc.o

CMakeFiles/test.dir/httpconn.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/httpconn.cc.o: ../httpconn.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sjp/webserver/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/httpconn.cc.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/httpconn.cc.o -c /home/sjp/webserver/httpconn.cc

CMakeFiles/test.dir/httpconn.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/httpconn.cc.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sjp/webserver/httpconn.cc > CMakeFiles/test.dir/httpconn.cc.i

CMakeFiles/test.dir/httpconn.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/httpconn.cc.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sjp/webserver/httpconn.cc -o CMakeFiles/test.dir/httpconn.cc.s

CMakeFiles/test.dir/httpconn.cc.o.requires:
.PHONY : CMakeFiles/test.dir/httpconn.cc.o.requires

CMakeFiles/test.dir/httpconn.cc.o.provides: CMakeFiles/test.dir/httpconn.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/httpconn.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/httpconn.cc.o.provides

CMakeFiles/test.dir/httpconn.cc.o.provides.build: CMakeFiles/test.dir/httpconn.cc.o

CMakeFiles/test.dir/tool.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/tool.cc.o: ../tool.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sjp/webserver/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/tool.cc.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/tool.cc.o -c /home/sjp/webserver/tool.cc

CMakeFiles/test.dir/tool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/tool.cc.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sjp/webserver/tool.cc > CMakeFiles/test.dir/tool.cc.i

CMakeFiles/test.dir/tool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/tool.cc.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sjp/webserver/tool.cc -o CMakeFiles/test.dir/tool.cc.s

CMakeFiles/test.dir/tool.cc.o.requires:
.PHONY : CMakeFiles/test.dir/tool.cc.o.requires

CMakeFiles/test.dir/tool.cc.o.provides: CMakeFiles/test.dir/tool.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/tool.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/tool.cc.o.provides

CMakeFiles/test.dir/tool.cc.o.provides.build: CMakeFiles/test.dir/tool.cc.o

CMakeFiles/test.dir/webserver.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/webserver.cpp.o: ../webserver.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sjp/webserver/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/webserver.cpp.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/webserver.cpp.o -c /home/sjp/webserver/webserver.cpp

CMakeFiles/test.dir/webserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/webserver.cpp.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sjp/webserver/webserver.cpp > CMakeFiles/test.dir/webserver.cpp.i

CMakeFiles/test.dir/webserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/webserver.cpp.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sjp/webserver/webserver.cpp -o CMakeFiles/test.dir/webserver.cpp.s

CMakeFiles/test.dir/webserver.cpp.o.requires:
.PHONY : CMakeFiles/test.dir/webserver.cpp.o.requires

CMakeFiles/test.dir/webserver.cpp.o.provides: CMakeFiles/test.dir/webserver.cpp.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/webserver.cpp.o.provides.build
.PHONY : CMakeFiles/test.dir/webserver.cpp.o.provides

CMakeFiles/test.dir/webserver.cpp.o.provides.build: CMakeFiles/test.dir/webserver.cpp.o

CMakeFiles/test.dir/TcpServer.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/TcpServer.cc.o: ../TcpServer.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sjp/webserver/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/TcpServer.cc.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/TcpServer.cc.o -c /home/sjp/webserver/TcpServer.cc

CMakeFiles/test.dir/TcpServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/TcpServer.cc.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sjp/webserver/TcpServer.cc > CMakeFiles/test.dir/TcpServer.cc.i

CMakeFiles/test.dir/TcpServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/TcpServer.cc.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sjp/webserver/TcpServer.cc -o CMakeFiles/test.dir/TcpServer.cc.s

CMakeFiles/test.dir/TcpServer.cc.o.requires:
.PHONY : CMakeFiles/test.dir/TcpServer.cc.o.requires

CMakeFiles/test.dir/TcpServer.cc.o.provides: CMakeFiles/test.dir/TcpServer.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/TcpServer.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/TcpServer.cc.o.provides

CMakeFiles/test.dir/TcpServer.cc.o.provides.build: CMakeFiles/test.dir/TcpServer.cc.o

CMakeFiles/test.dir/lst_timer.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/lst_timer.cc.o: ../lst_timer.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sjp/webserver/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/lst_timer.cc.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/lst_timer.cc.o -c /home/sjp/webserver/lst_timer.cc

CMakeFiles/test.dir/lst_timer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/lst_timer.cc.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sjp/webserver/lst_timer.cc > CMakeFiles/test.dir/lst_timer.cc.i

CMakeFiles/test.dir/lst_timer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/lst_timer.cc.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sjp/webserver/lst_timer.cc -o CMakeFiles/test.dir/lst_timer.cc.s

CMakeFiles/test.dir/lst_timer.cc.o.requires:
.PHONY : CMakeFiles/test.dir/lst_timer.cc.o.requires

CMakeFiles/test.dir/lst_timer.cc.o.provides: CMakeFiles/test.dir/lst_timer.cc.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/lst_timer.cc.o.provides.build
.PHONY : CMakeFiles/test.dir/lst_timer.cc.o.provides

CMakeFiles/test.dir/lst_timer.cc.o.provides.build: CMakeFiles/test.dir/lst_timer.cc.o

CMakeFiles/test.dir/FileUtil.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/FileUtil.cpp.o: ../FileUtil.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sjp/webserver/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/FileUtil.cpp.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/FileUtil.cpp.o -c /home/sjp/webserver/FileUtil.cpp

CMakeFiles/test.dir/FileUtil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/FileUtil.cpp.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sjp/webserver/FileUtil.cpp > CMakeFiles/test.dir/FileUtil.cpp.i

CMakeFiles/test.dir/FileUtil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/FileUtil.cpp.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sjp/webserver/FileUtil.cpp -o CMakeFiles/test.dir/FileUtil.cpp.s

CMakeFiles/test.dir/FileUtil.cpp.o.requires:
.PHONY : CMakeFiles/test.dir/FileUtil.cpp.o.requires

CMakeFiles/test.dir/FileUtil.cpp.o.provides: CMakeFiles/test.dir/FileUtil.cpp.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/FileUtil.cpp.o.provides.build
.PHONY : CMakeFiles/test.dir/FileUtil.cpp.o.provides

CMakeFiles/test.dir/FileUtil.cpp.o.provides.build: CMakeFiles/test.dir/FileUtil.cpp.o

CMakeFiles/test.dir/Config.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/Config.cpp.o: ../Config.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/sjp/webserver/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test.dir/Config.cpp.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test.dir/Config.cpp.o -c /home/sjp/webserver/Config.cpp

CMakeFiles/test.dir/Config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/Config.cpp.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/sjp/webserver/Config.cpp > CMakeFiles/test.dir/Config.cpp.i

CMakeFiles/test.dir/Config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/Config.cpp.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/sjp/webserver/Config.cpp -o CMakeFiles/test.dir/Config.cpp.s

CMakeFiles/test.dir/Config.cpp.o.requires:
.PHONY : CMakeFiles/test.dir/Config.cpp.o.requires

CMakeFiles/test.dir/Config.cpp.o.provides: CMakeFiles/test.dir/Config.cpp.o.requires
	$(MAKE) -f CMakeFiles/test.dir/build.make CMakeFiles/test.dir/Config.cpp.o.provides.build
.PHONY : CMakeFiles/test.dir/Config.cpp.o.provides

CMakeFiles/test.dir/Config.cpp.o.provides.build: CMakeFiles/test.dir/Config.cpp.o

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/FileInfo.cpp.o" \
"CMakeFiles/test.dir/test.cc.o" \
"CMakeFiles/test.dir/httpconn.cc.o" \
"CMakeFiles/test.dir/tool.cc.o" \
"CMakeFiles/test.dir/webserver.cpp.o" \
"CMakeFiles/test.dir/TcpServer.cc.o" \
"CMakeFiles/test.dir/lst_timer.cc.o" \
"CMakeFiles/test.dir/FileUtil.cpp.o" \
"CMakeFiles/test.dir/Config.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS = \
"/home/sjp/webserver/bundle.o"

test: CMakeFiles/test.dir/FileInfo.cpp.o
test: CMakeFiles/test.dir/test.cc.o
test: CMakeFiles/test.dir/httpconn.cc.o
test: CMakeFiles/test.dir/tool.cc.o
test: CMakeFiles/test.dir/webserver.cpp.o
test: CMakeFiles/test.dir/TcpServer.cc.o
test: CMakeFiles/test.dir/lst_timer.cc.o
test: CMakeFiles/test.dir/FileUtil.cpp.o
test: CMakeFiles/test.dir/Config.cpp.o
test: ../bundle.o
test: CMakeFiles/test.dir/build.make
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test
.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/requires: CMakeFiles/test.dir/FileInfo.cpp.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/test.cc.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/httpconn.cc.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/tool.cc.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/webserver.cpp.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/TcpServer.cc.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/lst_timer.cc.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/FileUtil.cpp.o.requires
CMakeFiles/test.dir/requires: CMakeFiles/test.dir/Config.cpp.o.requires
.PHONY : CMakeFiles/test.dir/requires

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /home/sjp/webserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sjp/webserver /home/sjp/webserver /home/sjp/webserver/build /home/sjp/webserver/build /home/sjp/webserver/build/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

