#pragma once
#include <tesseractui/buffer.hpp>
struct notcurses;
struct ncplane;

namespace tesseractui {
    class Renderer {
        public:
            Renderer();
            ~Renderer();

            // Non-copyable (owns terminal state)
            Renderer(const Renderer&) = delete;
            Renderer& operator=(const Renderer&) = delete;

            void render(const VirtualBuffer& buffer);
            int width() const { return m_width; }
            int height() const { return m_height; }

        private:
            notcurses* m_nc = nullptr;
            ncplane* m_plane = nullptr;
            int m_width = 0;
            int m_height = 0;
    };
} // namespace tesseractui
