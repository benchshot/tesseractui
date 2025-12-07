#include <tesseractui/buffer.hpp>
  #include <tesseractui/renderer.hpp>
  #include <tesseractui/widgets/label.hpp>
  #include <tesseractui/widgets/button.hpp>
  #include <thread>
  #include <chrono>

  using namespace tesseractui;

  int main() {
      // Create renderer (takes over terminal)
      Renderer renderer;

      // Create a buffer matching terminal size
      VirtualBuffer buffer(renderer.width(), renderer.height());

      // Create widgets
      Label title("Welcome to TesseractUI!");
      title.x = 2;
      title.y = 1;
      title.width = 30;
      title.height = 1;

      Label subtitle("A C++ Terminal UI Framework");
      subtitle.x = 2;
      subtitle.y = 2;
      subtitle.width = 30;
      subtitle.height = 1;

      Button button("Press Enter", []() {});
      button.x = 2;
      button.y = 4;
      button.width = 20;
      button.height = 1;
      button.focused = true;

      // Render widgets to buffer
      title.render(buffer);
      subtitle.render(buffer);
      button.render(buffer);

      // Output to terminal
      renderer.render(buffer);

      // Wait 3 seconds so you can see it
      std::this_thread::sleep_for(std::chrono::seconds(3));

      // Renderer destructor restores terminal automatically
      return 0;
  }