#pragma once
class VectorAttributeBuffer
{
private:
	bool DataIsValid;
	unsigned int bufferID;
	int floatsPerVector;
	int ElementCount;

public:
	VectorAttributeBuffer();
	VectorAttributeBuffer(int NumberOfVectors, int FloatsPerVector, void* Data);
	~VectorAttributeBuffer();

	// should have sole ownership of the buffer. Copying this buffer should also invalidate this buffer.
	VectorAttributeBuffer(VectorAttributeBuffer &Other);
	void operator=(VectorAttributeBuffer& Other);

	void BindBuffer(int AttributeIndex);
	void DisableBuffer(int AttributeIndex);

	inline int GetElementCount(){ return ElementCount; };
};

class IndexBuffer
{
private:
	bool DataIsValid = false;
	unsigned int bufferID;
	int ElementCount;
public:
	

	IndexBuffer();
	IndexBuffer(int NuberOfIndicies, int IndiceTypeSize , void* Data);
	~IndexBuffer();

	// should have sole ownership of the buffer. Another buffer should not be able to release this buffer's resources - do not allow copying.
	IndexBuffer(IndexBuffer &Other);
	void operator=(IndexBuffer &Other);

	void BindBuffer();
	inline int GetNumberOfIndicies(){ return ElementCount; };
};