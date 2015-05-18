
// TODO: Requires cleanup

#include <sudoku.h>

# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <numeric>
# include <functional>
# include <ctime>
# include <cstdlib>

using namespace std;
using namespace Phoenix;

const int TIME_PER_ITERATION = 1;
bool flag = true;

//********************************************************FUNCTION FOR UPDATE 1********************************************************//
/*
This function does the normal erasing stuff..
 */

void update1(Cell cell[9][9],int a,int b)
{
    //checking in the rows...
    for(auto j = 0; j < 9; j++) {
        if(j == b) continue;

        if(cell[a][j].value() != 0) {
            cell[a][b].removeFromProbabilities(cell[a][j].value());
        }
    }

    //checking in the columns..
    for(auto i = 0; i < 9; i++) {
        if(i == a) continue;

        if(cell[i][b].value() != 0) {
            cell[a][b].removeFromProbabilities(cell[i][b].value());
        }
    }

    //checking in the box..
    for(auto i = (a/3)*3; i < (a/3)*3+3; i++) {
        for(auto j = (b/3)*3; j < (b/3)*3+3; j++) {
            if(i == a && j == b) continue;

            if(cell[i][j].value() != 0) {
                cell[a][b].removeFromProbabilities(cell[i][j].value());
            }
        }
    }

    //updating the entries..
    if(cell[a][b].probabilities().size() == 1) {
        cell[a][b].value() = cell[a][b].probabilities()[0];
        flag = false;
    }
    return;
}

//****************************************************FUNCTION FOR UPDATE 2************************************************************//

/*
This function basically checks for the presence of n boxes having exactly n same possibility. If it finds such a occurence, it erases 
the occurence of these n possibility in other unfilled boxes. Simple isn't it?
 */

void update2(Cell cell[9][9],int a)
{

    //checking in the row a..

    int i,j;
    for(j = 0; j < 9; j++)
    {
        int tempsize = cell[a][j].probabilities().size();
        if(tempsize != 1)
        {
            int k,l;
            vector <int> temp;
            temp.push_back(j);
            for(k = j+1; k < 9; k++)
            {
                if(k == j)
                    continue;
                if(cell[a][j].probabilities() == cell[a][k].probabilities())
                {

                    temp.push_back(k);
                }
            }
            if(tempsize == temp.size())
            {
                for(l = 0; l < 9; l++)
                {
                    unsigned int h;
                    for(h = 0; h < temp.size(); h++)
                    {
                        if(l == temp[h])
                            break;
                    }
                    if(h < temp.size())
                        continue;
                    for(h = 0; h < temp.size(); h++)
                    {
                        cell[a][l].removeFromProbabilities(
                                                cell[a][j].probabilities()[h]);
                    }
                }
            }
        }
    }

    //checking in the colum a..
    for(i = 0; i < 9; i++)
    {
        int tempsize = cell[i][a].probabilities().size();
        if(tempsize != 1)
        {
            int k,l;vector <int> temp;
            temp.push_back(i);
            for(k = i+1; k < 9; k++)
            {
                if(k == i)
                    continue;
                if(cell[i][a].probabilities() == cell[k][a].probabilities())
                {

                    temp.push_back(k);
                }
            }
            if(tempsize == temp.size())
            {
                for(l = 0; l < 9; l++)
                {
                    unsigned int h;
                    for(h = 0; h < temp.size(); h++)
                    {
                        if(l == temp[h])
                            break;
                    }
                    if(h < temp.size())
                        continue;
                    for(h = 0; h < temp.size(); h++)
                    {
                        cell[l][a].removeFromProbabilities(
                                                cell[i][a].probabilities()[h]);

                    }
                }
            }
        }
    }


    return;
}

//*****************************************************FUNCTION FOR UPDATE 3***********************************************************//
/*
This function checks for the occurence of a possibility in exactly(FREQUENCY CHECK) one box (either in column or row or the 3x3 box..
You may wonder that this might be a redundant test(I wondered),but this is kind of different from other functions.. 
 */

