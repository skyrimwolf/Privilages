class Meni
{
protected:
    bool m_spremanMeni = 0;                                                                //javlja Caru da li je meni spreman
    MeniRegistri m_registriMenija;                                                         //registri za kontrolu toka pravljenja Menija
    std::vector<std::string> m_opcije;                                                     //lista svih opcija za korisnika
    
protected:                                                                                 //ne sme se kreirati van Cara, stroga kontrola
    Meni(bool, bool, std::string);
    ~Meni();
    
    void PrivilegovanMeni();                                                               //popunjava registre u slucaju da je superKorisnik ulogovan
    void PopuniRegistre(std::string);                                                      //popunjava registre u slucaju da nije superKorisnik vec obican korisnik
    
    static bool NadjiDozvolu(std::string);                                                 //isti razlog zasto je static kao i u CKKorisnik.h
};

Meni::Meni(bool superInd, bool spremanKorisnik, std::string grupa)
{
    if(spremanKorisnik)
    {
        superInd? PrivilegovanMeni() : PopuniRegistre(grupa);
        
        m_spremanMeni = m_registriMenija.glavni;                                           //m_spremanMeni sluzi da javi Caru da li je sve spremno
        
        std::cout << "Created Meni\n";
    };
}

Meni::~Meni()
{
    m_opcije.clear();                                                                      //mora se paziti na memoriju uvek, vektor se rucno brise
    
    std::cout << "Destroyed Meni\n";
}

void Meni::PrivilegovanMeni()
{
    bool ind = 1;
    std::fstream meni = Otvori("../TXT_fajlovi/MENI.txt", std::fstream::in);
    std::string unos;
    unsigned short i = 0;
    
    while(ind)
    {
        meni.seekg(121*(i++));
        
        ind = meni.eof() != (bool) (meni >> unos);
        if(ind) m_opcije.emplace_back(unos);
    };
    
    meni.close();
    
    m_registriMenija.glavni = 1;                                                          //superKorisnik je, glavni se postavlja na 1, svi drugi uslovi se smatraju zadovoljenim
}

void Meni::PopuniRegistre(std::string grupa)
{
    bool ind = true;
    std::fstream prprvlg = Otvori("../TXT_fajlovi/PRPRVLG.txt", std::fstream::in);
    std::string unos;
    unsigned short i = 0;
    
    while(ind)
    {
        prprvlg.seekg(52*(i++));
        
        ind = prprvlg.eof() != (bool) (prprvlg >> unos);
        if(ind && grupa == unos)
        {
            prprvlg >> unos;
            
            if(NadjiDozvolu(unos))
            {
                if(!m_registriMenija.nijePrazan) m_registriMenija.nijePrazan = 1;        //ako je nasao bar jednu opciju koja se smesta u vektor opcija u liniji 77, nijePrazan je true
                
                m_opcije.emplace_back(unos);                                             //bolji i brzi je emplace_back od push_back jer kod emplace_back nema ponovne alokacije memorije
            };
        };
    };
    
    prprvlg.close();
    
    m_registriMenija.jelGotov = !ind;                                                    //zavrsena while petlja -> jelGotov je true
    m_registriMenija.glavni = m_registriMenija.jelGotov && m_registriMenija.nijePrazan;  //true je ako su oba prethodna true
}

bool Meni::NadjiDozvolu(std::string opcija)                                              //pita da li je opcija u MENI.txt markirana sa TRUE, da li je osposobljena opcija
{
    bool ind = true, jelNasao = false;
    std::fstream meni = Otvori("../TXT_fajlovi/MENI.txt", std::fstream::in);
    std::string unos;
    unsigned short i = 0;
    
    while(ind)
    {
        meni.seekg(121*i);
        
        ind = meni.eof() != (bool) (meni >> unos);
        if(ind && opcija == unos)
        {
            meni.seekg(121*i+115);
            
            meni >> unos;
            
            jelNasao = unos == "TRUE";
            
            ind = 0;
        };
        
        i++;
    };
    
    meni.close();
    
    return jelNasao;
}
