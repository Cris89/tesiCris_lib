###############################################
##      Compiling the framework module       ##
###############################################

set( CLIENT_LIB_NAME "tesiCris_client" )


# -------- Defining the source/header files
set( CLIENT_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( CLIENT_HDR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include )

set( CLIENT_HEADERS ${CLIENT_HDR_PATH}/tesiCris/appStruct.hpp
                    ${CLIENT_HDR_PATH}/tesiCris/framework.hpp
                    ${CLIENT_HDR_PATH}/tesiCris/mqtt.hpp
                    ${CLIENT_HDR_PATH}/tesiCris/topics.hpp
		    ${CLIENT_HDR_PATH}/tesiCris/argoOPs.hpp
		    ${CLIENT_HDR_PATH}/tesiCris/argoManager.hpp
   )

set( CLIENT_SOURCES ${CLIENT_SRC_PATH}/appStruct.cpp
                    ${CLIENT_SRC_PATH}/framework.cpp
                    ${CLIENT_SRC_PATH}/mqtt.cpp
                    ${CLIENT_SRC_PATH}/topics.cpp
		    ${CLIENT_SRC_PATH}/argoOPs.cpp
		    ${CLIENT_SRC_PATH}/argoManager.cpp
   )

# --------  Build the module
include_directories( ${CLIENT_HDR_PATH} ${MQTT_INCLUDES})

if( LIB_STATIC )
	add_library( ${CLIENT_LIB_NAME} STATIC ${CLIENT_SOURCES} ${CLIENT_HEADERS} )
else( LIB_STATIC )
        add_library( ${CLIENT_LIB_NAME} SHARED ${CLIENT_SOURCES} ${CLIENT_HEADERS} )
endif( LIB_STATIC )

target_link_libraries( ${CLIENT_LIB_NAME} ${MQTT_LIBRARIES} )

# ------ Install the module
install( TARGETS ${CLIENT_LIB_NAME} DESTINATION lib )
install( FILES ${CLIENT_HEADERS} DESTINATION include/tesiCris )
