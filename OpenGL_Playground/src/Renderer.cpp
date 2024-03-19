#include "Renderer.h"

#include "GLErrorManager.h"

void Renderer::Clear(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) const
{
    glClearColor(red, green, blue, alpha);
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); // hard coded to GL_UNSIGNED_INT for now
}
