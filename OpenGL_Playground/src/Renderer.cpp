#include "Renderer.h"

#include "GLErrorManager.h"

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::SetClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) const
{
    glClearColor(red, green, blue, alpha);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); // hard coded to GL_UNSIGNED_INT for now
}

void Renderer::Draw(const VertexArray& va, unsigned int first, unsigned int count, const Shader& shader) const
{
    shader.Bind();
    va.Bind();

    GLCall(glDrawArrays(GL_TRIANGLES, first, count));
}
