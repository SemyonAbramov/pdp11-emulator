project (PDP-11-emulator)
cmake_minimum_required (VERSION 2.8)
cmake_policy(SET CMP0015 NEW) # relative pathes given to link_directories

list (APPEND DIR_LIST
		cpu
		decode
		emulation
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

foreach (DIR ${DIR_LIST})
	aux_source_directory ("${DIR}" EMU_SOURCES)
endforeach (DIR)

list (APPEND SOURCES main.c)


add_executable (pdp_emulator ${EMU_SOURCES} ${SOURCES})

