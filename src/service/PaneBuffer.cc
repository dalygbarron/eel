#include "service/PaneBuffer.hh"

PaneBuffer::PaneBuffer(int n):
    n(n),
    vertexBuffer(sf::PrimitiveType::Quads, sf::VertexBuffer::Usage::Dynamic)
{
    this->top = 0;
    this->vertices = new sf::Vertex[n * 4];
    this->panes = new Pane[n];
    for (int i = 0; i < n; i++) {
        for (int u = 0; u < 4; u++) {
            this->vertices[i * 4 + u].color = sf::Color::White;
        }
        this->panes[i].vertices = this->vertices + i * 4;
    }
    this->vertexBuffer.create(n * 4);
}

PaneBuffer::~PaneBuffer() {
    delete[] this->vertices;
    delete[] this->panes;
}

void PaneBuffer::clear() {
    this->top = 0;
}

Pane *PaneBuffer::claim() {
    if (this->top < this->n) {
        Pane *pane = this->panes + this->top;
        this->top++;
        return pane;
    }
    return 0;
}

void PaneBuffer::render(
    sf::RenderTarget &target,
    sf::Texture const &texture
) {
    sf::Texture::bind(&texture, sf::Texture::CoordinateType::Pixels);
    this->vertexBuffer.update(this->vertices);
    target.draw(this->vertexBuffer);
}

sf::Vector2u PaneBuffer::sort() {
    // TODO: sort this shit.
    return sf::Vector2u(0, 0);
}
