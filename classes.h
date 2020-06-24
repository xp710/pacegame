#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

//define object classes
class item {
private:
    //for doors
    string leads_to_room_name;
    string key_needed;
    bool is_locked;
protected:
    friend class door;
    friend class player;
    friend class computer;
    string name;
    string description;
    bool can_be_taken;
    bool can_kill = 0;

    //for setting the description
    void set_description(string description_to_be){
        description = description_to_be;
    }

public:
    //vector of names an item can be reffered to in-game
    vector<string> names;

    //for unlocking doors with that one cheat code
    void unlock(){
        if (is_locked){
            is_locked = 0;
        }
    }

    //for locking doors
    void lock(){
        if (!is_locked){
            is_locked = 1;
        }
    }

    bool hidden = 0; //if this is true, the item isn't displayed with the room

    //default use function
    virtual void use(){
        cout << "You can't find a use for this." << endl;
    }

    //for displaying description
    void describe(){
        cout << description << endl;
    }

    //for setting the name of the object
    void set_name(string name_to_be){
        name = name_to_be;
    }

    //for displaying name
    string disp_name(){
        return name;
    }
};

//define room class
class room : public item{
private:
    friend class computer;
    friend class player;

public:
    //the list for storing items in the room
    vector<item*> in_here;

    //disables the player from adding the room to their inventory
    bool can_be_taken = 0;

    //hint for when players are stuck
    string hint;

    //adds the ability to add items to the room
    void add_item(item* to_add){
        in_here.push_back(to_add);
    }

    room(string name_to_be, string desc_to_be){
        name = name_to_be;
        description = desc_to_be;
        hint = "There is no hint for this room.";
    }
};

//define keys
class key : public item {
public:
    //enables the player to pick it up

    //for construction
    key(string name_to_be, string description_to_be){
        can_be_taken = 1;
        name = name_to_be;
        description = description_to_be;
    }
};

//define generic items
class generic_item : public item {
private:
    string use_msg = "You can't find a use for this.";
public:
    generic_item(string name_to_be, string desc_to_be, bool able_to_get){
        name = name_to_be;
        description = desc_to_be;
        can_be_taken = able_to_get;
    }

    //declaration where you can change the message output by use
    generic_item(string name_to_be, string desc_to_be, bool able_to_get, string use_msg_to_be){
        name = name_to_be;
        description = desc_to_be;
        can_be_taken = able_to_get;
        use_msg = use_msg_to_be;
    }

    void use(){
        cout << use_msg << endl;
    }
};

//define non-player characters
class npc : public item {
protected:
    friend class player;
    friend class weapon; //weapon class is friend so that weapons can kill npcs
    bool alive;
    string talk_message; //what the npc says if you talk to them
    string death_message; //the message displayed on the npc's death
    room* in_room; //the room the NPC is in, compared to the player's current room to see if they are in the same room
public:

    bool is_alive(){
        return alive;
    }
    //default constructor
    npc(){
        name = "NPC";
        description = "Literally featureless because you refused to give them any life.";
        alive = 1;
        talk_message = "Hello, I am an NPC.";
        death_message = "NPC has died.";
    }
    //regular constructor
    npc(string name_to_be, string desc_to_be, string talk_to_be, string death_to_be, room* room_to_be_in){
        alive = 1;
        name = name_to_be;
        description = desc_to_be;
        talk_message = talk_to_be;
        death_message = death_to_be;
        in_room = room_to_be_in;
    }

    //the speech function
    void talk(){
        //makes sure that npcs can't talk if they're dead
        if (alive){
            cout << name << "Says \"" << talk_message << "\"" << endl;
        }else{
            cout << name << " can't talk if they're dead." << endl;
        }
    }
};

//the list of npcs to be scanned by player.disproom to see if there are npcs in the room
vector<npc*> npc_list;

//define doors
class door : public item {
private:
    friend class player;
    friend class computer;
    //function for locking or unlocking
    void change_state(){
        if(is_locked){
            is_locked = 0;
        }else{
            is_locked = 1;
        }
    }

public:
    //shows outside if it's locked
    bool* state = &is_locked;

