#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
	
}

void VertexArray::addBufferLayout(const VertexBuffer& verBuff, const VertexBufferLayout& layout)
{
	bind();
	verBuff.bind();
	unsigned int offset = 0;
	auto elements = layout.getElements();
	for (int i = 0; i < elements.size(); i++)
	{

		glVertexAttribPointer(i, elements[i].size, elements[i].type, elements[i].normalized, layout.getStride(), (const void*)offset);
		glEnableVertexAttribArray(i);
		offset += elements[i].size * VertexBufferElement::getTypeSize(elements[i].type);

	}


}
