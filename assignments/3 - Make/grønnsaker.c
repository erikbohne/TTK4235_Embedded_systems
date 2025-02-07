static char * TEXT[] = {
    "Løk + Mais",
    "Cherry tomater + Avokado",
    "Ananas + Nacho",
    "Sørlandschips Spansk Paprika",
    "Gruyere Ost + Mango",
    "Chilibønner"
};

char * gronnsaker(unsigned int degree){
    return TEXT[degree % 6];
}
