set(ModuleName App)

#Includes
set(Module${ModuleName}_Includes ${XD_ROOT_PATH}/_mod/App/)

#Sources
set(Module${ModuleName}_Sources 
    ${XD_ROOT_PATH}/_mod/App/App.cpp
)

message(============Module Info=============)
message("Module Name : ${ModuleName}")
message("Module Includes : ${Module${ModuleName}_Includes}")
message("Module Sources : ${Module${ModuleName}_Sources}")
message(====================================)