# Robot-Commands
In realizarea temei1 m-am bazat pe construirea acesteia pe baza
ResizableArray-urilor si a DoublyLinkedList-urilor, in special in construirea
stivelor(Stack.h) si a cozilor(Queue.h).

-> Modularizare
	Pentru modularizare am ales sa implementez doua headere suplimentare (pe
langa cele obligatorii, adica Stack.h si Queue.h) ResizableArray( am incercat
sa evit folosirea vectorilor obisnuiti, si am mers pe aceasta implementare
pentru mai multi vectori pe care i-am folosit ulterior in program) si 
Commands.h care contine toate fuctiile, care la randul lor definesc comenzile
necesare functionarii robotului.

-> Citirea
	Citirea numarului robotilor, a liniei si a coloanei matricei am realizat-o
basic, citindu-le pe rand de la tastatura, iar citirea restului de input, adica
comenzile implicite, am citit linie cu linie din fisierul de intrare, am memo-
rat pe rand fiecare linie intr-un fisier auxiliar, citind apoi din el linia,
insa nu sub forma de string, ci sub forma dorita de ipoteza(numele comenzii si
instructiunile implicite) reusind astfel manipularea fiecarei linii, memorand
toate comenzile intr-un ResizableArray si pentru fiecare comanda fiecare
instructiune tot intr-un ResizableArray.

-> Operatori necesari in executia programului
	n - numarul robotilor;
	lin - numarul liniilor;
	col - numarul coloanelor;
	map - mapa cutiilor;
	deq - vector cu fiecare coada a fiecarui robot;
	commands - ResizableArray care retine toate comenzile date de oameni;
	instr - vector de ResizableArray-uri care retine fiecare intructiune
		a fiecarei comenzi;
	nr_comm - numarul de comenzi date de oameni;
	comm - Stiva cu pozitiile tuturor comenzilor de tipul ADD, impreuna
		cu comenzile EXECUTE care se efectueaza cu succes;
	last - Stiva cu pozitiile tuturor comenzilor executate. Are rol in 
		aflarea ultimei comenzi executate(LAST_EXECUTED_COMMAND);
	pos - vector cu fiecare pozitie a fiecarei comenzi din coada fiecarui
		robot;
	pos_aux - vector auxiliar de pozitii a fiecarei comenzi a fiecarui
		robot, care are rol in aflarea comenzii HOW_MUCH_TIME, memorand
		pozitia comenzii in cazul unui posibil UNDO;
	many - vector care retine pentru fiecare robot numarul de cutii
		detinute la un moment dat, care la inceput este 0 pentru
		fiecare robot;
	much - vector care retine pentru fiecare comanda timpul de la
		ultima executare, care initial este 0 pentru fiecare comanda;
	

-> Executia programului implicit
	Am parcurs ResizableArray-ul de comenzi si pentru fiecare comanda am com-
parat-o cu fiecare comanda posibila existenta robotului, iar in cazul potri-
virii se executa cate una pe rand:
	->"ADD_DROP_BOX/ADD_GET_BOX"(implicit functia comm_add) -- la intalnirea
acestei comenzi in Resizable-Array-ul de comenzi, aceasta se adauga in stiva
de comenzi comm, stiva pe care se poate aplica comanda EXECUTE, dar si cea
de UNDO, si in acelasi timp adaugam comanda respectiva, in functie de
prioritate, in coada robotului al carui id era specificat de prima instructiune
a comenzii;
	->"EXECUTE"(implicit functia comm_execute_ -- executa comenzile de tipul
"ADD..." de la inceputul cozii robotului, atat timp cat aceasta nu este goala.
In acest caz se afiseaza unmesaj corespunzator, iar in caz contrar in functie
de cutiile care trebuie luate sau lasate actualizeaza numarul de cutii din
mapa, numarul de cutii detinute de robotul respectiv la acel moment(dropvalue),
cat si adaugarea comenzii executate in stiva last si eliminarea acesteia din
coada robotului;
	->"UNDO"(implicit functia comm_undo) -- cat timp stiva de comenzi nu este
goala, comanda se executa pe ultima comanda din stiva comm:
		>> In cazul in care intalneste un EXECUTE care nu a executat nimic,
trece la urmatoarea comanda( verifica asta prin prisma setarii de la inceput 
a instructiunii comenzii EXECUTE cu -1);
		>> In cazul in care intalneste o comanda de tipul EXECUTE restabileste
numarul initial de cutii din comanda, dar si din mapa(actualizeaza vectorul
many, si pune la loc cutiile in comanda prin intermediul vectorului dropvalue)
si pune la loc comanda in coada robotului(la inceputul cozii);
		>> In cazul in care intalneste o comanda de tipul ADD, sterge comanda
din coada robotului in functie de prioritate;
	->"PRINT_COMMANDS"(implicit functia comm_print) -- afiseaza toate
comenziile existente in coada robotului la acel moment( id-ul robotului se
identifica prin intermediul primei instructiuni). Daca nu exista nicio comanda
se afiseza un mesaj corespunzator;
	->"LAST_EXCUTED_COMMAND"(implicit functia comm_last) -- cat timp stiva last
nu este goala, afiseaza ultima comanda executata prin intermediul ultimului
elemement din last, care ofera pozitia ultimei comenzi executate;
	->"HOW_MUCH_TIME" -- este generat foarte usor prin intermediul vectorului
much care va afisa timpul ultimei comenzi prin intermediul pozitiei furnizate
de ultimul element din stiva last;
	->"HOW_MANY_BOXES" -- la fel ca HOW_MUCH_TIME, acesta este generat pe baza
vectorului many prin intermediul pozitiei furnizate chiar de comanda in sine;
