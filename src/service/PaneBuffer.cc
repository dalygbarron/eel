#include "service/PaneBuffer.hh"
#include "static/spdlog/spdlog.h"

PaneBuffer::PaneBuffer(int n):
    n(n),
    vertexBuffer(sf::PrimitiveType::Quads, sf::VertexBuffer::Usage::Dynamic)
{
    this->top = 0;
    this->cycle = 0;
    this->vertices = new sf::Vertex[n * 4];
    this->panes = new Pane*[n];
    for (int i = 0; i < n; i++) {
        Pane *pane = new Pane();
        for (int u = 0; u < 4; u++) {
            this->vertices[i * 4 + u].color = sf::Color::White;
        }
        pane->vertices = this->vertices + i * 4;
        this->panes[i] = pane;
    }
    this->vertexBuffer.create(n * 4);
}

PaneBuffer::~PaneBuffer() {
    delete[] this->vertices;
    for (int i = 0; i < this->n; i++) delete this->panes[i];
    delete[] this->panes;
}

void PaneBuffer::clear() {
    this->top = 0;
}

Pane *PaneBuffer::claim() {
    if (this->top < this->n) {
        this->top++;
        return this->panes[this->top - 1];
    }
    return 0;
}

void PaneBuffer::render(
    sf::RenderTarget &target,
    sf::Texture const &texture
) {
    sf::Vector2u dirty = this->sort();
    this->vertexBuffer.update(this->vertices + dirty.x * 4, dirty.y * 4, dirty.x * 4);
    sf::Texture::bind(&texture, sf::Texture::CoordinateType::Pixels);
    target.draw(this->vertexBuffer);
}

sf::Vector2u PaneBuffer::sort() {
    int min = this->n;
    int max = 0;
    if (this->panes[0]->dirty) {
        min = 0;
        this->panes[0]->dirty = false;
    }
    for (int i = 1; i < this->n; i++) {
        if (this->panes[i]->dirty) {
            if (i < min) min = i;
            if (i > max) max = i;
            this->panes[i]->dirty = 0;
        }
        for (int j = i; j > 0; j--) {
            if (this->panes[j - 1]->index <= this->panes[j]->index) break;
            sf::Vertex *tVP = this->panes[j]->vertices;
            this->panes[j]->vertices = this->panes[j - 1]->vertices;
            this->panes[j - 1]->vertices = tVP;
            for (int v = 0; v < 4; v++) {
                sf::Vertex tV = this->panes[j]->vertices[v];
                this->panes[j]->vertices[v] = this->panes[j - 1]->vertices[v];
                this->panes[j - 1]->vertices[v] = tV;
            }
            Pane *tP = this->panes[j];
            this->panes[j] = this->panes[j - 1];
            this->panes[j - 1] = tP;
            if (j > max) max = j;
            if ((j - 1) < min) min = j - 1;
        }
    }
    if (max < min) max = min;
    else if (max != min) spdlog::info("dirty {} {}", min, max - min);
    return sf::Vector2u(min, max - min + 1);
}
