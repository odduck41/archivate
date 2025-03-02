#pragma once
#include <cstdint>
#include <map>

class Byte {
    class Bit;
public:
    Byte() = default;
    explicit Byte(unsigned char *);
    Byte& operator=(const Byte& other);
    Byte(const Byte&);
    Byte(Byte&&) noexcept;
    explicit Byte(const uint8_t &);
    explicit operator int8_t() const;
    explicit operator int() const;


    static bool isUsed(unsigned char *);
    [[nodiscard]] unsigned char value() const;
    void setByte(unsigned char *);
    Bit operator[](const uint8_t &);
    ~Byte();
private:
    class Bit {
    public:
        Bit(unsigned char *, const uint8_t &);
        Bit(Bit &&) noexcept;

        Bit(const Bit &) = delete;
        Bit() = delete;
        Bit& operator=(const Bit &) = delete;

        Bit& operator=(const bool &);
        void flip() const;
        [[nodiscard]] bool value() const;
    private:
        unsigned char *ptr_{};
        uint8_t position_{};
    };
    unsigned char *byte_{};
    static std::map<unsigned char*, uint64_t> amount_;
};

class RawData {
public:
    RawData() = default;
    explicit RawData(const size_t &);
    Byte& operator[](const size_t &);

    void create(const size_t &);
    [[nodiscard]] const unsigned char *dump() const;
    [[nodiscard]] size_t size() const;

    ~RawData();
private:
    bool created{};
    Byte* sequence_{};
    void* data_{};
    size_t size_{};
};
