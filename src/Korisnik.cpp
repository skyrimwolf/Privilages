#include "../Klase/CCar.h"

int main( int argc, char **argv )
{
    Timer T("main");
    Car A(argc, argv);

    A.StampajKorisnika();
    
    return 0;
};
