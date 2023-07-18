////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	include\AIType.h
// author:	Travis Swaim
//
// summary:	Declares the AI type class
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef AITYPE_H
#define AITYPE_H

#include <string>
#include <map>

namespace DavinciEngine {

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> AIType Class holds information for an Actor's AI data. Data is loaded
	///			from external XML files defining the different AI types available. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class AIType
	{
	public:
		
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Destructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		~AIType();

		void Destroy();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Sets the AI properties of the AI Type object. Used to change AI Type on-the-fly.</summary>
		///
		/// <param name="detectRange">	    The detect range.</param>
		/// <param name="followRange">	    The follow range.</param>
		/// <param name="attitudeToPlayer"> The attitude to player.</param>
		/// <param name="attitudeToFamily"> The attitude to family.</param>
		/// <param name="attitudeToOthers"> The attitude to others.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void AI_SetProps(const float detectRange,const float followRange,const float roamRange,const char *attitudeToPlayer,const char *attitudeToFamily,const char * attitudeToOthers);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Retrieves the AI Type object by name.</summary>
		///
		/// <param name="AITypeName"> Name of the ai type.</param>
		///
		/// <returns> null if it fails, else.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static AIType* AI_GetAIType(const std::string &AITypeName);

		/// <summary> The attitude to player </summary>
		std::string m_sAttitudeToPlayer;

		/// <summary> The attitude to family </summary>
		std::string m_sAttitudeToFamily;

		/// <summary> The attitude to others </summary>
		std::string m_sAttitudeToOthers;

		/// <summary> The detect range </summary>
		float m_fDetectRange;

		/// <summary> The follow range </summary>
		float m_fFollowRange;

		/// <summary> The roam range </summary>
		float m_fRoamRange;

		/// <summary> Name of the AI type </summary>
		std::string m_sName;

	private:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		AIType();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Copy constructor.</summary>
		///
		/// <param name="orig"> The original.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		AIType(const AIType& orig);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Create and define Artificial Intelligence from script file.</summary>
		///
		/// <param name="filename"> Filename of the file.</param>
		///
		/// <returns> true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static bool AI_Load(const char *filename);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Loads the AI type properties.</summary>
		///
		/// <param name="fileName"> Filename of the file.</param>
		///
		/// <returns> true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static bool AI_LoadProps(const char *fileName);

		/// <summary> true if AI already is loaded </summary>
		static bool m_bAILoaded;

		/// <summary> Storage map for the AI types </summary>
		static std::map<const std::string, AIType*> m_mapAITypes;

		/// <summary> The AI type storage map iterator </summary>
		static std::map<const std::string, AIType*>::iterator m_mapAITypesIter;

		static int AICount;
	};
};

#endif