#include "cartridge.hpp"
#include <algorithm>
#include <cstdio>
#include <stdexcept>

// Constants
constexpr uint8_t MAXROM = 255;

void Cartridge::header_parser(std::vector<u8> &rombuf) {
  if (rombuf[0] != 0x4E || rombuf[1] != 0x45 || rombuf[2] != 0x53 ||
      rombuf[3] != 0x1A) {
    throw std::runtime_error("Invalid NES magic bytes");
  }

  if (rombuf[4] > MAXROM || rombuf[5] > MAXROM) {
    throw std::runtime_error("Size exceeded maximum size for ROM");
  } else {
    this->prg_rom.resize(rombuf[4] * 16384);
    this->chr_rom.resize(rombuf[5] * 8192);
  }
  std::copy_n(rombuf.begin(), this->header.size(), this->header.begin());
}

std::size_t Cartridge::nes_loader(const char *ines_path,
                                  std::vector<u8> &rombuf) {
  std::FILE *file = std::fopen(ines_path, "rb");
  if (!file) {
    throw std::runtime_error("Couldn't open .nes file");
  }

  std::fseek(file, 0, SEEK_END);
  long fileSize = std::ftell(file);
  std::rewind(file);

  rombuf.resize(fileSize);

  std::size_t bytesRead = std::fread(rombuf.data(), 1, fileSize, file);

  // Close FD
  std::fclose(file);
  if (bytesRead != static_cast<std::size_t>(fileSize)) {
    throw std::runtime_error("Bytes recieved not equal to file size");
  }
  return static_cast<std::size_t>(fileSize);
}

void Cartridge::nes_parser(std::vector<u8> &rombuf, std::size_t filesize) {
  header_parser(rombuf);

  std::size_t expectedSize_NoTrainer =
      16 + this->prg_rom.size() + this->chr_rom.size();

  if (filesize == expectedSize_NoTrainer + 512) {
  }
}

const bool Cartridge::cartridge_init(const char *ines_path) {
  std::vector<u8> rombuf;

  std::size_t fileSize = nes_loader(ines_path, rombuf);
  nes_parser(rombuf, fileSize);
  return true;
}
