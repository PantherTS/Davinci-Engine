#ifndef XMLSETTINGS_H
#define XMLSETTINGS_H

#include "TXMLWrapper.h"
//#include "tinyxml2.h"

namespace DavinciEngine{

	class XmlSettings{

	public:

		static XmlSettings *GetInstance ( void );
		void Destroy( void );
		static void DefaultSettings();
		void SaveSettings();
		void LoadSettings();

		int GetWidth() const noexcept(true){return width;};
		int GetHeight() const noexcept(true){return height;};
		int GetBPP() const noexcept(true){return bpp;};
		bool GetFS() const noexcept(true){return fullscreen;};
		std::string GetTitle() const{return title;};

		void SetWidth(int x);
		void SetHeight(int y);
		void SetBPP(int bpp);
		void SetFullscreen(bool isFullscreen);

	private:

		XmlSettings ( void );
		~XmlSettings ( void );
		static XmlSettings *m_XmlSettings;
		TXMLWrapper xmlObj;
		const char* title;
		int width;
		int height;
		int bpp;
		bool fullscreen;
	};
}
#endif