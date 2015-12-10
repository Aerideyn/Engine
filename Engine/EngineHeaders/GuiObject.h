#pragma once
#include "BaseGui.h"
#include <boost\signals2.hpp>

namespace Gui
{
	class GuiObject : public BaseGui
	{
	private:
		bool signalsBlocked;
		bool visible;
		glm::vec2 position;
		glm::vec2 scale;
		glm::mat4x4 modelMatrix;

	protected:
		virtual void dimensionChanged();
		virtual void draw2D(glm::mat4x4 WorldMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader);
		virtual void draw3D(glm::mat4x4 ViewMatrix, glm::mat4x4 ProjectionMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader);
		virtual void update(double DeltaT);

	public:
		bool GetVisible() { return visible; };
		void SetVisible(bool Visible);
		void SetLayer(int Layer);
		void SetPosition(glm::vec2 Position);
		glm::vec2 GetPosition() { return position; };
		void SetSize(glm::vec2 Size);
		glm::vec2 GetSize() { return scale; };
		void SetParent(std::shared_ptr<BaseGui> Parent);
		void SetSignalsAreBlocked(bool);
		void SetModelMatrix(glm::mat4x4 ModelMatrix);

	public:


	public:
		GuiObject();
		~GuiObject();
	};
}

