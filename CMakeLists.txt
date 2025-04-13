cmake_minimum_required(VERSION 3.10)
project(NodeImageEditor)

set(CMAKE_CXX_STANDARD 17)

# OpenCV
find_package(OpenCV REQUIRED)

# GLFW
# GLFW (Homebrew way)
find_package(glfw3 REQUIRED)


# OpenGL
find_package(OpenGL REQUIRED)
link_directories(/opt/homebrew/opt/glfw/lib)

# ImGui
include_directories(imgui)
include_directories(imgui/backends)
include_directories(/opt/homebrew/opt/glfw/include)
file(GLOB IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

#nodes
file(GLOB NODE_SOURCES nodes/*.cpp)

#graph fucntions
file(GLOB GRAPH_SORUCES graph/*.cpp)

# smkflow
include_directories(smkflow/include)
file(GLOB SMKFLOW_SOURCES smkflow/src/*.cpp)

# Source
file(GLOB SOURCES
    main.cpp
    ${IMGUI_SOURCES}
    ${SMKFLOW_SOURCES}
)

add_executable(NodeImageEditor
  main.cpp
  graph/GraphExecutor.cpp
  ${IMGUI_SOURCES}
  ${SMKFLOW_SOURCES}
  ${NODE_SOURCES}
  ${GRAPH_SOURCES}
)

# Link libraries
target_include_directories(NodeImageEditor PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(NodeImageEditor
    ${OpenCV_LIBS}
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
    glfw
)