# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.28
cmake_policy(SET CMP0009 NEW)

# headers at CMakeLists.txt:44 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/CG/opengl-env/opengl-env/include/*.h")
set(OLD_GLOB
  "D:/CG/opengl-env/opengl-env/include/Vertex.h"
  "D:/CG/opengl-env/opengl-env/include/core.h"
  "D:/CG/opengl-env/opengl-env/include/model.h"
  "D:/CG/opengl-env/opengl-env/include/shader.h"
  "D:/CG/opengl-env/opengl-env/include/stb_image.h"
  "D:/CG/opengl-env/opengl-env/include/stb_image_write.h"
  "D:/CG/opengl-env/opengl-env/include/stb_truetype.h"
  "D:/CG/opengl-env/opengl-env/include/texture.h"
  "D:/CG/opengl-env/opengl-env/include/tinyexr.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/CG/opengl-env/opengl-env/cmake-build-debug-visual-studio/CMakeFiles/cmake.verify_globs")
endif()

# headers at CMakeLists.txt:44 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/CG/opengl-env/opengl-env/include/*.hpp")
set(OLD_GLOB
  "D:/CG/opengl-env/opengl-env/include/GLRAII.hpp"
  "D:/CG/opengl-env/opengl-env/include/Game.hpp"
  "D:/CG/opengl-env/opengl-env/include/Image.hpp"
  "D:/CG/opengl-env/opengl-env/include/InputCtl.hpp"
  "D:/CG/opengl-env/opengl-env/include/KeyBinding.hpp"
  "D:/CG/opengl-env/opengl-env/include/OBJ.hpp"
  "D:/CG/opengl-env/opengl-env/include/check_gl.hpp"
  "D:/CG/opengl-env/opengl-env/include/print.hpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/CG/opengl-env/opengl-env/cmake-build-debug-visual-studio/CMakeFiles/cmake.verify_globs")
endif()

# sources at CMakeLists.txt:43 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/CG/opengl-env/opengl-env/src/*.cpp")
set(OLD_GLOB
  "D:/CG/opengl-env/opengl-env/src/main.cpp"
  "D:/CG/opengl-env/opengl-env/src/test.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/CG/opengl-env/opengl-env/cmake-build-debug-visual-studio/CMakeFiles/cmake.verify_globs")
endif()
