#ifndef TEXTURE_H
#define TEXTURE_H

class Texture
{
public:
    Texture(const char* texturePath);
    Texture(const char* texturePath, bool alpha);

    unsigned int loadTextureById();

private:
    unsigned int id;
    const char* texturePath;

protected:
    bool alpha = false;
};

#endif
