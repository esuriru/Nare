set(PROJECT_NAME Nare)

################################################################################
# Source groups
################################################################################
set(Nare
    "src/Nare.h"
    "src/nrpch.cpp"
    "src/nrpch.h"

    "src/Nare/Core/Application.cpp"
    "src/Nare/Core/Application.h"
    "src/Nare/Core/Core.h"
    "src/Nare/Core/Entry.hpp"
    "src/Nare/Core/Log.cpp"
    "src/Nare/Core/Log.h"
    "src/Nare/Core/Window.h"
    "src/Nare/Core/Logger.h"
    "src/Nare/Core/Logger.cpp"
    "src/Nare/Core/Layer.cpp"
    "src/Nare/Core/Layer.h"
    "src/Nare/Core/LayerStack.h"
    "src/Nare/Core/LayerStack.cpp"
    "src/Nare/Core/Input.h"
    "src/Nare/Core/Input.cpp"
    "src/Nare/Core/Keycodes.h"
    "src/Nare/Core/MouseButtonCodes.h"
    "src/Nare/Core/Timestep.h"



    "src/Nare/Events/ApplicationEvent.h"
    "src/Nare/Events/Event.h"
    "src/Nare/Events/EventDispatcher.h"
    "src/Nare/Events/KeyEvent.h"
    "src/Nare/Events/MouseEvent.h"

    "src/Nare/Mathf/Mathf.h"
    "src/Nare/Mathf/Vector2.cpp"
    "src/Nare/Mathf/Vector2.h"
    "src/Nare/Mathf/Vector3.cpp"
    "src/Nare/Mathf/Vector3.h"
    "src/Nare/Mathf/Vector4.cpp"
    "src/Nare/Mathf/Vector4.h"
    "src/Nare/Mathf/Matrix4x4.h"
    "src/Nare/Mathf/Matrix4x4.cpp"
    "src/Nare/Mathf/Quaternion.h"
    "src/Nare/Mathf/Quaternion.cpp"

    "src/Nare/Platform/Windows/WindowsWindow.cpp"
    "src/Nare/Platform/Windows/WindowsInput.cpp"
    "src/Nare/Platform/Windows/WindowsInput.h"

    # OpenGL specific
    "src/Nare/Platform/OpenGL/OpenGLContext.h"
    "src/Nare/Platform/OpenGL/OpenGLContext.cpp"
    "src/Nare/Platform/OpenGL/OpenGLBuffer.h"
    "src/Nare/Platform/OpenGL/OpenGLBuffer.cpp"
    "src/Nare/Platform/OpenGL/OpenGLVertexArray.h"
    "src/Nare/Platform/OpenGL/OpenGLVertexArray.cpp"
    "src/Nare/Platform/OpenGL/OpenGLRendererAPI.h"
    "src/Nare/Platform/OpenGL/OpenGLRendererAPI.cpp"

    # Renderer
    "src/Nare/Renderer/GraphicsContext.h"
    "src/Nare/Renderer/Shader.h"
    "src/Nare/Renderer/Shader.cpp"
    "src/Nare/Renderer/Buffer.h"
    "src/Nare/Renderer/Buffer.cpp"
    "src/Nare/Renderer/Renderer.h"
    "src/Nare/Renderer/Renderer.cpp"
    "src/Nare/Renderer/RendererAPI.h"
    "src/Nare/Renderer/RendererAPI.cpp"
    "src/Nare/Renderer/VertexArray.h"
    "src/Nare/Renderer/VertexArray.cpp"
    "src/Nare/Renderer/RenderCommand.h"
    "src/Nare/Renderer/RenderCommand.cpp"

    # Utility
    "src/Nare/Utils/Singleton.h"

    # Scene
    "src/Nare/Scene/Scene.h"
    "src/Nare/Scene/Scene.cpp"
    "src/Nare/Scene/Component.h"
    "src/Nare/Scene/IComponentArray.h"
    "src/Nare/Scene/ComponentArray.h"
    "src/Nare/Scene/ComponentManager.h"
    "src/Nare/Scene/System.h"
    "src/Nare/Scene/SystemManager.h"
    "src/Nare/Scene/Coordinator.h"
    "src/Nare/Scene/Coordinator.cpp"
    "src/Nare/Scene/Entity.h"
    "src/Nare/Scene/Entity.cpp"
    

)

set(ALL_FILES
    ${Nare}
)

# Arrange each file into it's own folder's filter
foreach(source IN LISTS Nare)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "$source")
endforeach()


################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE 
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/src/nrpch.h>"
)


use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Nare)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)

################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/${PROJECT_NAME}"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/${PROJECT_NAME}"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"

        # GLFW
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLAD"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "NR_PLATFORM_WINDOWS;"
        "$<$<CONFIG:Debug>:"
			"NR_ENABLE_ASSERTS"
		">"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE;"
        "GLFW_INCLUDE_NONE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF;
                /INCREMENTAL:NO
            >
            /DEBUG;
            /SUBSYSTEM:CONSOLE
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /SUBSYSTEM:CONSOLE
        )
    endif()
endif()

# The nitty gritty
target_link_libraries(${PROJECT_NAME} PRIVATE
	glfw
    GLAD
    opengl32
)
