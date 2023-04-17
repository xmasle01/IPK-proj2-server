#Serverová kalkulačka pre UDP a TCP komunikáciu

##Úvod
Táto dokumentácia popisuje program v jazyku C, ktorý slúži ako serverová kalkulačka pre UDP a TCP komunikáciu. Server dokáže prijať matematický výraz a vyhodnotiť ho. Na základe argumentov, ktoré sú mu poskytnuté pri spustení, rozhodne o tom, či bude používať UDP alebo TCP protokol. Ak sa rozhodne pre použitie TCP, bude tiež využívať forking na spracovanie viacerých požiadaviek súčasne.

##Implementácia

Hlavná funkcia main
Hlavná funkcia programu sa nachádza v súbore "server.c" a slúži na spracovanie argumentov, vytvorenie a ovládanie socketov, riadenie toku programu a poskytovanie odpovedí klientom.

Po spustení programu sa načítajú argumenty príkazového riadku, ktoré určujú adresu hostiteľa, číslo portu a režim komunikácie. Funkcia check_args() skontroluje správnosť počtu a typu argumentov. Potom sa vytvorí socket podľa zvoleného režimu (TCP alebo UDP).

V prípade použitia UDP je nutné vytvoriť serverový socket pomocou funkcie socket() so špecifikáciou protokolu a typu socketu. Pri použití TCP je najprv potrebné vytvoriť socket pomocou rovnakej funkcie a následne inicializovať adresu, na ktorej sa bude počúvať, pomocou funkcie bind().

Ak bol zvolený režim TCP, program používa funkciu fork() na vytvorenie nového procesu pre každý prichádzajúci požiadavok. V tomto prípade je potrebné uzavrieť duplicitné súbory (napr. socket) v dieťaťovskom procese a ďalej spracovávať požiadavok v ňom.

####Funkcia calculate()
Funkcia calculate() slúži na vyhodnotenie matematického výrazu, ktorý dostane od klienta. Najprv sa overí platnosť výrazu a ak nie je v poriadku, funkcia zavolá funkciu send_err() na odoslanie chybovej správy. Výraz je následne spracovaný pomocou cyklu, ktorý postupne získava operandy a vykonáva príslušnú matematickú operáciu.

####Funkcia send_err()
Funkcia send_err() slúži na odoslanie chybovej správy klientovi a ukončenie príslušnej komunikácie. V prípade TCP komunikácie funk

####Funkcia "check_args"
Funkcia "check_args" slúži na overenie správnej syntaxe argumentov, ktoré sú zadávané pri spustení programu.

#####Parametre funkcie:

argc: celkový počet argumentov
argv: pole s argumentmi programu
Návratová hodnota:

bool hodnota, ktorá vyjadruje, či boli argumenty zadávané správne (true), alebo nie (false).
Funkcia najprv overí, či počet argumentov je správny (7). Ak áno, prechádza poľom argumentov a kontroluje, či boli zadané argumenty "-h", "-p" a "-m". Ak áno, zvýši počítadlo "cnt" o 1 pre každý správne zadaný argument. Po skončení kontroly, ak "cnt" nie je rovný 3 (tj. nie sú zadané všetky tri požadované argumenty), vypíše sa chybová hláška a program sa ukončí s chybovým kódom. Ak sú argumenty zadávané správne, funkcia vráti true.

Ak počet argumentov nie je rovný 7, vypíše sa chybová hláška a program sa ukončí s chybovým kódom.

####Funkcia create_socket
Funkcia create_socket slúži na vytvorenie socketu s daným typom protokolu a príznakmi pre komunikáciu. Funkcia má dva argumenty, prvý argument určuje typ protokolu, ktorým bude komunikácia prebiehať a druhý argument určuje príznaky, ktoré sa nastavia pre socket. Funkcia vracia vytvorený socket.

#####Argumenty funkcie
- `mode` - reťazec, ktorý určuje typ protokolu pre komunikáciu. Možnosti sú "tcp" alebo "udp".
- `flags` - celé číslo, ktoré určuje príznaky pre socket.

#####Správanie funkcie
Funkcia skontroluje typ protokolu a na základe toho vytvorí socket s príslušným typom. Ak sa vytvorenie socketu nepodarí, funkcia ukončí program s chybovým hlásením.

Pre protokol TCP sa použije funkcia socket so zadanými parametrami AF_INET, SOCK_STREAM a flags. Ak vytvorenie socketu zlyhá, funkcia skončí a vypíše chybové hlásenie.

Pre protokol UDP sa použije funkcia socket so zadanými parametrami AF_INET, SOCK_DGRAM a flags. Ak vytvorenie socketu zlyhá, funkcia skončí a vypíše chybové hlásenie.

Ak sa vytvorenie socketu úspešne podarí, funkcia nastaví socketovú možnosť SO_REUSEADDR na hodnotu 1, aby sa zabránilo problémom s prerušeným spojením.

####Funkcia binding
Funkcia binding slúži na naviazanie vytvoreného socketu na zadaný port a na priradenie socketu k serverovej adrese. Funkcia má tri argumenty, prvý argument určuje port, na ktorom bude socket naviazaný, druhý argument je vytvorený socket a tretí argument je štruktúra, ktorá obsahuje informácie o serverovej adrese.

Argumenty funkcie
- `port` -  celé číslo, ktoré určuje port, na ktorom bude socket naviazaný.
- `Socket` - celé číslo, ktoré reprezentuje vytvorený socket.
- `server_addr` - štruktúra, ktorá obsahuje informácie o serverovej adrese.
