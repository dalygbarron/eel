#include "SubStream.hh"

SubStream::SubStream(sf::InputStream *mother, int size) {
    this->mother = mother;
    this->start = mother->tell();
    this->cursor = this->start;
    this->size = size;
}

virtual Int64 SubStream::read(void *data, Int64 size) {

}

virtual Int64 SubStream::seek(Int64 position) {

}

virtual Int64 SubStream::tell() {

}

virtual Int64 SubStream::getSize() {
    return this->size;
}
