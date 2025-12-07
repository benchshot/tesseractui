#include <tesseractui/buffer.hpp>

namespace tesseractui {
    VirtualBuffer::VirtualBuffer(int width, int height) : m_width(width), m_height(height), m_cells(width * height) {}

    void VirtualBuffer::set(int x, int y, const VirtualCell& cell) {
        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            m_cells[y * m_width + x] = cell;
        }
    }

    const VirtualCell& VirtualBuffer::get(int x, int y) const {
        static VirtualCell empty{};
        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            return m_cells[y * m_width + x];
        }
        return empty;
    }
}