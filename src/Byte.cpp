#include "../include/Byte.h"
#include <format>

std::map<unsigned char*, uint64_t> Byte::amount_;

Byte::Bit& Byte::Bit::operator=(const bool &value) {
    if (value) {
        *ptr_ |= (1 << position_);
    } else {
        *ptr_ &= ~(1 << position_);
    }
    return *this;
}

Byte::Bit::Bit(unsigned char *pointer, const uint8_t &position) :
ptr_(pointer), position_(position){}

Byte::Bit::Bit(Bit &&other) noexcept {
    *this = other.value();
}

void Byte::Bit::flip() const {
    if (*ptr_ & (1 << position_)) {
        *ptr_ ^= (1 << position_);
        return;
    }
    *ptr_ |= (1 << position_);
}

bool Byte::Bit::value() const {
    return *ptr_ & (1 << position_);
}

Byte::Byte(unsigned char *byte) : byte_(byte) {
    ++amount_[byte];
}

void Byte::setByte(unsigned char *byte) {
    if (byte_ != nullptr) {
        --amount_[byte_];
        if (!amount_[byte_]) {
            amount_.erase(byte_);
            delete byte_;
            byte_ = nullptr;
        }
    }
    byte_ = byte;
    ++amount_[byte_];
}

Byte::Bit Byte::operator[](const uint8_t &index) {
    if (index >= 8) {
        throw std::out_of_range(std::format("Index out of the range: {} >= {}",
            index, 8
        ));
    }
    return {byte_, static_cast<uint8_t>(7 - index)};
}

Byte::Byte(const Byte &other) {
    this->byte_ = other.byte_;
    ++amount_[byte_];
}

Byte::Byte(Byte &&other)  noexcept {
    this->byte_ = other.byte_;
    ++amount_[byte_];
}

Byte::Byte(const uint8_t &value) {
    for (uint8_t i = 0; i < 8; ++i) {
        (*this)[i] = (value & (1 << i));
    }
}

Byte::operator int8_t() const {
    return static_cast<int8_t>(*this->byte_);
}

Byte::operator int() const {
    return *this->byte_;
}

Byte::operator bool() const {
    return *this->byte_;
}

bool Byte::isUsed(unsigned char *byte) {
    return amount_[byte] != 0;
}

unsigned char Byte::value() const {
    return *this->byte_;
}

Byte& Byte::operator=(const Byte &other) {
    if (this == &other) return *this;

    if (byte_ != nullptr) {
        --amount_[byte_];
        if (!amount_[byte_]) {
            amount_.erase(byte_);
            delete byte_;
            byte_ = nullptr;
        }
    }

    this->byte_ = other.byte_;
    ++amount_[byte_];

    return *this;
}

Byte::~Byte() {
    --amount_[byte_];
    if (!amount_[byte_]) {
        amount_.erase(byte_);
        delete byte_;
    }
}

RawData::RawData(const size_t &size) : size_(size) {
    created = true;
    data_ = new unsigned char[size_ + 1];
    data_[size_] = 0;

    sequence_ = new Byte[size_];
    for (size_t i = 0; i < size_; ++i) {
        sequence_[i].setByte(data_ + i);
    }
}

Byte& RawData::operator[](const size_t &index) {
    if (index >= size_) {
        throw std::out_of_range(std::format("Index out of the range: {} >= {}",
            index, size_
        ));
    }
    return sequence_[index];
}

RawData::operator char*() const {
    return reinterpret_cast<char*>(data_);
}

void RawData::create(const size_t &size) {
    if (created) return;
    created = true;
    size_ = size;
    data_ = new unsigned char[size_ + 1];
    data_[size_] = 0;

    sequence_ = new Byte[size_];
    for (size_t i = 0; i < size_; ++i) {
        sequence_[i].setByte(data_ + i);
    }
}

const unsigned char* RawData::dump() const {
   return this->data_;
}

size_t RawData::size() const {
    return size_;
}

RawData::~RawData() {
    delete[] sequence_;
    for (size_t i = 0; i < size_; ++i) {
        if (Byte::isUsed(data_ + i)) continue;
        delete (data_ + i);
    }
    delete (data_ + size_);
}
