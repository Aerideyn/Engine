#pragma once
#include <memory>
#include <glm\glm.hpp>
#include <map>

namespace Render{ class VectorBuffer; class Shader; };
namespace Gui
{
	class BaseGui
	{
	private:
		int childIDCounter; int ID;
		std::weak_ptr<BaseGui> parent;
		std::map<int, BaseGui* > children;
	
	private:
		void removeChild(int id);
		int addChild(BaseGui* child);

	protected:
		virtual void setParent(std::shared_ptr<BaseGui> Parent);
		virtual void draw2D(glm::mat4x4 WorldMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader) = 0;
		virtual void draw3D(glm::mat4x4 ViewMatrix, glm::mat4x4 ProjectionMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader) = 0;
		virtual void update(double DeltaT) = 0;

	protected:
		void drawChildren2D(glm::mat4x4 WorldMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader);
		void drawChildren3D(glm::mat4x4 ViewMatrix, glm::mat4x4 ProjectionMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader);
		void updateChildren(double DeltaT);

	public:
		virtual ~BaseGui();
	};
}

