#pragma once

#include <iostream>

class Texture
{
public:
	static constexpr float DEFAULT_BORDER_COLOR[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
public:
	Texture(const std::string& path, bool generateMipMaps, unsigned int minFilter, unsigned int maxFilter, 
		unsigned int wrapModeS, unsigned int wrapModeT, const float* borderColor = DEFAULT_BORDER_COLOR);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
}; 

