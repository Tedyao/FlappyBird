#pragma once
#include "GameSettings.h"
#include <vector>

struct VertexBufferElement
{
	unsigned int size;
	unsigned int type;
	unsigned int normalized;
	
	static unsigned int getTypeSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		case GL_UNSIGNED_INT:
			return 4;
		default:
			return -1;
			break;
		}
	}
};

class VertexBufferLayout
{
private:
	unsigned int m_Stride;
	std::vector<VertexBufferElement> elements;
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		elements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += count * VertexBufferElement::getTypeSize(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		elements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_INT);
	}
/*
	void Push<unsigned char>(unsigned int count)
	{
		elements.push_back({ count, GL_FLOAT, GL_TRUE });
		m_Stride += count * VertexBufferElement::getTypeSize(GL_UNSIGNED_BYTE));
	}
	*/

	inline unsigned int getStride() const { return m_Stride; }
	inline std::vector<VertexBufferElement> getElements() const { return elements; }
};

