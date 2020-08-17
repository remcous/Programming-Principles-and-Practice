/*
    exercise12.cpp
    HUNT THE WUMPUS

    Revision History:
*/

#include "../std_lib_facilities.h"

/****************************************
*           CLASS DEFINITIONS
****************************************/

// classification of Room based hazards (ie, not wumpus)
enum class Hazard{
	Safe, Bat, Pit
};

class Room{
public:
	Room():h{Hazard::Safe}, wumpus{false}, tunnel(0){}

	// Tunnel interface
	int get_num_tunnels(){return tunnel.size();}
	void add_tunnel(Room* room){tunnel.push_back(room);}
	Room* get_tunnel(int n){return tunnel[n];}

	// Hazard interface
	void set_hazard(Hazard haz){h = haz;}
	Hazard get_hazard(){return h;}

	// Wumpus interface
	bool is_wumpus(){return wumpus;}
	void set_wumpus(bool present){wumpus = present;}

private:
	vector<Room*> tunnel;
	Hazard h;
	bool wumpus;
};

class Cave{
public:
	Cave();	// standard difficulty 2 bats, 2 pits, 1 wumpus, 20 rooms

	// returns a pointer to a room in rooms vector
	Room* get_room(int n){return &rooms[n];}

	// Moves the wumpus from current position to random connected room
	void move_wumpus();
	int get_room_num(Room* room);
	int get_max_rooms(){return max_rooms;}

	void print_all();	// debug printout

private:
	vector<Room> rooms;
	int num_bats;
	int num_pits;
	int max_rooms;
};

class Player{
public:
	Player(Room* start):num_arrows{5}, pos{start}, alive{true}
		{}

	// Interface functions
	Room* get_position(){return pos;}
	void set_position(Room* room){pos = room;}
	int get_num_arrows(){return num_arrows;}
	bool is_alive(){return alive;}
	void die(){alive = false;}

	// player actions
	void move(Room* dest);
	bool shoot(Room* target);
	bool shoot(vector<Room*> targets);

private:
	int num_arrows;
	Room* pos;
	bool alive;
};

/****************************************
*             MAIN FUNCTION
****************************************/

