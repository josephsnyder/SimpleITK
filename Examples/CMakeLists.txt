
include_directories ( ${SimpleITK_INCLUDE_DIR} )

# Add individual cxx executables
add_executable ( SimpleGaussian SimpleGaussian.cxx )
target_link_libraries ( SimpleGaussian ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )

add_executable ( ITKIntegration ITKIntegration.cxx )
target_link_libraries ( ITKIntegration ${ITK_LIBRARIES} ${SimpleITK_LIBRARIES} )

# Add individual c# executables
if( WRAP_CSHARP )
  csharp_add_executable(
    SimpleGaussianCSharp
    SimpleITKCSharpManaged.dll
    ${CMAKE_CURRENT_SOURCE_DIR}/SimpleGaussian.cs
  )
endif( WRAP_CSHARP )

#
# Go into testing subdirs
#
subdirs(Segmentation)
