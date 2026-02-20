# LibSWBF2
C++ Library handling files from Star Wars Battlefront 2 (2005) and the Mod Tools.<br />
<br />
Join us on [Discord](https://discord.com/invite/nNUapcU)<br />
<br />
This library is capable of reading various proprietary file formats from the old Star Wars Battlefront 2 game, focusing primarily on *munged* file formats, and providing desired data (models, textures, terrain, sounds, etc...) to the user in a high level, easy to use manner.<br />
From how this library is implemented on a low level, altering any value, or even creating a *munged* file from scratch is technically possible, although at this point write serializers are not implemented yet.
<br />
## Example
```
#include <stdio.h>
#include <LibSWBF2/LibSWBF2.h>

using LibSWBF2::Wrappers::Level;
using LibSWBF2::Wrappers::Texture;
using LibSWBF2::ETextureFormat;

int main()
{
    Level* lvl = Level::FromFile("geo1.lvl");
    const Texture* texture = lvl->GetTexture("geo_main_1");

    uint16_t width, height;
    const uint8_t* data;

    // param 1: Desired format you want the image data to be in. 
    //          Resulting data is always uncompressed. 
    //          The lib handles decompression and conversion, if necessary
    // param 2: Mip map index. Use 0 to always get the highest available resolution.
    texture->GetImageData(ETextureFormat::B8_G8_R8_A8, 0, width, height, data);

    // Now, do what you want with the image data. Copy, export, whatever.
    printf("Texture 'geo_main_1' has a resolution of %ix%i pixels", width, height);

    // This will free the Level and all it's children.
    // Note that the `data` pointer will get invalid once the Level instance is destroyed!
    Level::Destroy(lvl);
    return 0;
}
```

## Supported file formats
- MSH
- LVL
- BNK
- ZAFBIN
- ZAABIN

## How to build 
### Linux Requirements
- git
- gcc or clang
- cmake
### Windows Requirements 
- git
- MSVC (Visual Studio) 
- cmake
### Steps 
1. `git clone --recursive https://github.com/Ben1138/LibSWBF2.git`
2. `cd ./LibSWBF2`
3. `cmake -S ./ -B ./build`
4. `cmake --build ./build Release`
