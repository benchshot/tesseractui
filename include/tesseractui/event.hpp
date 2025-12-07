#pragma once

#include <cstdint>
#include <variant>

namespace tesseractui {
    struct KeyEvent {
        uint32_t key; // Unicode codepoint or special key
        bool ctrl = false;
        bool alt = false;
        bool shift = false;
    };

    struct ResizeEvent {
        int width;
        int height;
    };

    struct TickEvent {
        uint64_t elapsed_ms; // Milliseconds since app started
    };
    
    using Event = std::variant<KeyEvent, ResizeEvent, TickEvent>;

    template<typename T>
    const T& getEvent(const Event& e) {
        return std::get<T>(e);
    }

    // Common Key Codes
    namespace Key {
        constexpr uint32_t Enter = '\r';
        constexpr uint32_t Space = ' ';
        constexpr uint32_t Escape = 27;
        constexpr uint32_t Tab = '\t';
        constexpr uint32_t Backspace = 127;

        // Arrow Keys (Using Private Use Area)
        constexpr uint32_t Up = 0xF700;
        constexpr uint32_t Down = 0xF701;
        constexpr uint32_t Left = 0xF702;
        constexpr uint32_t Right = 0xF703;
    } // namespace Key
} // namespace tesseractui
