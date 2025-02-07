static char * TEXT[] = {
    "Old El Paso Stand 'N Stuff Soft Taco Boats",
    "First Price Hvetetortialla",
    "Santa Maria Super soft medium Tortiall Original",
    "Old El Paso Mexicana Street Market White Corn Tortillas",
    "Rema 1000 Tex Mex Taco Skjell"
};


char * taco_lefse(unsigned int degree){
    return TEXT[degree % 5];
}
