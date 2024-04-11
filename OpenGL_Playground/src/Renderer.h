#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
    void Clear(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const VertexArray& va, unsigned int first, unsigned int count, const Shader& shader) const;
};

