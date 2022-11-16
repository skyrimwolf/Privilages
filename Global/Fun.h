#include<iostream>
#include<fstream>
#include<string>
#include<vector>

std::fstream Otvori(const char *ime, std::ios_base::openmode kako)
{
    std::fstream ulaz;
    
    ulaz.open(ime, kako);
    if(!ulaz.is_open())
    {
        std::cout << "Greska pri otvaranju za " << ime << "\n";
        exit(EXIT_FAILURE);
    };
    
    return ulaz;
}

int VratiVremeDan(unsigned short *dan)                                     //vraca vreme u sekundama i dan u vidu broja od 0 do 6
{
    struct tm *info;
    time_t  vreme;
    
    time(&vreme);                                                          //vraca lokalno vreme
    
    info = localtime(&vreme);                                              //rasporedjuje lokalno vreme po strukturi, razvrstava minute, sate i sekunde, kao i dane
    
    *dan = info->tm_wday;                                                  //vraca broj trenutnog dana 0-6
    
    return 3600*info->tm_hour + 60*info->tm_min + info->tm_sec;            //vraca vreme u sekundama
}

int VratiVreme(std::string &vreme)                                         //vraca vreme iz HH:MM:SS formata u sekundama 
{
    char pom[2];
    int zbir = 0;
    
    pom[0] = vreme[0]; pom[1] = vreme[1];
    zbir += atoi(pom) * 3600;
    
    pom[0] = vreme[3]; pom[1] = vreme[4];
    zbir += atoi(pom) * 60;
    
    pom[0] = vreme[6]; pom[1] = vreme[7];
    zbir += atoi(pom);
    
    return zbir;
}
