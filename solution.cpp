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
    string *details;
    while(true){
        details = new string[6];  // [Title, Time, Artist, Album, Genre, Track]
        for(int i=0; i<5; i++){
            getline(sin, details[i], ' ');
            details[i] = fixString(details[i]);
        }
        getline(sin, details[5],'\n');
        details[5] = fixString(details[5]);
        
        /*Artist newArtist;
        Album newAlbum;
        Song newSong;

        auto artist_it = artists.find(details[2]); // checks to see if the artist already exists

        if(artist_it == artists.end()){ // artist doesn't exist

            newArtist = artist_it->second;
            map<string, Album> cur_albums = newArtist.albums;
            auto album_it = cur_albums.find(details[3]); // checks to see if the album already exists

            if(album_it == cur_albums.end()){ // album doesn't exist


            }



        }*/

        for(auto artist_itr = artists.begin(); artist_itr != artists.end(); artist_itr++){
            
            Artist cur_Artist = artist_itr->second;

            cout << details[2];            
            for(auto album_itr = cur_Artist.albums.begin(); album_itr != cur_Artist.end();album_itr++){

                Album cur_album = album_itr->second;

                cout << "\t" << details[3];
                for(auto song_itr = cur_album.songs.begin(); song_itr != cur_album.end(); song_itr++){
                    Song cur_song = song_itr->second;

                    cout << "\t\t" << detail[0] << "\t" << detail[1];

                }
            }
                

        }



        



        delete details;
    }
}


