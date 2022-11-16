#include "../Global/Fun.h"
#include "../Global/Structs.h"

class KKorisnik
{
private:                                                  //OSOBINE:
    std::string m_username   = "OBIWAN";                  //username, nikako kao globalna, maksimalna zastita - private
    std::string m_password   = "OBIWAN";                  //password, nikako kao globalna, maksimalna zastita - private
    std::string m_posebni[3] = {"AUTOR", "PERA", "ZIKA"}; //lista svih superkorisnika, maksimalna zastita - private
    
protected:
    int m_duzinaSysNiske = 15;                            //duzina username i password niske
    bool m_superInd      = 0;                             //indikator da li je superKorisnik ili ne
    std::string m_superKorisnik;                          //ukoliko je superKorisnik, ovde skladisti svoje ime
    
    KorisnikRegistri m_registriKorisnika;                 //registri za kontrolu toka pravljenja KKorisnika
    Info m_info;                                          //smesta informacije o grupi, dani, dbftmp, azur
    
private:                                                  //METODE:
    std::string Zakriptuj(std::string &);                 //kriptuje se unesena niska, nikako kao globalna funkcija, maksimalna zastita - private
    
protected:                                                //nista nije public, ne dozvoljava se kreiranje/upravljanje bilo kog objekta koji nije objekat klase Car, stroga kontrola
    KKorisnik(int, char **);
    virtual ~KKorisnik();
    
    void PopuniRegistre(int, char **);                    //popunjava sve registre i sprema se da salje informacije klasi Korisnik
    bool JelSuperKorisnik(int, char **);                  //odredjuje da li je superKorisnik preko argumenata komandne linije
    bool Logovanje();                                     //logovanje korisnika
    bool NadjiUsernamePassword();                         //trazi da li uneseni username i password postoje unutar PRVLG.txt
    bool ProveraVremeDan();                               //provarava da li je azur postoji unutar PRVLGT i da li taj korisnik sme da se uloguje u toku tog dana i u to vreme
    
    void StampajRegistre();                               //seljacko stampanje, moze posluziti
};

KKorisnik::KKorisnik(int argc, char **argv)
{
    PopuniRegistre(argc, argv);
    
    std::cout << "Created KKorisnik\n";
    
    StampajRegistre();
}

KKorisnik:: ~KKorisnik()
{
    std::cout << "Destroyed KKorisnik\n";
}

void KKorisnik::PopuniRegistre(int argc, char **argv)
{
    if(JelSuperKorisnik(argc, argv))
    {
        m_registriKorisnika.glavni = 1;
        m_info.grupa  = "SVE";
        m_info.dani   = "1111111";
        m_info.azur   = m_superKorisnik;
        m_info.dbftmp = m_superKorisnik.append(".log");
    }
    else m_registriKorisnika.glavni = Logovanje() && NadjiUsernamePassword() && ProveraVremeDan();
}

bool KKorisnik::JelSuperKorisnik(int argc, char **argv)
{
    if(m_superInd = argc == 2)
    {
        m_superKorisnik = *(argv + 1);
        
        for(std::string &poseban : m_posebni) if(m_superInd = m_superKorisnik == poseban) m_superKorisnik.append("#SYS");
    };
    
    return m_superInd;
}

bool KKorisnik::Logovanje()
{
    std::cout << "Korisničko ime   : ";  m_registriKorisnika.ulogovan =                                 (bool) (std::cin >> m_username);
    std::cout << "Korisnička šifra : ";  m_registriKorisnika.ulogovan = m_registriKorisnika.ulogovan && (bool) (std::cin >> m_password);
    
    return m_registriKorisnika.ulogovan;
}

