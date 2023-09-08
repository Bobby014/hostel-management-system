#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct HSTL
{
    int NUMBER;
    int fill;
    char CUS_NAMES[3][10];
    struct HSTL *NXT;
    struct HSTL *PREVIOUS;
};

struct hostel
{
    struct HSTL *TITLE[3];
    struct HSTL *WORDS;
};

void create(struct hostel *obj)
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            struct HSTL *ss = (struct HSTL *)malloc(sizeof(struct HSTL));
            ss->NXT = NULL;
            ss->PREVIOUS = NULL;
            ss->NUMBER = 1;
            ss->fill = 0;

            if (obj->TITLE[x] == NULL)
            {
                obj->TITLE[x] = ss;
            }
            else
            {
                struct HSTL *WORDS = obj->TITLE[x];
                while (WORDS->NXT != NULL)
                {
                    WORDS = WORDS->NXT;
                }

                if (y == 3 || y == 5 || y == 7 || y == 8)
                {
                    WORDS->NUMBER = 3;
                }
                if (y == 2 || y == 4 || y == 6)
                {
                    WORDS->NUMBER = 2;
                }

                WORDS->NXT = ss;
                ss->PREVIOUS = WORDS;
            }
        }
    }
}

void display(struct hostel *obj)
{
    int y = 0, z = 0, w = 0;
    for (int x = 0; x < 48; x++)
    {
        printf("--");
    }
    printf("\n ");
    for (int x = 1; x < 4; x++)
    {
        printf("| Floor number : %d \t\t", x);
    }
    printf("|\n");
    for (int x = 0; x < 48; x++)
    {
        printf("--");
    }
    obj->WORDS = obj->TITLE[y];
    struct HSTL *s = obj->TITLE[y + 1];
    struct HSTL *t = obj->TITLE[y + 2];
    printf("\n ");
    while (obj->WORDS != NULL)
    {
        if (obj->WORDS->fill != obj->WORDS->NUMBER && obj->WORDS->NUMBER != 0)
        {
            y++;
            printf("| room no : %d", y);
            printf("->Vacant cots->%d", obj->WORDS->NUMBER);
        }
        else
        {
            y++;
            printf("| room no : %d", y);
            printf("->Present ");
        }
        if (s->fill != s->NUMBER && s->NUMBER != 0)
        {
            z++;
            printf("\t | room no : %d", y);
            printf("->Vacant cots->%d", s->NUMBER);
        }
        else
        {
            z++;
            printf(" \t | room no : %d", y);
            printf("->Present ");
        }
        if (t->fill != t->NUMBER && t->NUMBER != 0)
        {
            w++;
            printf("\t | room no : %d", y);
            printf("->Vacant cots->%d | ", t->NUMBER);
        }
        else
        {
            w++;
            printf("\t | room no : %d", y);
            printf("->Present | ");
        }
        printf(" \n ");
        for (int x = 0; x < 48; x++)
        {
            printf("--");
        }
        printf("\n ");
        obj->WORDS = obj->WORDS->NXT;
        s = s->NXT;
        t = t->NXT;
    }
}

void booking(struct hostel *obj, int people)
{
    int fl, rom;
    printf("\nEnter the floor number : ");
    scanf("%d", &fl);

    if (fl < 0 || fl > 4)
    {
        printf("\ninvalid floor number : %d", fl);
        return;
    }

    obj->WORDS = obj->TITLE[fl - 1];

    printf("\nEnter the room number : ");
    scanf("%d", &rom);

    if (rom < 0 || rom > 10)
    {
        printf("\ninvalid room number : %d", rom);
        return;
    }
    else
    {
        int x = 1;
        while (x < rom)
        {
            obj->WORDS = obj->WORDS->NXT;
            x++;
        }
        if (obj->WORDS->NUMBER >= people)
        {
            printf("\nroom is vacant you can apply for room");

            int count = 0;
            while (obj->WORDS->fill - 1 <= obj->WORDS->NUMBER)
            {
                printf("\nEnter name %d : ", obj->WORDS->fill + 1);
                scanf("%s", obj->WORDS->CUS_NAMES[obj->WORDS->fill]);
                count++;
                obj->WORDS->fill++;
                if (count >= people)
                {
                    break;
                }
            }
            obj->WORDS->NUMBER = obj->WORDS->NUMBER - people;
        }
        else
        {
            printf("\nroom is not vacant... SORRY !!!");
        }
    }
}

