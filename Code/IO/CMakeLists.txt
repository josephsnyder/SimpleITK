file ( GLOB SimpleITKIOSource *.cxx *.h )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )
add_library ( SimpleITKIO ${SimpleITKIOSource} )
target_link_libraries ( SimpleITKIO SimpleITKCommon ITKIO )



# Add custom command that will delete java files which need to be rebuilt when changes
# are made to IO
if( WRAP_JAVA )
  add_custom_command(
    TARGET SimpleITIO
    POST_BUILD
    COMMENT "Cleaning java build..."
    COMMAND cmake -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/org/itk/simple/*.java
    COMMAND cmake -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/build/org/itk/simple/*.class
    COMMAND cmake -E remove -f ${SimpleITK_BINARY_DIR}/Wrapping/SimpleITKJAVA_wrap.cxx
  )
endif()
