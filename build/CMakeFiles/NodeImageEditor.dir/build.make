# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/anirudhsony/Downloads/mixar

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/anirudhsony/Downloads/mixar/build

# Include any dependencies generated for this target.
include CMakeFiles/NodeImageEditor.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/NodeImageEditor.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/NodeImageEditor.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NodeImageEditor.dir/flags.make

CMakeFiles/NodeImageEditor.dir/codegen:
.PHONY : CMakeFiles/NodeImageEditor.dir/codegen

CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.o: /Users/anirudhsony/Downloads/mixar/imgui/backends/imgui_impl_glfw.cpp
CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.o -MF CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.o -c /Users/anirudhsony/Downloads/mixar/imgui/backends/imgui_impl_glfw.cpp

CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anirudhsony/Downloads/mixar/imgui/backends/imgui_impl_glfw.cpp > CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.i

CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anirudhsony/Downloads/mixar/imgui/backends/imgui_impl_glfw.cpp -o CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.s

CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.o: /Users/anirudhsony/Downloads/mixar/imgui/backends/imgui_impl_opengl3.cpp
CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.o -MF CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.o -c /Users/anirudhsony/Downloads/mixar/imgui/backends/imgui_impl_opengl3.cpp

CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anirudhsony/Downloads/mixar/imgui/backends/imgui_impl_opengl3.cpp > CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.i

CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anirudhsony/Downloads/mixar/imgui/backends/imgui_impl_opengl3.cpp -o CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.s

CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.o: /Users/anirudhsony/Downloads/mixar/imgui/imgui.cpp
CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.o -MF CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.o -c /Users/anirudhsony/Downloads/mixar/imgui/imgui.cpp

CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anirudhsony/Downloads/mixar/imgui/imgui.cpp > CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.i

CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anirudhsony/Downloads/mixar/imgui/imgui.cpp -o CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.s

CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.o: /Users/anirudhsony/Downloads/mixar/imgui/imgui_demo.cpp
CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.o -MF CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.o -c /Users/anirudhsony/Downloads/mixar/imgui/imgui_demo.cpp

CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anirudhsony/Downloads/mixar/imgui/imgui_demo.cpp > CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.i

CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anirudhsony/Downloads/mixar/imgui/imgui_demo.cpp -o CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.s

CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.o: /Users/anirudhsony/Downloads/mixar/imgui/imgui_draw.cpp
CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.o -MF CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.o -c /Users/anirudhsony/Downloads/mixar/imgui/imgui_draw.cpp

CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anirudhsony/Downloads/mixar/imgui/imgui_draw.cpp > CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.i

CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anirudhsony/Downloads/mixar/imgui/imgui_draw.cpp -o CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.s

CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.o: /Users/anirudhsony/Downloads/mixar/imgui/imgui_tables.cpp
CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.o -MF CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.o -c /Users/anirudhsony/Downloads/mixar/imgui/imgui_tables.cpp

CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anirudhsony/Downloads/mixar/imgui/imgui_tables.cpp > CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.i

CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anirudhsony/Downloads/mixar/imgui/imgui_tables.cpp -o CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.s

CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.o: /Users/anirudhsony/Downloads/mixar/imgui/imgui_widgets.cpp
CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.o -MF CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.o -c /Users/anirudhsony/Downloads/mixar/imgui/imgui_widgets.cpp

CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anirudhsony/Downloads/mixar/imgui/imgui_widgets.cpp > CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.i

CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anirudhsony/Downloads/mixar/imgui/imgui_widgets.cpp -o CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.s

CMakeFiles/NodeImageEditor.dir/main.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/main.cpp.o: /Users/anirudhsony/Downloads/mixar/main.cpp
CMakeFiles/NodeImageEditor.dir/main.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/NodeImageEditor.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/main.cpp.o -MF CMakeFiles/NodeImageEditor.dir/main.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/main.cpp.o -c /Users/anirudhsony/Downloads/mixar/main.cpp

CMakeFiles/NodeImageEditor.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anirudhsony/Downloads/mixar/main.cpp > CMakeFiles/NodeImageEditor.dir/main.cpp.i

CMakeFiles/NodeImageEditor.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anirudhsony/Downloads/mixar/main.cpp -o CMakeFiles/NodeImageEditor.dir/main.cpp.s

CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.o: CMakeFiles/NodeImageEditor.dir/flags.make
CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.o: /Users/anirudhsony/Downloads/mixar/smkflow/src/Graph.cpp
CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.o: CMakeFiles/NodeImageEditor.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.o -MF CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.o.d -o CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.o -c /Users/anirudhsony/Downloads/mixar/smkflow/src/Graph.cpp

CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/anirudhsony/Downloads/mixar/smkflow/src/Graph.cpp > CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.i

CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/anirudhsony/Downloads/mixar/smkflow/src/Graph.cpp -o CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.s

# Object files for target NodeImageEditor
NodeImageEditor_OBJECTS = \
"CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/main.cpp.o" \
"CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.o"

# External object files for target NodeImageEditor
NodeImageEditor_EXTERNAL_OBJECTS =

NodeImageEditor: CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_glfw.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/imgui/backends/imgui_impl_opengl3.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/imgui/imgui.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/imgui/imgui_demo.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/imgui/imgui_draw.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/imgui/imgui_tables.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/imgui/imgui_widgets.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/main.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/smkflow/src/Graph.cpp.o
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/build.make
NodeImageEditor: /opt/homebrew/lib/libopencv_gapi.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_stitching.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_alphamat.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_aruco.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_bgsegm.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_bioinspired.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_ccalib.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_dnn_objdetect.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_dnn_superres.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_dpm.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_face.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_freetype.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_fuzzy.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_hfs.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_img_hash.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_intensity_transform.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_line_descriptor.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_mcc.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_quality.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_rapid.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_reg.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_rgbd.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_saliency.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_sfm.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_signal.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_stereo.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_structured_light.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_superres.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_surface_matching.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_tracking.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_videostab.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_viz.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_wechat_qrcode.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_xfeatures2d.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_xobjdetect.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_xphoto.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libglfw.3.4.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_shape.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_highgui.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_datasets.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_plot.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_text.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_ml.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_phase_unwrapping.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_optflow.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_ximgproc.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_video.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_videoio.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_imgcodecs.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_objdetect.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_calib3d.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_dnn.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_features2d.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_flann.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_photo.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_imgproc.4.11.0.dylib
NodeImageEditor: /opt/homebrew/lib/libopencv_core.4.11.0.dylib
NodeImageEditor: CMakeFiles/NodeImageEditor.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/anirudhsony/Downloads/mixar/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable NodeImageEditor"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NodeImageEditor.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NodeImageEditor.dir/build: NodeImageEditor
.PHONY : CMakeFiles/NodeImageEditor.dir/build

CMakeFiles/NodeImageEditor.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NodeImageEditor.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NodeImageEditor.dir/clean

CMakeFiles/NodeImageEditor.dir/depend:
	cd /Users/anirudhsony/Downloads/mixar/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/anirudhsony/Downloads/mixar /Users/anirudhsony/Downloads/mixar /Users/anirudhsony/Downloads/mixar/build /Users/anirudhsony/Downloads/mixar/build /Users/anirudhsony/Downloads/mixar/build/CMakeFiles/NodeImageEditor.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/NodeImageEditor.dir/depend

