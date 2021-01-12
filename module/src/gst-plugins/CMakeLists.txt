include_directories(
  ${GSTREAMER_INCLUDE_DIRS}
  ${GSTREAMER_VIDEO_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${OPENCV_INCLUDE_DIRS}
)

set(MNSCMIXER_SOURCES
  mnscmixer.c
  gstmnscmixer.h
  gstmnscmixer.c
)

add_library(mnscmixer MODULE ${MNSCMIXER_SOURCES})
if(SANITIZERS_ENABLED)
  add_sanitizers(mnscmixer)
endif()

target_link_libraries(mnscmixer
  kmssdpagent
  kmsgstcommons
  ${GSTREAMER_LIBRARIES}
  ${GSTREAMER_VIDEO_LIBRARIES}
  ${OPENCV_LIBRARIES}
)

install(
  TARGETS mnscmixer
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_GST_PLUGINS_DIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
