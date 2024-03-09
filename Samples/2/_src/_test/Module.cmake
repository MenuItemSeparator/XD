macro(print_var var)
	message("\n" ${var} = ${${var}} "\n")
endmacro(print_var)

macro(add_module name)

endmacro(add_module)

macro(import_module name)
	set (temp_path "../../${name}")

	file(GLOB temp_headers ${temp_path}/*.h ${temp_path}/win/*.h)
	message(${name}_headers = ${temp_headers})
	set(all_headers ${all_headers} ${temp_headers})

	file(GLOB temp_sources ${temp_path}/*.cpp ${temp_path}/win/*.cpp)
	message(${name}_sources = ${temp_sources})
	set(all_sources ${all_sources} ${temp_sources})

	set(all_dirs ${all_dirs} ${temp_path})

	include(${temp_path}/_module/Module.cmake)

endmacro(import_module)