bool KKorisnik::NadjiUsernamePassword()
{
    bool ind = true;
    std::fstream prvlg = Otvori("../TXT_fajlovi/PRVLG.txt", std::fstream::in);
    std::string unos1, unos2, unos3, unos4;
    std::string cryptUsername = Zakriptuj(m_username), cryptPassword = Zakriptuj(m_password);
    unsigned short i = 0;

    while(ind)
    {
        prvlg.seekg(150*(i++) + 42);                                                                            //skace na mesto gde su korisnik i sifra
        
        ind = prvlg.eof() != (bool) (prvlg >> unos1);
        if(ind)
        {
            m_registriKorisnika.userPass = m_registriKorisnika.ulogovan && cryptUsername == unos1;             //proverava se i je l prethodni registar uspesno upisan
            if (m_registriKorisnika.userPass)
            {
                prvlg >> unos1;
                m_registriKorisnika.userPass = cryptPassword == unos1;
                
                ind = 0;
            };
        };
    };
    
    m_registriKorisnika.unetInfo = m_registriKorisnika.userPass && (bool) (prvlg >> unos1 >> unos2 >> unos3 >> unos4); //proverava se i je l prethodni registar uspesno upisan
    if(m_registriKorisnika.unetInfo)
    {
        m_info.grupa  = unos1;                                                                                         //seljacki, ali radi
        m_info.dani   = unos2;
        m_info.dbftmp = unos3.append(".log");
        m_info.azur   = unos4;
    };
    
    prvlg.close();
    
    return m_registriKorisnika.unetInfo;                                                                               //vraca se poslednji koriscen registar
}

bool KKorisnik::ProveraVremeDan()
{
    bool ind = true;
    std::fstream prvlgt = Otvori("../TXT_fajlovi/PRVLGT.txt", std::fstream::in);
    std::string unos, vremeOd, vremeDo;
    unsigned short i = 0, trenutniDan = 0;
    unsigned int trenutnoVreme = VratiVremeDan(&trenutniDan);                                                          //vraca vraca vreme kao broj sekundi i dan kao broj od 0 do 6
    
    while(ind)
    {
        prvlgt.seekg(74*(i++));
        
        ind = prvlgt.eof() != (bool) (prvlgt >> unos);
        if(ind)
        {
            m_registriKorisnika.unetAzur = m_registriKorisnika.unetInfo && m_info.azur == unos;
            if(m_registriKorisnika.unetAzur)
            {
                prvlgt >> vremeOd >> vremeDo;
                
                m_registriKorisnika.dobarDan   = m_registriKorisnika.unetAzur && m_info.dani[trenutniDan] == '1';       //proverava dan, a u liniji ispod da li je vreme van datog opsega
                m_registriKorisnika.dobroVreme = m_registriKorisnika.dobarDan && (trenutnoVreme < VratiVreme(vremeOd) || trenutnoVreme > VratiVreme(vremeDo));
                
                ind = 0;
            };
        };
    };
    
    prvlgt.close();
    
    return m_registriKorisnika.dobroVreme;                                            //vraca se poslednji koriscen registar
}

std::string KKorisnik::Zakriptuj(std::string &niska)                                  //kriptuje unesenu nisku
{
    std::string result(m_duzinaSysNiske, '?');                     
    
    for(std::string::reverse_iterator it = niska.rbegin(); it != niska.rend(); it++)  //mehanizam za kriptovanje sifre i username-a
    {
        *it = (*it == ' ')? 63 : (*it)+1;
        result.push_back(*it);
    };
    
    result.erase(result.begin(), result.begin()+result.size()-m_duzinaSysNiske);      //obrisace se visak '?' i ostace niska duzine 15
    
    return result;
}

void KKorisnik::StampajRegistre()        
{
    std::cout << "\nPrikaz registara:\n\n";
    
    std::cout << "Ulogovan   : " << m_registriKorisnika.ulogovan   << "\n";
    std::cout << "userPass   : " << m_registriKorisnika.userPass   << "\n";
    std::cout << "unetInfo   : " << m_registriKorisnika.unetInfo   << "\n";
    std::cout << "unetAzur   : " << m_registriKorisnika.unetAzur   << "\n";
    std::cout << "dobarDan   : " << m_registriKorisnika.dobarDan   << "\n";
    std::cout << "dobroVreme : " << m_registriKorisnika.dobroVreme << "\n";
    std::cout << "glavni     : " << m_registriKorisnika.glavni     << "\n";
    
    std::cout << "\nKraj prikaza.\n\n";
}
