/*
 * Copyright [2018] <CIUPITU DENNIS-MIRCEA 313CA>
 */
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

#include "Deque.h"
#include "ResizableArray.h"
#include "Stack.h"
#include "Commands.h"

#define N 3000

int main() {
#ifdef TEMA_1
	std::ostream& out = std::cout;
#else
	std::ofstream file1;
	std::ifstream file2;
	file2.open("robots.in");
	file1.open("robots.out");
	std::ifstream& in = file2;
	std::ostream& out = file1;
#endif
	int n, lin, col, i, j, **map;
	Deque<std::string> *deq;
	ResizableArray<std::string> commands;
	ResizableArray<int> *instr;

	/* citim numarul robotilor(n), nr. liniilor(lin), nr.coloanelor(col) */
	in >> n >> lin >> col;
	map = new int*[lin];
	for (i = 0; i < lin; i++) {
		map[i] = new int[col];
	}

	// citim zona cu cutii(map[LIN][COL])
	for (i = 0; i < lin; i++) {
		for (j = 0; j < col; j++) {
			in >> map[i][j];
		}
	}
	deq = new Deque<std::string>[n];
	instr = new ResizableArray<int>[N];
	// parcurgem fisierul citind linie cu linie
	std::string line;
	getline(file2, line);  // prima linie va fi goala
	int nr_comm = -1;
	while (getline(file2, line)) {
		nr_comm++;
		// ne folosim de un fisier auxiliar pentru a manipula linia
		std::ofstream aux;
		aux.open("aux.txt");
		aux << line;
		aux.close();
		std::ifstream aux1;
		aux1.open("aux.txt");
		std::string command;
		aux1 >> command;
		commands.addLast(command);
		// in functie de tipul comenzii se retin instructiunile aferente
		if (command == "ADD_GET_BOX" || command == "ADD_DROP_BOX") {
			// id = idRobot;
			// x,y = coordonate map;
			// nr = NrBoxes;
			// pr = Priority;
			int id, x, y, nr, pr;
			aux1 >> id >> x >> y >> nr >> pr;
			instr[nr_comm].addLast(id);
			instr[nr_comm].addLast(x);
			instr[nr_comm].addLast(y);
			instr[nr_comm].addLast(nr);
			instr[nr_comm].addLast(pr);
		} else if (command == "EXECUTE" || command == "PRINT_COMMANDS" ||
					command == "HOW_MANY_BOXES") {
			int id;
			aux1 >> id;
			instr[nr_comm].addLast(id);
		}
		aux1.close();
	}
	Stack<int> last, comm;
	ResizableArray<int> *pos = new ResizableArray<int>[2000];
	ResizableArray<int> *pos_aux = new ResizableArray<int>[2000];
	ResizableArray<int> boxget, dropvalue;
	int much[3000], many[n];
	// initializam vectorul many
	for (j = 0; j < n; j++) {
		many[j] = 0;
	}
	// parcurgem tot vectorul cu comenzi
	for (j = 0; j <= nr_comm; j++) {
		much[j] = 0;
		if (commands.getElem(j) == "ADD_GET_BOX" ||
			commands.getElem(j) == "ADD_DROP_BOX") {
			comm_add(&comm, instr, deq, pos, pos_aux, j, &commands);
		}
		if (commands.getElem(j) == "EXECUTE") {
			if (deq[instr[j].getElem(0)].size() == 0) {
				instr[j].setElem(-1, 0);
				out << "EXECUTE: No command to execute" << std::endl;
			} else {
				comm_execute(&comm, &last, instr, &commands, pos, &boxget,
 &dropvalue, map, many, j, much, deq, pos_aux);
			}
		}
		if (commands.getElem(j) == "UNDO") {
			if (comm.size() != 0) {
				comm_undo(&comm, &last, instr, &commands, pos, &boxget,
 &dropvalue, map, many, j, deq, pos_aux);
				// elimina comanda in stiva de comenzi
				comm.pop();
			} else {
				out << "UNDO: No History" << std::endl;
			}
		}
		if (commands.getElem(j) == "PRINT_COMMANDS") {
			if (deq[instr[j].getElem(0)].size() != 0) {
				comm_print(out, deq, instr, pos, j);
			} else {
				out << "PRINT_COMMANDS: No command found" << std::endl;
			}
		}
		if (commands.getElem(j) == "LAST_EXECUTED_COMMAND") {
			if (last.size() != 0) {
				comm_last(out, &last, instr, &commands);
			} else {
				out << "No command was executed" << std::endl;
			}
		}
		if (commands.getElem(j) == "HOW_MUCH_TIME") {
			/**
			 *	cat timp s-au executat comenzi afiseaza timpul
			 *	ultimei comenzi executate pe baza vectorului much			
			 */
			if (last.size() == 0) {
				out << "HOW_MUCH_TIME: No command was executed"<< std::endl;
			} else {
				out << "HOW_MUCH_TIME: " << much[last.peek()] << std::endl;
			}
		}
		if (commands.getElem(j) == "HOW_MANY_BOXES") {
			out << "HOW_MANY_BOXES: ";
			out << many[instr[j].getElem(0)] << std::endl;
		}
	}
	// Eliberarea memoriei
	for (j = 0; j < lin; j++) {
		delete[] map[j];
	}
	delete[] map;
	delete[] deq;
	delete[] instr;
	delete[] pos;
	delete[] pos_aux;
#ifndef TEMA_1
	file2.close();
	file1.close();
#endif
	return 0;
}
