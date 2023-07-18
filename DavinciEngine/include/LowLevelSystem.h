#ifndef LOWLEVELSYSTEM_H
#define LOWLEVELSYSTEM_H

#define MIN(a, b) (((a) < (b)) ? (a) : (b)) 
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MAX_DELTA_TIME 1.0/30.0

#include "SystemTypes.h"

namespace DavinciEngine{
	// Don't worry, these things are going to be defined elsewhere in the engine code!

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Warning message.</summary>
	///
	/// <param name="fmt"> The message.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	extern void Warning(const char *fmt,...);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Log messages.</summary>
	///
	/// <param name="fmt"> The message.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	extern void Log(const char *fmt,...);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Error message.</summary>
	///
	/// <param name="fmt"> The message.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	extern void Error(const char *fmt,...);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Fatal error message followed by engine shutdown.</summary>
	///
	/// <param name="fmt"> The message.</param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	extern void FatalError(const char *fmt,...);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Queries if a given file exists.</summary>
	///
	/// <param name="Filename"> [in,out] If non-null, filename of the file.</param>
	/// <param name="critical"> true to critical.</param>
	///
	/// <returns> true if it succeeds, false if it fails.</returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	extern bool Verify_Exists(const char *Filename, bool critical = false);
};

#endif