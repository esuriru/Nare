cmake_minimum_required(VERSION 3.0...3.20 FATAL_ERROR)

project(GLFW VERSION 3.3.8 LANGUAGES C)

set(CMAKE_LEGACY_CYGWIN_WIN32 OFF)

if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif()

if (POLICY CMP0069)
    cmake_policy(SET CMP0069 NEW)
endif()

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" ON)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" ON)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" ON)
option(GLFW_INSTALL "Generate installation target" ON)
option(GLFW_VULKAN_STATIC "Assume the Vulkan loader is linked with the application" OFF)

include(GNUInstallDirs)
include(CMakeDependentOption)

cmake_dependent_option(GLFW_USE_OSMESA "Use OSMesa for offscreen context creation" OFF
                       "UNIX" OFF)
cmake_dependent_option(GLFW_USE_HYBRID_HPG "Force use of high-performance GPU on hybrid systems" OFF
                       "WIN32" OFF)
cmake_dependent_option(GLFW_USE_WAYLAND "Use Wayland for window creation" OFF
                       "UNIX;NOT APPLE" OFF)
cmake_dependent_option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC runtime library DLL" ON
                       "MSVC" OFF)

if (BUILD_SHARED_LIBS)
    set(_GLFW_BUILD_DLL 1)
endif()

if (BUILD_SHARED_LIBS AND UNIX)
    # On Unix-like systems, shared libraries can use the soname system.
    set(GLFW_LIB_NAME glfw)
else()
    set(GLFW_LIB_NAME glfw3)
endif()

if (GLFW_VULKAN_STATIC)
    if (BUILD_SHARED_LIBS)
        # If you absolutely must do this, remove this line and add the Vulkan
        # loader static library via the CMAKE_SHARED_LINKER_FLAGS
        message(FATAL_ERROR "You are trying to link the Vulkan loader static library into the GLFW shared library")
    endif()
    set(_GLFW_VULKAN_STATIC 1)
endif()

list(APPEND CMAKE_MODULE_PATH "${GLFW_SOURCE_DIR}/CMake/modules")

find_package(Threads REQUIRED)

if (GLFW_BUILD_DOCS)
    set(DOXYGEN_SKIP_DOT TRUE)
    find_package(Doxygen)
endif()

#--------------------------------------------------------------------
# Apply Microsoft C runtime library option
# This is here because it also applies to tests and examples
#--------------------------------------------------------------------
if (MSVC)
    if (MSVC90)
        # Workaround for VS 2008 not shipping with the DirectX 9 SDK
        include(CheckIncludeFile)
        check_include_file(dinput.h DINPUT_H_FOUND)
        if (NOT DINPUT_H_FOUND)
            message(FATAL_ERROR "DirectX 9 headers not found; install DirectX 9 SDK")
        endif()
        # Workaround for VS 2008 not shipping with stdint.h
        list(APPEND glfw_INCLUDE_DIRS "${GLFW_SOURCE_DIR}/deps/vs2008")
    endif()
endif()

