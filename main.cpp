/***************************/
/* Project ACE: Nox(b.1.3) */
/***************************/
/*
Contributors:
XP710

TODO: Add more to the new planet. Add saving and loading.
*/
#include <iostream>
#include "classes.h"
#include <string>
using namespace std;

int main()
{
    //Starting info for the game
    cout << "Welcome to Project ACE: Nox v b.1.3!" << endl
         << endl
         << "Although janitors' closets are usually small, this one is of a nice size. It's not as claustrophobic as you" << endl
         << "imagined when you first applied for the job. The job of janitor is always looked down upon, but you take" << endl
         << "pride in it for the same reason your janitor's closet is so big. The facility you clean is Umbrus Laboratories," << endl
         << "one of the leaders in current research and development in space exploration vehicles. While most of the science-y" << endl
         << "stuff flies right over your head, as your boss said, this facility couldn't run if it wasn't clean. Speaking of" << endl
         << "a clean facility, you've got an assignment! Look at the paper here to start your assignment." << endl << endl;

    /*
     * Janitor's Closet
     */
    room jc("Janitor's Closet", "A reasonably sized janitor's closet with an east door leading into the hall.");
    jc.hint = "Follow the directions on the paper.";
    door jc2seoh("e", "To the east is a door.", "South End of Hall");
    generic_item assignment_paper("paper", "!!!You might want to take this paper with you for guidence!!!\n\n"
                                           "Here is the list of rooms you need to clean:\n"
                                           "The south, middle, and north of the main hallway,\n"
                                           "The test chamber,\n"
                                           "and the Employee Lounge.\n\n"
                                           "Key:\n"
                                           "+: door\n"
                                           "jc: Janitor's closet\n"
                                           "tc: Test Chamber\n"
                                           "el: Employees' Lounge\n"
                                           "Rooms that have an X in them are\n"
                                           "off-limits to you and are locked.\n\n"
                                           "Map:\n"
                                           "    .---.---.\n"
                                           "    | X |   |\n"
                                           ".---|-+-| X |\n"
                                           "|el +   +   |\n"
                                           "|---|   |---|\n"
                                           "|tc +   + X |\n"
                                           "|---|   |---'\n"
                                           "|jc +   |\n"
                                           "'---'-+-'\n"
                                           "To clean a room, use the mop.", 1);
    assignment_paper.names.push_back("map");
    generic_item mop("mop", "This mop was given to you on the first day of the job. Type \"use mop\" to clean a room.", 1, "The room is now clean.");
    door jc2hr("wormhole", "How can you look at something you can't see?", "Hidden Room");
    jc2hr.hidden = 1;
    jc.add_item(&jc2hr);
    jc.add_item(&mop);
    jc.add_item(&assignment_paper);
    jc.add_item(&jc2seoh);
    roomlist.push_back(&jc);

    /*
     * South End of Hall
     */
    room seoh("South End of Hall", "This is the south end of a hall which continues to the north.\nTo the west is a janitor's closet.");
    seoh.hint = "Look very closely at the map.";
    door seoh2jc("w", "There is a door to a janitor's closet to the west.", "Janitor's Closet");
    door seoh2moh("n", "The hall continues north.", "Middle of Hall");
    door seoh2elv_l("s", "This door leads to the elevator lobby", "Elevator Lobby");
    seoh.add_item(&seoh2elv_l);
    seoh.add_item(&seoh2moh);
    seoh.add_item(&seoh2jc);
    roomlist.push_back(&seoh);

    /*
     * Middle of Hall
     */
    room moh("Middle of Hall", "You are in the middle of a hall that continues north and south.\nThere are doors to the east and west");
    door moh2seoh("s", "The hall continues south.", "South End of Hall");
    door moh2neoh("n", "The hall continues north.", "North End of Hall");
    door moh2tc("w", "There is a door to the west which leads to a test chamber.", "Test Chamber");
    door moh2tr("e", "There is a door to the east.", 1, "car keys", "Trap Room");
    moh.add_item(&moh2seoh);
    moh.add_item(&moh2neoh);
    moh.add_item(&moh2tc);
    moh.add_item(&moh2tr);
    roomlist.push_back(&moh);

    /*
     * North End of Hall
     */
    room neoh("North End of Hall", "You are in the north end of a hall that continues south.\nThere are doors to the north, east, and west");
    door neoh2moh("s", "The hall continues south", "Middle of Hall");
    door neoh2el("w", "The door is labeled \"Employee Lounge\"", "Employee Lounge");
    door neoh2pace("n", "The door is labeled \"Project A.C.E.\"", 1, "NULL", "Project A.C.E. Room");
    door neoh2orn("e", "The door is labeled \"Project A.C.E. Observation Room\"", 1, "key", "Observation Room South");
    neoh.add_item(&neoh2orn);
    neoh.add_item(&neoh2moh);
    neoh.add_item(&neoh2el);
    neoh.add_item(&neoh2pace);
    roomlist.push_back(&neoh);

    /*
     * Test Chamber
     */
    room tc("Test Chamber", "This is an interesting room which has an obervation deck behind incredibly strong windows. From the "
                            "observation deck, you can see something resembling a spaceship in a pretty empty room with strong-looking"
                            " walls.\nTo the east is an exit to the hall.");
    tc.hint = "There is currently nothing in this room. Stop wasting your time.";
    door tc2moh("e", "There is an exit to the hall to the east.", "Middle of Hall");
    tc.add_item(&tc2moh);
    roomlist.push_back(&tc);

    /*
     * Employee Lounge
     */
    room el("Employee Lounge", "This is a nice room, even if it is a little small. It has a sink and refrigerator in it,"
                               " as well as a water cooler. There's a decently sized table, with four foldable chairs set around it,"
                               " and a high window next to it, \nletting some sunlight in the room, lifting the mood.");
    door el2neoh("e", "To the east is the north end of a hall.", "North End of Hall");
    key car_keys("car keys", "These appear to be somebody's car keys. You probably shouldn't take them.");
    car_keys.names.push_back("car");
    car_keys.names.push_back("keys");
    el.add_item(&el2neoh);
    el.add_item(&car_keys);
    roomlist.push_back(&el);

    /*
     * Trap Room
     */
    room tr("Trap Room", "This seems to be some sort of security room. It's pretty dark.\nSuddenly, the door closes behind you! There's no way out!");
    tr.hint = "There is no way out of this room. You must restart the game.";
    generic_item note_in_tr("note", "The note says: \"Make sure to keep an eye on the janitor's closet. It looks like an invisible wormhole opened up in it.\"", 1);
    tr.add_item(&note_in_tr);
    roomlist.push_back(&tr);

    /*
     * Project A.C.E. Room
     */
        /* The wormhole in this room was discovered by Umbrus Laboratories only a few days ago
         * This room is called Project A.C.E. Room because after a few tests involving drones and
         * rovers, the scientists found out that the wormhole led to a habitable planet. The end goal
         * was to colonise this planet, so the project was called Advanced Celestial Exploration, or A.C.E.
         * The scientists wanted to send people through, but didn't know how to do so in an
         * ethical way, so the project is currently at a standstill
         * The fact that the wormhole moves every time the player goes through it isn't a freak coincidence, the wormhole
         * moves every time something goes through it. The scientists were aware of this, so that's why the
         * wormhole is inside a machine in the Project A.C.E. Room. The machine also feeds the wormhole negative
         * mass to keep it stable.
         */
    room pace("Project A.C.E. Room", "The room is lined with all sorts of equipment you don't recognize. There's a central machine"
                                     " in the room holding a wormhole.");
    door pace2neoh("s", "To the south is the north end of a hall.", "North End of Hall");
    door pace2dp("wormhole", "The wormhole looks strange. It's like a 3d hole. No matter which direction you look at it from, you can see through it like it's a hole.", "Different Planet");
    pace.add_item(&pace2dp);
    pace.add_item(&pace2neoh);
    roomlist.push_back(&pace);

    /*
     * Hidden Room
     */
    room hr("Hidden Room", "The wormhole brings you to a room you haven't seen before. There aren't any exits.");
    key orskey("key", "A brass key.");
    door hr2ors("wormhole", "You can't where the wormhole leads.", "Observation Room South");
    hr.add_item(&hr2ors);
    hr.add_item(&orskey);
    roomlist.push_back(&hr);

    /*
     * Observation Room South
     */
    room ors("Observation Room South", "This seems to be some sort of observation room. "
                                    "There's not much here besides a door to the west. There's more in the north end of the room.");
    ors.hint = "You need the car keys to go west.";
    door ors2neoh("w", "This door leads back to the north end of the hall.", 1, "car keys", "North End of Hall");
    door ors2orn("n", "The room continues north.", "Observation Room North");
    ors.add_item(&ors2orn);
    ors.add_item(&ors2neoh);
    roomlist.push_back(&ors);

    /*
     * Observation Room North
     */
    room orn("Observation Room North", "This side of the room has a computer in it and a window that shows you the "
                                       "Project A.C.E. Room. The Project A.C.E. Room is a strange looking room. You'll need to find"
                                       " a way to open the door to it to get a better look.");
    door orn2ors("s", "The room continues south.", "Observation Room South");
    computer paceunlocker("computer", "Amazingly, someone left it on. You kind of want to use it.", &neoh2pace);
    orn.add_item(&paceunlocker);
    orn.add_item(&orn2ors);
    roomlist.push_back(&orn);

    /*
     * Developer's Room
     */
    room dr("Developer's Room", "Welcome to the dev room! There are no exits.");
    generic_item dev_paper("cheat code book", "!!!Using commands listed in this book is considered cheating. However, using cheat codes NOT listed in this book is considered a legitamate way of beating the game.\n"
                                              "These are the current hidden commands:\nroomctl\nroomlist\nsoundtest:4126", 1);
    dev_paper.names.push_back("book");
    dev_paper.names.push_back("cheat");
    dev_paper.names.push_back("code");
    dr.add_item(&dev_paper);
    roomlist.push_back(&dr);

    /*
     * Elevator Lobby
     */
    room elv_l("Elevator Lobby", "This room is where the elevators leading downstairs are.\nThere is an exit to the north.");
    door elv_l2seoh("n", "This door leads back to the hallway.", "South End of Hall");
    door elv_l2dwn_elv_l("elevator", "This elevator leads downstairs.", "Downstairs Elevator Lobby");
    elv_l.add_item(&elv_l2seoh);
    elv_l.add_item(&elv_l2dwn_elv_l);
    roomlist.push_back(&elv_l);

    /*
     * Downstairs Elevator Lobby
     */
    room dwn_elv_l("Downstairs Elevator Lobby", "This is the downstairs elevator lobby.\nThere is an exit to the north.");
    door dwn_elv_l2elv_l("elevator", "This elevator leads upstairs.", "Elevator Lobby");
    door dwn_elv_l2ra("n", "The south end of a hallway is north of this room.", "Reception Area");
    dwn_elv_l.add_item(&dwn_elv_l2ra);
    dwn_elv_l.add_item(&dwn_elv_l2elv_l);
    roomlist.push_back(&dwn_elv_l);

    /*
     * Reception Area
     */
    room ra("Reception Area", "This is the reception area for clients looking to buy things from Umbrus Labs. There is a reception desk and a few\n"
                              "chairs here as well as some potted plants and a small table.\nThere are doors to the west, south, and east.");
    ra.hint = "Read the magazine.";
    door ra2dwn_el_l("s", "To the south is the north end of a hall.", "Downstairs Elevator Lobby");
    door ra2c("e", "There is a cafeteria to the east.", "Cafeteria");
    door ra2br("w", "There is a bathroom to the west.", "Bathroom");
    generic_item magazine("magazine", "Here's an article that peaks your interest:\n\n"
                                                 "Cheat Codes in Retro Games by Austin Patrick\n"
                                                 "Many people remember the Game Genie or Game Shark when they\n"
                                                 "think of cheat codes. However, many games, such as Sonic t-\n"
                                                 "he Hedgehog came with cheat codes built in. For example, w-\n"
                                                 "ith Sonic the Hedgehog, entering the correct input of butt-\n"
                                                 "ons would give you access to the soundtest screen, a place \n"
                                                 "for developers to make sure all the sounds worked in game. \n"
                                                 "In the Sonic the Hedgehog games, cheat codes would often be\n"
                                                 "put in through this soundtest screen.", 1);
    ra.add_item(&ra2dwn_el_l);
    ra.add_item(&ra2c);
    ra.add_item(&ra2br);
    ra.add_item(&magazine);
    roomlist.push_back(&ra);
    npc receptionist("Receptionist", "You haven't met the receptionist yet, but they seem nice enough.", "Hey, you're the new janitor, right?", "You killed the receptionist. What's wrong with you?", &ra);
    npc_list.push_back(&receptionist);

    /*
     * Cafeteria
     */
    room c("Cafeteria", "This is the cafeteria. It's a fairly large room with lots of tables lined up with chairs around them.\n"
                        "There is an exit to the west.");
    door c2ra("w", "The south end of a hall is to the west.", "Reception Area");
    generic_item c_food("hamburger", "Just a regular hamburger.", 1);
    c.add_item(&c2ra);
    c.add_item(&c_food);
    roomlist.push_back(&c);

    /*
     * Bathroom
     */
    room br("Bathroom", "This is the faculty bathroom. You are not looking forward to the day you have to clean this. There's writing on the mirror.\n"
                        "There is an exit to the east.");
    br.hint = "Remember the article. How where cheats entered in Sonic the Hedgehog? The easiest solution is usually the best one.";
    generic_item br_mirror("mirror", "There's handwriting on the mirror. It says \"19650917\"", 0);
    br_mirror.hidden = 1;
    door br2ra("e", "There is the south end of a hall to the east.", "Reception Area");
    br.add_item(&br_mirror);
    br.add_item(&br2ra);
    roomlist.push_back(&br);

    /*
     * Different Planet
     */
    room dp("Different Planet", "You emerge from the wormhole on a new planet. It looks very similar to earth, actually. The wormhole flies to your west to the top of a hill.");
    dp.hint = "You need a chainsaw. If you don't have one, restart the game and look incredibly closely at the map.";
    door dp2sh("w", "To your west is a strange house.", "Strange House");
    generic_item tree("tree", "This tree is keeping you from going west.", 0);
    dp.add_item(&tree);
    roomlist.push_back(&dp);

    /*
     * Top of Hill
     */
    room toh("Top of Hill", "You are at the top of a hill.");
    door toh2sh("s", "There is a strange looking house to the south.", 1, "alien key", "Strange House");
    door toh2end("wormhole", "This is just like the wormhole from earlier. This time you can see the Project A.C.E. room through it.", "The End");
    toh.add_item(&toh2end);
    toh.add_item(&toh2sh);
    roomlist.push_back(&toh);

    /*
     * Strange House
     */
    room sh("Strange House", "You are inside a pretty strange house. It seems to have been grown from a tree. There's what could be called a window "
                             "\nto the north, showing the top of a hill with the wormhole on top of it.\nThere are exits to the north, east, south, and west.");
    sh.hint = "You need the alien key to go north.";
    door sh2dp("e", "There's not much out of the east exit.", "Different Planet");
    door sh2toh("n", "Out of the north exit is a hill with the wormhole on it.", 1, "alien key", "Top of Hill");
    door sh2urn("w", "You can't tell what the room to the west is.", "Unknown Room North");
    door sh2ir("s", "This door reminds you of doors you see in spaceships in movies.", 1, "NULL", "Incubation Room");
    sh.add_item(&sh2ir);
    sh.add_item(&sh2urn);
    sh.add_item(&sh2toh);
    sh.add_item(&sh2dp);
    roomlist.push_back(&sh);

    /*
     * Incubation Room
     */
       /*
        * This room is where natives to Nox (the name humans will give this planet in a few years, named such because it is the
        * sister of Terra and the mother of Somnus) keep their children. Noxians have added intense genetic modification to themselves,
        * including beaks, mechanical digestive tracts, and brain implants that cause them to be linked mentally with every other
        * Noxian. Noxians naturally lay eggs, but due to genetic modification, shred the eggs in the ovaries so that they give
        * birth to live, undeveloped young. The fetuses are then placed in incubation tanks which allow them to develop as well as put
        * the correct modifications on them. Due to the link with all Noxian knowledge, newborn Noxians already have the mental
        * capacity of adults and immediatly go to work.
        */
    room ir("Incubation Room", "In the middle of this dark room is what looks like a broken tank. Dead lights and buttons are on the bottom\n"
                               "of the tank, covered in the yellow liquid spilling from the broken glass. Lots of thin, robotic arms fill\n"
                               "the tank, tipped with all sorts of different tools. Some have spikes, others have pinchers of sorts. To the\n"
                               "side of the take is a small metal box. From inside the tank, a thin tube connects the metal box to something\n"
                               "you never wanted to see. A small fetus lies in the bottom of the tank, it's stomach open, drying out.\n"
                               "The dead, metallic arms hover over the fetus, which you realize has pieces of metal attached to it."
                               "\nThere are exits to the north and west.");
    ir.hint = "Take the baby juice!";
    door ir2sh("n", "This door leads into the main part of the house.", "Strange House");
    door ir2urs("w", "This door leads to the west.", 1, "NULL", "Unknown Room South");

    //even though it doesn't appear in this room, the rover is given a custom class here so that the babyjuice class can actually use it
    class rover : public item{
    public:
        bool clean;
        rover(string name_to_be){
            name = name_to_be;
            description = "This rover seems to have writing on it, but needs to be cleaned to read it.";
            can_be_taken = 0;
            clean = 0;
        }
        void become_clean(){
            cout << "The rover is now clean." << endl;
            description = "The rover is labeled \"Advanced CElestial Rover 4\"";
        }
    };

    //tastefully named class for amniotic fluid so that it can have a custom use
    class babyjuice : public item{
    public:
        babyjuice(string name_to_be, string desc_to_be){
            name = name_to_be;
            description = desc_to_be;
            can_be_taken = 1;
        }
        void use(){
            //this only exits to stop if from saying "you can't find a use for this"
        }
    };
    babyjuice af("amniotic fluid", "A little bit of the stuff from the tank fell into a small jar. You think you can use this to clean.");
    af.names.push_back("amniotic");
    af.names.push_back("fluid");
    af.names.push_back("jar");
    ir.add_item(&ir2urs);
    ir.add_item(&ir2sh);
    ir.add_item(&af);
    roomlist.push_back(&ir);

    /*
     * Unknown Room North
     */
    room urn("Unknown Room North", "It's impossible to know what this room is for based on the architecture. You've never even imagined a room like this. There is"
                            "\na sign on the wall which says, \"Drop key on floor to leave.\""
                            "\nThere is an exit to the east.");
    door urn2sh("e", "This door seems to lock itself whenever you pick up its' key.", "Strange House");
    door urn2urs("s", "The room continues to the south", "Unknown Room South");
    key ak("alien key", "You can tell this is a key because of the way it's shaped, but it, like the house, seems to have been grown.");
    ak.names.push_back("alien");
    ak.names.push_back("key");
    computer lever("lever", "This lever seems to be in working condition", &sh2ir);
    urn.add_item(&lever);
    urn.add_item(&urn2urs);
    urn.add_item(&urn2sh);
    urn.add_item(&ak);
    roomlist.push_back(&urn);

    /*
     * Unknown Room South
     */
    room urs("Unknown Room South", "This is the south of the strange room.\nThere are exits to the north and east.");
    urs.hint = "You might be able to clean the rover with some sort of fluid.";
    door urs2ir("e", "This door leads to the east.", 1, "NULL", "Incubation Room");
    door urs2urn("n", "The room continues to the north", "Unknown Room North");
    rover rover("rover");
    urs.add_item(&rover);
    urs.add_item(&urs2urn);
    urs.add_item(&urs2ir);
    roomlist.push_back(&urs);

    /*
     * End Room
     */
    room end("The End", "");
    roomlist.push_back(&end);

    //create Steve Gates
    player sg;
    sg.set_room(&jc);

    //class for the chainsaw so that it can have a custom use
    class chainsaw : public item{
    private:
        void use(){
            cout << "You start the chainsaw." << endl;
        }
    public:
        chainsaw(string name_to_be, string desc_to_be){
            name = name_to_be;
            description = desc_to_be;
            can_be_taken = 1;
        }

    };

    //this is declared for later use in the bathroom
    chainsaw chainsaw("chainsaw", "This chainsaw can only cut trees. It says so on the back.");

    //make a bool for testing if the chainsaw has already been given
    bool given = 0;

    //gameloop
    while(sg.play){
        cout << ">";
        string move;
        getline(cin, move);
        sg.move(move);

        //this is basically the rest of the chainsaw use function, but it can't be declared in chainsaw for some reason
        if ((move == "use chainsaw") && (sg.showcurr_room()->in_here[0] == &tree)){
            //test if the player has a chainsaw
            for (int i = 0; i < sg.showinv().size(); i++){
                if (sg.showinv()[i] == &chainsaw){
                    cout << "You cut down the tree." << endl;
                    sg.showcurr_room()->in_here.pop_back();
                    dp.add_item(&dp2sh);
                }
            }
        }else if ((move == "use chainsaw") && (sg.showcurr_room()->in_here[0] != &tree)){
            //test if the player has a chainsaw
            for (int i = 0; i < sg.showinv().size(); i++){
                if (sg.showinv()[i] == &chainsaw){
                    cout << "There aren't any trees to cut down. You turn it off." << endl;
                }
            }
        }

        //little thing explaining why you can go west in chaintest
        if ((sg.showcurr_room() == &dp) && (move == "w") && (dp.in_here[0] == &tree)){
            cout << "The tree is in your way." << endl;
        }

        //though this is essentially a redefinition of quit,
        //it's here so that the ending text can't show up if the player is the one to quit
        if (move == "quit"){
            return 0;
        }

        //use functionality for babyjuice
        if ((move == "use amniotic fluid") || (move == "use fluid") || (move == "use amniotic")){
            //make sure player actually has amniotic fluid
            bool can_use = 0;
            for (int i = 0; i < sg.showinv().size(); i++){
                if (sg.showinv()[i]->disp_name() == "amniotic fluid"){
                    can_use = 1;
                    i = sg.showinv().size();
                }
            }
            if (can_use){
                if (sg.showcurr_room() == &urs){
                    rover.become_clean();
                }
            }
        }

        //cheat code command
        if (move == "soundtest"){
            cout << "Enter cheat code: ";
            string code;
            getline(cin, code);
            if (code == "devroom"){
                sg.set_room(&dr);
            }else if (code == "debug"){
                cout << "Nice job on finding a cheat code!\n"
                        "From now on, this is the only hint you get towards other cheat codes: There is a special room you can only reach with cheats." << endl;
            }else if (code == "19650917"){
                if (!given){
                    //give the chainsaw and make it so it can't be given again
                    br.add_item(&chainsaw);
                    cout << "A chainsaw has appeared in the bathroom." << endl;
                    given = 1;
                }else{
                    cout << "The chainsaw has already been given." << endl;
                }

            }else if ((code == "69") || (code == "420") || (code == "80085") || (code == "42069") || (code == "69420") || (code == "7175")){
                cout << "You have forfeited your right to play this game." << endl;
                return 0;
            }else if (code == "4126"){
                //unlock all doors cheat code
                cout << "All doors have been unlocked." << endl;
                for (int i = 0; i < roomlist.size(); i++){
                    for (int j = 0; j < roomlist[i]->in_here.size(); j++){
                        roomlist[i]->in_here[j]->unlock();
                    }
                }
            }else if (code == "19921124"){
                cout << "Nice. I don't have an actual effect for this yet. Try this code with each release, I'll do something with it." << endl;
            }else if ((code == "ACER 4") || (code == "acer 4")){
                urs2ir.unlock();
                ir2urs.unlock();
                if (sg.showcurr_room() == &urs){
                    cout << "The east exit opens." << endl;
                }else if (sg.showcurr_room() == &ir){
                    cout << "The west exit opens." << endl;
                }else{
                    cout << "The door from the south of the Unknown Room to the Incubations Room is now unlocked." << endl;
                }
            }
        }

        //lock the ur2sh door if alien key is not in Unknown Room
        for (int i = 0; i < urn.in_here.size(); i++){
            if (urn.in_here[i]->disp_name() == "alien key"){
                urn2sh.unlock();
                i = urn.in_here.size();
            }else if ((i == urn.in_here.size() - 1) && (urn.in_here[i]->disp_name() != "alien key")){
                urn2sh.lock();
            }
        }

        //end game if player reaches The End
        if (sg.in_room() == &end){
            sg.play = 0;
        }
    }
    //after the game is over, test that the car keys are in the employee lounge
    //if they are in the employee lounge, give it a good ending
    //otherwise, it's the bad ending
    for (int i = 0; i < el.in_here.size(); i++){
        if (el.in_here[i]->disp_name() == "car keys"){
            cout << "\nAfter returning from the wormhole, you are greeted by scientists" << endl
                 << "congragulating you on your discovery!" << endl;
            return 0;
        }else if (i == el.in_here.size() - 1){
            cout << "\nAfter returning from the wormhole, you are greeted by scientist, your boss, and" << endl
                 << "the security guard, Travis Bailey. Travis explains that he was looking for" << endl
                 << "his car keys in the employee lounge. He reviewed security footage and saw you move them." << endl
                 << "Your boss then explains that you're fired." << endl;
            return 0;
        }
    }
}
