#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
//Struct for birds
struct birdType{
  enum {MAX_CHAR_LEN=100};
  char name[MAX_CHAR_LEN];
  char sname[MAX_CHAR_LEN];
  char conStatus[MAX_CHAR_LEN];
  char color[MAX_CHAR_LEN];
  char diet[MAX_CHAR_LEN];
  birdType();
};
//default constructor
birdType::birdType()
{
  for(int i = 0; i < MAX_CHAR_LEN; i++)
    {
      name[i] = ' ';
      sname[i] = ' ';
      conStatus[i] = ' ';
      color[i] = ' ';
      diet[i] = ' ';
    }
}
//getting bird a bird from the file
birdType getBird(ifstream &infile)
{
  birdType bird;
  infile.get(bird.name, birdType::MAX_CHAR_LEN, ';');
  infile.ignore(100,';');
  infile.get(bird.sname, birdType::MAX_CHAR_LEN, ';');
  infile.ignore(100,';');
  infile.get(bird.conStatus, birdType::MAX_CHAR_LEN, ';');
  infile.ignore(100,';');
  infile.get(bird.color, birdType::MAX_CHAR_LEN, ';');
  infile.ignore(100,';');
  infile.get(bird.diet, birdType::MAX_CHAR_LEN);
  infile.ignore(100, '\n');
  
  return bird;
}

const int MAX_BIRD = 500;
//reading all the birds from the file
int readBirds(birdType bird[])
{
  ifstream birdfile("birds.txt");
  int numBirds = 0;
  while (birdfile.peek() != EOF && numBirds < MAX_BIRD)
    {
      bird[numBirds] = getBird(birdfile);
      numBirds++;
    }
  return numBirds;
}
//validating int inputs
int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}
//prints a bird
void printBirds(birdType bird)
{
  cout << bird.name << " " << bird.sname << " " << bird.conStatus << " " << bird.color << " " << bird.diet << endl;
}
//displays menu
void displayMenu()
{
  cout << "Birdy :D" << endl;
  cout << endl;
  cout <<"1. Reload data" << endl;
  cout <<"2. Print all birds" << endl;
  cout <<"3. Add new bird" << endl;
  cout <<"4. Remove bird" << endl;
  cout <<"5. Search by name" << endl;
  cout <<"6. Save database to file" << endl;
  cout <<"7. Quit :(" << endl;
}
//code to save birds to file
void saveFile(birdType bird[], int num){
  ofstream outfile("birds.txt");
  for(int i = 0; i < num; i++)
    {
    outfile << bird[i].name << ";";
    outfile << bird[i].sname << ";";
    outfile << bird[i].conStatus << ";";
    outfile << bird[i].color << ";";
    outfile << bird[i].diet << endl;
      }
}
int main()
{ birdType birds[MAX_BIRD];
  int numBird = 0;
  bool select = true;
  int choose = 0;
  numBird = readBirds(birds);
  //option selection
  while(select)
    {
      displayMenu();
      choose = readInt("Enter option here: ");
      while(choose <= 0 || choose > 7){
        choose = readInt("Out of range, try again: ");
      }
      //option 1 reload data
      if(choose == 1)
      {
        numBird = readBirds(birds);
        cout << "Reload successful!" << endl;
      }
      //option 2 print all birds
      if(choose == 2)
      {
      for (int i = 0; i < numBird; i++)
      {
        cout << i + 1 << ". "; 
        printBirds(birds[i]);
      }
      }
      //option 3 add new bird
      if(choose == 3)
      {
        if(numBird >= 500) cout << "Storage Full!!" << endl;
        else{
          cout << "Enter the Birds name" << endl;
          cin.ignore(100, '\n');
          cin.getline(birds[numBird].name, birdType::MAX_CHAR_LEN);
          cout << "Enter the Birds scientific name" << endl;
          cin.getline(birds[numBird].sname, birdType::MAX_CHAR_LEN);
          cout << "Enter the con status" << endl;
          cin.getline(birds[numBird].conStatus, birdType::MAX_CHAR_LEN);
          cout << "Enter the color of the bird" << endl;
          cin.getline(birds[numBird].color, birdType::MAX_CHAR_LEN);
          cout << "Enter the birds diet" << endl;
          cin.getline(birds[numBird].diet, birdType::MAX_CHAR_LEN);
          numBird++;
          
        }
      }
      //option 4 removing bird
      if (choose == 4)
      {
        int index = 0;
        index = readInt("Please enter what bird you want to remove by index: ");
        while(index <= 0 || index > numBird)
          {
            index = readInt("Index out of range! try again: ");
          }
        index--;
        for(int i = index; i < MAX_BIRD; i++)birds[i] = birds[i+1];
        numBird--;
        cout << "Removed!" << endl;
      }
      //option 5 search by name
      if (choose == 5)
      {
        char name[100];
        cout <<"Which bird do you wish to see: " << endl;
        cin.ignore(100,'\n');
        cin.getline(name, 100);
        for (int i = 0; i < 500; i++)
          {
            if(strcmp(birds[i].name, name)==0)
            {
              cout << i + 1 << ". ";
              printBirds(birds[i]);
            }
          }
      }
      //option 6 save birds to file
      if (choose == 6)
      {
        saveFile(birds, numBird);
        cout << "Save successful!!" << endl;
      }
      //option 7 quit :(
      if (choose == 7)
      {
        select = false;
      }
    }
  cout <<"Thanks for using my program" << endl;
  
  return 0;
}