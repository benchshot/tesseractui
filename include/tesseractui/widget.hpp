#pragma once

#include <tesseractui/buffer.hpp>
#include <tesseractui/event.hpp>
#include <memory>
#include <vector>

namespace tesseractui {
    class Widget {
        public:
            Widget() = default;
            virtual ~Widget() = default;

            // Pure virtual - subclasses must implement
            virtual void render(VirtualBuffer& buffer) = 0;

            // Virtual with default implementation - subclasses can override
            virtual void handleEvent(const Event& event) {}

            // Child management
            void addChild(std::shared_ptr<Widget> child);
            const std::vector<std::shared_ptr<Widget>>& children() const { return m_children; }

            int x = 0, y = 0;
            int width = 0, height = 0;

        protected:
            std::vector<std::shared_ptr<Widget>> m_children;
    };
} // namespace tesseractui 