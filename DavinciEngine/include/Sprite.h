#ifndef SPRITE2_H
#define SPRITE2_H

#include "TextureAsset.h"
#include "SpriteGraphic.h"
#include "glm/glm.hpp"

namespace DavinciEngine {

	class Object;
	class SpriteAnimation;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Values that represent Direction. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	enum Direction { INVALID_DIR = -1, NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Sprite Class represents any object on-screen that has the ability
	/// 		  to move. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Sprite : public SpriteGraphic {

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Constructor.</summary>
		///
		/// <param name="filename"> Filename of the file.</param>
		/// <param name="width">    (optional) the width.</param>
		/// <param name="height">   (optional) the height.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sprite(const std::string& filename, float width = -1, float height = -1);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Constructor.</summary>
		///
		/// <param name="filename"> Filename of the file.</param>
		/// <param name="filter">   The filter.</param>
		/// <param name="width">    (optional) the width.</param>
		/// <param name="height">   (optional) the height.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sprite(const std::string& filename, FilterType filter, float width = -1, float height = -1);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Copy constructor.</summary>
		///
		/// <param name="other"> The other.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sprite(const Sprite& other);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sprite();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Renders the given object.</summary>
		///
		/// <param name="object"> [in,out] If non-null, the object.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Render(const glm::mat4& vp, const glm::mat4& model) override;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the Sprite's texture's width and height and assigns the
		/// 		  appropriate pointers.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		glm::vec2 GetSize() override;

		void SetSpriteAnimation(SpriteAnimation* animation);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Initiates the movement routine for the Sprite. The Sprite is instructed
		/// 		  to move to the given coordinates.</summary>
		///
		/// <param name="coordinate"> The coordinate.</param>
		/// <param name="position">   The position.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void MoveTo(glm::vec2 coordinate, glm::vec2 position);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> The movement routine that is called for each frame if an object
		/// 		  was instructed to move somewhere on the screen. This method's
		/// 		  only parameters is the deltatime which is provided by the Timer
		/// 		  Class. The only caller of this function should be the Paint class.</summary>
		///
		/// <param name="position"> [in,out] The position.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Move(glm::vec2& position);

		unsigned int GetTextureID() const override { return texture->GetTextureID(); }

		/// <summary> The texture </summary>
		TextureAsset* texture;

		/// <summary> true if sprite is moving </summary>
		bool m_bIsMoving;

		/// <summary> The facing direction of the sprite </summary>
		Direction facingDirection;

		/// <summary> The last facing direction </summary>
		Direction lastFacingDirection;

		/// <summary> The current action </summary>
		std::string m_sCurrentAction;

		/// <summary> The last action </summary>
		std::string m_sLastAction;

		/// <summary> The speed of the sprite </summary>
		float m_fSpeed;

	protected:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Destructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		~Sprite();

	private:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Takes the direction the Sprite is trying to move in and converts
		/// 		  it to degrees. Once in degrees, the Sprite's facingDirection is
		/// 		  updated so the proper animation is being played depending on which
		/// 		  way the Sprite is facing.</summary>
		///
		/// <param name="v"> [in,out] The direction vector.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Normalize(glm::vec2& v);

		/// <summary> The direction to move </summary>
		glm::vec2 m_vec2Direction;

		/// <summary> The destination to move to </summary>
		glm::vec2 m_vec2Destination;

		/// <summary> A pointer to the SpriteAnimation object if the Sprite has one </summary>
		SpriteAnimation* m_pSpriteAnimation;
	};
};
#endif