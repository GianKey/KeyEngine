#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Vulkan::LayerSettings" for configuration "RelWithDebInfo"
set_property(TARGET Vulkan::LayerSettings APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Vulkan::LayerSettings PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/VulkanLayerSettings.lib"
  )

list(APPEND _cmake_import_check_targets Vulkan::LayerSettings )
list(APPEND _cmake_import_check_files_for_Vulkan::LayerSettings "${_IMPORT_PREFIX}/lib/VulkanLayerSettings.lib" )

# Import target "Vulkan::SafeStruct" for configuration "RelWithDebInfo"
set_property(TARGET Vulkan::SafeStruct APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Vulkan::SafeStruct PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/VulkanSafeStruct.lib"
  )

list(APPEND _cmake_import_check_targets Vulkan::SafeStruct )
list(APPEND _cmake_import_check_files_for_Vulkan::SafeStruct "${_IMPORT_PREFIX}/lib/VulkanSafeStruct.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
