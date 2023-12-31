#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vec2D.h"

namespace DavinciEngine{

	class FileNode;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> The Transform class is the main base class for all Objects in the game. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Transform{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Transform();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Copy constructor.</summary>
		///
		/// <param name="transform"> The transform.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Transform(const Transform &transform);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Destructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		~Transform();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Saves the given file.</summary>
		///
		/// <param name="fileNode"> [in,out] If non-null, the FileNode * to save.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Save(FileNode *fileNode);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Loads the given file.</summary>
		///
		/// <param name="fileNode"> [in,out] If non-null, the FileNode * to load.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void Load(FileNode *fileNode);

		/// <summary> The position </summary>
		Vec2D position;

		/// <summary> The layer that the object is to be drawn to (-100 - 100) </summary>
		int m_iLayer;

		/// <summary> The rotation </summary>
		float rotation;

		/// <summary> The scale </summary>
		Vec2D scale;
	};
}
#endif