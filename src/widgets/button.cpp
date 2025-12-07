#include <tesseractui/widgets/button.hpp>

namespace tesseractui {
    Button::Button(const std::string& text, std::function<void()> callback) : label(text), onClick(std::move(callback)) {}

    void Button::render(VirtualBuffer& buffer) {
        const std::string& str = label.get();

        std::string display = "[ " + str + " ]";
        Color fg = focused ? Color{0, 0, 0} : Color{255, 255, 255};
        Color bg = focused ? Color{255, 255, 255} : Color{0, 0, 0};

        for (size_t i = 0; i < display.size() && static_cast<int>(i) < width; ++i) {
            VirtualCell cell;
            cell.glyph = static_cast<char32_t>(display[i]);
            cell.fg = fg;
            cell.bg = bg;
            buffer.set(x + static_cast<int>(i), y, cell);
        }
    }

    void Button::handleEvent(const Event& event) {
        //
    }
} // namespace tesseractui
