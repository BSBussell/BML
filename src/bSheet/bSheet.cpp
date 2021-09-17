
//
//
//

#include "bSheet.h"

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