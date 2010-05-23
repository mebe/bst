# bst #

bst is a C binary search tree implementation. The tree's nodes use
strings as keys and integers as data stored in the node. A new node isn't
inserted into the tree if an existing node happens to have the same key -
in this situation we instead increase the existing node's data integer by one.

Only insertion, inorder-tree-walk and postorder-tree-walk algorithms have
been implemented - no search or deletion algorithms are available.

# sl #

sl is a word counting program that uses bst as its underlying data structure
It counts the number of occurences of words in the given input stream. A word
is defined as being at least two consecutive alphabetical characters as
recognized by C's standard isalpha()-implementation.

The program accepts up to two command line parameters. First one
defines the input file to be used and the second one the output file.
If the second one is omitted, stdout will be used for output.
If the first one is omitted, stdin will be used for input.

# In Finnish #

## sl - sanalaskuri ##

sl on sanalaskuri, joka laskee sanojen esiintymisen määrän joko annetussa
tiedostossa tai stdin:ssä. Tulostus ohjataan joko tiedostoon tai stdout:iin.

### Ohjelman kääntäminen: ###

Ohjelma käännetään joko komentamalla "make" tai "make all". Jos halutaan
käyttää debug-moodia, käännetään ohjelma komentamalla "make debug".
Käännöstiedostot voi poistaa komentamalla "make clean", mikä on syytä
tehdä ennen uutta käännöstä.

### Käyttöohje: ###

sl <input> <output>
Input on syöttötiedosto ja output tulostiedosto - tulostiedosto voidaan
määritellä vain, jos myös syöttötiedosto on määritelty. Jos syöttötiedosto
jätetään määrittelemättä, käytetään stdin:iä - jos tulostiedosto jätetään
määrittelemättä käytetään stdout:ia.

### Ohjelman rakenne: ###

Ohjelman selkärankana on binäärihakupuutoteutus, johon löytyneet sanat ja
niiden määrät tallennetaan. Sanat ovat puun solmujen avaimina ja niiden
määrät solmujen data-kenttinä. Jos puuhun yritetään lisätä solmua, jonka 
avaimella varustettu solmu puusta jo löytyy, kasvatetaankin olemassa olevan 
solmun data-kenttään tallennettua määrää ja uusi solmu tuhotaan.
	 
Puu on toteutettu tietorakenteet-kurssin kalvoilla esitettyjen puun
perusoperaatoiden pohjalta. Toteutetut algoritmit ovat inorder-tree-walk
ja uuden solmun lisääminen puuhun.  Haulle tai poistoille ei ollut tarvetta.
Avainten keskinäinen suuruusjärjestys lasketaan C:n standardin strcmp()-funktion
avulla.

Erikoisuutena jo mainitun data-kentän kasvattamisen lisäksi on inorder-
tree-walk-toteutuksen callback-ominaisuus, jonka avulla solmulle tehtävä
toiminne määritellään erillisessä funktiossa. Tätä käytetään sekä solmujen
tulostamisessa aakkosjärjestykseen että koko puun poistamisessa. 
	 
Itse pääohjelma käy annetun syöttötiedoston lävitse merkki kerrallaan.
Kun kahden C:n standardin isalpha()-funktion kirjainmerkeiksi tunnistaman
merkin jälkeen tulee ei-kirjainmerkki, tallennetaan saatu sana hakupuuhun. 
Kun tiedosto päättyy, tulostetaan hakupuu inorder-tree-walking avulla.
Tämän jälkeen puu tuhotaan ja suoritus on valmis.

### Testaus: ###

Ohjelmaa on testattu ajamalla sitä erilaisilla syötteillä. Tähän on käytetty
mm. ohjelman lähdekoodia sekä stdin:in kautta syötettettyjä mieleen
juolahtaineita merkkijonoja. Ohjelman lähdekoodissa tärkeimmät asiat on
tarkistettu assert-lausekkeiden avulla ja debug-moodissa oltaessa ohjelma
tulostaa ruudulle mitä on tekemässä.

Mahdollisten muistivuotojen löytämiseksi ohjelmaa on ajettu eri
testitilanteissa Valgrind-työkalun lävitse.