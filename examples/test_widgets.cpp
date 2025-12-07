#include <tesseractui/buffer.hpp>
#include <tesseractui/widgets/label.hpp>
#include <tesseractui/widgets/button.hpp>
#include <iostream>

using namespace tesseractui;

int main() {
    // Create a 40x40 buffer
    VirtualBuffer buffer(40, 10);

    // Create a Label
    Label label("Hello TesseractUI!");
    label.x = 2;
    label.y = 1;
    label.width = 30;
    label.height = 1;
    label.render(buffer);

    // Create a Button
    Button button("Click Me", []() {
        std::cout << "Button clicked!" << std::endl;
    });
    button.x = 2;
    button.y = 3;
    button.width = 20;
    button.height = 1;
    button.render(buffer);

    // Create a Focused Button
    Button focusedBtn("Focused", []() {});
    focusedBtn.x = 2;
    focusedBtn.y = 5;
    focusedBtn.width = 20;
    focusedBtn.height = 1;
    focusedBtn.focused = true;
    focusedBtn.render(buffer);

    std::cout << "+" << std::string(40, '-') << "+" << std::endl;
    for (int y = 0; y < 10; ++y) {
        std::cout << "|";
        for (int x = 0; x < 40; ++x) {
            char c = static_cast<char>(buffer.get(x, y).glyph);
            std::cout << (c ? c : ' ');
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+" << std::string(40, '-') << "+" << std::endl;

    std::cout << "\nUpdating label text..." << std::endl;
    label.text.onChange.connect([](const std::string& newText) {
        std::cout << "Label changed to: " << newText << std::endl;
    });
    label.text.set("Updated Text!");

    return 0;
}