#include "FileIO.h"

// Read all high score and players for file //
std::vector<Player> FileIO::read()
{
    std::vector<Player> players;
    std::stringstream ss;
    std::string name, line;
    int score;

    std::ifstream ifile(file);      // open file for reading
    if(ifile.is_open()) {           // if opened 
        while(getline(ifile, line)) // line by line
        {
            ss.clear();
            ss.str(line);                  // line in stream
            getline(ss, name, '\t');       // tab delimited
            ss >> score;                   // pull int score
            Player player(name, score);    // creates a player 
            players.push_back(player);     // adds to list of players
        }
    } else 
        std::cout << "File Error!" << std::endl;
        
    ifile.close();
    return players;
}
// Write top ten players to file //
void FileIO::write(std::vector<Player> players)
{   
    std::ofstream ofile("High_Scores.txt", std::ios::out); // open for writing
    for(int i=0; i < 10; i++) 
        ofile << players[i].playerName() << '\t' << players[i].playerScore() << '\n';
    ofile.close();
}