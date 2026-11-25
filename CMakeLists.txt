cmake_minimum_required(VERSION 3.16)
project(IvriPlusPlus VERSION 0.2.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

add_library(ivri INTERFACE)
add_library(Ivri::Ivri ALIAS ivri)
set_target_properties(ivri PROPERTIES EXPORT_NAME Ivri)
target_include_directories(ivri INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_compile_features(ivri INTERFACE cxx_std_17)
if(MSVC)
    target_compile_options(ivri INTERFACE /utf-8)
endif()

set(ivri_top_level OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(ivri_top_level ON)
    include(CTest)
endif()
option(IVRI_BUILD_EXAMPLES "Build the Ivri++ examples" ${ivri_top_level})

if(IVRI_BUILD_EXAMPLES)
    foreach(name IN ITEMS 01_basics 02_student_grades 03_hebrew_terminal)
        add_executable(${name} examples/${name}.cpp)
        target_link_libraries(${name} PRIVATE Ivri::Ivri)
    endforeach()

    if(ivri_top_level AND BUILD_TESTING)
        add_test(NAME basics COMMAND 01_basics)
        add_test(NAME student_grades COMMAND 02_student_grades)
        add_test(NAME terminal COMMAND "${CMAKE_COMMAND}"
            "-DAPP=$<TARGET_FILE:03_hebrew_terminal>"
            "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/tests/terminal_input.txt"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/check_terminal.cmake"
        )
    endif()
endif()

set(ivri_cmake_dir "${CMAKE_INSTALL_LIBDIR}/cmake/Ivri")
configure_package_config_file(cmake/IvriConfig.cmake.in IvriConfig.cmake
    INSTALL_DESTINATION "${ivri_cmake_dir}"
)
write_basic_package_version_file(IvriConfigVersion.cmake
    COMPATIBILITY SameMinorVersion
    ARCH_INDEPENDENT
)

install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(TARGETS ivri EXPORT IvriTargets)
install(EXPORT IvriTargets NAMESPACE Ivri:: DESTINATION "${ivri_cmake_dir}")
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/IvriConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/IvriConfigVersion.cmake"
    DESTINATION "${ivri_cmake_dir}"
)
