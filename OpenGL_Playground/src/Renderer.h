#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
    void Clear() const;
    void SetClearColor(GLclampf red = 0.0f, GLclampf green = 0.0f, GLclampf blue = 0.0f, GLclampf alpha = 1.0f) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Draw(const VertexArray& va, unsigned int first, unsigned int count, const Shader& shader) const;
};

