set(ModuleName Solution_Test)
set(ModuleRootPath ${CMAKE_CURRENT_LIST_DIR})

#Includes
set(Module${ModuleName}_Includes 
    ${ModuleRootPath}
    ${XD_ROOT_PATH}/Modules/
)

#Sources
set(Module${ModuleName}_Sources 
    ${ModuleRootPath}/Solution.h
    ${ModuleRootPath}/Solution.cpp
)

#Modules
set(Module${ModuleName}_Dependencies
    Log
)

message(------------------------------------)
message("Module Name : ${ModuleName}")
message("Module Includes : ${Module${ModuleName}_Includes}")
message("Module Sources : ${Module${ModuleName}_Sources}")
message(------------------------------------)