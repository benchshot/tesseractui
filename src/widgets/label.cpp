#include <tesseractui/widgets/label.hpp>

namespace tesseractui {
    Label::Label(const std::string& t) : text(t) {}

    void Label::render(VirtualBuffer& buffer) {
        const std::string& str = text.get();

        for (size_t i = 0; i < str.size() && static_cast<int>(i) < width; ++i) {
            VirtualCell cell;
            cell.glyph = static_cast<char32_t>(str[i]);
            buffer.set(x + static_cast<int>(i), y, cell);
        }
    }
} // namespace tesseractui
