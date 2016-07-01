#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <memory>

#include <iostream>

class Message {
public:
    static const size_t HEADER_LENGTH = 4;
    static const size_t BODY_LENGTH = 1024;
    Message() :
        length_(0) { };
    Message(std::string text) :
        length_(std::strlen(text.c_str())) {
        std::memcpy(this->body(), text.c_str(), this->length_);
        this->encode_header();
        std::cout << this->length_ << std::endl;
    };
    void encode_header() {
        char header[Message::HEADER_LENGTH + 1] = "";
        std::sprintf(header, "%4d", static_cast<int>(this->length_));
        std::memcpy(this->data_, header, Message::HEADER_LENGTH);
    };
    void decode_header() {
        char header[Message::HEADER_LENGTH + 1] = "";
        std::strncat(header, this->data_, Message::HEADER_LENGTH);
        this->length_ = std::atoi(header);
    };
    char* data() {
        return this->data_;
    };
    char* body() {
        return this->data_ + Message::HEADER_LENGTH + 1;
    };
    size_t length() {
        return this->length_;
    };
private:
    char data_[Message::HEADER_LENGTH + Message::BODY_LENGTH];
    size_t length_;
};

#endif