#include "LowLevelSystem.h"
#include <string>
#include <stdio.h>
#include <sys/stat.h>

namespace DavinciEngine{

	// Check if a file exists and return true or false
	bool Verify_Exists (const char *Filename, bool critical){

		struct stat stFileInfo;
		int intStat;

		// If the Filename is not given then return false.
		if(Filename == ""){
			return false;
		}

		// Attempt to get the file attributes
		intStat = stat(Filename,&stFileInfo);
		if(intStat == 0) {
			// We were able to get the file attributes
			// so the file obviously exists.
			return true;
		} else {
			// We were not able to get the file attributes.
			// This may mean that we don't have permission to
			// access the folder which contains this file. If you
			// need to do that level of checking, lookup the
			// return values of stat which will give you
			// more details on why stat failed. It also could mean
			// the file simply does not exist which is most likely
			// the case here.
			char buffer[1024] = "";
			switch (critical)
			{
			case true:{
				sprintf(buffer,"File Not Found: %s\nPress OK to exit.",Filename);
				FatalError(buffer);
				return false;										// Return false if the file does not exist
				break;}
			case false:{
				sprintf(buffer,"File Not Found: %s\n",Filename);
				Log(buffer);
				return false;										// Return false if the file does not exist
				break;}
			}
		}
		return false;
	} // End Verify_Exists
};
