#include "GuiWindow.h"

glm::vec3 QuadVertexBufferData[] = {
	glm::vec3(-1.0f, -1.0f, 0.0f),
	glm::vec3(1.0f, -1.0f, 0.0f),
	glm::vec3(-1.0f, 1.0f, 0.0f),
	glm::vec3(-1.0f, 1.0f, 0.0f),
	glm::vec3(1.0f, -1.0f, 0.0f),
	glm::vec3(1.0f, 1.0f, 0.0f),
};

glm::vec2 QuadUVBufferData[] = {
	glm::vec2(0.0f, 0.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.0f, 1.0f),
	glm::vec2(0.0f, 1.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(1.0f, 1.0f),
};

const char* vertexShaderCode =
R"(
#version 330 core; 
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 VertexUV;
out vec2 UV;
// variables inputs.
uniform mat4 ViewProjectionMatrix;
uniform mat4 ModelMatrix;
uniform mat4 WorldMatrix;
void main() {
    gl_Position = ViewProjectionMatrix *  WorldMatrix * ModelMatrix * vec4(vertexPosition , 1);	 
    UV = VertexUV;
}
)";

const char* fragmentShaderCode =
R"(
#version 330 core
in vec2 UV;
out vec3 color;
uniform sampler2D TextureSampler;
void main() {
	color = texture(TextureSampler , UV).rgb;
}
)";

// constructors.
Gui::GuiWindow::GuiWindow()
{
	vertexBuffer = Render::VectorBuffer(6, 3, &QuadVertexBufferData);
	uvBuffer = Render::VectorBuffer(6, 2, &QuadUVBufferData);
	shader = Render::Shader(vertexShaderCode, fragmentShaderCode);
};

Gui::GuiWindow::~GuiWindow(){

}

// public methods.
void Gui::GuiWindow::Draw3D(glm::mat4x4 ViewMatrix, glm::mat4x4 ProjectionMatrix) {
	drawChildren3D(ViewMatrix, ProjectionMatrix, vertexBuffer, uvBuffer, shader);
}

void Gui::GuiWindow::Draw2D() {
	drawChildren2D(glm::mat4x4(), vertexBuffer, uvBuffer, shader);
}

void Gui::GuiWindow::Update(double DeltaT)
{
	updateChildren(DeltaT);
}
