#pragma once

#include "GameSettings.h"


class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void bind() const;
	void unbind() const;
	unsigned int getCount() const;
};