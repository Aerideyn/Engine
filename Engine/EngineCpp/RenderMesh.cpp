#include "RenderMesh.h"
#include <GL\glew.h>

#include "Game.h"
#include "ContentService.h"
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>

RenderMesh::RenderMesh(unsigned int ShaderID)
{
	TextureSamplerMapper = std::map<unsigned int, unsigned int>();
	programID = ShaderID;

	SetModelMatrix(glm::mat4x4());
	SetWorldMatrix(glm::mat4x4());
	SetViewProjectionMatrix(glm::mat4x4());
}

RenderMesh::RenderMesh(const char* VertexShader, const char* FragmentShader)
{
	programID = Game::GetContentService().LoadShader(VertexShader, FragmentShader);
	SetModelMatrix(glm::mat4x4());
	SetWorldMatrix(glm::mat4x4());
	SetViewProjectionMatrix(glm::mat4x4());
}

RenderMesh::~RenderMesh()
{
	// unload current vertex buffer if one exists.
	if (VertexBufferUsed) glDeleteBuffers(1, &VertexBuffer);
	// unload current uv buffer if one exists.
	if (UVBufferUsed) glDeleteBuffers(1, &UVbuffer);
	// unload current normal buffer if one exists.
	if (NormalBufferUsed) glDeleteBuffers(1, &NormalBuffer);
	// unload current index buffer if one exists.
	if (IndexBufferUsed) glDeleteBuffers(1, &indexBuffer);
}

void RenderMesh::SetModelMatrix(const glm::mat4x4& modelMatrix)
{
	ModelMatrix = modelMatrix;
	unsigned int Location = glGetUniformLocation(programID, "ModelMatrix");
	if (Location == -1)
	{
		std::cout << "Could not find uniform: ModelMatrix. Was the uniform optimised away?" << std::endl;
	}
	else
	{
		ModelMatrixLocation = Location;
		ModelMatrixValid = true;
	}
}

void RenderMesh::SetWorldMatrix(const glm::mat4x4& worldMatrix)
{
	WorldMatrix = worldMatrix;
	unsigned int Location = glGetUniformLocation(programID, "WorldMatrix");
	if (Location == -1)
	{
		std::cout << "Could not find uniform: WorldMatrix. Was the uniform optimised away?" << std::endl;
	}
	else
	{
		WorldMatrixLocation = Location;
		WorldMatrixValid = true;
	}
}

void RenderMesh::SetWorldMatrix(const glm::vec3& translation)
{
	WorldMatrix = glm::translate(glm::mat4x4(), translation);
	unsigned int Location = glGetUniformLocation(programID, "WorldMatrix");
	if (Location == -1)
	{
		std::cout << "Could not find uniform: WorldMatrix. Was the uniform optimised away?" << std::endl;
	}
	else
	{
		WorldMatrixLocation = Location;
		WorldMatrixValid = true;
	}
}

void RenderMesh::SetWorldMatrix(const glm::dvec3& translation)
{
	WorldMatrix = glm::translate(glm::mat4x4(), glm::vec3(translation.x, translation.y, translation.z));
	unsigned int Location = glGetUniformLocation(programID, "WorldMatrix");
	if (Location == -1)
	{
		std::cout << "Could not find uniform: WorldMatrix. Was the uniform optimised away?" << std::endl;
	}
	else
	{
		WorldMatrixLocation = Location;
		WorldMatrixValid = true;
	}
}

void RenderMesh::SetViewProjectionMatrix(glm::mat4x4 viewProjectionMatrix)
{
	ViewProjectionMatrix = viewProjectionMatrix;
	unsigned int Location = glGetUniformLocation(programID, "ViewProjectionMatrix");
	if (Location == -1)
	{
		std::cout << "Could not find uniform: ViewProjection. Was the uniform optimised away?" << std::endl;
	}
	else
	{
		ViewProjectionMatrixLocation = Location;
		ViewProjectionMatrixValid = true;
	}
}

void RenderMesh::SetVerticies(const std::vector<glm::vec3>& vertices)
{
	// unload current vertex buffer if one exists.
	if (VertexBufferUsed) glDeleteBuffers(1, &VertexBuffer);
	
	// flag buffer as in use.
	VertexBufferUsed = true;
	vertexCount = vertices.size();

	// load in new vertex buffer.
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
}

