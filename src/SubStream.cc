#include "SubStream.hh"

SubStream::SubStream(sf::InputStream *mother, int size) {
    this->mother = mother;
    this->size = size;
    this->start = mother->tell();
    this->cursor = 0;
}

sf::Int64 SubStream::read(void *data, sf::Int64 size) {
    return this->mother->read(data, size);
}

sf::Int64 SubStream::seek(sf::Int64 position) {
    this->mother->seek(this->start + position);
    this->cursor = position;
}

sf::Int64 SubStream::tell() {
    return this->start + this->cursor;
}

sf::Int64 SubStream::getSize() {
    return this->size;
}
