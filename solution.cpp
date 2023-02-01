#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;


string fixString(string text){
    replace(text.begin(), text.end(), '_', ' ');
    return text;
}


struct Song { 
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
    map <string, Album > albums;
    string name;
    int time;
    int nsongs;
};




int main(char *argv[]){
    string filename = argv[1];
    ifstream fin;
    istringstream sin;
    ostringstream sout;
    fin.open(filename);
    if(!fin.is_open()){
        cerr << "Could not open file " << filename << endl;
    }
    map<string, Artist> artists;

    string data = sout.str();
    sin.str(data);
    
    while(true){
        string *details = new string[6];  // [Title, Time, Artist, Album, Genre, Track]
        for(int i=0; i<5; i++){
            getline(sin, details[i], ' ');
            details[i] = fixString(details[i]);
        }
        getline(sin, details[5],'\n');
        details[5] = fixString(details[5]);
        
        
        Artist newArtist;
        Album newAlbum;
        Song newSong;

        newArtist.name = details[2];
        newAlbum.name = details[3];
        newSong.title = details[0];
        string min = details[1].substr(0, details[1].find(':'));
        string seconds = details[1].substr(details[1].find(':')+1, 2);
        int songtime = stoi(min)*60 + stoi(seconds);
        newSong.time = songtime;
        newAlbum.songs[0] = newSong;
        newAlbum.nsongs++;
        newArtist.albums[details[3]] = newAlbum;
        artists[details[2]] = newArtist;

        map<string, Artist>::iterator itr_artist = artists.find(details[2]);
        if (itr_artist == artists.end()) {

        } else {
            Artist artist = itr_artist->second;
            map<string, Album>::iterator itr_album = artist.albums.find(albumName);
            if (itr_album == artist.albums.end()) {
                newAlbum.name = albumName;
                newSong.title = songTitle;
                newSong.time = songTime;
                newAlbum.songs[0] = newSong;
                newAlbum.nsongs = 1;
                artist.albums[albumName] = newAlbum;
                artists[artistName] = artist;
            } else {
                Album album = itr_album->second;
                newSong.title = songTitle;
                newSong.time = songTime;
                album.songs[album.nsongs++] = newSong;
                artist.albums[albumName] = album;
                artists[artistName] = artist;
            }
}




        delete details;
    }

}

