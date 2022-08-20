#include "Character.hpp"
#include "Artifact.hpp"
#include "Power.hpp"

// ASCII symbol ACS_PI

// lista degli artefatti che ha preso il protagonista
typedef struct inventoryA
{
    Artifact A;
    inventoryA *next;
} inventoryA;

typedef struct inventoryP
{
    Power P;
    inventoryP *next;
} inventoryP;

// pointer to protagonist's artifacts list
typedef inventoryA *p_inventA;

// pointer to protagonist's powers list
typedef inventoryP *p_inventP;

// lista dei proiettili sparati
typedef struct bulletlist
{
    bullet B;
    bulletlist *next;

} bulletlist;

// pointer to protagonist's bullets list
typedef bulletlist *p_bulletlist;

// classe protagonista
class Protagonist : public Character
{
public:
    p_inventA headA;
    p_inventP headP;
    p_bulletlist headB;

    // constructor
    Protagonist();

    // constructor
    Protagonist(p_inventA headA, p_inventP headP, p_bulletlist headB, int current_life, int max_life, int atk_damage, int y, int x, chtype tag);

    // print protagonist
    void printProtagonist(Protagonist P, WINDOW *w);

    // head insert a new bullet
    p_bulletlist bulletHeadInsert(p_bulletlist head, bullet b);

    // tail insert a new bullet
    p_bulletlist bulletTailInsert(p_bulletlist head, bullet b);

    // removes whatever bullet is given as parameter
    p_bulletlist bulletRemove(p_bulletlist head, bullet b);

    //increases life basing on the gained artifact
    void gainLife(Protagonist a, Artifact p);
};