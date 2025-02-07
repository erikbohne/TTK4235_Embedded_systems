static char * TEXT[] = {
    "Coop Tex Mex Taco Mild Sauce",
    "First Price Taco Saus",
    "Broken Taco Almost Illegal Salsa",
    "Broken Taco Supreme Taco Topping",
    "Heinz Ketchup",
    "Tine Rømme",
    "Huy Fong Sriracha"
};


char * taco_saus(unsigned int degree){
    return TEXT[degree % 7];
}
