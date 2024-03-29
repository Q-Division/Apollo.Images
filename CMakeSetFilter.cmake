cmake_minimum_required (VERSION 3.0)

function(SetFilter list srcroot)
	foreach(source IN ITEMS ${list})
		#message("${source}")
		get_filename_component(ext "${source}" EXT)
		get_filename_component(source_path "${source}" PATH)
		
		file(RELATIVE_PATH source_path_rel "${srcroot}" "${source_path}")
		#message("${source_path_rel}")
		
		if(ext STREQUAL ".h")
			set(source_path_rel "Include/${source_path_rel}")
		else()
			set(source_path_rel "Source/${source_path_rel}")
		endif()
		string(REPLACE "/" "\\" group_path "${source_path_rel}")
		
		if(ext STREQUAL ".h")
			message("Header: ${source}")
			source_group(${group_path} FILES "${source}")
		else()
			message("Source: ${source}\tExt: ${ext}")
			source_group(${group_path} FILES "${source}")
		endif()
	endforeach()
endfunction()
