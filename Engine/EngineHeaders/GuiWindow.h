#pragma once
#include "BaseGui.h"
#include "AttributeBuffers.h"
#include "Shader.h"

// servers as a root container for gui objects and also the point of origin for draw calls.
// holds resources that the gui's below will use. such as vertex and uv buffers as well as a generic shader.

namespace Gui
{
	class GuiWindow : public BaseGui
	{
	private:
		Render::VectorBuffer vertexBuffer;
		Render::VectorBuffer uvBuffer;
		Render::Shader shader;

	public:
		void Draw2D();
		void Draw3D(glm::mat4x4 ViewMatrix, glm::mat4x4 ProjectionMatrix);
		void Update(double DeltaT);

	public:
		GuiWindow();
		~GuiWindow();
	};
}
