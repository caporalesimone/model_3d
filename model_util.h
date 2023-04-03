// Libreria per la gestione del file contente il modello 3D

typedef struct vertex
{
        int x,y,z;  // Coordinate del vertice
        struct vertex *next;  // a link to the next particle.
} vertex;
