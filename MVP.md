TesseractUI — MVP Blueprint

A modern, Textual-inspired Terminal UI framework built in C++20.

📌 Overview

TesseractUI is a minimal, extensible terminal UI framework for C++ that provides:

A virtual terminal rendering engine (double-buffered diffing)

A reactive state system (Observable<T>)

A widget system (Label, Button, Containers)

A Yoga-powered Flexbox layout engine

A simple App runtime + event loop

notcurses backend for rendering

A Homebrew formula for installation

Clean public/private folder structure

This MVP establishes the foundation required for higher-level features such as routing, animations, advanced widgets, and full Textual parity.

📁 Project Structure (MVP)
tesseractui/
│
├── CMakeLists.txt
├── README.md
├── MVP.md
│
├── include/
│   └── tesseractui/
│       ├── app.hpp
│       ├── event.hpp
│       ├── event_loop.hpp
│       ├── widget.hpp
│       ├── container.hpp
│       ├── renderer.hpp
│       ├── buffer.hpp
│       ├── layout.hpp
│       ├── reactive.hpp
│       ├── signals.hpp
│       ├── style.hpp
│       └── theme.hpp
│
├── src/
│   ├── app.cpp
│   ├── buffer.cpp
│   ├── container.cpp
│   ├── event_loop.cpp
│   ├── layout.cpp
│   ├── reactive.cpp
│   ├── renderer.cpp
│   ├── signals.cpp
│   ├── style.cpp
│   ├── theme.cpp
│   └── widget.cpp
│
├── third_party/
│   ├── notcurses/
│   └── yoga/
│
├── widgets/
│   ├── button.hpp
│   ├── button.cpp
│   ├── label.hpp
│   └── label.cpp
│
├── examples/
│   └── counter/
│       └── main.cpp
│
└── package/
    └── tesseractui.rb     # Homebrew Formula

🧱 Core Components (MVP)

Below are the core systems required for a functional MVP.

🎨 1. Virtual Terminal Rendering Engine
VirtualCell
struct VirtualCell {
    char32_t glyph;
    Color fg;
    Color bg;
    bool bold = false;
};

VirtualBuffer
class VirtualBuffer {
public:
    VirtualBuffer(int width, int height);

    void set(int x, int y, const VirtualCell&);
    const VirtualCell& get(int x, int y) const;

    VirtualBuffer diff(const VirtualBuffer& prev) const;
};

Renderer

Responsible for:

Computing diff

Outputting ANSI/notcurses updates

class Renderer {
public:
    Renderer(int width, int height);
    void render(const VirtualBuffer& buff);
};

🧬 2. Reactive System (Signals + Observable)
Observable
template<typename T>
class Observable {
public:
    Observable(const T& initial);

    void set(const T& value);
    const T& get() const;

    Signal<T> onChange;
};

Signal
template<typename T>
class Signal {
public:
    using Callback = std::function<void(const T&)>;
    void connect(Callback cb);
    void emit(const T&);
};


This enables automatic widget updates when state changes.

🧩 3. Widget System
Base Widget
class Widget {
public:
    Widget();
    virtual ~Widget() = default;

    virtual void render(VirtualBuffer& buffer) = 0;
    virtual void handleEvent(const Event&);

    void addChild(std::shared_ptr<Widget>);
    std::vector<std::shared_ptr<Widget>> children;

    YGNodeRef yogaNode;
};

📐 4. Yoga Flexbox Layout Integration
class LayoutEngine {
public:
    void compute(Widget& root, int width, int height);
};


Widgets implement style configuration:

YGNodeStyleSetFlexGrow(yogaNode, 1);

🔘 5. Included MVP Widgets
Label
class Label : public Widget {
public:
    Observable<std::string> text;

    Label(const std::string& initial);

    void render(VirtualBuffer& buffer) override;
};

Button
class Button : public Widget {
public:
    Observable<std::string> text;
    std::function<void()> onClick;

    Button(std::string t, std::function<void()> cb);

    void render(VirtualBuffer&) override;
    void handleEvent(const Event&) override;
};

VBox / HBox Container
class VBox : public Widget {};
class HBox : public Widget {};

⌨️ 6. Event System + Event Loop
Event Types
struct Event {
    enum Type { KeyPress, Tick } type;
    int key;
};

Event Loop
class EventLoop {
public:
    void run(std::function<void(Event)> dispatch);
    void post(Event e);
};

🚀 7. App Runtime
class App {
public:
    App();

    virtual std::shared_ptr<Widget> build() = 0;
    void run();

private:
    EventLoop loop;
    Renderer renderer;
    std::shared_ptr<Widget> root;
};


Usage:

class CounterApp : public App {
    Observable<int> count{0};

    std::shared_ptr<Widget> build() override {
        return VBox({
            std::make_shared<Label>([&] { return "Count: " + std::to_string(count.get()); }),
            std::make_shared<Button>("Increment", [&]{ count.set(count.get() + 1); })
        });
    }
};

📦 Homebrew Formula (MVP)

package/tesseractui.rb

class Tesseractui < Formula
  desc "Modern C++ Terminal UI Framework inspired by Textual"
  homepage "https://github.com/yourname/tesseractui"
  url "https://github.com/yourname/tesseractui/archive/refs/tags/v0.1.0.tar.gz"
  sha256 "REPLACE_WITH_SHA"
  license "MIT"

  depends_on "cmake" => :build
  depends_on "notcurses"
  depends_on "libuv"
  depends_on "pkg-config"

  def install
    system "cmake", "-Bbuild", "-DCMAKE_BUILD_TYPE=Release", *std_cmake_args
    system "cmake", "--build", "build", "--target", "install"
  end
end


Install:

brew tap yourname/tesseractui
brew install tesseractui

🧪 Example App (Counter)

examples/counter/main.cpp

#include <tesseractui/app.hpp>
#include <tesseractui/button.hpp>
#include <tesseractui/label.hpp>

class Counter : public App {
public:
    Observable<int> count{0};

    std::shared_ptr<Widget> build() override {
        auto label = std::make_shared<Label>("Count: 0");

        count.onChange.connect([label](int newValue){
            label->text.set("Count: " + std::to_string(newValue));
        });

        auto button = std::make_shared<Button>("Increment", [&]{
            count.set(count.get() + 1);
        });

        auto root = std::make_shared<VBox>();
        root->addChild(label);
        root->addChild(button);
        return root;
    }
};

int main() {
    Counter().run();
}

🛣️ MVP Roadmap
Phase 1 — Core MVP

✔ VirtualBuffer
✔ Renderer
✔ Widget base class
✔ Label + Button
✔ Yoga layout
✔ Event loop
✔ App runtime
✔ Homebrew Formula

Phase 2 — Usability

⬜ InputField widget
⬜ Focus system
⬜ Theme system
⬜ Color palettes
⬜ Clean logging

Phase 3 — Advanced

⬜ ListView
⬜ Table
⬜ Animation system
⬜ Inspector tools
⬜ Async tasks