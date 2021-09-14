
//
//
//

#include "bSheet.h"

void writeSheetToBin(const char* filePath, bSheet data) {

    ofstream fout;
    fout.open(filePath);

    fout << "SPRITE_SHEET_INFO" << endl;
    fout << "PATH: " << data.imagePath << endl;
    fout << "WIDTH: " << data.totalWidth << endl;
    fout << "HEIGHT: " << data.totalHeight << endl;
    fout << "---SPRITE_DATA---" << endl;

    for (bRect& sprite : data.sprites)  {

    	fout << sprite.x << " " << sprite.y;
    	fout << sprite.width << " " << sprite.height << endl;
    }

    fout << "---END---";

    fout.close();
}

bSheet readSheetFromBin(const char* filePath) {

	ifstream fin;
	bSheet sheetData;

	std::string s;

	uint32_t width;
	uint32_t height;

	bRect sprite;
	vector<bRect> sprites;

	fin.open(filePath);
	if (fin.fail()) return false;

	if (!(fin >> s)) return 
}