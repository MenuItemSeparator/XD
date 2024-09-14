#pragma once
#include <iostream>
#include <string>

#ifdef XD_EXPORTING
    #define XD_ENGINE_API __declspec(dllexport)
#else
    #define XD_ENGINE_API __declspec(dllimport)
#endif

#ifdef XD_BUILD_TYPE_DEBUG
    #define dXD_DEBUG
#endif

#ifdef dXD_DEBUG
    #define mXD_ASSERTM(cond, msg)  if (!(cond)) { std::cout << ">> [Assert " << #cond << " fail] [ " << __FILE__ << " | " << __func__ << " | " << __LINE__ << " ] : " msg << std::endl; __debugbreak(); }
    #define mXD_ASSERT(cond)  if (!(cond)) mXD_ASSERTM(cond, "<<");
    #define mXD_NOT_IMPLEMENTED() mXD_ASSERTM(false, "Not implemented function reached");
#else
    #define mXD_ASSERTM(cond, msg);
    #define mXD_ASSERT(cond);
    #define mXD_NOT_IMPLEMENTED();
#endif

#define dXD_ENGINE_RESOURCE_FOLDER_PATH_STR XD_ENGINE_RESOURCE_FOLDER_PATH

const std::string cXD_ENGINE_RESOURCE_FOLDER_PATH = dXD_ENGINE_RESOURCE_FOLDER_PATH_STR;
