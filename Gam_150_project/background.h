
#pragma once
#include "Texture.h"
#include "Camera.h"

class Background {
public:
    void Add(const std::filesystem::path& texturePath, double speed);
    void Unload();
    void Draw(const Camera& camera);
    Math::ivec2 GetSize();
private:
    struct ParallaxLayer {
        Texture texture;
        double speed = 1;
    };

    std::vector<ParallaxLayer> backgrounds;
};