int main(){
    try{
        Cave cave{};
        Player pc{cave.get_room(0)};
        bool wumpus_alive = true;

        cout << "Enter commands to move or fire arrows\n"
        	<< "(ie, m2 to move to room 2, "
        	<< "or s2-3-4 to fire an arrow through rooms 2,3, and 4)\n\n";

        while(pc.is_alive() && wumpus_alive){
        	static char ch1;
        	static int num[3], num_rooms;
        	bool has_moved{false}, shot_arrow{false};

        	// output user location and available actions
        	cout << "You are in room " 
        		<< cave.get_room_num(pc.get_position())+1
        		<< ".\nYou can move to rooms: ";
        	for(int i=0; i<pc.get_position()->get_num_tunnels(); i++)
        	{
        		cout << cave.get_room_num(pc.get_position()->get_tunnel(i))+1 << ' '; 
        	}
        	cout << endl;

        	// Give user cues on adjacent hazards
    		for(int i=0; i<pc.get_position()->get_num_tunnels(); i++)
    		{
    			if(pc.get_position()->get_tunnel(i)->get_hazard() == Hazard::Pit)
    			{
    				cout << "I feel a breeze.\n";
    			}
    			else if(pc.get_position()->get_tunnel(i)->get_hazard() == Hazard::Bat)
    			{
    				cout << "I hear a bat.\n";
    			}
    			if(pc.get_position()->get_tunnel(i)->is_wumpus())
    			{
    				cout << "I smell the Wumpus.\n";
    			}
    		}

        	cout << "You have " << pc.get_num_arrows() << " arrows remaining.\n"
        		<< "What would you like to do: ";

        	cin >> ch1;

        	// parse user input
        	switch(ch1){
        	case 'm':
        		cin >> num[0];
        		if(num[0] > 0 && num[0] < cave.get_max_rooms())
        			has_moved = true;

        		// clear the buffer
        		cin.clear();
        		fflush(stdin);

        		break;
        	case 's':
        		num_rooms = 1;
        		cin >> num[0];

        		// get additional input up to 3 rooms
        		if(cin.get(ch1) && ch1 == '-'){
        			cin>>num[1];
        			num_rooms++;
        			if(cin.get(ch1) && ch1 == '-'){
        				cin >> num[2];
        				num_rooms++;
        			}
        		}

        		// clear the buffer
        		cin.clear();
        		fflush(stdin);

        		shot_arrow = true;

        		for(int i=0; i<num_rooms; i++){
        			if(num[i] <= 0 || num[i] > cave.get_max_rooms())
        				shot_arrow = false;
        		}

        		if(!shot_arrow) cerr << "\nError: Invalid room number\n";
        		
        		// verify rooms are within range
        		break;
        	/*
        	case 'd':	// get debug printout of all rooms, tunnels, and hazards
        		cave.print_all();
        		break;
        	*/
        	default:
        		cerr << "\nError: unknown command\n\n";
        		continue;
        	}

        	cout << "\n";

        	// handle user actions
        	if(has_moved){	// handle user movement
        		pc.move(cave.get_room(num[0] - 1));
        		has_moved = false;
        	}else if(shot_arrow){	// handle arrow firing mechanics
        		if(num_rooms==1)
	        		wumpus_alive = !(pc.shoot(cave.get_room(num[0]-1)));
	        	else if(num_rooms==2)
	        		wumpus_alive = !(pc.shoot({cave.get_room(num[0]-1),
	        			        			cave.get_room(num[1]-1)}));
	        	else
	        		wumpus_alive = !(pc.shoot({cave.get_room(num[0]-1),
						        			cave.get_room(num[1]-1), 
						        			cave.get_room(num[2]-1)}));

	        	if(!wumpus_alive){
	        		cout << "You successfully hunted the Wumpus!\n\n";
	        		continue;
	        	}

	        	cout << "You missed and the noise has caused the Wumpus to move!\n";
	        	cave.move_wumpus();

	        	if(pc.get_num_arrows() == 0){
	        		cout << "Game over! You ran out of arrows!\n\n";
	        		pc.die();
	        		continue;
	        	}
        	}

        	// handle npc actions
        	while(pc.get_position()->get_hazard() == Hazard::Bat){
        		cout << "You have been carried to a different room by a Giant Bat!\n";
        		pc.set_position(cave.get_room(randint(0, cave.get_max_rooms()-1)));
        	}

        	if(pc.get_position()->get_hazard() == Hazard::Pit){
        		cout << "Game over! You have fallen into a pit!\n\n";
        		pc.die();
        		continue;
        	}

        	if(pc.get_position()->is_wumpus()){
        		cout << "Game over! You were eaten by the Wumpus!\n\n";
        		pc.die();
        		continue;
        	}

        	cout << "\n";	// separate different turns visually
        }
    }
    catch(exception& e){
        cerr << e.what() << '\n';
        keep_window_open("~~");
        return 1;
    }
    catch(...){
        cerr << "exception\n";
        keep_window_open("~~");
        return 2;
    }
    return 0;
}

/****************************************
*       FUNCTION DEFINITIONS - Cave
****************************************/

Cave::Cave()
:rooms{20}, num_pits{2}, num_bats{2}
{
	cout << "Rooms constructed\n";

	max_rooms = rooms.size();

	cout << "Adding tunnels...\n";

	// iterate through each room
	for(int i=0; i<max_rooms; i++){
		while(rooms[i].get_num_tunnels() != 3)
		{
			static int temp;

			// value between current room and max room
			temp = randint(i+1, max_rooms-1);

			// both rooms need additional tunnels
			if(rooms[temp].get_num_tunnels() < 3)
			{
				// add link on both ends
				rooms[i].add_tunnel(&rooms[temp]);
				rooms[temp].add_tunnel(&rooms[i]);
			}
		}
	}

	cout << "Done adding tunnels\n"
		<< "Adding Bats...\n";

	// add bats
	for(int i=0; i < num_bats; i++){
		static int temp;
		temp = randint(1, max_rooms-1);

		if(rooms[temp].get_hazard() != Hazard::Safe)
		{
			i--;
			continue;
		}
		
		rooms[temp].set_hazard(Hazard::Bat);
	}

	cout << "Done adding Bats\n"
		<< "Adding Pits...\n";

	for(int i=0; i < num_pits; i++){
		static int temp;
		temp = randint(1, max_rooms-1);

		if(rooms[temp].get_hazard() != Hazard::Safe)
		{
			i--;
			continue;
		}
		
		rooms[temp].set_hazard(Hazard::Pit);
	}

	cout << "Done adding Pits\n";

	cout << "Placing Wumpus\n";

	rooms[randint(1, max_rooms-1)].set_wumpus(true);

	cout << "Placed Wumpus\n"
		<< "Cave construction complete\n\n";
}

