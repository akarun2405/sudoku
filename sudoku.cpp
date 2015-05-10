//IF YOU DON0T HAVE SUFFICIENTLY LARGE SCREEN,
//THE COMMENTS MAY LOOK CLUTTERED.
//SORRY NEVER THOUGHT ABOUT THAT WHILE 
//WRITING THE COMMENTS.

// TODO: Requires cleanup
# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <numeric>
# include <functional>
# include <ctime>
# include <cstdlib>

using namespace std;
          
# define TIME_PER_ITERATION 1
bool flag = true;
class Square
{
public:
  int no;
  vector <int> prob;
  Square(){no = 0;}
};

//********************************************************FUNCTION FOR UPDATE 1********************************************************//
/*
This function does the normal erasing stuff..
*/

void update1(Square sq[9][9],int a,int b)
{
  vector <int>::iterator new_end;
  
  //checking in the rows...
  
  int i,j;
  for(j = 0; j < 9; j++)
    {
      if(j == b)
    continue;
      if(sq[a][j].no != 0)
	{
	  new_end = remove(sq[a][b].prob.begin(),sq[a][b].prob.end(),sq[a][j].no);
	  sq[a][b].prob.erase(new_end,sq[a][b].prob.end());
	}
    }
  
  //checking in the columns..
  
  for(i = 0; i < 9; i++)
    {
      if(i == a)
	continue;
      if(sq[i][b].no != 0)
	{
	  new_end = remove(sq[a][b].prob.begin(),sq[a][b].prob.end(),sq[i][b].no);
	  sq[a][b].prob.erase(new_end,sq[a][b].prob.end());
	}
    }
  
  //checking in the box..
  
  for(i = (a/3)*3; i < (a/3)*3+3; i++)
    for(j = (b/3)*3; j < (b/3)*3+3; j++)
      {
	if(i == a && j == b)
	  continue;
	if(sq[i][j].no != 0)
	  {
	    
	    new_end = remove(sq[a][b].prob.begin(),sq[a][b].prob.end(),sq[i][j].no);
	    sq[a][b].prob.erase(new_end,sq[a][b].prob.end());
	  }
      }
	

  //updating the entries..

  if(sq[a][b].prob.size() == 1)
    {
      sq[a][b].no = sq[a][b].prob[0];
      flag = false;
    }
  return;
}

//****************************************************FUNCTION FOR UPDATE 2************************************************************//

/*
This function basically checks for the presence of n boxes having exactly n same possibility. If it finds such a occurence, it erases 
the occurence of these n possibility in other unfilled boxes. Simple isn't it?
*/

