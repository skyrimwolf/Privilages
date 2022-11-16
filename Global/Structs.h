//strukture su koriscene umesto vektora unutar klase da bi se ojacala semantika i da bi kod bio laksi za citanje i razumevanje u 3 ujutru
#include<chrono>

struct Timer
{
    std::string s_name;
    std::chrono::high_resolution_clock::time_point s_start, s_end;
    std::chrono::duration<float> s_duration;

    Timer(const char *name)
    {
        s_start = std::chrono::high_resolution_clock::now();
        s_name  = name;
    }

    ~Timer()
    {
        s_end      = std::chrono::high_resolution_clock::now();
        s_duration = s_end - s_start;

        printf("Timer for %s took %f ms.\n", s_name.c_str(), s_duration.count()*1000.0f);
    }
};

struct KorisnikRegistri
{
    bool ulogovan   = 0;              //true ako: nije bilo greske pri ucitavanju username i password
    bool userPass   = 0;              //true ako: username i password se poklapaju (dobro su uneti) i vazi sve prethdno
    bool unetInfo   = 0;              //true ako: nije bilo greske pri ucitavanju informacija iz datotekei vazi sve prethdno
    bool unetAzur   = 0;              //true ako: uspesno pronadjen azur u PRVLGT i vazi sve prethodno
    bool dobarDan   = 0;              //true ako: pokusaj logovanja je ucinjen u danu kada dati korisnik sme da se uloguje i vazi sve prethodno
    bool dobroVreme = 0;              //true ako: pokusaj logovanja je ucinjen u dozvoljenom vremenu u toku dana i vazi sve prethodno
    bool glavni     = 0;              //true ako: sve prethodno je true ili je superKorisnik (admin)
};

struct MeniRegistri
{
    bool jelGotov   = 0;              //true ako: je uspesno zavrsio sa pretragom opcija
    bool nijePrazan = 0;              //true ako: postoji barem jedna opcija za datog korisnika
    bool glavni     = 0;              //true ako: sve prethodno je true ili je superKorisnik (admin)
};

struct Info 
{
    std::string grupa  = "OBIWAN";    //uzima vrednost polja Grupa  iz PRVLG.txt
    std::string dani   = "OBIWAN";    //uzima vrednost polja Dani   iz PRVLG.txt
    std::string dbftmp = "OBIWAN";    //uzima vrednost polja DBFTMP iz PRVLG.txt
    std::string azur   = "OBIWAN";    //uzima vrednost polja Azur   iz PRVLG.txt
};
