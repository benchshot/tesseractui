#include <tesseractui/renderer.hpp>
#include <notcurses/notcurses.h>
#include <stdexcept>

namespace tesseractui {
    Renderer::Renderer() {
        notcurses_options opts{};
        opts.flags = NCOPTION_SUPPRESS_BANNERS; // No Startup Message

        m_nc = notcurses_init(&opts, nullptr);
        if (!m_nc) {
            throw std::runtime_error("Failed to initialize notcurses");
        }

        m_plane = notcurses_stdplane(m_nc);

        unsigned h, w;
        ncplane_dim_yx(m_plane, &h, &w);
        m_height = static_cast<int>(h);
        m_width = static_cast<int>(w);
    }

    Renderer::~Renderer() {
        if (m_nc) {
            notcurses_stop(m_nc); // Restore terminal to normal
        }
    }

    void Renderer::render(const VirtualBuffer& buffer) {
      // Clear the plane
      ncplane_erase(m_plane);

      // Draw each cell from our buffer
      for (int y = 0; y < buffer.height() && y < m_height; ++y) {
          for (int x = 0; x < buffer.width() && x < m_width; ++x) {
              const VirtualCell& cell = buffer.get(x, y);

              // Move cursor to position
              ncplane_cursor_move_yx(m_plane, y, x);

              // Set colors
              uint64_t channels = 0;
              ncchannels_set_fg_rgb8(&channels, cell.fg.r, cell.fg.g, cell.fg.b);
              ncchannels_set_bg_rgb8(&channels, cell.bg.r, cell.bg.g, cell.bg.b);
              ncplane_set_channels(m_plane, channels);

              // Draw the character
              char utf8[5] = {0};
              if (cell.glyph < 128) {
                  utf8[0] = static_cast<char>(cell.glyph);
              } else {
                  // Simple UTF-8 encoding for basic multilingual plane
                  if (cell.glyph < 0x80) {
                      utf8[0] = static_cast<char>(cell.glyph);
                  } else if (cell.glyph < 0x800) {
                      utf8[0] = static_cast<char>(0xC0 | (cell.glyph >> 6));
                      utf8[1] = static_cast<char>(0x80 | (cell.glyph & 0x3F));
                  } else {
                      utf8[0] = static_cast<char>(0xE0 | (cell.glyph >> 12));
                      utf8[1] = static_cast<char>(0x80 | ((cell.glyph >> 6) & 0x3F));
                      utf8[2] = static_cast<char>(0x80 | (cell.glyph & 0x3F));
                  }
              }
              ncplane_putstr(m_plane, utf8);
          }
      }

      // Flush to terminal
      notcurses_render(m_nc);
  }
} // namespace tesseractui
