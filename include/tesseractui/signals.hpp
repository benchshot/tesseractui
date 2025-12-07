#pragma once

#include <functional>
#include <vector>

namespace tesseractui {

    template<typename T>
    class Signal {
        public:
            using Callback = std::function<void(const T&)>;
            
            void connect(Callback cb) {
                m_callbacks.push_back(std::move(cb));
            }

            void emit(const T& value) {
                for (auto& cb : m_callbacks) {
                    cb(value);
                }
            }

        private:
            std::vector<Callback> m_callbacks;
    };
} // namespace tesseractui
