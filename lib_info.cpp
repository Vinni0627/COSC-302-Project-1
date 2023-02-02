#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

// Issues: Time issue and all songs are not printing

string fixString(string text){
    replace(text.begin(), text.end(), '_', ' ');
    return text;
}

string convertTime(int seconds){
    cout << seconds << " ";
    int min, sec;
    sec = seconds %60;
    min = seconds / 60;
    string secs = to_string(sec);
    if(sec < 10){
        secs = "0" + secs;
    }
    string finale = to_string(min) +":"+ secs;
    return finale;
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
    map <string, Album> albums;
    string name;
    int time;
    int nsongs;
};





int main(int argc, char** argv){

    int min, seconds, track;
    char title[100], artist[100], album[100], genre[100];
    string line;
    ifstream infile;

    infile.open(argv[1]);
    map<string, Artist> artists;

    while (getline(infile, line))
    {
        sscanf(line.c_str(), "%s %d:%d %s %s %s %d", title, &min, &seconds, artist, album, genre, &track);

        int time = min*60 + seconds;

        fixString(title);
        fixString(artist);
        fixString(album);


        Artist newArtist;
        Album newAlbum;
        Song newSong;

        newSong.title = title;
        newSong.time = time;

        auto artist_itr = artists.find(artist);

        if(artist_itr == artists.end()){ // artist not found // new everything
            newArtist.name = artist;
            newArtist.nsongs++;
            newArtist.time += time;


            newAlbum.name = album;
            newAlbum.nsongs++;
            newAlbum.time += time;
            
            newAlbum.songs.insert(pair<int, Song>(track, newSong)); // new song added
            newArtist.albums.insert(pair<string, Album>(album, newAlbum)); // new album added
            artists.insert(pair<string, Artist>(artist, newArtist)); // new artist added


        } else { // artist found
            newArtist = artist_itr->second;

            newArtist.nsongs++;
            newArtist.time += time;
            

            auto album_itr = newArtist.albums.find(album);
            if(album_itr == newArtist.albums.end()){ // album not found
                newAlbum.name = album;
                newAlbum.nsongs++;
                newAlbum.time += time;
                
                newAlbum.songs.insert(pair<int, Song>(track, newSong)); // new song added
                newArtist.albums.insert(pair<string, Album>(album, newAlbum)); // new album added



            }else { // album found
                newAlbum = album_itr->second;


                newAlbum.nsongs++;
                newAlbum.time += time;

                newAlbum.songs.insert(pair<int, Song>(track, newSong)); // new song added
            }

        }


        
    }

        for(auto artist: artists){
            cout << artist.first << ": " << artist.second.nsongs << ", " << convertTime(artist.second.time) << endl;
            //cout << "SIZE" << artist.second.albums.size() << "SIZEEND"<< endl;
            for(auto album: artist.second.albums){
                cout << "\t" << album.second.name << ": " << album.second.nsongs << ", " << convertTime(album.second.time) << endl;
                for(auto song: album.second.songs){
                    cout << "\t\t" << song.first << ". " << song.second.title << ": " << convertTime(song.second.time) << endl;
                }
            }

        }
    return 0;
}