void cancelled(struct hostel *obj, int check)
{
    char checking_namess[10];
    int fg = 0;
    int rms, x = 1;

    if (check < 0 || check > 4)
    {
        printf("\n floor doesn't exist : %d", check);
        return;
    }
    else
    {
        printf(" Enter the room no : ");
        scanf("%d", &rms);

        if (rms < 0 || rms > 10)
        {
            printf("\ninvalid room number : %d", rms);
            return;
        }
        else
        {
            printf(" Enter the name to be delete :");
            scanf("%s", checking_namess);

            obj->WORDS = obj->TITLE[check - 1];
            while (x < rms)
            {
                obj->WORDS = obj->WORDS->NXT;
                x++;
            }
            x = 0;
            while (x < 3)
            {
                if (strcmp(checking_namess, obj->WORDS->CUS_NAMES[x]) == 0)
                {
                    fg = 1;
                    break;
                    x = 0;
                }
                else
                    x++;
            }
            if (fg == 1 && obj->WORDS->fill != 0)
            {
                printf("\nrecord deleted : %s", obj->WORDS->CUS_NAMES[x]);

                obj->WORDS->CUS_NAMES[x][0] = 'A';
                obj->WORDS->CUS_NAMES[x][1] = '\0';
                obj->WORDS->fill--;
                obj->WORDS->NUMBER++;
            }
            else
                printf("\nrecord not present ");
        }
    }
}

void modify(struct hostel *obj, int check)
{
    char checking_namess[10];
    int rms, x = 1;

    if (check < 0 || check > 4)
    {
        printf("\n floor doesn't exist : %d", check);
        return;
    }
    else
    {
        printf(" Enter the room no : ");
        scanf("%d", &rms);

        if (rms < 0 || rms > 10)
        {
            printf("\ninvalid room number : %d", rms);
            return;
        }
        else
        {
            printf("Enter the name to be updated :");
            scanf("%s", checking_namess);

            obj->WORDS = obj->TITLE[check - 1];
            while (x < rms)
            {
                obj->WORDS = obj->WORDS->NXT;
                x++;
            }
            x = 0;
            while (x < 3)
            {
                if (strcmp(checking_namess, obj->WORDS->CUS_NAMES[x]) == 0)
                {
                    printf("\nenter updated name : ");
                    scanf("%s", obj->WORDS->CUS_NAMES[x]);
                    break;
                }
                else
                    x++;
            }
            if (x >= 3)
                printf("record not found ");
            else
            {
                printf("\nrecord updated\nprevious name : %s\nupdated name : %s", checking_namess, obj->WORDS->CUS_NAMES[x]);
            }
        }
    }
}

int main()
{
    struct hostel objectives;
    int key_rooms;
    char channels;
    int checking_floors;

    for (int x = 0; x < 3; x++)
    {
        objectives.TITLE[x] = NULL;
    }

    create(&objectives);

    do
    {
        printf("\n1.Book a room for 1 person\n2.Book a room for 2person\n3.Book a room for 3 person\n4.Display the current status of rooms\n5.cancel a booking\n6.modify\n");
        printf("Enter your choice : ");
        scanf("%d", &key_rooms);

        switch (key_rooms)
        {
        case 1:
        {
            booking(&objectives, 1);
            break;
        }
        case 2:
        {
            booking(&objectives, 2);
            break;
        }
        case 3:
        {
            booking(&objectives, 3);
            break;
        }
        case 4:
        {
            display(&objectives);
            break;
        }
        case 5:
        {
            printf("Enter floor number : ");
            scanf("%d", &checking_floors);
            cancelled(&objectives, checking_floors);
            break;
        }
        case 6:
        {
            printf("Enter floor number : ");
            scanf("%d", &checking_floors);
            modify(&objectives, checking_floors);
            break;
        }
        default:
            printf("\nInvalid choice ");
        }
        printf("\nDo you want to continue(Y / N) ");
        scanf(" %c", &channels);
    } while (channels == 'Y' || channels == 'y');

    return 0;
}
