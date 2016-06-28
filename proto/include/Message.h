#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>

#define HEADER_SIZE 4

template <class Type>
class Message {
public:
    Message(std::shared_ptr<Type> message);
    bool pack(std::vector<std::uint8_t>& buffer);
private:
    
};

#include "Message.inl"

#endif