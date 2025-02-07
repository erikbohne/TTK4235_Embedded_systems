static char * TEXT[] = {
    "Vegetariansk kjøttdeig",
    "Tofu",
    "Argentinske villreker",
    "Tilapia fisk",
    "Jeju svart gris",
    "Hanwoo biff",
    "Wagyu biff"
};

char * protein(unsigned int degree){
    return TEXT[degree % 7];
}
