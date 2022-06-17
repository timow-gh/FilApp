#include <Core/Utils/Assert.hpp>
#include <FilApp/FilAppConversion.hpp>
#include <FilApp/FilamentCoordinateSystem.hpp>
DISABLE_ALL_WARNINGS
#include <utils/Panic.h>
ENABLE_ALL_WARNINGS

using namespace Graphics;

namespace FilApp
{
filament::backend::Backend toFilamentBackend(BackendMode backendMode)
{
    switch (backendMode)
    {
    case BackendMode::VULKAN: return filament::backend::Backend::VULKAN;
    case BackendMode::OPENGL: return filament::backend::Backend ::OPENGL;
    default: PANIC_LOG("BackendMode not implemented."); return filament::backend::Backend::DEFAULT;
    }
}

filament::camutils::Mode toFilamentCameraMode(ViewConfig::CameraMode cameraMode)
{
    switch (cameraMode)
    {
    case ViewConfig::CameraMode::ORBIT: return filament::camutils::Mode::ORBIT;
    default: PANIC_LOG("CameraMode not implemented."); return filament::camutils::Mode::FREE_FLIGHT;
    }
}

filament::Camera::Projection toFilamentProjection(ViewConfig::CameraProjection cameraProjection)
{
    switch (cameraProjection)
    {
    case ViewConfig::CameraProjection::ORTHOGRAPHIC: return filament::Camera::Projection::ORTHO;
    case ViewConfig::CameraProjection::PERSPECTIVE:
        return filament::Camera::Projection::PERSPECTIVE;
    }
    return filament::Camera::Projection::ORTHO;
}

filament::camutils::Fov
toFilamentFovDirection(ViewConfig::FieldOfViewDirection fieldOfViewDirection, FilamentCamUtilsTag)
{
    switch (fieldOfViewDirection)
    {
    case ViewConfig::FieldOfViewDirection::HORIZONTAL: return filament::camutils::Fov::HORIZONTAL;
    case ViewConfig::FieldOfViewDirection::VERTICAL: return filament::camutils::Fov::VERTICAL;
    default:
    {
        CORE_POSTCONDITION_ASSERT(false, "ViewConfig::FieldOfViewDirection not defined.");
        return filament::camutils::Fov::VERTICAL;
    }
    }
}

filament::Camera::Fov toFilamentFovDirection(ViewConfig::FieldOfViewDirection fieldOfViewDirection,
                                             FilamentCameraTag)
{
    switch (fieldOfViewDirection)
    {
    case ViewConfig::FieldOfViewDirection::HORIZONTAL: return filament::Camera::Fov::HORIZONTAL;
    case ViewConfig::FieldOfViewDirection::VERTICAL: return filament::Camera::Fov::VERTICAL;
    default:
    {
        CORE_POSTCONDITION_ASSERT(false, "ViewConfig::FieldOfViewDirection not defined.");
        return filament::Camera::Fov::VERTICAL;
    }
    }
}

filament::Viewport toFilamentViewport(const Viewport& viewport)
{
    return {static_cast<int32_t>(viewport.left),
            static_cast<int32_t>(viewport.bottom),
            viewport.width,
            viewport.height};
}

filament::math::float4 vec4ToFloat4(const Vec4& vec4)
{
    return {vec4[0], vec4[1], vec4[2], vec4[3]};
}

filament::math::float3 vec3ToFloat3(const Vec3& vec3)
{
    return {vec3[0], vec3[1], vec3[2]};
}

Vec3 float3ToVec3(const filament::math::float3& float3Vec)
{
    return {float3Vec[0], float3Vec[1], float3Vec[2]};
}

Vec4 float4ToVec4(const filament::math::float4& float4Vec)
{
    return {float4Vec[0], float4Vec[1], float4Vec[2], float4Vec[3]};
}

filament::math::float3 toFilamentCS(const Vec3& vec3)
{
    return globalCSToFilCS3() * vec3ToFloat3(vec3);
}

filament::math::float4 toFilamentCS(const Vec4& vec4)
{
    return globalCSToFilCS4() * vec4ToFloat4(vec4);
}

Vec3 toGlobalCS(const filament::math::float3& floatVec)
{
    return float3ToVec3(filCSToGlobalCS3() * floatVec);
}

Vec4 toGlobalCS(const filament::math::float4& floatVec)
{
    return float4ToVec4(filCSToGlobalCS4() * floatVec);
}

SDL_Scancode toSDLScancode(KeyScancode scancode)
{
    switch (scancode)
    {
    case KeyScancode::SCANCODE_UNKNOWN: return SDL_SCANCODE_UNKNOWN;
    case KeyScancode::SCANCODE_A: return SDL_SCANCODE_A;
    case KeyScancode::SCANCODE_B: return SDL_SCANCODE_B;
    case KeyScancode::SCANCODE_C: return SDL_SCANCODE_C;
    case KeyScancode::SCANCODE_D: return SDL_SCANCODE_D;
    case KeyScancode::SCANCODE_E: return SDL_SCANCODE_E;
    case KeyScancode::SCANCODE_F: return SDL_SCANCODE_F;
    case KeyScancode::SCANCODE_G: return SDL_SCANCODE_G;
    case KeyScancode::SCANCODE_H: return SDL_SCANCODE_H;
    case KeyScancode::SCANCODE_I: return SDL_SCANCODE_I;
    case KeyScancode::SCANCODE_J: return SDL_SCANCODE_J;
    case KeyScancode::SCANCODE_K: return SDL_SCANCODE_K;
    case KeyScancode::SCANCODE_L: return SDL_SCANCODE_L;
    case KeyScancode::SCANCODE_M: return SDL_SCANCODE_M;
    case KeyScancode::SCANCODE_N: return SDL_SCANCODE_N;
    case KeyScancode::SCANCODE_O: return SDL_SCANCODE_O;
    case KeyScancode::SCANCODE_P: return SDL_SCANCODE_P;
    case KeyScancode::SCANCODE_Q: return SDL_SCANCODE_Q;
    case KeyScancode::SCANCODE_R: return SDL_SCANCODE_R;
    case KeyScancode::SCANCODE_S: return SDL_SCANCODE_S;
    case KeyScancode::SCANCODE_T: return SDL_SCANCODE_T;
    case KeyScancode::SCANCODE_U: return SDL_SCANCODE_U;
    case KeyScancode::SCANCODE_V: return SDL_SCANCODE_V;
    case KeyScancode::SCANCODE_W: return SDL_SCANCODE_W;
    case KeyScancode::SCANCODE_X: return SDL_SCANCODE_X;
    case KeyScancode::SCANCODE_Y: return SDL_SCANCODE_Y;
    case KeyScancode::SCANCODE_1: return SDL_SCANCODE_1;
    case KeyScancode::SCANCODE_2: return SDL_SCANCODE_2;
    case KeyScancode::SCANCODE_3: return SDL_SCANCODE_3;
    case KeyScancode::SCANCODE_4: return SDL_SCANCODE_4;
    case KeyScancode::SCANCODE_5: return SDL_SCANCODE_5;
    case KeyScancode::SCANCODE_6: return SDL_SCANCODE_6;
    case KeyScancode::SCANCODE_7: return SDL_SCANCODE_7;
    case KeyScancode::SCANCODE_8: return SDL_SCANCODE_8;
    case KeyScancode::SCANCODE_9: return SDL_SCANCODE_9;
    case KeyScancode::SCANCODE_0: return SDL_SCANCODE_0;
    case KeyScancode::SCANCODE_RETURN: return SDL_SCANCODE_RETURN;
    case KeyScancode::SCANCODE_ESCAPE: return SDL_SCANCODE_ESCAPE;
    case KeyScancode::SCANCODE_BACKSPACE: return SDL_SCANCODE_BACKSPACE;
    case KeyScancode::SCANCODE_TAB: return SDL_SCANCODE_TAB;
    case KeyScancode::SCANCODE_SPACE: return SDL_SCANCODE_SPACE;
    case KeyScancode::SCANCODE_MINUS: return SDL_SCANCODE_MINUS;
    case KeyScancode::SCANCODE_EQUALS: return SDL_SCANCODE_EQUALS;
    case KeyScancode::SCANCODE_LEFTBRACKET: return SDL_SCANCODE_LEFTBRACKET;
    case KeyScancode::SCANCODE_RIGHTBRACKET: return SDL_SCANCODE_RIGHTBRACKET;
    case KeyScancode::SCANCODE_NONUSHASH: return SDL_SCANCODE_NONUSHASH;
    case KeyScancode::SCANCODE_SEMICOLON: return SDL_SCANCODE_SEMICOLON;
    case KeyScancode::SCANCODE_APOSTROPHE: return SDL_SCANCODE_APOSTROPHE;
    case KeyScancode::SCANCODE_GRAVE: return SDL_SCANCODE_GRAVE;
    case KeyScancode::SCANCODE_COMMA: return SDL_SCANCODE_COMMA;
    case KeyScancode::SCANCODE_PERIOD: return SDL_SCANCODE_PERIOD;
    case KeyScancode::SCANCODE_SLASH: return SDL_SCANCODE_SLASH;
    case KeyScancode::SCANCODE_CAPSLOCK: return SDL_SCANCODE_CAPSLOCK;
    case KeyScancode::SCANCODE_F1: return SDL_SCANCODE_F1;
    case KeyScancode::SCANCODE_F2: return SDL_SCANCODE_F2;
    case KeyScancode::SCANCODE_F3: return SDL_SCANCODE_F3;
    case KeyScancode::SCANCODE_F4: return SDL_SCANCODE_F4;
    case KeyScancode::SCANCODE_F5: return SDL_SCANCODE_F5;
    case KeyScancode::SCANCODE_F6: return SDL_SCANCODE_F6;
    case KeyScancode::SCANCODE_F7: return SDL_SCANCODE_F7;
    case KeyScancode::SCANCODE_F8: return SDL_SCANCODE_F8;
    case KeyScancode::SCANCODE_F9: return SDL_SCANCODE_F9;
    case KeyScancode::SCANCODE_F10: return SDL_SCANCODE_F10;
    case KeyScancode::SCANCODE_F11: return SDL_SCANCODE_F11;
    case KeyScancode::SCANCODE_F12: return SDL_SCANCODE_F12;
    case KeyScancode::SCANCODE_PRINTSCREEN: return SDL_SCANCODE_PRINTSCREEN;
    case KeyScancode::SCANCODE_SCROLLLOCK: return SDL_SCANCODE_SCROLLLOCK;
    case KeyScancode::SCANCODE_PAUSE: return SDL_SCANCODE_PAUSE;
    case KeyScancode::SCANCODE_INSERT: return SDL_SCANCODE_INSERT;
    case KeyScancode::SCANCODE_HOME: return SDL_SCANCODE_HOME;
    case KeyScancode::SCANCODE_PAGEUP: return SDL_SCANCODE_PAGEUP;
    case KeyScancode::SCANCODE_DELETE: return SDL_SCANCODE_DELETE;
    case KeyScancode::SCANCODE_END: return SDL_SCANCODE_END;
    case KeyScancode::SCANCODE_PAGEDOWN: return SDL_SCANCODE_PAGEDOWN;
    case KeyScancode::SCANCODE_RIGHT: return SDL_SCANCODE_RIGHT;
    case KeyScancode::SCANCODE_LEFT: return SDL_SCANCODE_LEFT;
    case KeyScancode::SCANCODE_DOWN: return SDL_SCANCODE_DOWN;
    case KeyScancode::SCANCODE_UP: return SDL_SCANCODE_UP;
    case KeyScancode::SCANCODE_NUMLOCKCLEAR: return SDL_SCANCODE_NUMLOCKCLEAR;
    case KeyScancode::SCANCODE_KP_DIVIDE: return SDL_SCANCODE_KP_DIVIDE;
    case KeyScancode::SCANCODE_KP_MULTIPLY: return SDL_SCANCODE_KP_MULTIPLY;
    case KeyScancode::SCANCODE_KP_MINUS: return SDL_SCANCODE_KP_MINUS;
    case KeyScancode::SCANCODE_KP_PLUS: return SDL_SCANCODE_KP_PLUS;
    case KeyScancode::SCANCODE_KP_ENTER: return SDL_SCANCODE_KP_ENTER;
    case KeyScancode::SCANCODE_KP_1: return SDL_SCANCODE_KP_1;
    case KeyScancode::SCANCODE_KP_2: return SDL_SCANCODE_KP_2;
    case KeyScancode::SCANCODE_KP_3: return SDL_SCANCODE_KP_3;
    case KeyScancode::SCANCODE_KP_4: return SDL_SCANCODE_KP_4;
    case KeyScancode::SCANCODE_KP_5: return SDL_SCANCODE_KP_5;
    case KeyScancode::SCANCODE_KP_6: return SDL_SCANCODE_KP_6;
    case KeyScancode::SCANCODE_KP_7: return SDL_SCANCODE_KP_7;
    case KeyScancode::SCANCODE_KP_8: return SDL_SCANCODE_KP_8;
    case KeyScancode::SCANCODE_KP_9: return SDL_SCANCODE_KP_9;
    case KeyScancode::SCANCODE_KP_0: return SDL_SCANCODE_KP_0;
    case KeyScancode::SCANCODE_KP_PERIOD: return SDL_SCANCODE_KP_PERIOD;
    case KeyScancode::SCANCODE_NONUSBACKSLASH: return SDL_SCANCODE_NONUSBACKSLASH;
    case KeyScancode::SCANCODE_APPLICATION: return SDL_SCANCODE_APPLICATION;
    case KeyScancode::SCANCODE_POWER: return SDL_SCANCODE_POWER;
    case KeyScancode::SCANCODE_KP_EQUALS: return SDL_SCANCODE_KP_EQUALS;
    case KeyScancode::SCANCODE_F13: return SDL_SCANCODE_F13;
    case KeyScancode::SCANCODE_F14: return SDL_SCANCODE_F14;
    case KeyScancode::SCANCODE_F15: return SDL_SCANCODE_F15;
    case KeyScancode::SCANCODE_F16: return SDL_SCANCODE_F16;
    case KeyScancode::SCANCODE_F17: return SDL_SCANCODE_F17;
    case KeyScancode::SCANCODE_F18: return SDL_SCANCODE_F18;
    case KeyScancode::SCANCODE_F19: return SDL_SCANCODE_F19;
    case KeyScancode::SCANCODE_F20: return SDL_SCANCODE_F20;
    case KeyScancode::SCANCODE_F21: return SDL_SCANCODE_F21;
    case KeyScancode::SCANCODE_F22: return SDL_SCANCODE_F22;
    case KeyScancode::SCANCODE_F23: return SDL_SCANCODE_F23;
    case KeyScancode::SCANCODE_F24: return SDL_SCANCODE_F24;
    case KeyScancode::SCANCODE_EXECUTE: return SDL_SCANCODE_EXECUTE;
    case KeyScancode::SCANCODE_HELP: return SDL_SCANCODE_HELP;
    case KeyScancode::SCANCODE_MENU: return SDL_SCANCODE_MENU;
    case KeyScancode::SCANCODE_SELECT: return SDL_SCANCODE_SELECT;
    case KeyScancode::SCANCODE_STOP: return SDL_SCANCODE_STOP;
    case KeyScancode::SCANCODE_AGAIN: return SDL_SCANCODE_AGAIN;
    case KeyScancode::SCANCODE_UNDO: return SDL_SCANCODE_UNDO;
    case KeyScancode::SCANCODE_CUT: return SDL_SCANCODE_CUT;
    case KeyScancode::SCANCODE_COPY: return SDL_SCANCODE_COPY;
    case KeyScancode::SCANCODE_PASTE: return SDL_SCANCODE_PASTE;
    case KeyScancode::SCANCODE_FIND: return SDL_SCANCODE_FIND;
    case KeyScancode::SCANCODE_MUTE: return SDL_SCANCODE_MUTE;
    case KeyScancode::SCANCODE_VOLUMEUP: return SDL_SCANCODE_VOLUMEUP;
    case KeyScancode::SCANCODE_VOLUMEDOWN: return SDL_SCANCODE_VOLUMEDOWN;
    case KeyScancode::SCANCODE_KP_COMMA: return SDL_SCANCODE_KP_COMMA;
    case KeyScancode::SCANCODE_KP_EQUALSAS400: return SDL_SCANCODE_KP_EQUALSAS400;
    case KeyScancode::SCANCODE_INTERNATIONAL1: return SDL_SCANCODE_INTERNATIONAL1;
    case KeyScancode::SCANCODE_INTERNATIONAL2: return SDL_SCANCODE_INTERNATIONAL2;
    case KeyScancode::SCANCODE_INTERNATIONAL3: return SDL_SCANCODE_INTERNATIONAL3;
    case KeyScancode::SCANCODE_INTERNATIONAL4: return SDL_SCANCODE_INTERNATIONAL4;
    case KeyScancode::SCANCODE_INTERNATIONAL5: return SDL_SCANCODE_INTERNATIONAL5;
    case KeyScancode::SCANCODE_INTERNATIONAL6: return SDL_SCANCODE_INTERNATIONAL6;
    case KeyScancode::SCANCODE_INTERNATIONAL7: return SDL_SCANCODE_INTERNATIONAL7;
    case KeyScancode::SCANCODE_INTERNATIONAL8: return SDL_SCANCODE_INTERNATIONAL8;
    case KeyScancode::SCANCODE_INTERNATIONAL9: return SDL_SCANCODE_INTERNATIONAL9;
    case KeyScancode::SCANCODE_LANG1: return SDL_SCANCODE_LANG1;
    case KeyScancode::SCANCODE_LANG2: return SDL_SCANCODE_LANG2;
    case KeyScancode::SCANCODE_LANG3: return SDL_SCANCODE_LANG3;
    case KeyScancode::SCANCODE_LANG4: return SDL_SCANCODE_LANG4;
    case KeyScancode::SCANCODE_LANG5: return SDL_SCANCODE_LANG5;
    case KeyScancode::SCANCODE_LANG6: return SDL_SCANCODE_LANG6;
    case KeyScancode::SCANCODE_LANG7: return SDL_SCANCODE_LANG7;
    case KeyScancode::SCANCODE_LANG8: return SDL_SCANCODE_LANG8;
    case KeyScancode::SCANCODE_LANG9: return SDL_SCANCODE_LANG9;
    case KeyScancode::SCANCODE_ALTERASE: return SDL_SCANCODE_ALTERASE;
    case KeyScancode::SCANCODE_SYSREQ: return SDL_SCANCODE_SYSREQ;
    case KeyScancode::SCANCODE_CANCEL: return SDL_SCANCODE_CANCEL;
    case KeyScancode::SCANCODE_CLEAR: return SDL_SCANCODE_CLEAR;
    case KeyScancode::SCANCODE_PRIOR: return SDL_SCANCODE_PRIOR;
    case KeyScancode::SCANCODE_RETURN2: return SDL_SCANCODE_RETURN2;
    case KeyScancode::SCANCODE_SEPARATOR: return SDL_SCANCODE_SEPARATOR;
    case KeyScancode::SCANCODE_OUT: return SDL_SCANCODE_OUT;
    case KeyScancode::SCANCODE_OPER: return SDL_SCANCODE_OPER;
    case KeyScancode::SCANCODE_CLEARAGAIN: return SDL_SCANCODE_CLEARAGAIN;
    case KeyScancode::SCANCODE_CRSEL: return SDL_SCANCODE_CRSEL;
    case KeyScancode::SCANCODE_EXSEL: return SDL_SCANCODE_EXSEL;
    case KeyScancode::SCANCODE_KP_00: return SDL_SCANCODE_KP_00;
    case KeyScancode::SCANCODE_KP_000: return SDL_SCANCODE_KP_000;
    case KeyScancode::SCANCODE_THOUSANDSSEPARATOR: return SDL_SCANCODE_THOUSANDSSEPARATOR;
    case KeyScancode::SCANCODE_DECIMALSEPARATOR: return SDL_SCANCODE_DECIMALSEPARATOR;
    case KeyScancode::SCANCODE_CURRENCYUNIT: return SDL_SCANCODE_CURRENCYUNIT;
    case KeyScancode::SCANCODE_CURRENCYSUBUNIT: return SDL_SCANCODE_CURRENCYSUBUNIT;
    case KeyScancode::SCANCODE_KP_LEFTPAREN: return SDL_SCANCODE_KP_LEFTPAREN;
    case KeyScancode::SCANCODE_KP_RIGHTPAREN: return SDL_SCANCODE_KP_RIGHTPAREN;
    case KeyScancode::SCANCODE_KP_LEFTBRACE: return SDL_SCANCODE_KP_LEFTBRACE;
    case KeyScancode::SCANCODE_KP_RIGHTBRACE: return SDL_SCANCODE_KP_RIGHTBRACE;
    case KeyScancode::SCANCODE_KP_TAB: return SDL_SCANCODE_KP_TAB;
    case KeyScancode::SCANCODE_KP_BACKSPACE: return SDL_SCANCODE_KP_BACKSPACE;
    case KeyScancode::SCANCODE_KP_A: return SDL_SCANCODE_KP_A;
    case KeyScancode::SCANCODE_KP_B: return SDL_SCANCODE_KP_B;
    case KeyScancode::SCANCODE_KP_C: return SDL_SCANCODE_KP_C;
    case KeyScancode::SCANCODE_KP_D: return SDL_SCANCODE_KP_D;
    case KeyScancode::SCANCODE_KP_E: return SDL_SCANCODE_KP_E;
    case KeyScancode::SCANCODE_KP_F: return SDL_SCANCODE_KP_F;
    case KeyScancode::SCANCODE_KP_XOR: return SDL_SCANCODE_KP_XOR;
    case KeyScancode::SCANCODE_KP_POWER: return SDL_SCANCODE_KP_POWER;
    case KeyScancode::SCANCODE_KP_PERCENT: return SDL_SCANCODE_KP_PERCENT;
    case KeyScancode::SCANCODE_KP_LESS: return SDL_SCANCODE_KP_LESS;
    case KeyScancode::SCANCODE_KP_GREATER: return SDL_SCANCODE_KP_GREATER;
    case KeyScancode::SCANCODE_KP_AMPERSAND: return SDL_SCANCODE_KP_AMPERSAND;
    case KeyScancode::SCANCODE_KP_DBLAMPERSAND: return SDL_SCANCODE_KP_DBLAMPERSAND;
    case KeyScancode::SCANCODE_KP_VERTICALBAR: return SDL_SCANCODE_KP_VERTICALBAR;
    case KeyScancode::SCANCODE_KP_DBLVERTICALBAR: return SDL_SCANCODE_KP_DBLVERTICALBAR;
    case KeyScancode::SCANCODE_KP_COLON: return SDL_SCANCODE_KP_COLON;
    case KeyScancode::SCANCODE_KP_HASH: return SDL_SCANCODE_KP_HASH;
    case KeyScancode::SCANCODE_KP_SPACE: return SDL_SCANCODE_KP_SPACE;
    case KeyScancode::SCANCODE_KP_AT: return SDL_SCANCODE_KP_AT;
    case KeyScancode::SCANCODE_KP_EXCLAM: return SDL_SCANCODE_KP_EXCLAM;
    case KeyScancode::SCANCODE_KP_MEMSTORE: return SDL_SCANCODE_KP_MEMSTORE;
    case KeyScancode::SCANCODE_KP_MEMRECALL: return SDL_SCANCODE_KP_MEMRECALL;
    case KeyScancode::SCANCODE_KP_MEMCLEAR: return SDL_SCANCODE_KP_MEMCLEAR;
    case KeyScancode::SCANCODE_KP_MEMADD: return SDL_SCANCODE_KP_MEMADD;
    case KeyScancode::SCANCODE_KP_MEMSUBTRACT: return SDL_SCANCODE_KP_MEMSUBTRACT;
    case KeyScancode::SCANCODE_KP_MEMMULTIPLY: return SDL_SCANCODE_KP_MEMMULTIPLY;
    case KeyScancode::SCANCODE_KP_MEMDIVIDE: return SDL_SCANCODE_KP_MEMDIVIDE;
    case KeyScancode::SCANCODE_KP_PLUSMINUS: return SDL_SCANCODE_KP_PLUSMINUS;
    case KeyScancode::SCANCODE_KP_CLEAR: return SDL_SCANCODE_KP_CLEAR;
    case KeyScancode::SCANCODE_KP_CLEARENTRY: return SDL_SCANCODE_KP_CLEARENTRY;
    case KeyScancode::SCANCODE_KP_BINARY: return SDL_SCANCODE_KP_BINARY;
    case KeyScancode::SCANCODE_KP_OCTAL: return SDL_SCANCODE_KP_OCTAL;
    case KeyScancode::SCANCODE_KP_DECIMAL: return SDL_SCANCODE_KP_DECIMAL;
    case KeyScancode::SCANCODE_KP_HEXADECIMAL: return SDL_SCANCODE_KP_HEXADECIMAL;
    case KeyScancode::SCANCODE_LCTRL: return SDL_SCANCODE_LCTRL;
    case KeyScancode::SCANCODE_LSHIFT: return SDL_SCANCODE_LSHIFT;
    case KeyScancode::SCANCODE_LALT: return SDL_SCANCODE_LALT;
    case KeyScancode::SCANCODE_LGUI: return SDL_SCANCODE_LGUI;
    case KeyScancode::SCANCODE_RCTRL: return SDL_SCANCODE_RCTRL;
    case KeyScancode::SCANCODE_RSHIFT: return SDL_SCANCODE_RSHIFT;
    case KeyScancode::SCANCODE_RALT: return SDL_SCANCODE_RALT;
    case KeyScancode::SCANCODE_RGUI: return SDL_SCANCODE_RGUI;
    case KeyScancode::SCANCODE_MODE: return SDL_SCANCODE_MODE;
    case KeyScancode::SCANCODE_AUDIONEXT: return SDL_SCANCODE_AUDIONEXT;
    case KeyScancode::SCANCODE_AUDIOPREV: return SDL_SCANCODE_AUDIOPREV;
    case KeyScancode::SCANCODE_AUDIOSTOP: return SDL_SCANCODE_AUDIOSTOP;
    case KeyScancode::SCANCODE_AUDIOPLAY: return SDL_SCANCODE_AUDIOPLAY;
    case KeyScancode::SCANCODE_AUDIOMUTE: return SDL_SCANCODE_AUDIOMUTE;
    case KeyScancode::SCANCODE_MEDIASELECT: return SDL_SCANCODE_MEDIASELECT;
    case KeyScancode::SCANCODE_WWW: return SDL_SCANCODE_WWW;
    case KeyScancode::SCANCODE_MAIL: return SDL_SCANCODE_MAIL;
    case KeyScancode::SCANCODE_CALCULATOR: return SDL_SCANCODE_CALCULATOR;
    case KeyScancode::SCANCODE_COMPUTER: return SDL_SCANCODE_COMPUTER;
    case KeyScancode::SCANCODE_AC_SEARCH: return SDL_SCANCODE_AC_SEARCH;
    case KeyScancode::SCANCODE_AC_HOME: return SDL_SCANCODE_AC_HOME;
    case KeyScancode::SCANCODE_AC_BACK: return SDL_SCANCODE_AC_BACK;
    case KeyScancode::SCANCODE_AC_FORWARD: return SDL_SCANCODE_AC_FORWARD;
    case KeyScancode::SCANCODE_AC_STOP: return SDL_SCANCODE_AC_STOP;
    case KeyScancode::SCANCODE_AC_REFRESH: return SDL_SCANCODE_AC_REFRESH;
    case KeyScancode::SCANCODE_AC_BOOKMARKS: return SDL_SCANCODE_AC_BOOKMARKS;
    case KeyScancode::SCANCODE_BRIGHTNESSDOWN: return SDL_SCANCODE_BRIGHTNESSDOWN;
    case KeyScancode::SCANCODE_BRIGHTNESSUP: return SDL_SCANCODE_BRIGHTNESSUP;
    case KeyScancode::SCANCODE_DISPLAYSWITCH: return SDL_SCANCODE_DISPLAYSWITCH;
    case KeyScancode::SCANCODE_KBDILLUMTOGGLE: return SDL_SCANCODE_KBDILLUMTOGGLE;
    case KeyScancode::SCANCODE_KBDILLUMDOWN: return SDL_SCANCODE_KBDILLUMDOWN;
    case KeyScancode::SCANCODE_KBDILLUMUP: return SDL_SCANCODE_KBDILLUMUP;
    case KeyScancode::SCANCODE_EJECT: return SDL_SCANCODE_EJECT;
    case KeyScancode::SCANCODE_SLEEP: return SDL_SCANCODE_SLEEP;
    case KeyScancode::SCANCODE_APP1: return SDL_SCANCODE_APP1;
    case KeyScancode::SCANCODE_APP2: return SDL_SCANCODE_APP2;
    case KeyScancode::SCANCODE_AUDIOREWIND: return SDL_SCANCODE_AUDIOREWIND;
    case KeyScancode::SCANCODE_AUDIOFASTFORWARD: return SDL_SCANCODE_AUDIOFASTFORWARD;
    default:
        CORE_POSTCONDITION_DEBUG_ASSERT(false, "KeyScancode not known.");
        return SDL_SCANCODE_UNKNOWN;
    }
}
KeyScancode toKeyScancode(SDL_Scancode sdlScancode)
{
    switch (sdlScancode)
    {
    case SDL_SCANCODE_UNKNOWN: return KeyScancode::SCANCODE_UNKNOWN;
    case SDL_SCANCODE_A: return KeyScancode::SCANCODE_A;
    case SDL_SCANCODE_B: return KeyScancode::SCANCODE_B;
    case SDL_SCANCODE_C: return KeyScancode::SCANCODE_C;
    case SDL_SCANCODE_D: return KeyScancode::SCANCODE_D;
    case SDL_SCANCODE_E: return KeyScancode::SCANCODE_E;
    case SDL_SCANCODE_F: return KeyScancode::SCANCODE_F;
    case SDL_SCANCODE_G: return KeyScancode::SCANCODE_G;
    case SDL_SCANCODE_H: return KeyScancode::SCANCODE_H;
    case SDL_SCANCODE_I: return KeyScancode::SCANCODE_I;
    case SDL_SCANCODE_J: return KeyScancode::SCANCODE_J;
    case SDL_SCANCODE_K: return KeyScancode::SCANCODE_K;
    case SDL_SCANCODE_L: return KeyScancode::SCANCODE_L;
    case SDL_SCANCODE_M: return KeyScancode::SCANCODE_M;
    case SDL_SCANCODE_N: return KeyScancode::SCANCODE_N;
    case SDL_SCANCODE_O: return KeyScancode::SCANCODE_O;
    case SDL_SCANCODE_P: return KeyScancode::SCANCODE_P;
    case SDL_SCANCODE_Q: return KeyScancode::SCANCODE_Q;
    case SDL_SCANCODE_R: return KeyScancode::SCANCODE_R;
    case SDL_SCANCODE_S: return KeyScancode::SCANCODE_S;
    case SDL_SCANCODE_T: return KeyScancode::SCANCODE_T;
    case SDL_SCANCODE_U: return KeyScancode::SCANCODE_U;
    case SDL_SCANCODE_V: return KeyScancode::SCANCODE_V;
    case SDL_SCANCODE_W: return KeyScancode::SCANCODE_W;
    case SDL_SCANCODE_X: return KeyScancode::SCANCODE_X;
    case SDL_SCANCODE_Y: return KeyScancode::SCANCODE_Y;
    case SDL_SCANCODE_Z: return KeyScancode::SCANCODE_Z;
    case SDL_SCANCODE_1: return KeyScancode::SCANCODE_1;
    case SDL_SCANCODE_2: return KeyScancode::SCANCODE_2;
    case SDL_SCANCODE_3: return KeyScancode::SCANCODE_3;
    case SDL_SCANCODE_4: return KeyScancode::SCANCODE_4;
    case SDL_SCANCODE_5: return KeyScancode::SCANCODE_5;
    case SDL_SCANCODE_6: return KeyScancode::SCANCODE_6;
    case SDL_SCANCODE_7: return KeyScancode::SCANCODE_7;
    case SDL_SCANCODE_8: return KeyScancode::SCANCODE_8;
    case SDL_SCANCODE_9: return KeyScancode::SCANCODE_9;
    case SDL_SCANCODE_0: return KeyScancode::SCANCODE_0;
    case SDL_SCANCODE_RETURN: return KeyScancode::SCANCODE_RETURN;
    case SDL_SCANCODE_ESCAPE: return KeyScancode::SCANCODE_ESCAPE;
    case SDL_SCANCODE_BACKSPACE: return KeyScancode::SCANCODE_BACKSPACE;
    case SDL_SCANCODE_TAB: return KeyScancode::SCANCODE_TAB;
    case SDL_SCANCODE_SPACE: return KeyScancode::SCANCODE_SPACE;
    case SDL_SCANCODE_MINUS: return KeyScancode::SCANCODE_MINUS;
    case SDL_SCANCODE_EQUALS: return KeyScancode::SCANCODE_EQUALS;
    case SDL_SCANCODE_LEFTBRACKET: return KeyScancode::SCANCODE_LEFTBRACKET;
    case SDL_SCANCODE_RIGHTBRACKET: return KeyScancode::SCANCODE_RIGHTBRACKET;
    case SDL_SCANCODE_NONUSHASH: return KeyScancode::SCANCODE_NONUSHASH;
    case SDL_SCANCODE_SEMICOLON: return KeyScancode::SCANCODE_SEMICOLON;
    case SDL_SCANCODE_APOSTROPHE: return KeyScancode::SCANCODE_APOSTROPHE;
    case SDL_SCANCODE_GRAVE: return KeyScancode::SCANCODE_GRAVE;
    case SDL_SCANCODE_COMMA: return KeyScancode::SCANCODE_COMMA;
    case SDL_SCANCODE_PERIOD: return KeyScancode::SCANCODE_PERIOD;
    case SDL_SCANCODE_SLASH: return KeyScancode::SCANCODE_SLASH;
    case SDL_SCANCODE_CAPSLOCK: return KeyScancode::SCANCODE_CAPSLOCK;
    case SDL_SCANCODE_F1: return KeyScancode::SCANCODE_F1;
    case SDL_SCANCODE_F2: return KeyScancode::SCANCODE_F2;
    case SDL_SCANCODE_F3: return KeyScancode::SCANCODE_F3;
    case SDL_SCANCODE_F4: return KeyScancode::SCANCODE_F4;
    case SDL_SCANCODE_F5: return KeyScancode::SCANCODE_F5;
    case SDL_SCANCODE_F6: return KeyScancode::SCANCODE_F6;
    case SDL_SCANCODE_F7: return KeyScancode::SCANCODE_F7;
    case SDL_SCANCODE_F8: return KeyScancode::SCANCODE_F8;
    case SDL_SCANCODE_F9: return KeyScancode::SCANCODE_F9;
    case SDL_SCANCODE_F10: return KeyScancode::SCANCODE_F10;
    case SDL_SCANCODE_F11: return KeyScancode::SCANCODE_F11;
    case SDL_SCANCODE_F12: return KeyScancode::SCANCODE_F12;
    case SDL_SCANCODE_PRINTSCREEN: return KeyScancode::SCANCODE_PRINTSCREEN;
    case SDL_SCANCODE_SCROLLLOCK: return KeyScancode::SCANCODE_SCROLLLOCK;
    case SDL_SCANCODE_PAUSE: return KeyScancode::SCANCODE_PAUSE;
    case SDL_SCANCODE_INSERT: return KeyScancode::SCANCODE_INSERT;
    case SDL_SCANCODE_HOME: return KeyScancode::SCANCODE_HOME;
    case SDL_SCANCODE_PAGEUP: return KeyScancode::SCANCODE_PAGEUP;
    case SDL_SCANCODE_DELETE: return KeyScancode::SCANCODE_DELETE;
    case SDL_SCANCODE_END: return KeyScancode::SCANCODE_END;
    case SDL_SCANCODE_PAGEDOWN: return KeyScancode::SCANCODE_PAGEDOWN;
    case SDL_SCANCODE_RIGHT: return KeyScancode::SCANCODE_RIGHT;
    case SDL_SCANCODE_LEFT: return KeyScancode::SCANCODE_LEFT;
    case SDL_SCANCODE_DOWN: return KeyScancode::SCANCODE_DOWN;
    case SDL_SCANCODE_UP: return KeyScancode::SCANCODE_UP;
    case SDL_SCANCODE_NUMLOCKCLEAR: return KeyScancode::SCANCODE_NUMLOCKCLEAR;
    case SDL_SCANCODE_KP_DIVIDE: return KeyScancode::SCANCODE_KP_DIVIDE;
    case SDL_SCANCODE_KP_MULTIPLY: return KeyScancode::SCANCODE_KP_MULTIPLY;
    case SDL_SCANCODE_KP_MINUS: return KeyScancode::SCANCODE_KP_MINUS;
    case SDL_SCANCODE_KP_PLUS: return KeyScancode::SCANCODE_KP_PLUS;
    case SDL_SCANCODE_KP_ENTER: return KeyScancode::SCANCODE_KP_ENTER;
    case SDL_SCANCODE_KP_1: return KeyScancode::SCANCODE_KP_1;
    case SDL_SCANCODE_KP_2: return KeyScancode::SCANCODE_KP_2;
    case SDL_SCANCODE_KP_3: return KeyScancode::SCANCODE_KP_3;
    case SDL_SCANCODE_KP_4: return KeyScancode::SCANCODE_KP_4;
    case SDL_SCANCODE_KP_5: return KeyScancode::SCANCODE_KP_5;
    case SDL_SCANCODE_KP_6: return KeyScancode::SCANCODE_KP_6;
    case SDL_SCANCODE_KP_7: return KeyScancode::SCANCODE_KP_7;
    case SDL_SCANCODE_KP_8: return KeyScancode::SCANCODE_KP_8;
    case SDL_SCANCODE_KP_9: return KeyScancode::SCANCODE_KP_9;
    case SDL_SCANCODE_KP_0: return KeyScancode::SCANCODE_KP_0;
    case SDL_SCANCODE_KP_PERIOD: return KeyScancode::SCANCODE_KP_PERIOD;
    case SDL_SCANCODE_NONUSBACKSLASH: return KeyScancode::SCANCODE_NONUSBACKSLASH;
    case SDL_SCANCODE_APPLICATION: return KeyScancode::SCANCODE_APPLICATION;
    case SDL_SCANCODE_POWER: return KeyScancode::SCANCODE_POWER;
    case SDL_SCANCODE_KP_EQUALS: return KeyScancode::SCANCODE_KP_EQUALS;
    case SDL_SCANCODE_F13: return KeyScancode::SCANCODE_F13;
    case SDL_SCANCODE_F14: return KeyScancode::SCANCODE_F14;
    case SDL_SCANCODE_F15: return KeyScancode::SCANCODE_F15;
    case SDL_SCANCODE_F16: return KeyScancode::SCANCODE_F16;
    case SDL_SCANCODE_F17: return KeyScancode::SCANCODE_F17;
    case SDL_SCANCODE_F18: return KeyScancode::SCANCODE_F18;
    case SDL_SCANCODE_F19: return KeyScancode::SCANCODE_F19;
    case SDL_SCANCODE_F20: return KeyScancode::SCANCODE_F20;
    case SDL_SCANCODE_F21: return KeyScancode::SCANCODE_F21;
    case SDL_SCANCODE_F22: return KeyScancode::SCANCODE_F22;
    case SDL_SCANCODE_F23: return KeyScancode::SCANCODE_F23;
    case SDL_SCANCODE_F24: return KeyScancode::SCANCODE_F24;
    case SDL_SCANCODE_EXECUTE: return KeyScancode::SCANCODE_EXECUTE;
    case SDL_SCANCODE_HELP: return KeyScancode::SCANCODE_HELP;
    case SDL_SCANCODE_MENU: return KeyScancode::SCANCODE_MENU;
    case SDL_SCANCODE_SELECT: return KeyScancode::SCANCODE_SELECT;
    case SDL_SCANCODE_STOP: return KeyScancode::SCANCODE_STOP;
    case SDL_SCANCODE_AGAIN: return KeyScancode::SCANCODE_AGAIN;
    case SDL_SCANCODE_UNDO: return KeyScancode::SCANCODE_UNDO;
    case SDL_SCANCODE_CUT: return KeyScancode::SCANCODE_CUT;
    case SDL_SCANCODE_COPY: return KeyScancode::SCANCODE_COPY;
    case SDL_SCANCODE_PASTE: return KeyScancode::SCANCODE_PASTE;
    case SDL_SCANCODE_FIND: return KeyScancode::SCANCODE_FIND;
    case SDL_SCANCODE_MUTE: return KeyScancode::SCANCODE_MUTE;
    case SDL_SCANCODE_VOLUMEUP: return KeyScancode::SCANCODE_VOLUMEUP;
    case SDL_SCANCODE_VOLUMEDOWN: return KeyScancode::SCANCODE_VOLUMEDOWN;
    case SDL_SCANCODE_KP_COMMA: return KeyScancode::SCANCODE_KP_COMMA;
    case SDL_SCANCODE_KP_EQUALSAS400: return KeyScancode::SCANCODE_KP_EQUALSAS400;
    case SDL_SCANCODE_INTERNATIONAL1: return KeyScancode::SCANCODE_INTERNATIONAL1;
    case SDL_SCANCODE_INTERNATIONAL2: return KeyScancode::SCANCODE_INTERNATIONAL2;
    case SDL_SCANCODE_INTERNATIONAL3: return KeyScancode::SCANCODE_INTERNATIONAL3;
    case SDL_SCANCODE_INTERNATIONAL4: return KeyScancode::SCANCODE_INTERNATIONAL4;
    case SDL_SCANCODE_INTERNATIONAL5: return KeyScancode::SCANCODE_INTERNATIONAL5;
    case SDL_SCANCODE_INTERNATIONAL6: return KeyScancode::SCANCODE_INTERNATIONAL6;
    case SDL_SCANCODE_INTERNATIONAL7: return KeyScancode::SCANCODE_INTERNATIONAL7;
    case SDL_SCANCODE_INTERNATIONAL8: return KeyScancode::SCANCODE_INTERNATIONAL8;
    case SDL_SCANCODE_INTERNATIONAL9: return KeyScancode::SCANCODE_INTERNATIONAL9;
    case SDL_SCANCODE_LANG1: return KeyScancode::SCANCODE_LANG1;
    case SDL_SCANCODE_LANG2: return KeyScancode::SCANCODE_LANG2;
    case SDL_SCANCODE_LANG3: return KeyScancode::SCANCODE_LANG3;
    case SDL_SCANCODE_LANG4: return KeyScancode::SCANCODE_LANG4;
    case SDL_SCANCODE_LANG5: return KeyScancode::SCANCODE_LANG5;
    case SDL_SCANCODE_LANG6: return KeyScancode::SCANCODE_LANG6;
    case SDL_SCANCODE_LANG7: return KeyScancode::SCANCODE_LANG7;
    case SDL_SCANCODE_LANG8: return KeyScancode::SCANCODE_LANG8;
    case SDL_SCANCODE_LANG9: return KeyScancode::SCANCODE_LANG9;
    case SDL_SCANCODE_ALTERASE: return KeyScancode::SCANCODE_ALTERASE;
    case SDL_SCANCODE_SYSREQ: return KeyScancode::SCANCODE_SYSREQ;
    case SDL_SCANCODE_CANCEL: return KeyScancode::SCANCODE_CANCEL;
    case SDL_SCANCODE_CLEAR: return KeyScancode::SCANCODE_CLEAR;
    case SDL_SCANCODE_PRIOR: return KeyScancode::SCANCODE_PRIOR;
    case SDL_SCANCODE_RETURN2: return KeyScancode::SCANCODE_RETURN2;
    case SDL_SCANCODE_SEPARATOR: return KeyScancode::SCANCODE_SEPARATOR;
    case SDL_SCANCODE_OUT: return KeyScancode::SCANCODE_OUT;
    case SDL_SCANCODE_OPER: return KeyScancode::SCANCODE_OPER;
    case SDL_SCANCODE_CLEARAGAIN: return KeyScancode::SCANCODE_CLEARAGAIN;
    case SDL_SCANCODE_CRSEL: return KeyScancode::SCANCODE_CRSEL;
    case SDL_SCANCODE_EXSEL: return KeyScancode::SCANCODE_EXSEL;
    case SDL_SCANCODE_KP_00: return KeyScancode::SCANCODE_KP_00;
    case SDL_SCANCODE_KP_000: return KeyScancode::SCANCODE_KP_000;
    case SDL_SCANCODE_THOUSANDSSEPARATOR: return KeyScancode::SCANCODE_THOUSANDSSEPARATOR;
    case SDL_SCANCODE_DECIMALSEPARATOR: return KeyScancode::SCANCODE_DECIMALSEPARATOR;
    case SDL_SCANCODE_CURRENCYUNIT: return KeyScancode::SCANCODE_CURRENCYUNIT;
    case SDL_SCANCODE_CURRENCYSUBUNIT: return KeyScancode::SCANCODE_CURRENCYSUBUNIT;
    case SDL_SCANCODE_KP_LEFTPAREN: return KeyScancode::SCANCODE_KP_LEFTPAREN;
    case SDL_SCANCODE_KP_RIGHTPAREN: return KeyScancode::SCANCODE_KP_RIGHTPAREN;
    case SDL_SCANCODE_KP_LEFTBRACE: return KeyScancode::SCANCODE_KP_LEFTBRACE;
    case SDL_SCANCODE_KP_RIGHTBRACE: return KeyScancode::SCANCODE_KP_RIGHTBRACE;
    case SDL_SCANCODE_KP_TAB: return KeyScancode::SCANCODE_KP_TAB;
    case SDL_SCANCODE_KP_BACKSPACE: return KeyScancode::SCANCODE_KP_BACKSPACE;
    case SDL_SCANCODE_KP_A: return KeyScancode::SCANCODE_KP_A;
    case SDL_SCANCODE_KP_B: return KeyScancode::SCANCODE_KP_B;
    case SDL_SCANCODE_KP_C: return KeyScancode::SCANCODE_KP_C;
    case SDL_SCANCODE_KP_D: return KeyScancode::SCANCODE_KP_D;
    case SDL_SCANCODE_KP_E: return KeyScancode::SCANCODE_KP_E;
    case SDL_SCANCODE_KP_F: return KeyScancode::SCANCODE_KP_F;
    case SDL_SCANCODE_KP_XOR: return KeyScancode::SCANCODE_KP_XOR;
    case SDL_SCANCODE_KP_POWER: return KeyScancode::SCANCODE_KP_POWER;
    case SDL_SCANCODE_KP_PERCENT: return KeyScancode::SCANCODE_KP_PERCENT;
    case SDL_SCANCODE_KP_LESS: return KeyScancode::SCANCODE_KP_LESS;
    case SDL_SCANCODE_KP_GREATER: return KeyScancode::SCANCODE_KP_GREATER;
    case SDL_SCANCODE_KP_AMPERSAND: return KeyScancode::SCANCODE_KP_AMPERSAND;
    case SDL_SCANCODE_KP_DBLAMPERSAND: return KeyScancode::SCANCODE_KP_DBLAMPERSAND;
    case SDL_SCANCODE_KP_VERTICALBAR: return KeyScancode::SCANCODE_KP_VERTICALBAR;
    case SDL_SCANCODE_KP_DBLVERTICALBAR: return KeyScancode::SCANCODE_KP_DBLVERTICALBAR;
    case SDL_SCANCODE_KP_COLON: return KeyScancode::SCANCODE_KP_COLON;
    case SDL_SCANCODE_KP_HASH: return KeyScancode::SCANCODE_KP_HASH;
    case SDL_SCANCODE_KP_SPACE: return KeyScancode::SCANCODE_KP_SPACE;
    case SDL_SCANCODE_KP_AT: return KeyScancode::SCANCODE_KP_AT;
    case SDL_SCANCODE_KP_EXCLAM: return KeyScancode::SCANCODE_KP_EXCLAM;
    case SDL_SCANCODE_KP_MEMSTORE: return KeyScancode::SCANCODE_KP_MEMSTORE;
    case SDL_SCANCODE_KP_MEMRECALL: return KeyScancode::SCANCODE_KP_MEMRECALL;
    case SDL_SCANCODE_KP_MEMCLEAR: return KeyScancode::SCANCODE_KP_MEMCLEAR;
    case SDL_SCANCODE_KP_MEMADD: return KeyScancode::SCANCODE_KP_MEMADD;
    case SDL_SCANCODE_KP_MEMSUBTRACT: return KeyScancode::SCANCODE_KP_MEMSUBTRACT;
    case SDL_SCANCODE_KP_MEMMULTIPLY: return KeyScancode::SCANCODE_KP_MEMMULTIPLY;
    case SDL_SCANCODE_KP_MEMDIVIDE: return KeyScancode::SCANCODE_KP_MEMDIVIDE;
    case SDL_SCANCODE_KP_PLUSMINUS: return KeyScancode::SCANCODE_KP_PLUSMINUS;
    case SDL_SCANCODE_KP_CLEAR: return KeyScancode::SCANCODE_KP_CLEAR;
    case SDL_SCANCODE_KP_CLEARENTRY: return KeyScancode::SCANCODE_KP_CLEARENTRY;
    case SDL_SCANCODE_KP_BINARY: return KeyScancode::SCANCODE_KP_BINARY;
    case SDL_SCANCODE_KP_OCTAL: return KeyScancode::SCANCODE_KP_OCTAL;
    case SDL_SCANCODE_KP_DECIMAL: return KeyScancode::SCANCODE_KP_DECIMAL;
    case SDL_SCANCODE_KP_HEXADECIMAL: return KeyScancode::SCANCODE_KP_HEXADECIMAL;
    case SDL_SCANCODE_LCTRL: return KeyScancode::SCANCODE_LCTRL;
    case SDL_SCANCODE_LSHIFT: return KeyScancode::SCANCODE_LSHIFT;
    case SDL_SCANCODE_LALT: return KeyScancode::SCANCODE_LALT;
    case SDL_SCANCODE_LGUI: return KeyScancode::SCANCODE_LGUI;
    case SDL_SCANCODE_RCTRL: return KeyScancode::SCANCODE_RCTRL;
    case SDL_SCANCODE_RSHIFT: return KeyScancode::SCANCODE_RSHIFT;
    case SDL_SCANCODE_RALT: return KeyScancode::SCANCODE_RALT;
    case SDL_SCANCODE_RGUI: return KeyScancode::SCANCODE_RGUI;
    case SDL_SCANCODE_MODE: return KeyScancode::SCANCODE_MODE;
    case SDL_SCANCODE_AUDIONEXT: return KeyScancode::SCANCODE_AUDIONEXT;
    case SDL_SCANCODE_AUDIOPREV: return KeyScancode::SCANCODE_AUDIOPREV;
    case SDL_SCANCODE_AUDIOSTOP: return KeyScancode::SCANCODE_AUDIOSTOP;
    case SDL_SCANCODE_AUDIOPLAY: return KeyScancode::SCANCODE_AUDIOPLAY;
    case SDL_SCANCODE_AUDIOMUTE: return KeyScancode::SCANCODE_AUDIOMUTE;
    case SDL_SCANCODE_MEDIASELECT: return KeyScancode::SCANCODE_MEDIASELECT;
    case SDL_SCANCODE_WWW: return KeyScancode::SCANCODE_WWW;
    case SDL_SCANCODE_MAIL: return KeyScancode::SCANCODE_MAIL;
    case SDL_SCANCODE_CALCULATOR: return KeyScancode::SCANCODE_CALCULATOR;
    case SDL_SCANCODE_COMPUTER: return KeyScancode::SCANCODE_COMPUTER;
    case SDL_SCANCODE_AC_SEARCH: return KeyScancode::SCANCODE_AC_SEARCH;
    case SDL_SCANCODE_AC_HOME: return KeyScancode::SCANCODE_AC_HOME;
    case SDL_SCANCODE_AC_BACK: return KeyScancode::SCANCODE_AC_BACK;
    case SDL_SCANCODE_AC_FORWARD: return KeyScancode::SCANCODE_AC_FORWARD;
    case SDL_SCANCODE_AC_STOP: return KeyScancode::SCANCODE_AC_STOP;
    case SDL_SCANCODE_AC_REFRESH: return KeyScancode::SCANCODE_AC_REFRESH;
    case SDL_SCANCODE_AC_BOOKMARKS: return KeyScancode::SCANCODE_AC_BOOKMARKS;
    case SDL_SCANCODE_BRIGHTNESSDOWN: return KeyScancode::SCANCODE_BRIGHTNESSDOWN;
    case SDL_SCANCODE_BRIGHTNESSUP: return KeyScancode::SCANCODE_BRIGHTNESSUP;
    case SDL_SCANCODE_DISPLAYSWITCH: return KeyScancode::SCANCODE_DISPLAYSWITCH;
    case SDL_SCANCODE_KBDILLUMTOGGLE: return KeyScancode::SCANCODE_KBDILLUMTOGGLE;
    case SDL_SCANCODE_KBDILLUMDOWN: return KeyScancode::SCANCODE_KBDILLUMDOWN;
    case SDL_SCANCODE_KBDILLUMUP: return KeyScancode::SCANCODE_KBDILLUMUP;
    case SDL_SCANCODE_EJECT: return KeyScancode::SCANCODE_EJECT;
    case SDL_SCANCODE_SLEEP: return KeyScancode::SCANCODE_SLEEP;
    case SDL_SCANCODE_APP1: return KeyScancode::SCANCODE_APP1;
    case SDL_SCANCODE_APP2: return KeyScancode::SCANCODE_APP2;
    case SDL_SCANCODE_AUDIOREWIND: return KeyScancode::SCANCODE_AUDIOREWIND;
    case SDL_SCANCODE_AUDIOFASTFORWARD: return KeyScancode::SCANCODE_AUDIOFASTFORWARD;
    default:
        CORE_POSTCONDITION_DEBUG_ASSERT(false, "SDL_Scancode not known.");
        return KeyScancode::SCANCODE_UNKNOWN;
    }
}

} // namespace FilApp