void Cave::print_all(){
	for(int i=0; i<max_rooms; i++)
	{
		cout << i+1 << ":\ttunnels: ";

		for(int j=0; j<rooms[i].get_num_tunnels(); j++)
		{
			static Room* tun;
			tun = rooms[i].get_tunnel(j);

			for(int k=0; k < max_rooms; k++)
			{
				if(tun == &rooms[k]) cout << setw(2) << k+1 << " ";
			}
		}

		if(rooms[i].get_hazard() != Hazard::Safe){
			cout << "\tHazard: ";
			if(rooms[i].get_hazard() == Hazard::Bat) cout << "Bat";
			else if(rooms[i].get_hazard() == Hazard::Pit) cout << "Pit";
		}

		if(rooms[i].is_wumpus()) cout << "\tWumpus";

		cout << '\n';
	}
}

void Cave::move_wumpus(){
	int i;

	for(i=0; i<max_rooms; i++)
	{
		if(rooms[i].is_wumpus())
			break;
	}

	Room& temp = rooms[i];

	temp.set_wumpus(false);

	(temp.get_tunnel(randint(0,temp.get_num_tunnels()-1))) -> set_wumpus(true);
}

int Cave::get_room_num(Room* room){
	for(int i=0; i<max_rooms; i++)
	{
		if(&rooms[i] == room)
			return i;
	}

	// not in room vector
	return -1;
}

void Player::move(Room* dest){
	bool valid = false;

	// confirm that the destination is valid
	for(int i=0; i<pos->get_num_tunnels(); i++)
	{
		if(dest == pos->get_tunnel(i))
			valid = true;
	}

	if(!valid){
		cerr << "Error: Invalid player move\n";
		return;
	}

	pos = dest;
}

bool Player::shoot(Room* target){
	bool valid{false};
	for(int i=0; i<pos->get_num_tunnels(); i++)
	{
		if(target == pos->get_tunnel(i)) valid = true;
	}

	if(!valid){	// change target
		cout << "Arrow fired randomly\n";
		target = pos->get_tunnel(randint(0, pos->get_num_tunnels()-1));
	}

	num_arrows--;

	if(target->is_wumpus())
			return true;

	return false;
}

bool Player::shoot(vector<Room*> targets){
	num_arrows--;

	// Handle first case based on player position
	bool valid{false};
	for(int i=0; i<pos->get_num_tunnels(); i++)
	{
		if(targets[0] == pos->get_tunnel(i)) valid = true;
	}

	if(!valid){	// change target
		cout << "Arrow went in a random direction!\n";
		targets[0] = pos->get_tunnel(randint(0, pos->get_num_tunnels()-1));
	}

	if(targets[0]->is_wumpus())
			return true;

	// Handle general case
	for(int i=1; i< targets.size(); i++){
		valid = false;

		for(int j=0; j<targets[i-1]->get_num_tunnels(); j++)
		{
			if(targets[i] == targets[i-1]->get_tunnel(j)) valid = true;
		}

		if(!valid){	// change target
			cout << "Arrow went in a random direction!\n";
			targets[i] = targets[i-1]->get_tunnel(
				randint(0, targets[i-1]->get_num_tunnels()-1));
		}

		if(targets[i]->is_wumpus())
			return true;
	}

	return false;
}
