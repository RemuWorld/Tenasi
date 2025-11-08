#include "texture.h"

namespace Tenasi::Texture
{
    TTexture::TTexture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
    {
        type = texType;
        int widthImg, heightImg, numColCh;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
        if (!bytes)
        {
            fprintf(stderr, "stbi_load failed\n"); /* bail */
        }

        glGenTextures(1, &ID);
        glActiveTexture(slot);
        glBindTexture(texType, ID);
        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
        glGenerateMipmap(texType);

        stbi_image_free(bytes);
        glBindTexture(texType, 0);
    }

    void TTexture::texUnit(Shader::TShader shader, const char *uniform, GLuint unit)
    {
        GLuint tex0Uni = glGetUniformLocation(shader.getID(), uniform);
        shader.use();
        glUniform1i(tex0Uni, unit);
    }

    

    
}
