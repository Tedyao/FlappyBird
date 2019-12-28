#pragma once
#include "GameSettings.h"

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();
	void addBufferLayout(const VertexBuffer& verBuff, const VertexBufferLayout& layout);
	inline void bind()const { GLCall(glBindVertexArray(m_RendererID)); };
	inline void unbind() const { GLCall(glBindVertexArray(0)); };

};

