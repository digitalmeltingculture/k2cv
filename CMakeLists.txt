CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.1)

PROJECT(SERVER_PROJECT)

SET(opencv "/usr/local/include/opencv" )
SET(opencv2 "/usr/local/include/opencv2")
SET(libfreenect2Dir "/opt/libfreenect2" )

#SET(freenect2_DIR ${libfreenect2Dir}/build)
#FIND_PACKAGE(freenect2 REQUIRED) # Costruisce il contenuto di ${freenect2_INCLUDE_DIR} >>--> include 
								 # ${Protonect_LIBRARIES} >>--> opzioni link 

SET(DEPENDS_DIR ${libfreenect2Dir}depends CACHE STRING "Dependency directory")

# The example build system is standalone and will work out-of-tree with these files copied
#SET(freenect2_ROOT_DIR "/opt/libfreenect2")

IF(TARGET freenect2)
  MESSAGE(STATUS "Using in-tree freenect2 target")
  SET(freenect2_LIBRARIES freenect2)
  SET(freenect2_DLLS ${LIBFREENECT2_DLLS})
ELSE()
  MESSAGE( STATUS "DLLS" ${LIBFREENECT2_DLLS})
  SET(freenect2_DIR ${libfreenect2Dir}/build)
  FIND_PACKAGE(freenect2 REQUIRED)
  # Out-of-tree build will have to have DLLs manually copied.
ENDIF()

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

SET(dirInclude ${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(dirCpp ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET(dirBin ${CMAKE_CURRENT_SOURCE_DIR}/bin)

FILE(GLOB fileSrc ${dirCpp} src/*cpp)  

INCLUDE_DIRECTORIES(${dirInclude} ${libxml2} ${opencv} ${opencv2} ${freenect2_INCLUDE_DIR} /usr/local/include)
# Potrebbe essere nescessario aggiungere find_package(OpenCV) 

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dirBin})
ADD_EXECUTABLE(server  ${fileSrc} )

TARGET_LINK_LIBRARIES(server opencv_highgui opencv_core opencv_imgproc opencv_videoio opencv_imgcodecs opencv_video pthread ${freenect2_LIBRARIES})

#MESSAGE(STATUS "")
#MESSAGE(STATUS "")
#MESSAGE(STATUS "File Esterni Compilati")
#MESSAGE(STATUS "")
#FOREACH(infileName ${File_SRC})
#    MESSAGE(STATUS "File: ${infileName}")
#ENDFOREACH(infileName)
#MESSAGE(STATUS "")

