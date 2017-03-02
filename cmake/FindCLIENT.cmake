# Check for the presence of the tesiCris framework
#
# The following variables are set when tesiCris is found:
# 	HAVE_TESICRIS		= Set to true, if tesiCris have been found.
# 	TESICRIS_INCLUDES  	= Include path for the header files of tesiCris
# 	TESICRIS_LIBRARIES	= Link these to use ANTAREX

## -----------------------------------------------------------------------------
## Check for the header files

set( TESICRIS_SOURCE_PATH /home/cris/tesiCris )
set( TESICRIS_BINARY_PATH /home/cris/tesiCris/build )
set( TESICRIS_INSTALL_PATH /usr/local )

# check for the header of the client module
find_path( TESICRIS_CLIENT_INCLUDES tesiCris/framework.hpp PATHS
                    ${TESICRIS_SOURCE_PATH}/framework/client/include
                    /usr/local/include
                    /usr/include
                    ${TESICRIS_INSTALL_PATH}/include
                    ${CMAKE_EXTRA_INCLUDES}
          )

# check for the header of the client module
find_path( TESICRIS_MQTT_INCLUDES MQTTClient.h PATHS
                    /usr/local/include
                    /usr/include
                    ${CMAKE_EXTRA_INCLUDES}
          )

# compose the real list of paths
set( TESICRIS_INCLUDES ${TESICRIS_CLIENT_INCLUDES} ${TESICRIS_MQTT_INCLUDES} )

list( REMOVE_DUPLICATES TESICRIS_INCLUDES )

## -----------------------------------------------------------------------------
## Check for the libraries

# check for the CLIENT library
find_library( CLIENT_LIBRARIES libtesiCris_client.a libtesiCris_client.so tesiCris_client
	PATHS ${TESICRIS_BINARY_PATH}/framework/client ${TESICRIS_INSTALL_PATH}/lib
	NO_DEFAULT_PATH
	)
if( NOT CLIENT_LIBRARIES )
	find_library( MQTT_LIBRARIES libtesiCris_client.a libtesiCris_client.so tesiCris_client
		PATHS /usr/local/lib /usr/lib /lib ${CLIENT_ROOT}
		)
endif( NOT CLIENT_LIBRARIES )

# check for the MQTT library
find_library( MQTT_LIBRARIES lib/libpaho-mqtt3c.so
	PATHS ${MQTT_ROOT}
	NO_DEFAULT_PATH
	)
if( NOT MQTT_LIBRARIES )
	find_library( MQTT_LIBRARIES lib/libpaho-mqtt3c.so
		PATHS /usr/local/lib /usr/lib /lib ${MQTT_ROOT}
		)
endif( NOT MQTT_LIBRARIES )

# append the libraries
set( TESICRIS_LIBRARIES ${CLIENT_LIBRARIES} ${MQTT_LIBRARIES} )

list( REMOVE_DUPLICATES TESICRIS_LIBRARIES )










## -----------------------------------------------------------------------------
## Actions taken when all components have been found

if( TESICRIS_CLIENT_INCLUDES AND MQTT_LIBRARIES )
  set( HAVE_TESICRIS TRUE )
else( TESICRIS_CLIENT_INCLUDES AND MQTT_LIBRARIES )
  if( NOT TESICRIS_FIND_QUIETLY )
    if( NOT TESICRIS_CLIENT_INCLUDES )
      message( STATUS "Unable to find tesiCris header files!" )
    endif( NOT TESICRIS_CLIENT_INCLUDES )
    if( NOT MQTT_LIBRARIES )
      message( STATUS "Unable to find tesiCris library files!" )
    endif( NOT MQTT_LIBRARIES )
  endif( NOT ARGO_FIND_QUIETLY )
endif( TESICRIS_CLIENT_INCLUDES AND MQTT_LIBRARIES )

if( HAVE_TESICRIS )
  if( NOT TESICRIS_FIND_QUIETLY )
    message( STATUS "Found components for tesiCris" )
    message( STATUS "TESICRIS_INCLUDES .... = ${TESICRIS_INCLUDES}" )
    message( STATUS "TESICRIS_LIBRARIES ... = ${TESICRIS_LIBRARIES}" )
  endif( NOT TESICRIS_FIND_QUIETLY )
else( HAVE_TESICRIS )
  if( TESICRIS_FIND_QUIETLY )
    message( FATAL_ERROR "Could not find tesiCris!" )
  endif( TESICRIS_FIND_QUIETLY )
endif( HAVE_TESICRIS )

mark_as_advanced (
  HAVE_TESICRIS
  TESICRIS_INCLUDES
  TESICRIS_LIBRARIES
  )
