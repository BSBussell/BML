
// Bee Bussell
// Jan 8 2023
// bSheet and bAnimation source

#include "bSheet.h"

bool bSheet::startAnimation(std::string key) {

	if (animations.count(key) == 0) {
		fprintf(stderr, "Animation %s does not exist\n", key.c_str());
		return false;
	}

	animated = true;

	currentAnimation = &animations[key];
	currentAnimation -> tickCount = BML_GetTicks();

	currentSprite = currentAnimation -> frames.front();

	currentAnimation -> frames.pop();
	currentAnimation -> frames.push(currentSprite);

	return true;
}

bool bSheet::startAnimation(bAnimation *animation) {

	animated = true;

	currentAnimation = animation;

	currentAnimation -> tickCount = BML_GetTicks();

	currentSprite = currentAnimation -> frames.front();

	currentAnimation -> frames.pop();
	currentAnimation -> frames.push(currentSprite);

	return true;

}

bool bSheet::updateAnimation() {

	// For readability
	bAnimation *current = currentAnimation;
	Uint64 changeInTick = BML_GetTicks();

	changeInTick = BML_GetTicks() - current -> tickCount;

	Uint32 duration = current -> duration.front();

	if (changeInTick > duration) {

		currentSprite = current -> frames.front();

		// Remove the current animation and toss it to the back
		current -> frames.pop();
		current -> frames.push(currentSprite);

		// Do the same thing to speeds
		current -> duration.pop();
		current -> duration.push(duration);

		current -> tickCount = BML_GetTicks();
	}

	return true;
}

bool bSheet::stopAnimation() {

	animated = false;

	currentAnimation -> tickCount = 0;
	currentAnimation = NULL;

	return true;
}


bool readSheetFromJSON(const char *filePath, bSheet &data) {


	try {
		std::ifstream f(filePath);
		json dataFile = json::parse(f);

		
		json meta = dataFile["meta"];
		json dimensions = meta["size"];
		json frames = dataFile["frames"];
		

		data.imagePath = meta["image"].get<std::string>();

		data.totalWidth = dimensions["w"];
		data.totalHeight = dimensions["h"];
		
		int count = 0;
		
		// This is noels fault
		// Get Aseprite to have multiple animations per sheet
		bAnimation animation;
		animation.name = "default";


		for (auto& frame : frames ) {

			json rect = frame["frame"];
			bRect sprite;
			sprite.x = rect["x"];
			sprite.y = rect["y"];
			sprite.width = rect["w"];
			sprite.height = rect["h"];

			data.sprites.push_back(sprite);

			animation.duration.push(frame["duration"]);
			animation.frames.push(count);

			count++;
		}
		data.animations[animation.name] = animation;
		data.totalSprites = count;

		return true;

	// If the JSON file is invalid
	} catch (...) {


		fprintf(stderr, "JSON Parsing Error: %s\n", filePath);
		exit(1);
	}
	

}

Uint64 BML_GetTicks() {
    #if SDL_VERSION_ATLEAST(2, 0, 18)  // Zorin is behind on their SDL versions
        return SDL_GetTicks64();
    #else
        return static_cast<Uint64>(SDL_GetTicks());
    #endif
}

