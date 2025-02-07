static char * TEXT[] = {
    "Santa Maria Original Taco spice mix",
    "Old El Peso Spice Mix for Tacos",
    "First Price Taco spice mix",
    "Raske-Retter Økologisk Tacokrydder",
    "Cemo Gourmetkrydder Taco"
};


char * taco_krydder(unsigned int degree){
    return TEXT[degree % 5];
}
