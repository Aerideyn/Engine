#include "GuiObject.h"
#include "AttributeBuffers.h"
#include "Shader.h"
#include <glm\gtc\matrix_transform.hpp>

Gui::GuiObject::GuiObject() {

}

Gui::GuiObject::~GuiObject() {

}

void Gui::GuiObject::draw2D(glm::mat4x4 ObjectMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader) {
	// create scale matrix based on size.
	glm::vec2 dim = GetSize();
	glm::mat4x4 NewObjectMatrix = ObjectMatrix * glm::scale(glm::mat4x4(), glm::vec3(dim.x, dim.y, 1));

	quadVertex.BindBuffer(0);
	quadUV.BindBuffer(1);

	quadShader.UseProgram();
	quadShader.ApplyMatrix("ObjectMatrix", NewObjectMatrix);
	quadShader.DrawNonIndexedElements(6, false);

	drawChildren2D(NewObjectMatrix, quadVertex, quadUV, quadShader);

	quadVertex.DisableBuffer(0);
	quadUV.DisableBuffer(1);

	// render.
}

void Gui::GuiObject::draw3D(glm::mat4x4 ViewMatrix, glm::mat4x4 ProjectionMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader) {

}

// setters.
void Gui::GuiObject::SetVisible(bool Visible)
{
	visible = Visible;
	//StateChanged("Visible");
};

void Gui::GuiObject::SetPosition(glm::vec2 Position)
{
	position = Position;
	dimensionChanged(); // allow gui to react polymorphically.
	//StateChanged("Position");
}

void Gui::GuiObject::SetSize(glm::vec2 Size)
{
	scale = Size;
	dimensionChanged(); // allow gui to react polymorphically.
	//StateChanged("Scale");
}

void Gui::GuiObject::SetParent(std::shared_ptr<BaseGui> Parent)
{
	setParent(Parent); // inherited method.
}

void Gui::GuiObject::SetSignalsAreBlocked(bool Blocked)
{
	signalsBlocked = Blocked;
	//StateChanged("SignalsAreBlocked");
}

//translates gui into 3d space with the origin of the translation being the centre of the GUI's initial 2d position.
//applied after first rotation.
void Gui::GuiObject::SetModelMatrix(glm::mat4x4 ModelMatrix)
{
	modelMatrix = ModelMatrix;
	//StateChanged("ModelMatrix");
}