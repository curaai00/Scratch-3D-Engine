#pragma once

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#error Windows_OS
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include "SDL.h"
#include "SDL_image.h"
#endif

#include <string>

struct Resource
{
    Resource(const std::string& rsc_path)
        : rsc_path(rsc_path)
        , textured(true)
    {
        rsc = IMG_Load(rsc_path.c_str());
        auto res = SDL_GetError();
    }
    Resource(SDL_Color c)
        : textured(false)
    {
        color.r = c.r;
        color.g = c.g;
        color.b = c.b;
        color.a = c.a;
    }

    SDL_Color pixel(float x, float y) const
    {
        if (textured) {
            const uint _x = std::fmod(rsc->w * x, rsc->w - 1.0f);
            const uint _y = std::fmod(rsc->h * y, rsc->h - 1.0f);
            return pixel(_x, _y);

        } else {
            return color;
        }
    }
    SDL_Color pixel(const uint x, const uint y) const
    {
        if (!textured)
            return color;

        int bpp = rsc->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        uint8_t* p = (uint8_t*)rsc->pixels + y * rsc->pitch + x * bpp;
        uint32_t _pixel;
        switch (bpp) {
            case 1:
                _pixel = static_cast<uint32_t>(*p);
                break;
            case 2:
                _pixel = static_cast<uint32_t>(*(uint16_t*)p);
                break;

            case 3:
                if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                    _pixel = p[0] << 16 | p[1] << 8 | p[2];
                else
                    _pixel = p[0] | p[1] << 8 | p[2] << 16;
                break;
            case 4:
                _pixel = static_cast<uint32_t>(*(uint32_t*)p);
                break;
            default:
                return SDL_Color();
        }
        SDL_Color rgb;
        SDL_GetRGB(_pixel, rsc->format, &rgb.r, &rgb.g, &rgb.b);
        rgb.a = 255;
        return rgb;
    }

    bool textured;
    // texture elements
    const std::string rsc_path;
    SDL_Surface* rsc;
    // not texture elements
    SDL_Color color;
};