#include <tesseractui/widget.hpp>

namespace tesseractui {
    void Widget::addChild(std::shared_ptr<Widget> child) {
        m_children.push_back(std::move(child));
    }
} // namespace tesseractui
