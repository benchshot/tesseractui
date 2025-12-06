#pragma once

#include <cstdint>

/*
    - namespace - groups related code, prevents name collisions. Access this as tesseractui::Color
    - struct - like a class but members are public by default. Use for simple data containers
*/
namespace tesseractui {
    // - uint8_t - unsigned 8-bit integer (0-255), perfect for RBG values
    // - Default member initializers - = 0 means if you create Color{} it defaults to black
    struct Color {
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
    };

    // - char32_t - a 32-bit character type for Unicode suppoert (emojis, international characters)
    // - U' ' - the U prefix makes it a char32_t literal (a space character)
    // Aggregate initialization = Color{255, 255, 255} creates a Color with those RGB values
    struct VirtualCell {
        char32_t glyph = U' ';
        Color fg{255, 255, 255}; // White Text
        Color bg{0, 0, 0}; // Black Background
        bool bold = false;
    };
}