#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;


/*string fixString(string text){
    replace(text.begin(), text.end(), '_', ' ');
    return text;
}*/


/*struct Song { 
    string title;
    int time;  // could also be a string
};

struct Album {
    map <int, Song > songs;
    string name;
    int time;
    int nsongs;  // optional variable but makes it easier
};

struct Artist {
    map <string, Album> albums;
    string name;
    int time;
    int nsongs;
};*/




int main(int argc, char** argv){

    int min, seconds, track;
    char Title[100], Artist[100], Album[100], Genre[100];
    string line;
    ifstream infile;

    infile.open(argv[1]);

    while (getline(infile, line))
    {
        sscanf(line.c_str(), "%s %d:%d %s %s %s %d", Title, &min, &seconds, Artist, Album, Genre, &track);

        
        
     }
    return 0;
}