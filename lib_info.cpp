// Vineeth Konjeti and Amal Sam - CS302 - 02/03/23 [PROJECT 1]
/* Description: Program organizes a given list of artists, their albums, the album's contents (songs),
number of songs, and the time for both the album and each song.
*/


#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

// Issues: Time issue and all songs are not printing

void fixString(string &text){ // Removes underscores in input file to creates spaces

    for (int i = 0; i< text.length(); i++) {
        if (text[i] == '_') {
            text[i] = ' ';
        }
    }

    
}

string convertTime(int seconds){ // Function to coverts seconds to minutes and seconds
    int min, sec;
    sec = seconds %60;
    min = seconds / 60;
    string secs = to_string(sec);
    if(sec < 10){
        secs = '0' + secs;
    }
    string finale = to_string(min) +':'+ secs;
    return finale;
}


struct Song { 
    string title = "";
	int time = 0;  
};

struct Album {
    map <int, Song > songs;
    string name = "";
    int time = 0;
    int nsongs = 0;  // optional variable but makes it easier
};

struct Artist {
    map <string, Album> albums;
    string name = "";
    int time = 0;
    int nsongs = 0;
};



int main(int argc, char** argv){ 

    int min, seconds, track;
    char title[150], artist[150], album[150], genre[100]; // allocating space for char arrays
	string stitle = "", sartist = "",salbum = "";
    string line;
    ifstream infile;

    infile.open(argv[1]);
    map<string, Artist> artists;
    int time = 0;

    while (getline(infile, line)) // reads input files
    {
        sscanf(line.c_str(), "%s %d:%d %s %s %s %d", title, &min, &seconds, artist, album, genre, &track);

        time = min*60 + seconds;
		stitle = title;
		sartist = artist;
		salbum = album;

        fixString(stitle);
        fixString(sartist);
        fixString(salbum);


        Artist newArtist;
        Album newAlbum;
        Song newSong;

        newSong.title = stitle; // converting from char array to a string for easier use

        newSong.time = time;

        auto artist_itr = artists.find(sartist);

        if(artist_itr == artists.end()){ // artist not found // new everything
            newArtist.name = sartist;
            newArtist.nsongs++;
            newArtist.time += time;


            newAlbum.name = salbum;
            newAlbum.nsongs++;
            newAlbum.time += time;
 
            
            newAlbum.songs.insert(pair<int, Song>(track, newSong)); // new song added
            newArtist.albums.insert(pair<string, Album>(salbum, newAlbum)); // new album added
            artists.insert(pair<string, Artist>(sartist, newArtist)); // new artist added


        } else { // artist found

            artist_itr->second.nsongs++;
            artist_itr->second.time += time;
            

            auto album_itr = artist_itr->second.albums.find(salbum);
            if(album_itr == artist_itr->second.albums.end()){ // album not found
                newAlbum.name = salbum;
                newAlbum.nsongs++;
                newAlbum.time += time;
                
                newAlbum.songs.insert(pair<int, Song>(track, newSong)); // new song added
                artist_itr->second.albums.insert(pair<string, Album>(salbum, newAlbum)); // new album added



            }else { // album found


                album_itr->second.nsongs++;
                album_itr->second.time += time;

                album_itr->second.songs.insert(pair<int, Song>(track, newSong)); // new song added
            }

        }


        
    }
        /* Printing out artists and their respective albums and their songs(and times)*/
        for(auto artist = artists.begin();artist != artists.end();artist++) { 
			printf("%s: %d, %s\n", artist->second.name.c_str(), artist->second.nsongs,convertTime(artist->second.time).c_str());            
            for(auto album = artist->second.albums.begin();album !=artist->second.albums.end();album++){
				printf("        %s: %d, %s\n", album->second.name.c_str(), album->second.nsongs, convertTime(album->second.time).c_str());
                for(auto song = album->second.songs.begin();song != album->second.songs.end();song++){
					printf("                %d. %s: %s\n", song->first, song->second.title.c_str(), convertTime(song->second.time).c_str());
				}
            }
        }
		
	infile.close();	
    return 0;
}
