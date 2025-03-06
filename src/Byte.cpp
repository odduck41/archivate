#include "../include/Byte.h"
#include <format>
#include <utility>

Byte::Bit& Byte::Bit::operator=(const bool &value) {
    if (value) {
        *ptr_ |= (1 << position_);
    } else {
        *ptr_ &= ~(1 << position_);
    }
    return *this;
}

Byte::Bit::Bit(std::shared_ptr<unsigned char> pointer, const uint8_t &position) :
ptr_(std::move(pointer)), position_(position){}

Byte::Bit::Bit(Bit &&other) noexcept : ptr_(std::move(other.ptr_)), position_(other.position_) {}

void Byte::Bit::flip() const {
    if (*ptr_ & (1 << position_)) {
        *ptr_ &= ~(1 << position_);
        return;
    }
    *ptr_ |= (1 << position_);
}

bool Byte::Bit::value() const {
    return *ptr_ & (1 << position_);
}

Byte::Byte(std::shared_ptr<unsigned char> byte) : byte_(std::move(byte)) {}

Byte::Byte(unsigned char *&& byte) : byte_(std::shared_ptr<unsigned char>(byte)) {}

void Byte::setByte(std::shared_ptr<unsigned char> byte) {
    byte_ = std::move(byte);
}

Byte::Bit Byte::operator[](const uint8_t &index) {
    if (byte_ == nullptr) {
        throw std::runtime_error("Byte is nullptr");
    }
    if (index >= 8) {
        throw std::out_of_range(std::format("Index out of the range: {} >= {}",
            index, 8
        ));
    }
    return {byte_, static_cast<uint8_t>(7 - index)};
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

unsigned char Byte::value() const {
    return *this->byte_;
}

Byte& Byte::operator=(const Byte &other) {
    if (this == &other) return *this;

    this->byte_ = other.byte_;

    return *this;
}

RawData::RawData(const size_t &size) :
data_(new unsigned char[size + 1], std::default_delete<unsigned char[]>()),
size_(size) {
    created = true;
    data_[static_cast<long>(size_)] = 0;

    sequence_.resize(size);
    for (size_t i = 0; i < size_; ++i) {
        sequence_[i].setByte(std::shared_ptr<unsigned char>(data_, data_.get() + i));
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
    return reinterpret_cast<char*>(data_.get());
}

void RawData::create(const size_t &size) {
    if (created) return;
    *this = RawData(size);
}

const unsigned char* RawData::dump() const {
   return this->data_.get();
}

size_t RawData::size() const {
    return size_;
}

std::vector<Byte>::iterator RawData::begin() { return sequence_.begin(); }

std::vector<Byte>::iterator RawData::end() { return sequence_.end(); }