if (MSVC AND NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
    if (CMAKE_VERSION VERSION_LESS 3.15)
        foreach (flag CMAKE_C_FLAGS
                      CMAKE_C_FLAGS_DEBUG
                      CMAKE_C_FLAGS_RELEASE
                      CMAKE_C_FLAGS_MINSIZEREL
                      CMAKE_C_FLAGS_RELWITHDEBINFO)

            if (flag MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            endif()
            if (flag MATCHES "/MDd")
                string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
            endif()

        endforeach()
    else()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif()
endif()

if (MINGW)
    # Workaround for legacy MinGW not providing XInput and DirectInput
    include(CheckIncludeFile)

    check_include_file(dinput.h DINPUT_H_FOUND)
    check_include_file(xinput.h XINPUT_H_FOUND)
    if (NOT DINPUT_H_FOUND OR NOT XINPUT_H_FOUND)
        list(APPEND glfw_INCLUDE_DIRS "${GLFW_SOURCE_DIR}/deps/mingw")
    endif()

    # Enable link-time exploit mitigation features enabled by default on MSVC
    include(CheckCCompilerFlag)

    # Compatibility with data execution prevention (DEP)
    set(CMAKE_REQUIRED_FLAGS "-Wl,--nxcompat")
    check_c_compiler_flag("" _GLFW_HAS_DEP)
    if (_GLFW_HAS_DEP)
        set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--nxcompat ${CMAKE_SHARED_LINKER_FLAGS}")
    endif()

    # Compatibility with address space layout randomization (ASLR)
    set(CMAKE_REQUIRED_FLAGS "-Wl,--dynamicbase")
    check_c_compiler_flag("" _GLFW_HAS_ASLR)
    if (_GLFW_HAS_ASLR)
        set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--dynamicbase ${CMAKE_SHARED_LINKER_FLAGS}")
    endif()

    # Compatibility with 64-bit address space layout randomization (ASLR)
    set(CMAKE_REQUIRED_FLAGS "-Wl,--high-entropy-va")
    check_c_compiler_flag("" _GLFW_HAS_64ASLR)
    if (_GLFW_HAS_64ASLR)
        set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--high-entropy-va ${CMAKE_SHARED_LINKER_FLAGS}")
    endif()

    # Clear flags again to avoid breaking later tests
    set(CMAKE_REQUIRED_FLAGS)
endif()

#--------------------------------------------------------------------
# Detect and select backend APIs
#--------------------------------------------------------------------
if (GLFW_USE_WAYLAND)
    set(_GLFW_WAYLAND 1)
    message(STATUS "Using Wayland for window creation")
elseif (GLFW_USE_OSMESA)
    set(_GLFW_OSMESA 1)
    message(STATUS "Using OSMesa for headless context creation")
elseif (WIN32)
    set(_GLFW_WIN32 1)
    message(STATUS "Using Win32 for window creation")
elseif (APPLE)
    set(_GLFW_COCOA 1)
    message(STATUS "Using Cocoa for window creation")
elseif (UNIX)
    set(_GLFW_X11 1)
    message(STATUS "Using X11 for window creation")
else()
    message(FATAL_ERROR "No supported platform was detected")
endif()

#--------------------------------------------------------------------
# Find and add Unix math and time libraries
#--------------------------------------------------------------------
if (UNIX AND NOT APPLE)
    find_library(RT_LIBRARY rt)
    mark_as_advanced(RT_LIBRARY)
    if (RT_LIBRARY)
        list(APPEND glfw_LIBRARIES "${RT_LIBRARY}")
        list(APPEND glfw_PKG_LIBS "-lrt")
    endif()

    find_library(MATH_LIBRARY m)
    mark_as_advanced(MATH_LIBRARY)
    if (MATH_LIBRARY)
        list(APPEND glfw_LIBRARIES "${MATH_LIBRARY}")
        list(APPEND glfw_PKG_LIBS "-lm")
    endif()

    if (CMAKE_DL_LIBS)
        list(APPEND glfw_LIBRARIES "${CMAKE_DL_LIBS}")
        list(APPEND glfw_PKG_LIBS "-l${CMAKE_DL_LIBS}")
    endif()
endif()

#--------------------------------------------------------------------
# Use Win32 for window creation
#--------------------------------------------------------------------
if (_GLFW_WIN32)

    list(APPEND glfw_PKG_LIBS "-lgdi32")

    if (GLFW_USE_HYBRID_HPG)
        set(_GLFW_USE_HYBRID_HPG 1)
    endif()
endif()

#--------------------------------------------------------------------
# Use X11 for window creation
#--------------------------------------------------------------------
if (_GLFW_X11)

    find_package(X11 REQUIRED)

    list(APPEND glfw_PKG_DEPS "x11")

    # Set up library and include paths
    list(APPEND glfw_INCLUDE_DIRS "${X11_X11_INCLUDE_PATH}")
    list(APPEND glfw_LIBRARIES "${X11_X11_LIB}" "${CMAKE_THREAD_LIBS_INIT}")

    # Check for XRandR (modern resolution switching and gamma control)
    if (NOT X11_Xrandr_INCLUDE_PATH)
        message(FATAL_ERROR "RandR headers not found; install libxrandr development package")
    endif()

    # Check for Xinerama (legacy multi-monitor support)
    if (NOT X11_Xinerama_INCLUDE_PATH)
        message(FATAL_ERROR "Xinerama headers not found; install libxinerama development package")
    endif()

    # Check for Xkb (X keyboard extension)
    if (NOT X11_Xkb_INCLUDE_PATH)
        message(FATAL_ERROR "XKB headers not found; install X11 development package")
    endif()

    # Check for Xcursor (cursor creation from RGBA images)
    if (NOT X11_Xcursor_INCLUDE_PATH)
        message(FATAL_ERROR "Xcursor headers not found; install libxcursor development package")
    endif()

    # Check for XInput (modern HID input)
    if (NOT X11_Xi_INCLUDE_PATH)
        message(FATAL_ERROR "XInput headers not found; install libxi development package")
    endif()

    list(APPEND glfw_INCLUDE_DIRS "${X11_Xrandr_INCLUDE_PATH}"
                                  "${X11_Xinerama_INCLUDE_PATH}"
                                  "${X11_Xkb_INCLUDE_PATH}"
                                  "${X11_Xcursor_INCLUDE_PATH}"
                                  "${X11_Xi_INCLUDE_PATH}")
endif()

#--------------------------------------------------------------------
# Use Wayland for window creation
#--------------------------------------------------------------------
if (_GLFW_WAYLAND)
    find_package(ECM REQUIRED NO_MODULE)
    list(APPEND CMAKE_MODULE_PATH "${ECM_MODULE_PATH}")

    find_package(Wayland REQUIRED Client Cursor Egl)
    find_package(WaylandScanner REQUIRED)
    find_package(WaylandProtocols 1.15 REQUIRED)

    list(APPEND glfw_PKG_DEPS "wayland-client")

    list(APPEND glfw_INCLUDE_DIRS "${Wayland_INCLUDE_DIRS}")
    list(APPEND glfw_LIBRARIES "${Wayland_LIBRARIES}" "${CMAKE_THREAD_LIBS_INIT}")

    find_package(XKBCommon REQUIRED)
    list(APPEND glfw_INCLUDE_DIRS "${XKBCOMMON_INCLUDE_DIRS}")

    include(CheckIncludeFiles)
    include(CheckFunctionExists)
    check_function_exists(memfd_create HAVE_MEMFD_CREATE)

    if (NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
        find_package(EpollShim)
        if (EPOLLSHIM_FOUND)
            list(APPEND glfw_INCLUDE_DIRS "${EPOLLSHIM_INCLUDE_DIRS}")
            list(APPEND glfw_LIBRARIES "${EPOLLSHIM_LIBRARIES}")
        endif()
    endif()
endif()

#--------------------------------------------------------------------
# Use OSMesa for offscreen context creation
#--------------------------------------------------------------------
if (_GLFW_OSMESA)
    find_package(OSMesa REQUIRED)
    list(APPEND glfw_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}")
endif()

#--------------------------------------------------------------------
# Use Cocoa for window creation and NSOpenGL for context creation
#--------------------------------------------------------------------
if (_GLFW_COCOA)

    list(APPEND glfw_LIBRARIES
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreFoundation")

    set(glfw_PKG_DEPS "")
    set(glfw_PKG_LIBS "-framework Cocoa -framework IOKit -framework CoreFoundation")
endif()

#--------------------------------------------------------------------
# Add the Vulkan loader as a dependency if necessary
#--------------------------------------------------------------------
if (GLFW_VULKAN_STATIC)
    list(APPEND glfw_PKG_DEPS "vulkan")
endif()

#--------------------------------------------------------------------
# Export GLFW library dependencies
#--------------------------------------------------------------------
foreach(arg ${glfw_PKG_DEPS})
    set(GLFW_PKG_DEPS "${GLFW_PKG_DEPS} ${arg}")
endforeach()
foreach(arg ${glfw_PKG_LIBS})
    set(GLFW_PKG_LIBS "${GLFW_PKG_LIBS} ${arg}")
endforeach()

#--------------------------------------------------------------------
# Create generated files
#--------------------------------------------------------------------
include(CMakePackageConfigHelpers)

set(GLFW_CONFIG_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/glfw3")

configure_package_config_file(src/glfw3Config.cmake.in
                              src/glfw3Config.cmake
                              INSTALL_DESTINATION "${GLFW_CONFIG_PATH}"
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(src/glfw3ConfigVersion.cmake
                                 VERSION ${GLFW_VERSION}
                                 COMPATIBILITY SameMajorVersion)

configure_file(src/glfw_config.h.in src/glfw_config.h @ONLY)

configure_file(src/glfw3.pc.in src/glfw3.pc @ONLY)

#--------------------------------------------------------------------
# Add subdirectories
#--------------------------------------------------------------------
add_subdirectory(src)

if (GLFW_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (GLFW_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (DOXYGEN_FOUND AND GLFW_BUILD_DOCS)
    add_subdirectory(docs)
endif()

#--------------------------------------------------------------------
# Install files other than the library
# The library is installed by src/CMakeLists.txt
#--------------------------------------------------------------------
if (GLFW_INSTALL)
    install(DIRECTORY include/GLFW DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            FILES_MATCHING PATTERN glfw3.h PATTERN glfw3native.h)

    install(FILES "${GLFW_BINARY_DIR}/src/glfw3Config.cmake"
                  "${GLFW_BINARY_DIR}/src/glfw3ConfigVersion.cmake"
            DESTINATION "${GLFW_CONFIG_PATH}")

    install(EXPORT glfwTargets FILE glfw3Targets.cmake
            EXPORT_LINK_INTERFACE_LIBRARIES
            DESTINATION "${GLFW_CONFIG_PATH}")
    install(FILES "${GLFW_BINARY_DIR}/src/glfw3.pc"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

    # Only generate this target if no higher-level project already has
    if (NOT TARGET uninstall)
        configure_file(cmake_uninstall.cmake.in
                       cmake_uninstall.cmake IMMEDIATE @ONLY)

        add_custom_target(uninstall
                          "${CMAKE_COMMAND}" -P
                          "${GLFW_BINARY_DIR}/cmake_uninstall.cmake")
        set_target_properties(uninstall PROPERTIES FOLDER "GLFW3")
    endif()
endif()



























set(PROJECT_NAME GLFW)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "docs/footer.html"
    "docs/header.html"
    "docs/html/build_8dox.html"
    "docs/html/build_guide.html"
    "docs/html/compat_8dox.html"
    "docs/html/compat_guide.html"
    "docs/html/compile_8dox.html"
    "docs/html/compile_guide.html"
    "docs/html/context_8dox.html"
    "docs/html/context_guide.html"
    "docs/html/deprecated.html"
    "docs/html/dir_1dfd43b3952c5bc1ba15d15b12afff7b.html"
    "docs/html/dir_4351554941a2744586042c1cf3cf139a.html"
    "docs/html/dir_f6ba4c3dca55a8d4e7d63c8235e0ad43.html"
    "docs/html/dir_fda32cf7bec00275262cb8799a618f76.html"
    "docs/html/files.html"
    "docs/html/glfw3_8h.html"
    "docs/html/glfw3_8h_source.html"
    "docs/html/glfw3native_8h.html"
    "docs/html/glfw3native_8h_source.html"
    "docs/html/group__buttons.html"
    "docs/html/group__context.html"
    "docs/html/group__errors.html"
    "docs/html/group__gamepad__axes.html"
    "docs/html/group__gamepad__buttons.html"
    "docs/html/group__hat__state.html"
    "docs/html/group__init.html"
    "docs/html/group__input.html"
    "docs/html/group__joysticks.html"
    "docs/html/group__keys.html"
    "docs/html/group__mods.html"
    "docs/html/group__monitor.html"
    "docs/html/group__native.html"
    "docs/html/group__shapes.html"
    "docs/html/group__vulkan.html"
    "docs/html/group__window.html"
    "docs/html/index.html"
    "docs/html/input_8dox.html"
    "docs/html/input_guide.html"
    "docs/html/internal_8dox.html"
    "docs/html/internals_guide.html"
    "docs/html/intro_8dox.html"
    "docs/html/intro_guide.html"
    "docs/html/main_8dox.html"
    "docs/html/modules.html"
    "docs/html/monitor_8dox.html"
    "docs/html/monitor_guide.html"
    "docs/html/moving_8dox.html"
    "docs/html/moving_guide.html"
    "docs/html/news.html"
    "docs/html/news_8dox.html"
    "docs/html/pages.html"
    "docs/html/quick_8dox.html"
    "docs/html/quick_guide.html"
    "docs/html/search/all_0.html"
    "docs/html/search/all_1.html"
    "docs/html/search/all_10.html"
    "docs/html/search/all_11.html"
    "docs/html/search/all_2.html"
    "docs/html/search/all_3.html"
    "docs/html/search/all_4.html"
    "docs/html/search/all_5.html"
    "docs/html/search/all_6.html"
    "docs/html/search/all_7.html"
    "docs/html/search/all_8.html"
    "docs/html/search/all_9.html"
    "docs/html/search/all_a.html"
    "docs/html/search/all_b.html"
    "docs/html/search/all_c.html"
    "docs/html/search/all_d.html"
    "docs/html/search/all_e.html"
    "docs/html/search/all_f.html"
    "docs/html/search/classes_0.html"
    "docs/html/search/defines_0.html"
    "docs/html/search/files_0.html"
    "docs/html/search/files_1.html"
    "docs/html/search/files_2.html"
    "docs/html/search/files_3.html"
    "docs/html/search/files_4.html"
    "docs/html/search/files_5.html"
    "docs/html/search/files_6.html"
    "docs/html/search/files_7.html"
    "docs/html/search/files_8.html"
    "docs/html/search/functions_0.html"
    "docs/html/search/groups_0.html"
    "docs/html/search/groups_1.html"
    "docs/html/search/groups_2.html"
    "docs/html/search/groups_3.html"
    "docs/html/search/groups_4.html"
    "docs/html/search/groups_5.html"
    "docs/html/search/groups_6.html"
    "docs/html/search/groups_7.html"
    "docs/html/search/groups_8.html"
    "docs/html/search/groups_9.html"
    "docs/html/search/groups_a.html"
    "docs/html/search/nomatches.html"
    "docs/html/search/pages_0.html"
    "docs/html/search/pages_1.html"
    "docs/html/search/pages_2.html"
    "docs/html/search/pages_3.html"
    "docs/html/search/pages_4.html"
    "docs/html/search/pages_5.html"
    "docs/html/search/pages_6.html"
    "docs/html/search/pages_7.html"
    "docs/html/search/pages_8.html"
    "docs/html/search/pages_9.html"
    "docs/html/search/pages_a.html"
    "docs/html/search/typedefs_0.html"
    "docs/html/search/variables_0.html"
    "docs/html/search/variables_1.html"
    "docs/html/search/variables_2.html"
    "docs/html/search/variables_3.html"
    "docs/html/search/variables_4.html"
    "docs/html/search/variables_5.html"
    "docs/html/search/variables_6.html"
    "docs/html/search/variables_7.html"
    "docs/html/structGLFWgamepadstate.html"
    "docs/html/structGLFWgammaramp.html"
    "docs/html/structGLFWimage.html"
    "docs/html/structGLFWvidmode.html"
    "docs/html/vulkan_8dox.html"
    "docs/html/vulkan_guide.html"
    "docs/html/window_8dox.html"
    "docs/html/window_guide.html"
)
source_group("" FILES ${no_group_source_files})

set(Header_Files
    "deps/getopt.h"
    "deps/glad/gl.h"
    "deps/glad/khrplatform.h"
    "deps/glad/vk_platform.h"
    "deps/glad/vulkan.h"
    "deps/linmath.h"
    "deps/mingw/_mingw_dxhelper.h"
    "deps/mingw/dinput.h"
    "deps/mingw/xinput.h"
    "deps/nuklear.h"
    "deps/nuklear_glfw_gl2.h"
    "deps/stb_image_write.h"
    "deps/tinycthread.h"
    "deps/vs2008/stdint.h"
    "include/GLFW/glfw3.h"
    "include/GLFW/glfw3native.h"
    "src/cocoa_joystick.h"
    "src/cocoa_platform.h"
    "src/egl_context.h"
    "src/glx_context.h"
    "src/internal.h"
    "src/linux_joystick.h"
    "src/mappings.h"
    "src/nsgl_context.h"
    "src/null_joystick.h"
    "src/null_platform.h"
    "src/osmesa_context.h"
    "src/posix_thread.h"
    "src/posix_time.h"
    "src/wgl_context.h"
    "src/win32_joystick.h"
    "src/win32_platform.h"
    "src/wl_platform.h"
    "src/x11_platform.h"
    "src/xkb_unicode.h"
)
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
    "deps/getopt.c"
    "deps/glad_gl.c"
    "deps/glad_vulkan.c"
    "deps/tinycthread.c"
    "examples/boing.c"
    "examples/gears.c"
    "examples/heightmap.c"
    "examples/offscreen.c"
    "examples/particles.c"
    "examples/sharing.c"
    "examples/simple.c"
    "examples/splitview.c"
    "examples/wave.c"
    "src/cocoa_time.c"
    "src/context.c"
    "src/egl_context.c"
    "src/glx_context.c"
    "src/init.c"
    "src/input.c"
    "src/linux_joystick.c"
    "src/monitor.c"
    "src/null_init.c"
    "src/null_joystick.c"
    "src/null_monitor.c"
    "src/null_window.c"
    "src/osmesa_context.c"
    "src/posix_thread.c"
    "src/posix_time.c"
    "src/vulkan.c"
    "src/wgl_context.c"
    "src/win32_init.c"
    "src/win32_joystick.c"
    "src/win32_monitor.c"
    "src/win32_thread.c"
    "src/win32_time.c"
    "src/win32_window.c"
    "src/window.c"
    "src/wl_init.c"
    "src/wl_monitor.c"
    "src/wl_window.c"
    "src/x11_init.c"
    "src/x11_monitor.c"
    "src/x11_window.c"
    "src/xkb_unicode.c"
    "tests/clipboard.c"
    "tests/cursor.c"
    "tests/empty.c"
    "tests/events.c"
    "tests/gamma.c"
    "tests/glfwinfo.c"
    "tests/icon.c"
    "tests/iconify.c"
    "tests/inputlag.c"
    "tests/joysticks.c"
    "tests/monitors.c"
    "tests/msaa.c"
    "tests/opacity.c"
    "tests/reopen.c"
    "tests/tearing.c"
    "tests/threads.c"
    "tests/timeout.c"
    "tests/title.c"
    "tests/triangle-vulkan.c"
    "tests/windows.c"
)
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
    ${no_group_source_files}
    ${Header_Files}
    ${Source_Files}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/${PROJECT_NAME}/"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/${PROJECT_NAME}/"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
            MultiThreadedDebugDLL
        >
        $<$<CONFIG:Release>:
            MultiThreadedDLL
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "_LIB"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            /W3;
            /Zi;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            /DEBUG:FULL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /MACHINE:X86;
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

