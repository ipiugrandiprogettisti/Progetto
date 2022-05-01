#include "header/Map.hpp"
#include "header/utils.hpp"

/*
Map::Map()
{
}*/

// Constructor
Map::Map(WINDOW *win)
{
    mainWin = win;
    totalRooms = 1; // game starts with only 1 room. next rooms are one at a time
    this->freeKey = 0;

    rooms = new listRooms;
    rooms->currentRoom = Room(newKey());

    // sets all next rooms to NULL; a pointer will be assigned to its room when one is created
    for (int i = 0; i < MAXDOORS; i++)
        rooms->door[i] = NULL;
}

// returns and create a new unique key
int Map::newKey()
{
    freeKey += 1;
    return freeKey - 1;
}

// returns the main window
WINDOW *Map::getMainWindow()
{
    return mainWin;
}

// returns the room window
WINDOW *Map::getRoomWindow(int key)
{
    // TODO
    // search in rooms for current room; then returns the room's window
    return rooms->currentRoom.getWindow();
}

// head insert
pListRooms insertHead(pListRooms rooms, struct door previousDoorInfo, Room roomInfo)
{
    pListRooms list = new listRooms;
    switch (previousDoorInfo.side)
    {
    case 0:
        list->currentRoom = roomInfo;
        list->currentRoom.setDoor(2, previousDoorInfo); // if player enters room from bottom side; previous room is located top side
        list->door[2] = rooms;                          // if player enters room from bottom side; previous room is located top side
        break;
    case 1:
        // copia list->currentRoom=room ecc
        // list->door1 = rooms;
        break;
    case 2:
        // copia list->currentRoom=room ecc
        // list->door2 = rooms;
        break;
    case 3:
        // copia list->currentRoom=room ecc
        // list->door3 = rooms;
        break;

    default:
        return NULL;
        break;
    }

    return list;
}

// search and return specific room. returns NULL if not found
pListRooms getRooms(pListRooms rooms, int key)
{
    if (rooms == NULL)
        return rooms;
    else if (rooms->door[0]->currentRoom.getKey() == key)
    {
        return rooms->door[0];
    }
    else
    {
        pListRooms tmp = rooms;
        pListRooms tmpAfter = rooms->door[0];
        bool found = false;
        while (!found && tmpAfter != NULL)
        {
            if (tmpAfter->currentRoom.getKey() == key)
            {
                tmp->door[0] = tmpAfter->door[0];
                found = true;
            }
            else
            {
                tmp = tmpAfter;
                tmpAfter = tmpAfter->door[0];
            }
        }
    }
    return rooms;
}

// tail insert
pListRooms insertTail(pListRooms rooms, int doorNumber, int newRoomKey)
{
    pListRooms list;
    if (rooms == NULL)
    {
        rooms = new listRooms;
        rooms->currentRoom = Room(newRoomKey);
        for (int i = 0; i < MAXDOORS; i++)
            rooms->door[i] = NULL;
    }
    else
    {
        for (list = rooms; list->door[0] != NULL; list = list->door[0])
        {
        }
        list = new listRooms;
        list->currentRoom = Room(newRoomKey);
        for (int i = 0; i < MAXDOORS; i++)
            rooms->door[i] = NULL;
    }
    return rooms;
}

// creates new room
void Map::createRoom(struct door doorInfo)
{
    int key = newKey();
    switch (doorInfo.side)
    {
    case 0: // bottom side
        /*
        rooms->door0->currentRoom = Room(key);
        rooms->door0->door2Info = doorInfo; // if player enters room from bottom side; previous room is located top side
        rooms->door0->door2 = rooms;
        */
        rooms = insertHead(rooms, doorInfo, Room(key));
        break;
    case 1: // left side
        break;
    case 2: // top side
        break;
    case 3: // right side
        break;
    default:
        break;
    }
}

// enter new room: make it currentRoom
// FIXME non è piu cosi
void Map::enterRoom(int side)
{
    // rooms = getRooms(rooms, key);
    rooms = rooms->door[side];
}

// Create the rooms for the n doors that are on the screen
void Map::createRooms()
{
    MyString debug = "Ho creato la stanza: ";
    for (int i = 0; i < MAXDOORS; i++)
    {
        rooms->door[i] = new listRooms;
        door myDoors = rooms->currentRoom.getDoor(i);
        if (myDoors.x >= 0 && myDoors.y >= 0) // if door exists creates room
        {

            rooms->door[i]->currentRoom = Room(newKey());
            debug += "door[";
            debug += itoa(i);
            debug += "]";
            debug += " -> ";
            debug += itoa(rooms->door[i]->currentRoom.getKey());
            debug += ", ";
            for (int i = 0; i < MAXDOORS; i++) // sets to NULL the doors of the new room
                rooms->door[i] = NULL;
        }
        mvaddstr(3, 0, debug.get());
    }
}

int Map::getKeyByDoor(int side)
{
    return 1;
}