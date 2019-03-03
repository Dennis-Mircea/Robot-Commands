/*
 * Copyright [2018] <CIUPITU DENNIS-MIRCEA 313CA>
 */
#ifndef _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_COMMANDS_H_
#define _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_COMMANDS_H_

#include <iostream>
#include <string>
#include "Deque.h"
#include "ResizableArray.h"
#include "Stack.h"

void comm_add(Stack<int> *comm, ResizableArray<int> *instr,
 			Deque<std::string> *deq, ResizableArray<int> *pos,
 			ResizableArray<int> *pos_aux, int j,
			ResizableArray<std::string> *commands) {
	comm->push(j);
	// in functie de prioritate comenzile sunt adaugate in coada
	if (instr[j].getElem(4) == 0) {
		deq[instr[j].getElem(0)].push_front(commands->getElem(j));
		pos[instr[j].getElem(0)].addFirst(j);
		pos_aux[instr[j].getElem(0)].addFirst(j);
	} else {
		deq[instr[j].getElem(0)].push_back(commands->getElem(j));
		pos[instr[j].getElem(0)].addLast(j);
		pos_aux[instr[j].getElem(0)].addLast(j);
	}
}

void comm_execute(Stack<int> *comm, Stack<int> *last,
 	ResizableArray<int> *instr, ResizableArray<std::string> *commands,
 	ResizableArray<int> *pos, ResizableArray<int> *boxget,
 	ResizableArray<int> *dropvalue, int **map, int many[2000], int j,
 	int much[3000], Deque<std::string> *deq, ResizableArray<int> *pos_aux) {
	comm->push(j);
	// contoare pentru memorarea fiecarei instructiuni aferente
	int i0, i1, i2, i3;
	i0 = instr[pos[instr[j].getElem(0)].getElem(0)].getElem(0);
	i1 = instr[pos[instr[j].getElem(0)].getElem(0)].getElem(1);
	i2 = instr[pos[instr[j].getElem(0)].getElem(0)].getElem(2);
	i3 = instr[pos[instr[j].getElem(0)].getElem(0)].getElem(3);
	// verifica tipul comenzii de executat
	if (commands->getElem(pos[instr[j].getElem(0)].getElem(0)) ==
	"ADD_GET_BOX") {
	/**
	*	In cazul in care numarul cutiilor pe care robotul
	*	trebuie sa le ia este mai mare decat cutiile disponibile
	*	in acea zona
	*/
		if (map[i1][i2] < i3) {
			// In acest caz robotul va lua toate cutiile din zona
			instr[pos[instr[j].getElem(0)].getElem(0)].setElem(map[i1][i2], 3);
			map[i1][i2] = 0;
			boxget->addLast(i3);
		} else {
			map[i1][i2] -= i3;
		}
		// se actualizeaza numarul de cutii detinute de robot
		many[i0] += instr[pos[instr[j].getElem(0)].getElem(0)].getElem(3);
	} else if (commands->getElem(pos[instr[j].getElem(0)].getElem(0)) ==
 "ADD_DROP_BOX") {
		/**
		*	Verificam faptul ca robotul dispune de cutiile care
		*	trebuie lasate
		*/
		if (many[i0] >= i3) {
			// in cazul in care dispune de numarul de cutii
			many[i0] -= i3;
			map[i1][i2] += i3;
			dropvalue->addLast(i3);
		} else {
			map[i1][i2] += many[i0];
			dropvalue->addLast(many[i0]);
			instr[pos[instr[j].getElem(0)].getElem(0)].setElem(many[i0], 3);
			many[i0] = 0;
		}
	}
	last->push(pos[instr[j].getElem(0)].getElem(0));
	much[pos[instr[j].getElem(0)].getElem(0)] = j - pos_aux[i0].getElem(0);
	// se calculeaza si timpul de la aparitie pana la executie
	deq[i0].pop_front();
	pos[i0].removeFirst();
	pos_aux[i0].removeFirst();
}

