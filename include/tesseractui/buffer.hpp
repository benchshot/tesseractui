#pragma once

#include <tesseractui/types.hpp>
#include <vector>

namespace tesseractui {

    class VirtualBuffer {
        public:
            VirtualBuffer(int width, int height);

            void set(int x, int y, const VirtualCell& cell);
            const VirtualCell& get(int x, int y) const;

            int width() const { return m_width; }
            int height() const { return m_height; }

        private:
            int m_width;
            int m_height;
            std::vector<VirtualCell> m_cells;
    };

} // namespace tesseractui