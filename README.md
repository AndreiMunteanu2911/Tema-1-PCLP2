# Tema-1-PCLP2

get_byte_length
Functie auxiliara ce primeste vectorul arr si lungimea sa si calculeaza cati octeti ocupa. Va fi folosita in functiile urmatoare.

add_last
Daca arr e nul, adica adaugam primul element, atunci alocam memorie de data->header->len octeti, altfel realocam memoria pentru a mari dimensiunea vectorului. Folosind memcpy copiem mai intai headerul, apoi datele propriu-zise din data_structure* data in arr, incepand de la finalul arr, semnificat de variabila byte_count. Apoi incrementam len.

add_at
Similar ca mai sus, doar ca inainte calculam pozitia octetului de la inceputul caruia trebuie sa copiem headerul si datele primite, stocand indexul in variabila current. Apoi mutam toti octetii ce sunt dupa pozitia specificata in arr la o distanta data->header->len + sizeof(head) mai in fata pentru a face loc elementului nou, dupa care il copiem. Incrementam len.

find
Similar cu mai sus, inainte ajungem la octetul de la care incepe elementul determinat de indexul primit, pozitie pe care o stocam in current. Printam primul nume, memoram inceputul zonei ce contine numerele in nr_start iar apoi, in functie de tipul headerului (1, 2 sau 3) sarim peste atatia octeti cati ocupa numerele stocate (2, 6 si 8 respectiv) si printam si al doilea nume. Ne intoarcem la pozitia nr_start si afisam si numerele, in functie de cati octeti ocupa.

delete_at
Inainte ajungem la pozitia de la care incepe elementul pe care trebuie sa il stergem, si o memoram in index_start. Apoi copiem urmatorii biti ramasi in arr (byte_count - sizeof(head) - len_rem - index_start) la pozitia index_start si scadem len cu 1.

print
Acelasi algoritm ca find, doar ca se afla intr-un while (byte_count>0) pentru a printa intreg arr.
