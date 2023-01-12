
// Bee Bussell
// Jan 8 2023
// bSheet and bAnimation source

#include "bSheet.h"

bool bSheet::startAnimation(uint16_t animation) {

	animated = true;

	currentAnimation = &animations[animation];
	currentAnimation -> frameIndex = 0;
	currentAnimation -> frameCount = 0;

	currentSprite = currentAnimation -> frames[0];

	return true;
}

bool bSheet::updateAnimation() {

	// For readability
	bAnimation *current = currentAnimation;
	current -> frameCount++;

	if (current -> frameCount > current -> frameRate) {

		current -> frameIndex++;
		if (current -> frameIndex > current -> frames.size()) {
			current -> frameIndex = 0;
		}
		currentSprite = current -> frames[current -> frameIndex];
	}

	return true;
}

bool bSheet::stopAnimation() {

	animated = false;

	currentAnimation -> frameIndex = 0;
	currentAnimation -> frameCount = 0;
	currentAnimation = NULL;

	return true;
}

void writeSheetToBin(const char* filePath, bSheet data) {

    std::ofstream fout;
    fout.open(filePath);

    fout << "SPRITE_SHEET_INFO" << std::endl;
    fout << "PATH: " << data.imagePath << std::endl;
    fout << "WIDTH: " << data.totalWidth << std::endl;
    fout << "HEIGHT: " << data.totalHeight << std::endl;
    fout << "SPRITES: " << data.totalSprites << std::endl;
    fout << "---SPRITE_DATA---" << std::endl;

    for (bRect& sprite : data.sprites)  {

    	fout << sprite.x << " " << sprite.y << " ";
    	fout << sprite.width << " " << sprite.height << std::endl;
    }

    fout << "---END---";

    fout.close();
}

bool readSheetFromBin(const char* filePath, bSheet &data) {

	std::ifstream fin;
	

	std::string s;

	bRect sprite;
	///vector<bRect> sprites;

	fin.open(filePath);
	if (fin.fail()) return false;

	if (!(fin >> s) || s != "SPRITE_SHEET_INFO") return false;
	if (!(fin >> s) || s != "PATH:") return false; 
	if (!(fin >> data.imagePath)) return false;
	if (!(fin >> s) || s != "WIDTH:") return false;
	if (!(fin >> data.totalWidth)) return false;
	if (!(fin >> s) || s != "HEIGHT:") return false;
	if (!(fin >> data.totalHeight)) return false;
	if (!(fin >> s) || s != "SPRITES:") return false;
	if (!(fin >> data.totalSprites)) return false;
	if (!(fin >> s) || s != "---SPRITE_DATA---") return false;

	for (int i = 0; i < data.totalSprites; i++) {
		if (!(fin >> sprite.x)) return false;
		if (!(fin >> sprite.y)) return false;
		if (!(fin >> sprite.width)) return false;
		if (!(fin >> sprite.height)) return false;
		data.sprites.push_back(sprite);
	}

	if (!(fin >> s) || s != "---END---") return false;
	
	fin.close();
	return true;

}