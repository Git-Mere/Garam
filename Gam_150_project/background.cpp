
#include "Background.h"


void Background::Add(const std::filesystem::path& texturePath, double speed) {
	backgrounds.push_back({ texturePath, speed });
}
void Background::Unload() {
	backgrounds.clear();
}
void Background::Draw(const Camera& camera) {
	for (int i = 0; i < backgrounds.size(); i++) {
		double pos_x = camera.GetPosition().x * backgrounds[i].speed;
		double pos_y = camera.GetPosition().y * backgrounds[i].speed;
		Math::vec2 a = { 0 - pos_x, 0 - pos_y };
		backgrounds[i].texture.Draw(Math::TranslationMatrix(a));
	}
}
Math::ivec2 Background::GetSize() {
	return backgrounds[0].texture.GetSize();
}
