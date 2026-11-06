// #if defined(__3DS__)

#include "platform.hpp"

// platform-specific includes

#include <3ds.h>
#include <citro3d.h>
#include <tex3ds.h>

// graphics

#include "kitten_t3x.h"

// defines

#define CLEAR_COLOR 0x68B0D8FF

#define DISPLAY_TRANSFER_FLAGS                                                                   \
  (GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) |               \
   GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
   GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

static C3D_Tex kitten_tex;

static C3D_RenderTarget *rendertarget_mainscreen;

// functions

int platform::graphics_begin()
{
  C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

  // Initialize the render target
  rendertarget_mainscreen = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
  C3D_RenderTargetSetOutput(rendertarget_mainscreen, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);

  // Create a console (text screen) on the Bottom Screen
  gfxInitDefault();
  consoleInit(GFX_BOTTOM, NULL);

  return 0;
}

int platform::graphics_end()
{
  // Deinitialize graphics
  C3D_Fini();
  gfxExit();

  return 0;
}

/*/ Helper function for loading a texture from memory
static bool loadTextureFromMem(C3D_Tex *tex, C3D_TexCube *cube, const void *data, size_t size)
{
  Tex3DS_Texture t3x = Tex3DS_TextureImport(data, size, tex, cube, false);
  if (!t3x)
    return false;

  // Delete the t3x object since we don't need it
  Tex3DS_TextureFree(t3x);
  return true;
}

int platform::load_texture()
{
  C3D_Tex tex;
  size_t tex_size;

  // Load the texture and bind it to the first texture unit
  if (!loadTextureFromMem(&tex, NULL, &tex, tex_size))
    svcBreak(USERBREAK_PANIC);
  C3D_TexSetFilter(&tex, GPU_LINEAR, GPU_NEAREST);
  C3D_TexBind(0, &tex);

  return 0;
}
//*/

int platform::main_loop()
{
  if (!aptMainLoop())
    return 2;

  hidScanInput();

  // Respond to user input
  int kDown = hidKeysDown();
  if (kDown & KEY_SELECT)
    return 1; // break in order to return to hbmenu

  return 0;
}

int platform::draw()
{
  // Render the scene
  C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
  C3D_RenderTargetClear(rendertarget_mainscreen, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
  C3D_FrameDrawOn(rendertarget_mainscreen);

  // sceneRender();

  C3D_FrameEnd(0);
  return 0;
}

void platform::cleanup()
{
  // Free the texture
  C3D_TexDelete(&kitten_tex);
}

void platform::log(int input)
{
  printf("%i\n", input);
}

void platform::log(const char *input)
{
  printf("%s\n", input);
}

void platform::log(std::string input)
{
  printf("%s\n", input.c_str());
}

// #endif