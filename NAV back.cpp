#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <utility>
#include <map>


using namespace std;



class Room {
public:
	string name;
	bool visited = 0;
	char floor;
	map <string, Room*> connections; // содержит имена и указатели на комнаты, к которым можно попасть
	void show_name() {
		cout << name << " " << "on the floor: " << floor << endl;
	}
};

class Building {


public:
	map <string, Room> rooms; // содержит имя и уже объект
	int size = 0; // решить проблему с размером, когда добавлять запросы будем!!!!!!


	void add_ifnotexists(string name) {  //добавил в функцию добавление, если его нет
		if (rooms.count(name) == 0) {
			Room room;
			room.name = name;
			room.floor = name[0]; // этаж с лестницами запили сука!1!!1! :3
			rooms[name] = room;
		}
	}

	// добавление комнат -------------------------------------------------------------------------------------------
	void add_connections(vector<string> mass, string name) {	// добавить в map имя и к нему привязать комнату, также создать связи
		add_ifnotexists(name); // добавил комнату
		for (int i = 0; i < mass.size(); i++) {
			add_ifnotexists(mass[i]);  // добавил то, чего нет из тех, с кем она свяжется
			rooms[name].connections[mass[i]] = &rooms[mass[i]];
			rooms[mass[i]].connections[name] = &rooms[name];
		}
	}

	// поиск ---------------------------------------------------------------------------------------------------------
	string find_room(Room* beginning, string destination, string answer, vector<string> local) {
		Room* current = beginning; // комната, которая сейчас обрабатывается
		cout << "rec" << current->name << endl;
		local.push_back(current->name);
		current->visited = 1;
		if (beginning->name == destination) { // getting out of the recursion
			current->visited = 0;
			
			if (size == 0) {
				answer = "";
				size = local.size();
				for (string it : local) {
					answer += it + " ";
				}
				cout << "rec answer1: " << answer << endl;
			}
			else {
				if (size > local.size()) {
					answer = "";
					size = local.size();
					for (string it : local) {
						answer += it + " ";
					}
				}
				cout << "rec answer2: " << answer << endl;
			}
			cout << "size: " << size << endl;
			return answer;
		}
		if (size != 0 && local.size() >= size) {
			return answer; // если размер локального пути больше чем найденный короткий, то скипаем его
		}
		map <string, Room*> ::iterator room = current->connections.begin(); // объявление итератора для map, я хуй знает почему во всей функции
		for (int i = 0; room != current->connections.end(); i++, room++) {
			if (room->second->visited == 0) {
				answer = find_room(room->second, destination, answer, local); // room->second должен указать на указатель комнаты (да я даун)
			}
		}
		current->visited = 0;
		return answer; // затычка
	}

};



int main() {
	// инициализация всего -----------------------------------------------------------
	int n, m;
	string name;
	vector<string> cons;
	Building cronva;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> m;
		cin >> name;
		for (int j = 0; j < m; j++) {
			string a;
			cin >> a;
			cons.push_back(a);
		}
		cronva.add_connections(cons, name);
		cons.clear();
	}

	// примеры итераций по vector and map ---------------------------------------------------
	map <string, Room> ::iterator it = cronva.rooms.begin();
	for (int i = 0; it != cronva.rooms.end(); it++, i++) {
		cons.push_back(it->first);
		cout << i << " " << it->first << endl;
	}
	cout << "all the cons go now:" << endl;
	for (string y : cons) {
		cout << "name of room " << y << endl;
		map <string, Room*> ::iterator t = cronva.rooms[y].connections.begin();
		for (int j = 0; t != cronva.rooms[y].connections.end(); j++, t++)
			t->second->show_name();
	}

	// тест поиска -------------------------------------------
	cout << endl << "do stuff " << endl;
	string room1, room2, ans;
	vector<string> test;
	cin >> room1 >> room2;
	ans = cronva.find_room(&cronva.rooms[room1], room2, "", test);
	cout << ans;
	return 0;

}