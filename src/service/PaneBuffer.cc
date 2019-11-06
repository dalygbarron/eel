#include "service/PaneBuffer.hh"

PaneBuffer::PaneBuffer(int n): n(n) {
    this->top = 0;
    this->vertices = new sf::Vertex[n * 4];
    this->panes = new Pane[n];
    for (int i = 0; i < n; i++) {
        this->panes[i].topLeft = this->vertices[i * 4];
        this->panes[i].topRight = this->vertices[i * 4 + 1];
        this->panes[i].bottomRight = this->vertices[i * 4 + 2];
        this->panes[i].bottomLeft = this->vertices[i * 4 + 3];
    }
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

void PaneBuffer::sort() {
    // TODO: sort this shit.

}