    //default constructor defining an unlocked door not needing a key
    door(){
        can_be_taken = 0;
        is_locked = 0;
        name = "n";
        description = "just a generic door";
    }

    //different constructor
    door(string name_to_be, string description_to_be, string where_to){
        can_be_taken = 0;
        is_locked = 0;
        name = name_to_be;
        description = description_to_be;
        leads_to_room_name = where_to;
    }

    door(string name_to_be, string description_to_be, bool locked, string key_thats_needed, string where_to){
        can_be_taken = 0;
        name = name_to_be;
        description = description_to_be;
        is_locked = locked;
        key_needed = key_thats_needed;
        leads_to_room_name = where_to;
    }
};

//room list for searching for room names
vector<room*> roomlist;

//define computers
class computer : public item {
private:
    //the door the computer can lock and unlock
    door* lockable;
public:
    //default constructor
    computer(){
        cout << "Computer requires actual definitions\n\n";
    }

    //real constructor
    computer(string name_to_be, string desc_to_be, door* door_to_control){
        lockable = door_to_control;
        name = name_to_be;
        description = desc_to_be;
        can_be_taken = 0;
    }

    //function for using the computer in the game
    void use(){
        lockable->change_state();

        //search for the room the door is in
        //so that player can be told what room it's in
        string roomname;
        for (int i = 0; i < roomlist.size(); i++){
            for (int j = 0; j < roomlist[i]->in_here.size(); j++){
                if (roomlist[i]->in_here[j] == lockable){
                    roomname = roomlist[i]->name;
                }
            }
        }
        //figure out what type of exit the door is
        //once again, to tell the player
        string direction;
        if (lockable->name == "n"){
            direction = "North";
        }else if (lockable->name == "e"){
            direction = "East";
        }else if (lockable->name == "s"){
            direction = "South";
        }else if (lockable->name == "w"){
            direction = "West";
        }else{
            cout << "something is wrong with door variable in " << roomname << endl;
        }

        //display unlock message
        if (lockable->is_locked){
            cout << direction << " exit in " << roomname << " is now locked." << endl;
        }else{
            cout << direction << " exit in " << roomname << " is now unlocked." << endl;
        }
    }
};

//define weapons
class weapon : public item{
public:
    //default constructor
    weapon(){
        name = "crowbar";
        description = "Just a regular crowbar.";
        can_kill = 1;
    }

    //constructor
    weapon(string name_to_be, string description_to_be){
        name = name_to_be;
        description = description_to_be;
        can_kill = 1;
    }
};

//define player
class player {
protected:
    vector<room*> been_in;
    vector<item*> inventory;
    room* current_room;
public:
    bool play = 1;
    void disproom(){
        cout << current_room->name << endl
             << current_room->description << endl;
        for (int i = 0; i < current_room->in_here.size(); i++){
            if ((current_room->in_here[i]->name == "n") || (current_room->in_here[i]->name == "e") ||
                    (current_room->in_here[i]->name == "s") || (current_room->in_here[i]->name == "w")){
                cout << "";
            }else{
                //only display the item if it isn't hidden
                if (!current_room->in_here[i]->hidden){
                    cout << "There is a " << current_room->in_here[i]->name << " here." << endl;
                }
            }
        }
        //the part of the function that sees in npcs are in the room
        for (int i = 0; i < npc_list.size(); i++){
            if (npc_list[i]->in_room == current_room){
                //tests if they're dead and describes them accordingly
                if (npc_list[i]->alive){
                    cout << npc_list[i]->name << " is here." << endl;
                }else{
                    cout << "The corpse of " << npc_list[i]->name << " lies here." << endl;
                }
            }
        }
    }

    int set_room(room* room_to_move_to){
        current_room = room_to_move_to;
        for (int i = 0; i < been_in.size(); i++){
            if (been_in[i]->name == current_room->name){
                cout << current_room->name << endl;
                return 0;
            }
        }
        disproom();
        been_in.push_back(current_room);
    }

    //for the rest of the code to see the current room
    room* showcurr_room(){
        return current_room;
    }

