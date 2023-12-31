#ifndef SPRITE2_H
#define SPRITE2_H

#include "TextureAsset.h"
#include "Graphic.h"
#include "Vec2D.h"

namespace DavinciEngine{

	class Object;
	class SpriteAnimation;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Values that represent Direction. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	enum Direction{INVALID_DIR=-1,NORTH,NORTHEAST,EAST,SOUTHEAST,SOUTH,SOUTHWEST,WEST,NORTHWEST};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Sprite Class represents any object on-screen that has the ability
	/// 		  to move. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Sprite : public Graphic {

	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Constructor.</summary>
		///
		/// <param name="filename"> Filename of the file.</param>
		/// <param name="width">    (optional) the width.</param>
		/// <param name="height">   (optional) the height.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sprite(const std::string &filename, float width=-1, float height=-1);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Constructor.</summary>
		///
		/// <param name="filename"> Filename of the file.</param>
		/// <param name="filter">   The filter.</param>
		/// <param name="width">    (optional) the width.</param>
		/// <param name="height">   (optional) the height.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sprite(const std::string &filename, FilterType filter, float width=-1, float height=-1);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Copy constructor.</summary>
		///
		/// <param name="other"> The other.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sprite(const Sprite &other);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Sprite();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Renders the given object.</summary>
		///
		/// <param name="object"> [in,out] If non-null, the object.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Render(Object *object);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the Sprite's texture's width and height and assigns the
		/// 		  appropriate pointers.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		const Vec2D GetWidthHeight() override;

		void SetSpriteAnimation(SpriteAnimation *animation);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Initiates the movement routine for the Sprite. The Sprite is instructed
		/// 		  to move to the given coordinates.</summary>
		///
		/// <param name="coordinate"> The coordinate.</param>
		/// <param name="position">   The position.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void MoveTo(Vec2D coordinate, Vec2D position);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> The movement routine that is called for each frame if an object
		/// 		  was instructed to move somewhere on the screen. This method's
		/// 		  only parameters is the deltatime which is provided by the Timer
		/// 		  Class. The only caller of this function should be the Paint class.</summary>
		///
		/// <param name="position"> [in,out] The position.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Move(Vec2D &position);

		/// <summary> The texture </summary>
		TextureAsset *texture;

		/// <summary> Height and width of the sprite </summary>
		float m_fWidth, m_fHeight;

		/// <summary> The texture offset </summary>
		Vec2D textureOffset;

		/// <summary> The texture scale </summary>
		Vec2D textureScale;

		/// <summary> The blend type being used </summary>
		BlendType blend;

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
		void Normalize(Vec2D &v);

		/// <summary> The direction to move </summary>
		Vec2D m_vec2Direction;

		/// <summary> The destination to move to </summary>
		Vec2D m_vec2Destination;

		/// <summary> A pointer to the SpriteAnimation object if the Sprite has one </summary>
		SpriteAnimation *m_pSpriteAnimation;
	};
};
#endif