void RenderMesh::SetUVCoordinates(const std::vector<glm::vec2>& uvs)
{
	// unload current uv buffer if one exists.
	if (UVBufferUsed) glDeleteBuffers(1, &UVbuffer);

	// flag buffer as in use.
	UVBufferUsed = true;

	// load in new uv buffer.
	glGenBuffers(1, &UVbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, UVbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

void RenderMesh::SetNormals(const std::vector<glm::vec3>& normals)
{
	// unload current normal buffer if one exists.
	if (NormalBufferUsed) glDeleteBuffers(1, &NormalBuffer);

	// flag buffer as in use.
	NormalBufferUsed = true;

	// load in new uv buffer.
	glGenBuffers(1, &NormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

void RenderMesh::SetIndicies(const std::vector<unsigned short>& indices)
{
	// unload current index buffer if one exists.
	if (IndexBufferUsed) glDeleteBuffers(1, &indexBuffer);

	// flag buffer as in use.
	IndexBufferUsed = true;
	indexCount = indices.size();
	indiceTypeSize = sizeof(unsigned short);
	indiceType = GL_UNSIGNED_SHORT;

	// load in new uv buffer.
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, indices.size() * indiceTypeSize, &indices[0], GL_STATIC_DRAW);
}

void RenderMesh::SetIndicies(const std::vector<unsigned int>& indices)
{
	// unload current index buffer if one exists.
	if (IndexBufferUsed) glDeleteBuffers(1, &indexBuffer);

	// flag buffer as in use.
	IndexBufferUsed = true;
	indexCount = indices.size();
	indiceTypeSize = sizeof(unsigned int);
	indiceType = GL_UNSIGNED_INT;

	// load in new uv buffer.
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, indices.size() * indiceTypeSize, &indices[0], GL_STATIC_DRAW);
}

void RenderMesh::SetIndicies(const std::vector<int>& indices)
{
	// unload current index buffer if one exists.
	if (IndexBufferUsed) glDeleteBuffers(1, &indexBuffer);

	// flag buffer as in use.
	IndexBufferUsed = true;
	indexCount = indices.size();
	indiceTypeSize = sizeof(int);
	indiceType = GL_INT;

	// load in new uv buffer.
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, indices.size() * indiceTypeSize, &indices[0], GL_STATIC_DRAW);
}

void RenderMesh::AddTexture(const GLuint textureID, const char* SamplerName)
{
	// get the id of the sampler which will sample this texture.
	GLuint samplerID = glGetUniformLocation(programID, SamplerName);
	TextureSamplerMapper[samplerID] = textureID;
}

void RenderMesh::AddTexture(const char* TextureName, const char* SamplerName)
{
	// get the id of the texture.
	GLuint ID = Game::GetContentService().LoadGLTexture(TextureName);

	// get the id of the sampler which will sample this texture.
	GLuint samplerID = glGetUniformLocation(programID, SamplerName);
	TextureSamplerMapper[samplerID] = ID;
}

void RenderMesh::Draw()
{

	int wireframemode = (WireFrameMode) ? GL_LINE : GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, wireframemode);

	if (BackfaceCullingEnabled)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	// set shader.
	glUseProgram(programID);

	// set textures.
	int count = 0;
	for (auto iter = TextureSamplerMapper.begin(); iter != TextureSamplerMapper.end(); iter++)
	{
		glActiveTexture(GL_TEXTURE0 + count);
		glBindTexture(GL_TEXTURE_2D, iter->second);
		glUniform1i(iter->first, count);
		count++;
	}
	
	// apply matricies.
	if (ModelMatrixValid) glUniformMatrix4fv(ModelMatrixLocation, 1, GL_FALSE, &ModelMatrix[0][0]);
	if (WorldMatrixValid) glUniformMatrix4fv(WorldMatrixLocation, 1, GL_FALSE, &WorldMatrix[0][0]);
	if (ViewProjectionMatrixValid) glUniformMatrix4fv(ViewProjectionMatrixLocation, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);

	GLuint AttributeIndex = 0;
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(AttributeIndex);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	AttributeIndex++;

	// if the uv buffer was used - bind it.
	if (UVBufferUsed)
	{
		glEnableVertexAttribArray(AttributeIndex);
		glBindBuffer(GL_ARRAY_BUFFER, UVbuffer);
		glVertexAttribPointer(AttributeIndex, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		AttributeIndex++;
	}

	// if the normal buffer was used - bind it.
	if (NormalBufferUsed)
	{
		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(AttributeIndex);
		glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
		glVertexAttribPointer(AttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		AttributeIndex++;
	}

	// Draw the mesh:
	if (IndexBufferUsed)
	{
		// bind the index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		// Draw the triangles
		switch (mode)
		{
		case MeshDrawMode::Lines:
			glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_SHORT, (void*)0);
			break;
		case MeshDrawMode::Triangles:
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, (void*)0);
			break;
		}
	}
	else // render via drawArrays()
	{
		switch (mode)
		{
		case MeshDrawMode::Lines:
			glDrawArrays(GL_LINE_STRIP, 0, vertexCount);
			break;
		case MeshDrawMode::Triangles:
			glDrawArrays(GL_TRIANGLES, 0, vertexCount);
			break;
		}

	}

	// tidy up.
	for (unsigned int i = 0; i < AttributeIndex; i++) glDisableVertexAttribArray(i);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
}