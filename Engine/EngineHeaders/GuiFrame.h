#pragma once
#include "GuiObject.h"
#include "Texture2D.h"

namespace Render{ class VectorBuffer; class Shader; };
namespace Gui
{
	class GuiFrame : public GuiObject
	{
	private:
		Render::Texture2D texture;

	public:
		void SetTexture(const Render::Texture2D& Texture);

	public:
		GuiFrame();
		~GuiFrame();
	};
}
