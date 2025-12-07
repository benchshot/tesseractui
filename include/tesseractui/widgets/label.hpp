#pragma once

#include <tesseractui/widget.hpp>
#include <tesseractui/reactive.hpp>
#include <string>

namespace tesseractui {
    class Label: public Widget {
        public:
            explicit Label(const std::string& text);
            void render(VirtualBuffer& buffer) override;

            Observable<std::string> text;
    };
} // namespace tesseractui
