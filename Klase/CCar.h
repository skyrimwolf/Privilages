#include "CKorisnik.h"
#include "CMeni.h"

class Car : virtual Korisnik,
            virtual Meni
{
private:
    bool m_spremanCar      = 0;               //javlja da li je Car osposobljen, za svaku narednu metodu se raditi unutar if(m_spremanCar){..} da bi se strogo kontrolisao pristup
    std::string m_fajl     = "OBIWAN";        //informacija o dbftmp korisnika
    std::string m_azurirao = "OBIWAN";        //informacija o azur-u korisnika
    std::vector<std::string> m_meni;          //lista opcija u meniju za datog korisnika
    
public:
    Car(int, char **);
    ~Car();
    
    void StampajKorisnika();                  //stampa informacije o korisniku, kao i listu mogucih opcija korisnika
};

Car::Car(int argc, char **argv) : Korisnik(argc, argv),
                                  Meni(this->m_superKorisnikInd, this->m_spremanKorisnik, this->m_informacije.grupa)
{
    if(this->m_spremanKorisnik && this->m_spremanMeni)
    {
        m_fajl       = this->m_informacije.dbftmp;
        m_azurirao   = this->m_informacije.azur;
        m_meni       = this->m_opcije;
        m_spremanCar = 1;
        
        std::cout << "Created Car\n";
    };
}

Car::~Car()
{
    m_meni.clear();
    
    std::cout << "Destroyed Car\n";
}

void Car::StampajKorisnika()
{
    if(m_spremanCar)
    {
        std::cout << "\nPrikaz Korisnika :\n\n";
        
        std::cout << "Fajl Korisnika   : " << m_fajl << "\n";
        std::cout << "Azur Korisnika   : " << m_azurirao << "\n\n";
        
        std::cout << "Prikaz Menija    :\n\n";
        
        for(std::string &opcija : m_meni) std::cout << opcija << "\n";
        
        std::cout << "\nKraj prikaza.\n\n";
    };
}