void update3(Cell cell[9][9],unsigned int a, unsigned int b)
{
    unsigned int i,j,k,l;
    bool f_flag = false;

    for(k = 0; k < cell[a][b].probabilities().size(); k++)
    {
        bool t_flag = true;

        //checking for its freq in the rows....
        if(t_flag)
        {
            for(j = 0; j < 9; j++)
            {
                if(j == b)
                    continue;
                else
                {
                    for(l = 0; l < cell[a][j].probabilities().size(); l++)
                    {
                        if(cell[a][b].probabilities()[k] == cell[a][j].probabilities()[l])
                        {
                            t_flag = false;
                            break;
                        }
                    }
                }
            }
        }

        if(t_flag)
        {
            f_flag = true;
            break;
        }

        t_flag = true;

        //checking in the columns...
        if(t_flag)
        {
            for(i = 0; i < 9; i++)
            {
                if(i == a)
                    continue;
                else
                {
                    for(l = 0; l < cell[i][b].probabilities().size(); l++)
                    {
                        if(cell[a][b].probabilities()[k] == cell[i][b].probabilities()[l])
                        {
                            t_flag = false;
                            break;
                        }
                    }
                }
            }
        }
        if(t_flag)
        {
            f_flag = true;
            break;
        }

        t_flag = true;

        //checking in the box...
        if(t_flag)
        {
            for(i = (a/3)*3; i < (a/3)*3+3; i++)
            {
                for(j = (b/3)*3; j < (b/3)*3+3; j++)
                {
                    if(i == a && j == b)
                        continue;
                    else
                    {
                        for(l = 0; l < cell[i][j].probabilities().size(); l++)
                        {
                            if(cell[a][b].probabilities()[k] == cell[i][j].probabilities()[l])
                            {
                                t_flag = false;
                                break;
                            }
                        }
                    }
                }
            }
        }

        if(t_flag)
        {
            f_flag = true;
            break;
        }
    }

    //The search ended up fruitful...

    if(f_flag)
    {
        cell[a][b].value() = cell[a][b].probabilities()[k];
        cell[a][b].probabilities().clear();
        cell[a][b].probabilities().push_back(cell[a][b].value());
    }
    return;
}

//**********************************************FUNCTION TO CHECK THE COMPLETION OF MATRIX*********************************************//

bool incomplete(Cell cell[9][9])
{
    for (auto i = 0; i < 9; ++i) {
        for (auto j = 0; j < 9; ++j) {
            if (cell[i][j].value() == 0) {
                return true;
            }
        }
    }
    return false;
}


void print_matrix(Cell cell[9][9])
{
    int i,j;
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            cout<<cell[i][j].value()<<" ";
        }
        cout<<endl;
    }
    return;
}
//**************************************************************THE MAIN CLIENT********************************************************//

int  main()
{
    int i,j,time = 0;
    bool is_complete = true;
    Cell cell[9][9];
    string s;
    system("cls");
    cout<<"Please enter the matrix as a number with blanks replaced by 0's"<<endl;

    cin>>s;

    for(i = 0; i < 9; i++)
        for(j = 0; j < 9; j++)
        {
            cell[i][j].value() = (int)(s[i*9+j] - '0');
        }

    for(i = 0; i < 9; i++)
        for(j = 0; j < 9; j++)
        {
            if(cell[i][j].value() == 0)
            {
                for(int k = 0; k < 9; k++)
                    cell[i][j].probabilities().push_back(k+1);
            }
            else cell[i][j].probabilities().push_back(cell[i][j].value());
        }

    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            cout<<cell[i][j].value()<<" ";
        }
        cout<<endl;
    }

    cout << endl << endl << endl;
    //system("sleep 2");

    //cout<<"Is the matrix properly printed?  if yes print y else n .."<<endl;

    //cin>>c;
    if(true)
    {
        while(incomplete(cell))
        {
            for(i = 0; i < 9; i++)
                for(j = 0; j < 9; j++)
                {
                    if(cell[i][j].value() == 0)
                        update1(cell,i,j);
                }

            if(flag)
            {
                for(i = 0; i < 9; i++)
                {
                    update2(cell,i);
                }

                for(i = 0; i < 9; i++)
                {
                    for(j = 0; j < 9; j++)
                    {
                        if(cell[i][j].value() == 0)
                        {
                            update3(cell,i,j);
                        }
                    }
                }
            }
            flag = true;

            system("cls");
            print_matrix(cell);                                //Change "clear" to "cls" in windows..
            time += TIME_PER_ITERATION;
            printf("Time elapsed : %d\n",time);
            //system("sleep 1");                               //Comment this statement in windows..
            if(time > 35)
            {
                cout<<endl<<endl<<" Sorry the program is unable to solve it.\nMaybe there is some guess required to solve the matrix further.\nOr that the initial problem was wrong....\n";
                break;
                is_complete = false;
            }

        }

        if(is_complete)
        {
            //system("clear");                                  //Change "clear" to "cls" in windows..
            cout<<"The completed matrix is as follows..."<<endl;
            print_matrix(cell);
            cout<<"Total time taken : "<<time<<endl;          //The program doesn't really tale this much time.I am halting the system so
            //that people can watch the actual progress of the solution process.../*:)*/
            //system("sleep 3");                                //Comment this statement in windows..
        }
    }
    return 0;
}


//**************************************************THE CODE ENDS HERE*****************************************************************//

