#pragma once

#ifdef DAVINCIENGINE_EXPORTS
#define DAVINCI_API __declspec(dllexport)
#else
#define DAVINCI_API __declspec(dllimport)
#endif