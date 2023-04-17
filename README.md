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