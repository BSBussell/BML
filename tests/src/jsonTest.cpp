// Bee Bussell
// Sept 17, 2022
// Testing animation class creator.

#include <iostream>
#include <string>
#include <BML/BML.h>

int main() {
     
    bool run = true;
    
    BML_Init();

    bSheet spriteSheet;
    readSheetFromJSON(BML_GetPath("../resources/NoelAssets/MCaniHIGH-Start_walk.json").c_str(), spriteSheet);
    spriteSheet.startAnimation("default");
    
    bWindow* window = new bWindow("JSON Test", 0, 0, 800, 450);
    
    // Ok looking at this a year after I developed this, I hate it
    // This should be something that should be set, like maybe a bool?
    // However now that I've peaked at bit more at this function... I get it a bit more...
    window->toggleResizeable();
    window->toggleHighDPI();

    // Flags for our renderer
//  //window->toggleSoftwareRender();
    window -> toggleHardwareRender();
    window->toggleVSync();

    // Create Window returns a pointer to the renderer
    bRenderer *renderer = window->createWindow();

    // Setting the Background Color
    renderer->background(255, 255, 255, 255);


    // Setting the font
    renderer->setFont("../resources/fonts/daydream_3/Daydream.ttf", 50, {0,0,0,255});
    
    bRect dest = {10,10,128,128};
    
    if (!bSound::openAudio())
        printf(":(");

    //  bSound music;
    bSound::loadMUS("../resources/BLUE-Compress.wav");
    bSound::playMUS(5);

    
    // I think this should be something handled in the sheet function
    renderer->initSpriteSheet(spriteSheet);
    spriteSheet.sourceTexture.angle = 0;
    spriteSheet.sourceTexture.center = {64, 128};

    // Enable linear filtering
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2" );

    // Setting up a texture
    bTexture texture = renderer->initTexture("../resources/blueSquare.png", {0,0,128,128});
    texture.angle = 0;

    renderer -> setCameraTransformations({dest.x, dest.y}, {1.0,1.0}, 0.0);

    bPoint camera = {0,0};
    float angle = 0.0f;
    float scale = 1.0f;

    while(run) {

        
        // Event loop
        run = bEvent::eventLoop();

        if (bEvent::keyDown('W')) {
            dest.y--;
        } 
        if (bEvent::keyDown('S')) {
            dest.y++;
        }
        if (bEvent::keyDown('A')) {

            printf("%f\n", spriteSheet.sourceTexture.angle);
            dest.x--;
        }
        if (bEvent::keyDown('D')) {

            printf("%f\n", spriteSheet.sourceTexture.angle);
            dest.x++;
        }

        // Quit the program
        if (bEvent::keyDown('Q')) {
            run = false;
        }

        // Camera Controls

        // Position
        if (bEvent::keyDown('L')) {
            camera.x+= 5;
        }
        if (bEvent::keyDown('J')) {
            camera.x-= 5;
        }
        if (bEvent::keyDown('I')) {
            camera.y-= 5;
        }
        if (bEvent::keyDown('K')) {
            camera.y+= 5;
        }

        // Rotation
        if (bEvent::keyDown('U')) {
            angle++;
        }
        if (bEvent::keyDown('O')) {
            angle--;
        }

        // Scale
        if (bEvent::keyDown('Z')) {
            scale += 0.1;
        }
        if (bEvent::keyDown('X')) {
            scale -= 0.1;
        }

        // Change the minimum zoom
        if (bEvent::keyDown('c')) {
            bPointF minZoom = {1, 1};
            renderer -> setMinZoom(minZoom);
        }
        if (bEvent::keyDown('v')) {
            bPointF minZoom = {.3, .3};
            renderer -> setMinZoom(minZoom);
        }

        // Resize Renderer to Window
        if (bEvent::keyDown('r')) {
            renderer -> resizeToWindow();
        }

        // This would be optimal usage for rendering, do inputs/math
        // Clear our buffer, draw our shit and finally, present the buffer
        renderer -> clearBuffer();

        renderer -> setCameraTransformations(camera, {scale,scale}, angle);
        renderer -> drawText("Hello World!", {960, 540});
        renderer -> drawTexture(texture, dest);
        renderer -> drawSprite(spriteSheet, dest);

        
        
        renderer -> presentBuffer();

    }

    spriteSheet.stopAnimation();
    //
    renderer -> unloadTexture(texture);
    renderer -> unloadSpriteSheet(spriteSheet);
    
    bSound::freeMUS();
    bSound::closeAudio();
    

    // This Deletes the renderer
    window->closeWindow();
    
    BML_Close();
    
    return 0;
}
