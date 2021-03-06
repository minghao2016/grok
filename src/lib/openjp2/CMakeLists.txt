include_regular_expression("^.*$")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

IF(MSVC)
    SET(CMAKE_CXX_FLAGS "/EHsc")
ENDIF(MSVC)

install( FILES  ${CMAKE_CURRENT_BINARY_DIR}/opj_config.h
 DESTINATION ${GROK_INSTALL_INCLUDE_DIR} COMPONENT Headers)

include_directories(
  ${${GROK_NAMESPACE}_BINARY_DIR}/src/lib/openjp2 # opj_config.h and opj_config_private.h
  ${GROK_SOURCE_DIR}/src/bin/common
  ${GROK_SOURCE_DIR}/src/bin/jp2
)
# Defines the source code for the library
set(GROK_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/Barrier.h
  ${CMAKE_CURRENT_SOURCE_DIR}/BitIO.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/BitIO.h
  ${CMAKE_CURRENT_SOURCE_DIR}/IBitIO.h
  ${CMAKE_CURRENT_SOURCE_DIR}/GrokStream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/GrokStream.h
  ${CMAKE_CURRENT_SOURCE_DIR}/IGrokStream.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dwt_interface.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dwt.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dwt.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dwt53.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dwt53.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dwt97.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dwt97.h
  ${CMAKE_CURRENT_SOURCE_DIR}/event.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/event.h
  ${CMAKE_CURRENT_SOURCE_DIR}/image.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/image.h
  ${CMAKE_CURRENT_SOURCE_DIR}/invert.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/invert.h
  ${CMAKE_CURRENT_SOURCE_DIR}/j2k.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/j2k.h
  ${CMAKE_CURRENT_SOURCE_DIR}/jp2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/jp2.h
  ${CMAKE_CURRENT_SOURCE_DIR}/mem_stream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mem_stream.h
  ${CMAKE_CURRENT_SOURCE_DIR}/mct.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mct.h
  ${CMAKE_CURRENT_SOURCE_DIR}/grok.h
  ${CMAKE_CURRENT_SOURCE_DIR}/grok.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/openjpeg.h
  ${CMAKE_CURRENT_SOURCE_DIR}/grok_clock.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/grok_clock.h
  ${CMAKE_CURRENT_SOURCE_DIR}/overflow_utils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/pi.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/pi.h
  ${CMAKE_CURRENT_SOURCE_DIR}/segmented_stream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/segmented_stream.h
  ${CMAKE_CURRENT_SOURCE_DIR}/tile_buf.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tile_buf.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Tier1.h
  ${CMAKE_CURRENT_SOURCE_DIR}/Tier1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mqc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/mqc.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_factory.cpp  
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_factory.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_interface.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_impl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_impl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_opt_luts.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_luts.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_decode_base.cpp  
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_decode_base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_decode_opt.cpp  
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_decode_opt.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_decode.cpp  
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_decode.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_encode.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/t1_encode.h
  ${CMAKE_CURRENT_SOURCE_DIR}/t2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/t2.h
  ${CMAKE_CURRENT_SOURCE_DIR}/tcd.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tcd.h
  ${CMAKE_CURRENT_SOURCE_DIR}/tgt.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tgt.h
  ${CMAKE_CURRENT_SOURCE_DIR}/util.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/util.h
  ${CMAKE_CURRENT_SOURCE_DIR}/function_list.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/function_list.h
  ${CMAKE_CURRENT_SOURCE_DIR}/grok_codec.h
  ${CMAKE_CURRENT_SOURCE_DIR}/grok_includes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/grok_intmath.h
  ${CMAKE_CURRENT_SOURCE_DIR}/grok_malloc.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/grok_malloc.h
  ${CMAKE_CURRENT_SOURCE_DIR}/vector.h
  ${CMAKE_CURRENT_SOURCE_DIR}/vector.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/minpf_dynamic_library.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/minpf_dynamic_library.h
  ${CMAKE_CURRENT_SOURCE_DIR}/minpf_plugin_manager.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/minpf_plugin_manager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/minpf_common.h
  ${CMAKE_CURRENT_SOURCE_DIR}/minpf_plugin.h
  ${CMAKE_CURRENT_SOURCE_DIR}/plugin_interface.h
  ${CMAKE_CURRENT_SOURCE_DIR}/BlockingQueue.h
  ${CMAKE_CURRENT_SOURCE_DIR}/T1Decoder.h
  ${CMAKE_CURRENT_SOURCE_DIR}/T1Decoder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/T1Encoder.h
  ${CMAKE_CURRENT_SOURCE_DIR}/T1Encoder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ThreadPool.h
  ${CMAKE_CURRENT_SOURCE_DIR}/plugin_bridge.h
  ${CMAKE_CURRENT_SOURCE_DIR}/plugin_bridge.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/RateControl.h
  ${CMAKE_CURRENT_SOURCE_DIR}/RateControl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/RateInfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/RateInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/testing.h
  ${CMAKE_CURRENT_SOURCE_DIR}/EncodedTileData.h
  ${CMAKE_CURRENT_SOURCE_DIR}/EncodedTileData.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/grok_exceptions.h
  ${CMAKE_CURRENT_SOURCE_DIR}/CPUArch.h
  ${CMAKE_CURRENT_SOURCE_DIR}/CPUArch.cpp
)

