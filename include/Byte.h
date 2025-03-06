#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <iterator>

class Byte {
    class Bit;
public:
    Byte() = default;
    explicit Byte(std::shared_ptr<unsigned char>);
    explicit Byte(unsigned char*&&);
    Byte& operator=(const Byte& other);
    Byte(const Byte&) = default;
    Byte(Byte&&) noexcept = default;
    explicit Byte(const uint8_t &);
    operator int8_t() const; // NOLINT
    operator int() const; // NOLINT
    operator bool() const; // NOLINT

    [[nodiscard]] unsigned char value() const;
    void setByte(std::shared_ptr<unsigned char>);
    Bit operator[](const uint8_t &);
    ~Byte() = default;
private:
    class Bit {
    public:
        Bit(std::shared_ptr<unsigned char>, const uint8_t &);
        Bit(Bit &&) noexcept;

        Bit(const Bit &) = delete;
        Bit() = delete;
        Bit& operator=(const Bit &) = delete;

        Bit& operator=(const bool &);
        void flip() const;
        [[nodiscard]] bool value() const;
        operator bool() const; // NOLINT
    private:
        std::shared_ptr<unsigned char> ptr_{};
        uint8_t position_{};
    };
    std::shared_ptr<unsigned char> byte_{};
};

class RawData {
public:
    RawData() = default;
    explicit RawData(const size_t &);
    Byte& operator[](const size_t &);
    operator char*() const; // NOLINT

    void create(const size_t &);
    [[nodiscard]] const unsigned char *dump() const;
    [[nodiscard]] size_t size() const;

    std::vector<Byte>::iterator begin();
    std::vector<Byte>::iterator end();

    ~RawData() = default;
private:
    bool created{};
    std::vector<Byte> sequence_{};
    std::shared_ptr<unsigned char[]> data_{};
    size_t size_{};
};
