#include "CKKorisnik.h"

class Korisnik : public KKorisnik                                   //ne moze biti virtual, ne dozvoljav slanje argumenata u virtual natklasu virtual natklase
{
protected:
    bool m_spremanKorisnik  = false;                                //indikator koji javlja Caru da li je Korisnik spreman
    bool m_superKorisnikInd = false;                                //indikator da li je u pitanju superKorisnik ili ne
    Info m_informacije;                                             //uzima informacije o grupi, danima, dbftmp i azur koje su prikupljene od strane KKorisnika
    
protected:                                                          //nista nije public, ne dozvoljava se kreiranje/upravljanje bilo kog objekta koji nije objekat klase Car, stroga kontrola
    Korisnik(int, char **);
    ~Korisnik();
};

Korisnik::Korisnik(int argc, char **argv) : KKorisnik(argc, argv) 
{
    m_informacije      = this->m_info;                              //uzima informacije od KKorisnika
    m_superKorisnikInd = this->m_superInd;                          //uzima informaciju da li je korisnik superKorisnik ili ne
    m_spremanKorisnik  = this->m_registriKorisnika.glavni;          //uzima informaciju da li su svi uslovi zadovoljeni pri logovanju

    std::cout << "Created Korisnik\n";
}

Korisnik::~Korisnik()
{
    std::cout << "Destroyed Korisnik\n";
}
