# Install script for directory: E:/Project/GameProject/Enginer/Library/Vulkan-Utility-Libraries

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/VUL")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/scripts/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/src/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/include/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/vulkan" TYPE DIRECTORY FILES "E:/Project/GameProject/Enginer/Library/Vulkan-Utility-Libraries/include/vulkan/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/src/layer/Debug/VulkanLayerSettings.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/src/layer/Release/VulkanLayerSettings.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/src/layer/MinSizeRel/VulkanLayerSettings.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/src/layer/RelWithDebInfo/VulkanLayerSettings.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/src/vulkan/Debug/VulkanSafeStruct.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/src/vulkan/Release/VulkanSafeStruct.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/src/vulkan/MinSizeRel/VulkanSafeStruct.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/src/vulkan/RelWithDebInfo/VulkanSafeStruct.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries/VulkanUtilityLibraries-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries/VulkanUtilityLibraries-targets.cmake"
         "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/CMakeFiles/Export/002fcec190a570ef6af2b558f7afd86d/VulkanUtilityLibraries-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries/VulkanUtilityLibraries-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries/VulkanUtilityLibraries-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries" TYPE FILE FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/CMakeFiles/Export/002fcec190a570ef6af2b558f7afd86d/VulkanUtilityLibraries-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries" TYPE FILE FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/CMakeFiles/Export/002fcec190a570ef6af2b558f7afd86d/VulkanUtilityLibraries-targets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries" TYPE FILE FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/CMakeFiles/Export/002fcec190a570ef6af2b558f7afd86d/VulkanUtilityLibraries-targets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries" TYPE FILE FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/CMakeFiles/Export/002fcec190a570ef6af2b558f7afd86d/VulkanUtilityLibraries-targets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries" TYPE FILE FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/CMakeFiles/Export/002fcec190a570ef6af2b558f7afd86d/VulkanUtilityLibraries-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/VulkanUtilityLibraries" TYPE FILE FILES "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/VulkanUtilityLibrariesConfig.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "E:/Project/GameProject/Enginer/Engine/KeyEngine/KeyEngine/vendor/ImGuizmo/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
