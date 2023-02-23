
// Bee Bussell
// Jan 8 2023
// bSheet and bAnimation source

#include "bSheet.h"

bool bSheet::startAnimation(std::string key) {

	if (animations.count(key) == 0) {
		perror("KEY DID NOT EXIST\n");
		return false;
	}

	animated = true;

	currentAnimation = &animations[key];
	currentAnimation -> tickCount = SDL_GetTicks64();

	currentSprite = currentAnimation -> frames.front();

	currentAnimation -> frames.pop();
	currentAnimation -> frames.push(currentSprite);

	return true;
}

bool bSheet::startAnimation(bAnimation *animation) {

	animated = true;

	currentAnimation = animation;

	currentAnimation -> tickCount = SDL_GetTicks64();

	currentSprite = currentAnimation -> frames.front();

	currentAnimation -> frames.pop();
	currentAnimation -> frames.push(currentSprite);

	return true;

}

bool bSheet::updateAnimation() {

	// For readability
	bAnimation *current = currentAnimation;
	uint64_t changeInTick = SDL_GetTicks64();

	changeInTick = SDL_GetTicks64() - current -> tickCount;

	if (changeInTick > current -> speed) {

		currentSprite = current -> frames.front();

		// Remove the current animation and toss it to the back all in beautiful O(1)
		current -> frames.pop();
		current -> frames.push(currentSprite);

		current -> tickCount = SDL_GetTicks64();
	}

	return true;
}

bool bSheet::stopAnimation() {

	animated = false;

	currentAnimation -> tickCount = 0;
	currentAnimation = NULL;

	return true;
}

/*
// As we shift to using Aseprite JSON files for this yeah..
void writeSheetToBin(const char* filePath, bSheet data) {

    std::ofstream fout;
    fout.open(filePath);

    fout << "SPRITE_SHEET_INFO" << std::endl;
    fout << "PATH: " << data.imagePath << std::endl;
    fout << "WIDTH: " << data.totalWidth << std::endl;
    fout << "HEIGHT: " << data.totalHeight << std::endl;
    fout << "SPRITES: " << data.totalSprites << std::endl;
	fout << "ANIMATIONS: " << data.animations.size() << std::endl;
    fout << "---SPRITE_DATA---" << std::endl;

    for (bRect& sprite : data.sprites)  {

    	fout << sprite.x << " " << sprite.y << " ";
    	fout << sprite.width << " " << sprite.height << std::endl;
    }

	fout << "---END_SPRITES---" << std::endl;
	fout << "---ANIMATION_DATA---" << std::endl;
	for (auto& element : data.animations) {

		bAnimation& animation = element.second;

		fout << "---ANIMATION---" << std::endl;
		fout << animation.name << std::endl;
		fout << animation.speed << std::endl;
		fout << animation.frames.size() << std::endl;

		for (size_t i = 0; i < animation.frames.size(); i++) {
			
			fout << animation.frames.front() << " ";


			animation.frames.push(animation.frames.front());
			animation.frames.pop();
		}
		
		fout << std::endl;

		
		fout << "---END_ANIMATION---" << std::endl;

	}

	fout << "---END_ANIMATION_DATA---" << std::endl;

    fout << "---END---";

    fout.close();
}
*/

bool readSheetFromJSON(const char* filePath, bSheet &data) {


	std::ifstream f(filePath);
	json dataFile = json::parse(f);

	
	json meta = dataFile["meta"];
	json dimensions = meta["size"];
	json frames = dataFile["frames"];
	

	data.imagePath = meta["image"].get<std::string>();


	data.totalWidth = dimensions["w"];
	data.totalHeight = dimensions["h"];
	
	printf("Path: %s\n", data.imagePath.c_str());
	printf("Dimensions: (%d,%d)\n", data.totalWidth, data.totalHeight);

	int count = 0;
	
	// This is noels fault
	bAnimation animation;
	animation.name = "defaultAseprite";


	for (auto& frame : frames ) {

		//printf("Filename: %s\n", frame["filename"].get<std::string>().c_str());
		
		json rect = frame["frame"];
		bRect sprite;
		sprite.x = rect["x"];
		sprite.y = rect["y"];
		sprite.width = rect["w"];
		sprite.height = rect["h"];

		data.sprites.push_back(sprite);

		// LOL, I'm gonna have to change this
		animation.speed = frame["duration"];
		animation.frames.push(count);

		count++;
	}
	data.animations[animation.name] = animation;
	data.totalSprites = count;
	printf("Total Sprites: %d\n", data.totalSprites);
	return true;
	/*
	std::ifstream fin;
	

	std::string s;

	bRect sprite;
	uint8_t animations;
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
	
	if (!(fin >> s) || s != "ANIMATIONS:") return false;
	if (!(fin >> animations)) return false;

	if (!(fin >> s) || s != "---SPRITE_DATA---") return false;

	for (int i = 0; i < data.totalSprites; i++) {
		if (!(fin >> sprite.x)) return false;
		if (!(fin >> sprite.y)) return false;
		if (!(fin >> sprite.width)) return false;
		if (!(fin >> sprite.height)) return false;
		data.sprites.push_back(sprite);
	}

	if (!(fin >> s) || s != "---END_SPRITES---") return false;

	if (!(fin >> s) || s != "---ANIMATION_DATA---") return false;

	for (int i = 0; i < animations; i++) {

		bAnimation anim;
		uint16_t frameCount;

		if (!(fin >> s) || s != "---ANIMATION---") return false;

		if (!(fin >> anim.name)) return false;
		if (!(fin >> anim.speed)) return false;
		if (!(fin >> frameCount)) return false;
		
		for (int i = 0; i < frameCount; i++) {

			uint16_t temp;
			if (!(fin >> temp)) return false;
			anim.frames.push(temp);
		}

		data.animations[anim.name] = anim;

		if (!(fin >> s) || s != "---END_ANIMATION---") return false;


	}

	if (!(fin >> s) || s != "---END_ANIMATION_DATA---") return false;

	if (!(fin >> s) || s != "---END---") return false;
	
	fin.close();
	return true;
	*/

}
