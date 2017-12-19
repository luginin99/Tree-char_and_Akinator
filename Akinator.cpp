#include "lib_for_ak.h"
#include <stdio.h>
#include <locale>
#include <stdlib.h>


int main()
{
    Akinator* Akin = new Akinator();
    FILE* database = fopen ("database.txt", "r");

    setlocale (LC_CTYPE, "Russian");


    if (Akin->ScanFromFile(database))
    {
        fclose (database);

        int answer = 1;
        Node* last_guessed = 0;

        while (answer)
        {
            Node* cur_obj = Akin->Head();
            while (cur_obj->right != NULL)
            {

                printf ("Toт, кого вы загадали, %s?  (1 - да, 0 - нет)\n", cur_obj->line);
                scanf ("%d", &answer);

                if (answer)
                    cur_obj = cur_obj ->right;
                else
                    cur_obj = cur_obj ->left;
            }

            printf ("Мне кажется, вы загадали - %s, я прав? (1 - да, 0 - нет)\n", cur_obj->line);
            scanf ("%d", &answer);

            if (answer)
            {
                printf ("Я и не сомневался\n");
                Akin->GiveCharacteristic(cur_obj);
                if (last_guessed != NULL)
                {
                    printf ("Рассказать чем данный объект отличается от последнего угаданного? (1 - да, 0 - нет)\n");
                    scanf ("%d", &answer);
                    if (answer)
                    {
                        if (last_guessed != cur_obj )
                            Akin->CompareCharacteristicWith (cur_obj, last_guessed);
                        else
                            printf ("Прошлый раз вы загадали тот же объект\n");
                    }
                }
                last_guessed = cur_obj;
            }
            else
                last_guessed = Akin->AddNewObj(cur_obj);
            printf ("Хотите играть еще раз? (1-да, 0 - нет)\n");
            scanf ("%d", &answer);
        }

        database = fopen ("database.txt", "w");

        Akin->PrintToFile(database);

        Akin->DotDump();
    }
    else
        printf ("База данных пуста, вы не сможете никого и ничего загадать\n");
    return 0;
}
