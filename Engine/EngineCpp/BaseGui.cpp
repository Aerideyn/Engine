#pragma once 
#include "BaseGui.h"

// privates and destructors.

Gui::BaseGui::~BaseGui()
{
	// remove as child of current parent if it exists.
	if (auto currentParent = parent.lock()) {
		currentParent->removeChild(ID);
	}
}

int Gui::BaseGui::addChild(BaseGui* child)
{
	// parent does not own the child. 
	childIDCounter++;
	children[childIDCounter] = child;
	return childIDCounter;
}

void Gui::BaseGui::removeChild(int ID)
{
	children[ID] = nullptr;
}

void Gui::BaseGui::setParent(std::shared_ptr<BaseGui> Parent)
{
	// check for circular parenting.

	// remove as child of current parent if it exists.
	if (auto currentParent = parent.lock()) {
		currentParent->removeChild(ID);
	}

	// set new parent
	parent = Parent;

	// storing "this" pointer feels wrong, however parent does not own this gui.
	// I'm just going to have to be carefull that the gui is always removed as a child of parent at destruction.
	if (Parent != nullptr){
		ID = Parent->addChild(this);
	}

	//StateChanged("Parent");
}

// propgates draw call here since derived class wont be able to call a protected method on pointers of type BaseGui.
void Gui::BaseGui::drawChildren3D(glm::mat4x4 ViewMatrix, glm::mat4x4 ProjectionMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader)
{
	for (auto childIter = children.begin(); childIter != children.end(); childIter++){
		childIter->second->draw3D(ViewMatrix, ProjectionMatrix, quadVertex, quadUV, quadShader);
	}
}

void Gui::BaseGui::drawChildren2D(glm::mat4x4 WorldMatrix, Render::VectorBuffer& quadVertex, Render::VectorBuffer& quadUV, Render::Shader& quadShader)
{
	for (auto childIter = children.begin(); childIter != children.end(); childIter++){
		childIter->second->draw2D(WorldMatrix, quadVertex, quadUV, quadShader);
	}
}

void Gui::BaseGui::updateChildren(double DeltaT)
{
	for (auto childIter = children.begin(); childIter != children.end(); childIter++) {
		childIter->second->update(DeltaT);
	}
}
