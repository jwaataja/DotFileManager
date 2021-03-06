include (CheckIncludeFiles)

if (HAS_GRAPHICS)
	find_package (PkgConfig REQUIRED)
	execute_process (
		COMMAND ${PKG_CONFIG_EXECUTABLE} --variable=glib_compile_resources gio-2.0
		OUTPUT_VARIABLE GLIB_COMPILE_RESOURCES
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	add_custom_command (
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources.c
		DEPENDS res/gdfm.gresource.xml res/ui/mainwindow.glade
		COMMAND ${GLIB_COMPILE_RESOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/res/gdfm.gresource.xml --target=${CMAKE_CURRENT_BINARY_DIR}/resources.c --sourcedir=${CMAKE_CURRENT_SOURCE_DIR}/res --generate-source)
	set_source_files_properties (${CMAKE_CURRENT_BINARY_DIR}/resources.c
		PROPERTIES GENERATED TRUE)
endif (HAS_GRAPHICS)

check_include_files (wordexp.h HAVE_WORDEXP_H)
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
	${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories (${CMAKE_CURRENT_BINARY_DIR})

set (COMMON_SOURCES module.cc moduleaction.cc installaction.cc removeaction.cc
	options.cc shellaction.cc messageaction.cc configfilereader.cc command.cc
	dependencyaction.cc readerenvironment.cc filecheckaction.cc util.cc
	configfilewriter.cc modulefile.cc)

set (DFM_SOURCES dfm.cc dotfilemanager.cc terminalwindow.cc)

set (GDFM_SOURCES gdfm.cc gdfmwindow.cc createmoduledialog.cc messageeditor.cc
	shelleditor.cc modulefileeditor.cc moduleactioneditor.cc
	installactioneditor.cc filecheckeditor.cc removeactioneditor.cc
	dependencyeditor.cc ${CMAKE_CURRENT_BINARY_DIR}/resources.c)

add_library (dfmcommon STATIC ${COMMON_SOURCES})
add_executable (dfm ${DFM_SOURCES})
target_link_libraries (dfm dfmcommon)
install (TARGETS dfm DESTINATION bin)

set_property(TARGET dfm dfmcommon PROPERTY CXX_STANDARD 11)

if (HAS_GRAPHICS)
	add_executable (gdfm ${GDFM_SOURCES})
	target_link_libraries (gdfm dfmcommon)
	set_property(TARGET gdfm PROPERTY CXX_STANDARD 11)

	pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
	include_directories(${GTKMM_INCLUDE_DIRS})
	link_directories(${GTKMM_LIBRARY_DIRS})
	add_definitions(${GTKMM_CFLAGS_OTHER})
	target_link_libraries(gdfm ${GTKMM_LIBRARIES})
	install (TARGETS gdfm DESTINATION bin)
endif (HAS_GRAPHICS)
