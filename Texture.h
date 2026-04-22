// Texture.h
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture {
public:
	Texture(const char* filepath);

	void bind(unsigned int unit = 0) ;
private:
	GLuint textureID;
	std::string m_FilePath;
	unsigned char* m_data;
	int m_Width, m_Height, m_Channel;
};

#endif