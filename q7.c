#include "q7.h"

void menu()
{
    bool end = false, location = false, tree = false, listPath = false;
    int choice;
    chessPos pos;
    pathTree PathTree;
    chessPosList* path;
    printf("Welcome to Keren & Bar Chess \n\n");
    while (!end)
    {
        print_menu();

        scanf("%d", &choice);
        while (choice < 1 || choice > 6)
        {
            printf("Wrong choice, select again \n");
            scanf("%d", &choice);
        }

        switch (choice)
        {
        case 1:/* option 1 - get location   */

            if (location == true)/* the user choose other location   */
            {
                if (tree == true)
                {
                    freePathTree(PathTree);
                    tree = false;
                }

                if (listPath == true)
                {
                    freeChessPosList(&path);/////////////
                    listPath = false;
                }
            }

            option_one(&pos);
            location = true;
            break;

        case 2:/* option 2 - make tree from location   */
            PathTree = option_two(&pos, &location);
            tree = true;
            break;

        case 3:/* option 3 - make list path that cover all the board if there is not return null   */
            path = option_3(&pos, &PathTree, &location, &tree, &listPath);
            break;

        case 4:/* option 4 - put the path in binary file  */
            option_4(&pos, &PathTree, &path, &location, &tree, &listPath);///////////////





            break;

        case 5:/* option 5 - read from binary file   */
            option_5();
            break;

        case 6:/* option 6 - free and exit   */
            if (tree == true)
                freePathTree(PathTree);

            if (listPath == true)
                freeChessPosList(&path);/////////////
            end = true;
            break;
        }
    }
    exit(1);
}

void print_menu()
{ /* print the menu */
    printf("1. Enter a Knight's starting position \n");
    printf("2. Create all possible knight pats \n");
    printf("3. Find a knight path covering all board \n");
    printf("4. Save knight path covering all board to file \n");
    printf("5. Load and display path from file \n");
    printf("6. Exit \n");
    printf("\nPlease select from the menu \n");
}

void option_one(chessPos* pos)
{
    printf("Please enter location \n");
    vaild_location(pos); /* get location  */
}

pathTree option_two(chessPos* pos, bool* location)
{
    pathTree PathTree;
    if (*location == false) /* if the user cant choose location  */
    {
        option_one(pos);
        *location = true;
    }
    PathTree = findAllPossibleKnightPaths(pos);
    return PathTree;
}

chessPosList* option_3(chessPos* pos, pathTree* PathTree, bool* location, bool* tree, bool* listPath)
{
    chessPosList* path;
    if (*location == false)/* if the user cant choose location  */
    {
        option_one(pos);
        *location = true;
    }
    if (*tree == false)/* if not make tree yet  */
    {
        *PathTree = option_two(pos, location);
        *tree = true;
    }

    path = findknightPathCoveringAllBoard(PathTree);
    if (path == NULL)
        printf("There is not path that covering all board");

    listPath = true;
    return path;
}

void option_4(chessPos* pos, pathTree* PathTree, chessPosList** path, bool* location, bool* tree, bool* listPath)
{
    char* nameFile;

    if (*location == false)/* if the user cant choose location  */
    {
        option_one(pos);
        *location = true;
    }
    if (*tree == false)/* if not make tree yet  */
    {
        *PathTree = option_two(pos, location);
        *tree = true;
    }

    if (*listPath == false)/* if not make list path yet  */
    {
        *path = option_3(pos, PathTree, location, tree, listPath);

        chessPosCell* ptr = (*path)->head;

        while (ptr != NULL)
        {
            printf("%c%c ", ptr->position[0], ptr->position[1]);
            ptr = ptr->next;
        }
        printf("\n");

        *listPath = true;
    }

    nameFile = getNameFile();
    saveListToBinFile(nameFile, *path);
    free(nameFile);
}

void option_5()
{
    char* file_name;
    int num;

    file_name = getNameFile();
    num = checkAndDisplayPathFromeFile(file_name);

    if (num == -1)
        printf("The file not exists");

    if (num == 1)
        printf("The list does not contain a legal path of a knight");

    if (num == 2)
        printf("The list covers all board slots");

    if (num == 3)
        printf("Else");

    free(file_name);
}

char* getNameFile()
{/* Get the file name   */
    int logicalSize = 0, phisicalSize = 1;
    char ch;
    char* fname = (char*)malloc(phisicalSize * sizeof(char));
    checkMemoryAllocation(fname);

    printf("Please enter your file name\n");

    scanf(" %c", &ch);

    while (ch != '\n')
    {
        if (logicalSize == phisicalSize)
        {
            phisicalSize *= 2;
            fname = (char*)realloc(fname, phisicalSize * sizeof(char));
            checkMemoryAllocation(fname);
        }
        fname[logicalSize++] = ch;
        ch = getchar();
    }
    fname[logicalSize] = '\0';

    fname = (char*)realloc(fname, (logicalSize+5) * sizeof(char));
    checkMemoryAllocation(fname);

    strcat(fname, ".bin");


    return fname;
}

void vaild_location(chessPos* pos)
{ /* Get the location and checks if the location is valid  */
    scanf(" %c%c", &pos[0][0], &pos[0][1]);

    while (pos[0][0] < UPPER_LIMIT || pos[0][0] > LOWER_LIMIT || pos[0][1] < LEFT_LIMIT || pos[0][1] > RIGHT_LIMIT)
    {
        printf("Invalid location, please try again \n");
        scanf(" %c%c", &pos[0][0], &pos[0][1]);
    }

}