    //for the rest of the code to see the inventory
    vector<item*> showinv(){
        return inventory;
    }

    //the way to control the player
    void move(string move){
        //convert the move to a way to see each argument individually
        stringstream long_move;
        string movepart;
        long_move << move;
        long_move >> movepart;

        //look function. a player can see the room description with "look" and
        //can see item descriptions with "look at [item]"
        if ((movepart == "look") || (movepart == "l")){
            long_move >> movepart;
            if (movepart == "at"){
                long_move >> movepart;
                //looks at every item in the room or player's inventory
                //for one with a matching name. if it finds one,
                //it outputs the description
                for (int i = 0; i < current_room->in_here.size(); i++){
                    if (movepart == current_room->in_here[i]->name){
                        cout << current_room->in_here[i]->description << endl;
                        i = current_room->in_here.size();
                    }else{
                        for (int j = 0; j < current_room->in_here[i]->names.size(); j++){
                            if (movepart == current_room->in_here[i]->names[j]){
                                cout << current_room->in_here[i]->description << endl;
                            }
                        }
                    }
                }
                //the abiliaty to look at npcs
                for (int i = 0; i < npc_list.size(); i++){
                    //makes sure the npc exists and is in the same room
                    if ((npc_list[i]->name == movepart) && (npc_list[i]->in_room == current_room)){
                        cout << npc_list[i]->description << endl;
                    }
                }
                for (int i = 0; i < inventory.size(); i++){
                    if (movepart == inventory[i]->name){
                        cout << inventory[i]->description << endl;
                    }else{
                        for (int j = 0; j < inventory[i]->names.size(); j++){
                            if (movepart == inventory[i]->names[j]){
                                cout << inventory[i]->description << endl;
                            }
                        }
                    }
                }
            }else if ((movepart == "n") || (movepart == "e") || (movepart == "s") || (movepart == "w")){
                for (int i = 0; i < current_room->in_here.size(); i++){
                    if (current_room->in_here[i]->name == movepart){
                        cout << current_room->in_here[i]->description << endl;
                    }
                }
            }else{
                disproom();
            }
        }
        /*quit function*/else if (movepart == "quit"){
            play = 0;
        }
        /*take function*/else if (movepart == "take"){
            long_move >> movepart;
            for (int i = 0; i < current_room->in_here.size(); i++){
                //tests for item player is trying to pick up
                if (movepart == current_room->in_here[i]->name){
                    //tests if it can be picked up
                    if (current_room->in_here[i]->can_be_taken){
                        inventory.push_back(current_room->in_here[i]);
                        current_room->in_here.erase(current_room->in_here.begin() + i);
                        cout << "Taken." << endl;
                        i = current_room->in_here.size();
                    }else{
                        cout << "That can't be taken." << endl;
                        i = current_room->in_here.size();
                    }
                //if it's not equal to what's displayed, see if it works with any of the other names
                }else if (movepart != current_room->in_here[i]->name){
                    for (int j = 0; j < current_room->in_here[i]->names.size(); j++){
                        if (movepart == current_room->in_here[i]->names[j]){
                            //tests if it can be picked up
                            if (current_room->in_here[i]->can_be_taken){
                                inventory.push_back(current_room->in_here[i]);
                                current_room->in_here.erase(current_room->in_here.begin() + i);
                                cout << "Taken." << endl;
                                i = current_room->in_here.size();
                            }else{
                                cout << "That can't be taken." << endl;
                                i = current_room->in_here.size();
                            }
                        }
                    }

                //oh em effing gee, it's just like the end of the look and door function!
                }else if (i == current_room->in_here.size() - 1){
                    cout << "That isn't here." << endl;
                }
            }
        }
        /*inventory function*/else if (movepart == "i"){
            cout << "Inventory:" << endl;
            for (int i = 0; i < inventory.size();i++){
                cout << inventory[i]->name << endl;
            }
        }
        /*drop function*/else if (movepart == "drop"){
            long_move >> movepart;
            //tests to see if player even has anything. if not, call them out
            if (inventory.size() == 0){
                cout << "You don't have anything to drop." << endl;
            }else{
                //otherwise, search their inventory for what they want to drop
                for (int i = 0; i < inventory.size(); i++){
                    //tests for item player is trying to drop
                    if (inventory[i]->name == movepart){
                        current_room->add_item(inventory[i]);
                        inventory.erase(inventory.begin() + i);
                        cout << "Dropped." << endl;
                        //after dropping the item, stop the loop
                        i = inventory.size();
                    }else if (inventory[i]->name != movepart){
                        for (int j = 0; j < inventory[i]->names.size(); j++){
                            if (inventory[i]->names[j] == movepart){
                                current_room->add_item(inventory[i]);
                                inventory.erase(inventory.begin() + i);
                                cout << "Dropped." << endl;
                                //after dropping the item, stop the loop
                                i = inventory.size();
                            }
                        }

                    //if the last item in the inventory isn't what they said to drop, call them out
                    }else if (i == inventory.size() - 1){
                        cout << "You don't have such a thing." << endl;
                    }
                }
            }
        }
        /*help function*/else if (movepart == "help"){
            cout << "PACE Game/Project ACE: Nox public beta 1.3" << endl
                 << "Controls:" << endl
                 << "Type \"look\" to view the room description and the items in it again." << endl
                 << "You can also \"look [n, e, s or w]\" to look in the corresponding direction." << endl
                 << "Type \"look at [item]\" to view the description of whatever item you typed." << endl
                 << "This item can be in the room or in your inventory." << endl
                 << "Type \"i\" to view your inventory." << endl
                 << "You don't HAVE anything in your inventory?" << endl
                 << "Just type \"take [item]\" to pick up whatever you want! (Within reason, of course; you'll never be any good" << endl
                 << "at picking up chicks)" << endl
                 << "If the item you want to pick up, drop, or look at has a name that's longer than you'd like to type, you" << endl
                 << "may be able to shorten it. For example, you can pick up car keys by typing \"take keys.\"" << endl
                 << "Once you have an item, it might have a use. Try use [item] to use it." << endl
                 << "Items can also be used without picking them up." << endl
                 << "Type \"drop [item]\" to drop an item from your inventory onto the ground." << endl
                 << "Type the first letter of a direction to move in that direction. (n, e, s, w) If there's a locked door there," << endl
                 << "you'll need the corresponding key." << endl
                 << "If you have the corresponding key, just walk towards the door again. As long as you have the key," << endl
                 << "you will enter the door." << endl
                 << "Sometimes, you might come across something that seems like it could be entered that isn't a door. In that case," << endl
                 << "type \"enter [item]\" to enter it." << endl
                 << "If you come accross a person, you can \"talk to [them]\"." << endl
                 << "If you get stuck, some rooms have hints. To access a room's hint, type \"hint\"." << endl
                 << "Finally, type \"quit\" to quit the game." << endl;
        }
        /*door function*/else if ((movepart == "n") || (movepart == "e") || (movepart == "s") || (movepart == "w")){
            //variable for testing if door is locked. the game knows the door is locked
            //if after the player tries to enter the door and the current room doesn't change
            string before_moving = current_room->name;
            for (int i = 0; i < current_room->in_here.size(); i++){
                //searches the room for a door named n, e, s, or w
                if (current_room->in_here[i]->name == movepart){
                    //searches the room list for a room of the same name as door.leads_to_room_name
                    for (int j = 0; j < roomlist.size(); j++){
                        //looks for room the door leads to
                        if (roomlist[j]->name == current_room->in_here[i]->leads_to_room_name){
                            //checks if door is locked
                            if (current_room->in_here[i]->is_locked){
                                //checks if player has key
                                for (int n = 0; n < inventory.size(); n++){
                                    if (inventory[n]->name == current_room->in_here[i]->key_needed){
                                        //they have the key? let 'em through
                                        set_room(roomlist[j]);
                                        //makes the thing too big to loop
                                        j = roomlist.size();
                                        n = inventory.size();
                                        movepart = "";
                                    }
                                }
                            }else{
                                //not locked? let 'em through
                                set_room(roomlist[j]);
                                //makes the thing too big to loop
                                j = roomlist.size();
                                movepart = "";
                            }
                        }
                    }
                }
            }
            //now that the movement is done, say the door is locked if the
            //room hasn't changed and there's a door with the correct direction
            if (current_room->name == before_moving){
                for (int i = 0; i < current_room->in_here.size(); i++){
                    //if there's a door in that direction and they player hasn't moved, say the door is locked
                    //then stop the loop
                    if (current_room->in_here[i]->name == movepart){
                        cout << "The door is locked." << endl;
                        i = current_room->in_here.size();

                    //if the loop reaches the second to last item in the list, say there is no exit
                    //this shouldn't cause any issues because the first if has to return false to get to this one,
                    //so hopefully, if the second to last item in a room is a door, it's fine
                    }else if (i == current_room->in_here.size() - 1){
                        cout << "There's no exit in that direction." << endl;
                    }
                }
            }
        }
        /*swearing function*/else if ((movepart == "fuck") || (movepart == "Fuck") || (movepart == "damn") || (movepart == "Damn") ||(movepart == "shit") || (movepart == "Shit") || (movepart == "cunt") || (movepart == "Cunt") ||(movepart == "bitch") || (movepart == "Bitch") || (movepart == "slut") || (movepart == "Slut") || (movepart == "whore") || (movepart == "Whore") || (movepart == "bastard") || (movepart == "bastard") || (movepart == "dick") || (movepart == "Dick") || (movepart == "cock") || (movepart == "Cock") || (movepart == "pussy") || (movepart == "Pussy") || (movepart == "ass") || (movepart == "Ass") || (movepart == "twat") || (movepart == "Twat") || (movepart == "snatch") || (movepart == "Snatch")){
            cout << "Calm down, Gordon Ramsey! No need for that kind of language! If you need help, just type \"help.\"" << endl;
        }
        /*frick and heck function*/else if ((movepart == "frick") || (movepart == "Frick") || (movepart == "frickin") || (movepart == "Frickin") || (movepart == "fricc") || (movepart == "Fricc") || (movepart == "heck") || (movepart == "Heck") || (movepart == "hecc") || (movepart == "Hecc")){
            cout << "Did you just say " << movepart << " on my christian minecraft server?!" << endl;
        }
        /*enter function*/else if (movepart == "enter"){
            long_move >> movepart;
            //makes it so that the player cannot enter doors labeled with a direction. without
            //such a specification, the player can bypass locked doors by entering them
            if ((movepart != "n") && (movepart != "e") && (movepart != "s") && (movepart != "w")){
                //works the same as the door function but w/out locks or anything
                string before_moving = current_room->name;
                for (int i = 0; i < current_room->in_here.size(); i++){
                    if (movepart == current_room->in_here[i]->name){
                        for (int j = 0; j < roomlist.size(); j++){
                            if (roomlist[j]->name == current_room->in_here[i]->leads_to_room_name){
                                set_room(roomlist[j]);
                                j = roomlist.size();
                                movepart = "";
                            }
                        }
                    }
                }
                if (current_room->name == before_moving){
                    cout << "There is no such thing to enter." << endl;
                }
            }else{
                //tell the player they can't enter directional doors
                cout << "You can't enter a direction!" << endl;
            }
        }
        /*use function*/else if (movepart == "use"){
            long_move >> movepart;
            //first uses anything maching the name in the room
            for (int i = 0; i < current_room->in_here.size(); i++){
                if (current_room->in_here[i]->name == movepart){
                    current_room->in_here[i]->use();
                }
            }
            //then tries again with anything in the inventory. don't name any two items the same,
            //or this will fuck things up
            for (int i = 0; i < inventory.size(); i++){
                if (inventory[i]->name == movepart){
                    inventory[i]->use();
                }
            }
        }
        /*talk function*/else if (movepart == "talk"){
            long_move >> movepart;
            //skip over the second word. the player could say "talk fuck billy" and it would still work
            //i don't care if they say talk to, talk at, i'm just making it talk [word] [person]
            long_move >> movepart;
            //now search for the actual npc. the search is copied from look but repurposed to have the npc talk
            for (int i = 0; i < npc_list.size(); i++){
                //makes sure the npc exists and is in the same room
                if ((npc_list[i]->name == movepart) && (npc_list[i]->in_room == current_room) && (npc_list[i]->alive)){
                    cout << npc_list[i]->name << " says: \"" << npc_list[i]->talk_message << "\"" << endl;

                //tell the player they can't talk to existing npcs if not in the room
                }else if ((npc_list[i]->name == movepart) && (npc_list[i]->in_room != current_room)){
                    cout << npc_list[i]->name << " is not in the room to talk to." << endl;

                //tell the player they can't talk to dead people
                }else if ((npc_list[i]->name == movepart) && (npc_list[i]->in_room == current_room) && (!npc_list[i]->alive)){
                    cout << "You can't talk to dead people." << endl;

                //much like the door function, we're gonna hope this can't be triggered if the others are
                }else if (i == npc_list.size() - 1){
                    cout << movepart << " does not exist." << endl;
                }
            }

        }
        /*kill function*/else if (movepart == "kill"){
            long_move >> movepart;
            string to_kill = movepart;
            //skip the "with" part
            long_move >> movepart;
            if (movepart == "with"){
                //item to kill them with
                long_move >> movepart;
                string item_name = movepart;

                //test for an npc with a matching name
                for (int i = 0; i < npc_list.size(); i++){
                    //kill npc with matching name
                    if (npc_list[i]->name == to_kill){
                        //first make sure they're in the same room
                        if (npc_list[i]->in_room == current_room){
                            //make sure they're trying to kill them with a weapon
                            for (int j = 0; j < inventory.size(); j++){
                                if (inventory[j]->name == item_name){
                                    if (inventory[j]->can_kill){
                                        //kill the npc
                                        npc_list[i]->alive = 0;
                                        //show the death message
                                        cout << npc_list[i]->death_message << endl;
                                        //create new description
                                        string newdescription = "The corpse of ";
                                        newdescription+= npc_list[i]->name;
                                        npc_list[i]->description = newdescription;
                                        //end for loop
                                        i = npc_list.size();
                                        j = inventory.size();
                                    }else{
                                        cout << "You can't kill " << to_kill << " with a " << item_name << "." << endl;
                                    }
                                }else if ((j == inventory.size() - 1) && (!npc_list[i]->is_alive())){
                                    cout << "You don't have a " << item_name << "." << endl;
                                    i = npc_list.size();
                                    j = inventory.size();
                                }
                            }
                        }else if (npc_list[i]->in_room != current_room){
                            cout << npc_list[i]->name << " isn't here to kill." << endl;
                            i = npc_list.size();
                        }else if (i == npc_list.size() - 1){
                            cout << to_kill << " does not exist." << endl;
                        }
                    }
                }
            }else{
                cout << "With what?" << endl;
            }
        }
        /*teleport function*/else if (movepart == "roomctl"){
            long_move >> movepart;
            string roomname;
            cout << "Teleport to which room? : ";
            getline(cin, roomname);
            for (int i = 0; i < roomlist.size(); i++){
                if (roomlist[i]->name == roomname){
                    set_room(roomlist[i]);
                }
            }
        }
        /*roomlist function*/else if (movepart == "roomlist"){
            for (int i = 0; i < roomlist.size(); i++){
                cout << roomlist[i]->name << endl;
            }
        }
        /*soundtest function*/else if (movepart == "soundtest"){
            //this function serves no purpose other than to not cause
            //a glitch when the player uses the soundtest function
        }
        /*hint function*/else if (movepart == "hint"){
            cout << current_room->hint << endl;
        }

        //display message if input doesn't match any commands
        else{
            cout << "Unrecognized command. Type \"help\" for a list of commands." << endl;
        }
    }

    //a way for the rest of the code to see the current room
    room* in_room(){
        return current_room;
    }

    //a way for the rest of the code to see the current room's item list
    vector<item*> current_room_items(){
        return current_room->in_here;
    }
};