void comm_undo(Stack<int> *comm, Stack<int> *last, ResizableArray<int> *instr,
			ResizableArray<std::string> *commands, ResizableArray<int> *pos,
 			ResizableArray<int> *boxget, ResizableArray<int> *dropvalue,
			int **map, int many[2000], int j, Deque<std::string> *deq,
			ResizableArray<int> *pos_aux) {
	if (commands->getElem(comm->peek()) == "ADD_GET_BOX" ||
		commands->getElem(comm->peek()) == "ADD_DROP_BOX") {
		// contor care retine pozitia ultimei comenzi executate
		int k = comm->peek();
		// sterge comanda in functie de prioritate
		if (instr[k].getElem(4) == 0) {
			deq[instr[k].getElem(0)].pop_front();
			pos[instr[k].getElem(0)].removeFirst();
			pos_aux[instr[k].getElem(0)].removeFirst();
		} else {
			deq[instr[k].getElem(0)].pop_back();
			pos[instr[k].getElem(0)].removeLast();
			pos_aux[instr[k].getElem(0)].removeLast();
		}
	}
	if (commands->getElem(comm->peek()) == "EXECUTE" &&
		instr[comm->peek()].getElem(0) != -1) {
		// contoare pentru memorarea fiecarei instructiuni aferente
		int i0, i1, i2, i3;
		i0 = instr[last->peek()].getElem(0);
		i1 = instr[last->peek()].getElem(1);
		i2 = instr[last->peek()].getElem(2);
		i3 = instr[last->peek()].getElem(3);
		if (commands->getElem(last->peek()) == "ADD_DROP_BOX") {
			// pune la loc toate cutiile
			many[i0] += dropvalue->getElem(dropvalue->size() - 1);
			map[i1][i2] -= dropvalue->getElem(dropvalue->size() - 1);
			dropvalue->removeLast();
		}
		if (commands->getElem(last->peek()) == "ADD_GET_BOX") {
			// in cazul in care s-au luat toate cutiile dintr-o zona
			if (boxget->getLast() == 0) {
				map[i1][i2] += i3;
			} else {
				map[i1][i2] += i3;
				instr[last->peek()].setElem(boxget->getElem(boxget->size() - 1), 3);
			}
			boxget->removeLast();
			// actualizeaza numarul de cutii detinute de robot
			many[i0] -= instr[last->peek()].getElem(3);
		}
		// pune la loc comanda in coada robotului
		deq[i0].push_front(commands->getElem(last->peek()));
		pos[i0].addFirst(last->peek());
		pos_aux[i0].addFirst(j);
		last->pop();
	}
}

void comm_print(std::ostream& out, Deque<std::string> *deq,
				ResizableArray<int> *instr, ResizableArray<int> *pos, int j) {
	out << "PRINT_COMMANDS: ";
	int contor = 0;
	for (int k = 0; k < deq[instr[j].getElem(0)].size(); k++) {
		Node<std::string> *temp = deq[instr[j].getElem(0)].front();
		contor++;
		// inainte sa afisam comenzile, printam id-ul robotului
		if (contor == 1) {
			out << instr[j].getElem(0) << ": ";
		}
		// daca exista mai multe comenzi in coada pune ;
		if (contor > 1) {
			out << "; ";
		}
		std::string str = temp->data;
		// afisare tip comanda(GET sau DROP)
		for (unsigned int l = 4; l < str.size() - 4; l++) {
			out << str[l];
		}
		// afisare conform modului din ipoteza
		out << " " << instr[pos[instr[j].getElem(0)].getElem(k)].getElem(1);
		out << " " << instr[pos[instr[j].getElem(0)].getElem(k)].getElem(2);
		out << " " << instr[pos[instr[j].getElem(0)].getElem(k)].getElem(3);
		// parcurg coada punand primul element la sfarsit
		deq[instr[j].getElem(0)].push_back(deq[instr[j].getElem(0)].pop_front());
	}
	out << std::endl;
}

void comm_last(std::ostream& out, Stack<int> *last, ResizableArray<int> *instr,
 				ResizableArray<std::string> *commands) {
	out << "LAST_EXECUTED_COMMAND: ";
	// extrage numele ultimei comenzi executate
	std::string str = commands->getElem(last->peek());
	out << instr[last->peek()].getElem(0) << ": ";
	// afisare tip comanda
	for (unsigned int l = 4; l < str.size() - 4; l++) {
		out << str[l];
	}
	// afisare conform modului din ipoteza
	out << " " << instr[last->peek()].getElem(1) << " ";
	out << instr[last->peek()].getElem(2) << " ";
	out << instr[last->peek()].getElem(3) << std::endl;
}

#endif  // _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_COMMANDS_H_