option(OPJ_DISABLE_TPSOT_FIX "Disable TPsot==TNsot fix. See https://github.com/uclouvain/openjpeg/issues/254." OFF)
if(OPJ_DISABLE_TPSOT_FIX)
  add_definitions(-DOPJ_DISABLE_TPSOT_FIX)
endif()

# Build the library
if (BUILD_PLUGIN_LOADER)
    add_definitions(-DOPJ_BUILD_PLUGIN_LOADER)
endif()
if(WIN32)
  if(BUILD_SHARED_LIBS)
    add_definitions(-DOPJ_EXPORTS)
  else()
    add_definitions(-DOPJ_STATIC)
  endif()
  add_library(${GROK_LIBRARY_NAME} ${GROK_SRCS})
  set(INSTALL_LIBS ${GROK_LIBRARY_NAME})
else()
  # Builds both static and dynamic libs
  add_library(${GROK_LIBRARY_NAME} SHARED ${GROK_SRCS})
  add_library(${GROK_LIBRARY_NAME}_static STATIC ${GROK_SRCS})
  set_target_properties(${GROK_LIBRARY_NAME}_static PROPERTIES OUTPUT_NAME ${GROK_LIBRARY_NAME})
  set(INSTALL_LIBS ${GROK_LIBRARY_NAME} ${GROK_LIBRARY_NAME}_static)
endif()
if(UNIX)
  target_link_libraries(${GROK_LIBRARY_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif()
set_target_properties(${GROK_LIBRARY_NAME} PROPERTIES ${GROK_LIBRARY_PROPERTIES})
if(${CMAKE_VERSION} VERSION_GREATER "2.8.11")
  target_compile_options(${GROK_LIBRARY_NAME} PRIVATE ${GROK_COMPILE_OPTIONS})
endif()

# Install library
install(TARGETS ${INSTALL_LIBS}
  EXPORT GrokTargets
  RUNTIME DESTINATION ${GROK_INSTALL_BIN_DIR} COMPONENT Applications
  LIBRARY DESTINATION ${GROK_INSTALL_LIB_DIR} COMPONENT Libraries
  ARCHIVE DESTINATION ${GROK_INSTALL_LIB_DIR} COMPONENT Libraries
)

# Install includes files
install(FILES openjpeg.h 
  DESTINATION ${GROK_INSTALL_INCLUDE_DIR} COMPONENT Headers
)

if(BUILD_DOC)
# install man page of the library
install(
  FILES       ${GROK_SOURCE_DIR}/doc/man/man3/libopenjp2.3
  DESTINATION ${GROK_INSTALL_MAN_DIR}/man3)
endif()

if(BUILD_LUTS_GENERATOR)
# internal utility to generate t1_luts.h (part of the jp2 lib)
# no need to install:
add_executable(t1_generate_luts t1_generate_luts.cpp)
  if(UNIX)
    target_link_libraries(t1_generate_luts)
  endif()
endif()

# Experimental option; let's how cppcheck performs
# Implementation details:
# I could not figure out how to easily upload a file to CDash. Instead simply
# pretend cppcheck is part of the Build step. Technically cppcheck can even
# output gcc formatted error/warning report
# Another implementation detail: I could not redirect error to the error
# catching mechanism something is busted in cmake 2.8.5, I had to use the
# warning regex to catch them.
if(GROK_CPPCHECK)
  find_package(CPPCHECK REQUIRED)
  foreach(f ${GROK_SRCS})
    # cppcheck complains about too many configuration, pretend to be WIN32:
    add_custom_command(TARGET ${GROK_LIBRARY_NAME}
      COMMAND ${CPPCHECK_EXECUTABLE} -DWIN32 ${f})
  endforeach()
endif()

if(GROK_USE_DSYMUTIL)
  if(BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${GROK_LIBRARY_NAME} POST_BUILD
    COMMAND "dsymutil" "$<TARGET_SONAME_FILE:${GROK_LIBRARY_NAME}>"
    COMMENT "dsymutil $<TARGET_SONAME_FILE:${GROK_LIBRARY_NAME}>"
    DEPENDS ${GROK_LIBRARY_NAME})
  endif()
endif()