void update2(Square sq[9][9],int a)
{
 
  //checking in the row a..

  int i,j;
  vector <int>::iterator new_end;
  for(j = 0; j < 9; j++)
    {
      int tempsize = sq[a][j].prob.size();
      if(tempsize != 1)
	{
	  int k,l;
	  vector <int> temp;
	  temp.push_back(j);
	  for(k = j+1; k < 9; k++)
	    {
	      if(k == j)
		continue;
	      if(sq[a][j].prob == sq[a][k].prob)
		{
		  
		  temp.push_back(k);
		}
	    }
	  if(tempsize == temp.size())
	    {
	      for(l = 0; l < 9; l++)
		{
		  int h;
		  for(h = 0; h < temp.size(); h++)
		    {
		      if(l == temp[h])
			break;
		    }
		  if(h < temp.size())
		    continue;
		  for(h = 0; h < temp.size(); h++)
		    {
		      new_end = remove(sq[a][l].prob.begin(),sq[a][l].prob.end(),sq[a][j].prob[h]);
		      sq[a][l].prob.erase(new_end,sq[a][l].prob.end());
		    }
		}
	    }
	}
    }
  
  //checking in the colum a..
  for(i = 0; i < 9; i++)
    {
      int tempsize = sq[i][a].prob.size();
      if(tempsize != 1)
	{
	  int k,l;vector <int> temp;
	  temp.push_back(i);
	  for(k = i+1; k < 9; k++)
	    {
			  if(k == i)
			    continue;
			  if(sq[i][a].prob == sq[k][a].prob)
			    {
			      
			      temp.push_back(k);
			    }
			}
	  if(tempsize == temp.size())
	    {
	      for(l = 0; l < 9; l++)
		{
		  int h;
		  for(h = 0; h < temp.size(); h++)
		    {
		      if(l == temp[h])
			break;
		    }
		  if(h < temp.size())
		    continue;
		  for(h = 0; h < temp.size(); h++)
		    {
		      new_end = remove(sq[l][a].prob.begin(),sq[l][a].prob.end(),sq[i][a].prob[h]);
		      sq[l][a].prob.erase(new_end,sq[l][a].prob.end());
		          
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

void update3(Square sq[9][9],int a, int b)
{
  int i,j,k,l;
  bool f_flag = false;
 
  for(k = 0; k < sq[a][b].prob.size(); k++)
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
		  for(l = 0; l < sq[a][j].prob.size(); l++)
		    {
		      if(sq[a][b].prob[k] == sq[a][j].prob[l])
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
		  for(l = 0; l < sq[i][b].prob.size(); l++)
		    {
		      if(sq[a][b].prob[k] == sq[i][b].prob[l])
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
		      for(l = 0; l < sq[i][j].prob.size(); l++)
			{
			  if(sq[a][b].prob[k] == sq[i][j].prob[l])
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
      sq[a][b].no = sq[a][b].prob[k];
      sq[a][b].prob.erase(sq[a][b].prob.begin(),sq[a][b].prob.end());
      sq[a][b].prob.push_back(sq[a][b].no);
    }
  return;
}

//**********************************************FUNCTION TO CHECK THE COMPLETION OF MATRIX*********************************************//

bool incomplete(Square sq[9][9])
{
	int i,j;
	bool found = false;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			if(sq[i][j].no == 0)
			{
				found = true;
				break;
			}
		}
		if(found)
			break;
	}
	if(i < 9 || j < 9)
		return true;
	else return false;
}


void print_matrix(Square a[9][9])
{
  int i,j;
  for(i = 0; i < 9; i++)
  {
    for(j = 0; j < 9; j++)
      {
	cout<<a[i][j].no<<" ";
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
  char c;
  Square sq[9][9];
  string s;
  system("clear");
  cout<<"Please enter the matrix as a number with blanks replaced by 0's"<<endl;
  
  cin>>s;
  
  for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
      {			
	sq[i][j].no = (int)(s[i*9+j] - '0');
      }
  
  for(i = 0; i < 9; i++)
    for(j = 0; j < 9; j++)
      {
	if(sq[i][j].no == 0)
	  {
	    for(int k = 0; k < 9; k++)
	      sq[i][j].prob.push_back(k+1);
	  }
	else sq[i][j].prob.push_back(sq[i][j].no);
      }
  
  for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
	{
	  cout<<sq[i][j].no<<" ";
	}
      cout<<endl;
    }
  
  cout << endl << endl << endl;
  //system("sleep 2");
  
  //cout<<"Is the matrix properly printed?  if yes print y else n .."<<endl;
  
  //cin>>c;
  if(true)
    {  
      while(incomplete(sq))
	{
	  for(i = 0; i < 9; i++)
	    for(j = 0; j < 9; j++)
	      {
		if(sq[i][j].no == 0)
		  update1(sq,i,j);
	      }
	  
	  if(flag)
	    {
	      for(i = 0; i < 9; i++)
		{
		  update2(sq,i);
		}
		
	      for(i = 0; i < 9; i++)
		{
		  for(j = 0; j < 9; j++)
		    {
		      if(sq[i][j].no == 0)
			{
			  update3(sq,i,j);
			}
		    }
		}
	    }
	  flag = true;
	  
	  system("clear");
	  print_matrix(sq);                                //Change "clear" to "cls" in windows..
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
	  print_matrix(sq);
	  cout<<"Total time taken : "<<time<<endl;          //The program doesn't really tale this much time.I am halting the system so 
	                                                    //that people can watch the actual progress of the solution process.../*:)*/
	  //system("sleep 3");                                //Comment this statement in windows..
	}
    }
  return 0;
}


//**************************************************THE CODE ENDS HERE*****************************************************************//

