#pragma once
#include "GameSettings.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void bind() const;
	void unbind() const;
};

