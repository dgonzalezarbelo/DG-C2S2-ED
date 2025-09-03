#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class iPud {
private:
	using Song = string;
	using Artist = string;
public:

	iPud() : playList() {}

	void addSong(Song s, Artist a, int d) {
		if (songs.count(s))
			throw domain_error("ERROR");
		songs[s] = { false, d };
		songs[s].playListIt = playList.songsQueue.end();
	}

	void addToPlayList(Song s) {
		if (!songs.count(s))
			throw domain_error("ERROR");
		if (songs[s].playListIt == playList.songsQueue.end()) {
			playList.songsQueue.push_back(s);
			songs[s].playListIt = --playList.songsQueue.end();
			playList.duration += songs[s].duration;
		}
	}

	Song current() {
		if (playList.songsQueue.empty())
			throw domain_error("ERROR");
		return playList.songsQueue.front();
	}

	Song play() {
		if (!playList.songsQueue.empty()) {
			Song current = playList.songsQueue.front();
			playList.songsQueue.pop_front();
			playList.duration -= songs[current].duration;
			songs[current].playListIt = playList.songsQueue.end();
			if (songs[current].reproduced) {
				recentSongs.erase(songs[current].recentSongsIt);
			}
			songs[current].reproduced = true;
			recentSongs.push_front(current);
			songs[current].recentSongsIt = recentSongs.begin();
			cout << "Sonando " << current << '\n';
			return current;
		}
		cout << "No hay canciones en la lista\n";
		return "";
	}

	int totalTime() {
		return playList.duration;
	}

	list<Song> recent(int n) {
		int i = 0;
		list<Song> ret;
		auto it = recentSongs.begin();
		while (it != recentSongs.end() && i < n) {
			ret.push_back(*it);
			it++;
			i++;
		}
		return ret;
	}

	void deleteSong(Song s) {
		if (songs.count(s)) {
			if (songs[s].playListIt != playList.songsQueue.end()) {
				playList.duration -= songs[s].duration;
				playList.songsQueue.erase(songs[s].playListIt);
			}
			if (songs[s].reproduced) {
				recentSongs.erase(songs[s].recentSongsIt);
			}
			songs.erase(s);
		}
	}

private:
	struct PlayList {
		PlayList() : duration(0) {}
		list<Song> songsQueue;
		int duration;
	};
	struct SongInfo {
		SongInfo() : reproduced(false) {};
		SongInfo(bool reproduced, int duration) : reproduced(reproduced), duration(duration) {};
		bool reproduced;
		int duration;
		list<Song>::iterator recentSongsIt;
		list<Song>::iterator playListIt;
	}; 
	unordered_map<Song, SongInfo> songs;	//Cancion -> {Reproducida, Duracion}
	PlayList playList;
	list<Song> recentSongs; //Ordenada de mas reciente a mas antigua
};

bool resuelveCaso() {
	string operacion;
	cin >> operacion;
	if (!cin) return false;
	iPud ipud;
	while (operacion != "FIN") {
		try {
			if (operacion == "play") {
				string current = ipud.play();
			}
			else if (operacion == "totalTime") {
				int time = ipud.totalTime();
				cout << "Tiempo total " << time << '\n';
			}
			else if (operacion == "recent") {
				int n;
				cin >> n;
				list<string> songs = ipud.recent(n);
				if (songs.empty()) {
					cout << "No hay canciones recientes\n";
				}
				else {
					cout << "Las " << songs.size() << " mas recientes\n";
					auto it = songs.begin();
					while (it != songs.end()) {
						cout << "    " << *it << '\n';
						it++;
					}
				}
				
			}
			else if (operacion == "addSong") {
				string song, artist;
				int duration;
				cin >> song >> artist >> duration;
				ipud.addSong(song, artist, duration);
			}
			else if (operacion == "addToPlaylist") {
				string song;
				cin >> song;
				ipud.addToPlayList(song);
			}
			else if (operacion == "deleteSong") {
				string song;
				cin >> song;
				ipud.deleteSong(song);
			}
			else if (operacion == "current") {
				ipud.current();
			}
			else throw domain_error("ERROR");
		}
		catch (domain_error e) {
			cout << e.what() << ' ' << operacion << '\n';
		}
		cin >> operacion;
	}
	cout << "---\n";
	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}