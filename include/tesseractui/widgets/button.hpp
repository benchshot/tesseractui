#pragma once

#include <tesseractui/widget.hpp>
#include <tesseractui/reactive.hpp>
#include <tesseractui/event.hpp>
#include <functional>
#include <string>

namespace tesseractui {
    class Button: public Widget {
        public:
            Button(const std::string& label, std::function<void()> callback);

            void render(VirtualBuffer& buffer) override;
            void handleEvent(const Event& event) override;

            Observable<std::string> label;
            std::function<void()> onClick;

            bool focused = false;
    };
} // namespace tesseractui
