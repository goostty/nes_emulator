#include "mapper.hpp"
#include <array>
#include <cstdint>
#include <vector>

using u8 = std::uint8_t;
using u16 = std::uint16_t;

class Cartridge {
private:
  std::array<u8, 16> header;
  std::vector<u8> prg_rom;
  std::vector<u8> chr_rom;
  std::array<u8, 512> trainer;
  uint8_t mapper_id;
  bool mirroring_mode;

  std::size_t nes_loader(const char *ines_path, std::vector<u8> &rombuf);
  void nes_parser(std::vector<u8> &rombuf, std::size_t filesize);
  void header_parser(std::vector<u8> &rombuf);

public:
  Cartridge();
  const bool cartridge_init(const char *ines_path);
  const std::vector<u8> &get_prg_rom() const;
  const std::vector<u8> &get_chr_rom() const;
  uint8_t get_mapper_id() const;
  bool is_loaded() const;
  void reset();
};
